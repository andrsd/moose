//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "IntegratedBC.h"

class SinglePhaseFluidProperties;
class PorousFlowDictator;
class Function;

/**
 * Applies a flux sink to a boundary with specified mass flux and inlet temperature.
 */
class PorousFlowSinkEnthalpy : public IntegratedBC
{
public:
  static InputParameters validParams();

  PorousFlowSinkEnthalpy(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  /// PorousFlowDictator UserObject
  const PorousFlowDictator & _dictator;

  /// The flux
  const Function & _m_func;

  /// Pressure
  const VariableValue & _pressure;

  /// Pressure variable number
  unsigned int _pressure_var_num;

  /// Specified inlet temperature
  const Real & _T_in;

  /// Fluid properties UserObject
  const SinglePhaseFluidProperties & _fp;

  /// Derivative of residual with respect to the jvar variable
  Real jac(unsigned int jvar) const;
};
