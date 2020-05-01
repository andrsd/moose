//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "DiracKernel.h"

class SinglePhaseFluidProperties;

/**
 * Point source (or sink) that adds (removes) fluid at a mass flux rate specified by a postprocessor
 */
class PorousFlowPointEnthalpySourceFromPostprocessor : public DiracKernel
{
public:
  static InputParameters validParams();

  PorousFlowPointEnthalpySourceFromPostprocessor(const InputParameters & parameters);

  virtual void addPoints() override;
  virtual Real computeQpResidual() override;

protected:
  /// The constant mass flux (kg/s)
  const PostprocessorValue & _mass_flux;
  /// Pressure
  const VariableValue & _pressure;
  /// Specified inlet temperature
  const Real & _T_in;
  /// Fluid properties UserObject
  const SinglePhaseFluidProperties & _fp;
  /// The location of the point source (sink)
  const Point _p;
};
