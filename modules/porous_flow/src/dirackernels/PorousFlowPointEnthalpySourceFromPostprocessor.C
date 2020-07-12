//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PorousFlowPointEnthalpySourceFromPostprocessor.h"
#include "SinglePhaseFluidProperties.h"

registerMooseObject("PorousFlowApp", PorousFlowPointEnthalpySourceFromPostprocessor);

InputParameters
PorousFlowPointEnthalpySourceFromPostprocessor::validParams()
{
  InputParameters params = DiracKernel::validParams();
  params.addRequiredParam<PostprocessorName>(
      "mass_flux",
      "The postprocessor name holding the mass flux at this point in kg/s (positive is flux in, "
      "negative is flux out)");
  params.addRequiredParam<UserObjectName>("fp", "The name of the user object for fluid properties");
  params.addRequiredCoupledVar("pressure", "Pressure");
  params.addRequiredParam<PostprocessorName>("T_in", "The postprocessor name holding the specified inlet temperature");
  params.addRequiredParam<Point>("point", "The x,y,z coordinates of the point source (or sink)");
  params.addClassDescription(
      "Point source (or sink) that adds (or removes) fluid at a mass flux rate "
      "specified by a postprocessor.");
  return params;
}

PorousFlowPointEnthalpySourceFromPostprocessor::PorousFlowPointEnthalpySourceFromPostprocessor(
    const InputParameters & parameters)
  : DiracKernel(parameters),
    _mass_flux(getPostprocessorValue("mass_flux")),
    _pressure(coupledValue("pressure")),
    _T_in(getPostprocessorValue("T_in")),
    _fp(getUserObject<SinglePhaseFluidProperties>("fp")),
    _p(getParam<Point>("point"))
{
}

void
PorousFlowPointEnthalpySourceFromPostprocessor::addPoints()
{
  addPoint(_p, 0);
}

Real
PorousFlowPointEnthalpySourceFromPostprocessor::computeQpResidual()
{
  // Negative sign to make a positive mass_flux in the input file a source
  if (_mass_flux > 0)
  {
    Real h = _fp.h_from_p_T(_pressure[_qp], _T_in);
    return -_test[_i][_qp] * _mass_flux * h;
  }
  else
    return 0.;
}
