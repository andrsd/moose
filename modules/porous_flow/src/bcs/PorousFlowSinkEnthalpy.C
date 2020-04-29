//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PorousFlowSinkEnthalpy.h"
#include "Function.h"
#include "PorousFlowDictator.h"
#include "SinglePhaseFluidProperties.h"
#include "MooseVariable.h"

#include "libmesh/quadrature.h"

#include <iostream>

registerMooseObject("PorousFlowApp", PorousFlowSinkEnthalpy);

InputParameters
PorousFlowSinkEnthalpy::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addRequiredParam<UserObjectName>(
      "PorousFlowDictator", "The UserObject that holds the list of PorousFlow variable names");
  params.addRequiredParam<FunctionName>(
      "flux_function",
      "The mass flux.  The flux is OUT of the medium: hence positive values of "
      "this function means this BC will act as a SINK, while negative values "
      "indicate this flux will be a SOURCE.  The functional form is useful "
      "for spatially or temporally varying sinks.");
  params.addRequiredParam<UserObjectName>("fp", "The name of the user object for fluid properties");
  params.addRequiredCoupledVar("pressure", "Pressure");
  params.addRequiredParam<Real>("T_in", "Specifiec inlet temperature");
  params.addClassDescription("Applies a flux sink to a boundary.");

  return params;
}

PorousFlowSinkEnthalpy::PorousFlowSinkEnthalpy(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _dictator(getUserObject<PorousFlowDictator>("PorousFlowDictator")),
    _m_func(getFunction("flux_function")),
    _pressure(coupledValue("pressure")),
    _pressure_var_num(coupled("pressure")),
    _T_in(getParam<Real>("T_in")),
    _fp(getUserObject<SinglePhaseFluidProperties>("fp"))
{
}

Real
PorousFlowSinkEnthalpy::computeQpResidual()
{
  Real h = _fp.h_from_p_T(_pressure[_qp], _T_in);
  return _test[_i][_qp] * _m_func.value(_t, _q_point[_qp]) * h;
}

Real
PorousFlowSinkEnthalpy::computeQpJacobian()
{
  return jac(_var.number());
}

Real
PorousFlowSinkEnthalpy::computeQpOffDiagJacobian(unsigned int jvar)
{
  return jac(jvar);
}

Real
PorousFlowSinkEnthalpy::jac(unsigned int jvar) const
{
  if (jvar == _pressure_var_num)
  {
    Real h, dh_dp, dh_dT;
    _fp.h_from_p_T(_pressure[_qp], _T_in, h, dh_dp, dh_dT);
    return _test[_i][_qp] * _phi[_j][_qp] * dh_dp;
  }
  else
    return 0;
}
