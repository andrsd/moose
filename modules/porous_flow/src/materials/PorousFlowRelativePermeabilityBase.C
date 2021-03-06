/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "PorousFlowRelativePermeabilityBase.h"

template<>
InputParameters validParams<PorousFlowRelativePermeabilityBase>()
{
  InputParameters params = validParams<PorousFlowMaterialBase>();
  params.addRangeCheckedParam<Real>("s_jr", 0, "s_jr >= 0 & s_jr < 1", "The residual saturation of phase j. Must be between 0 and 1");
  params.addRangeCheckedParam<Real>("sum_s_r", 0, "sum_s_r >= 0 & sum_s_r < 1", "Sum of residual saturations over all phases. Must be between 0 and 1");
  params.addClassDescription("Base class for PorousFlow relative permeability materials");
  return params;
}

PorousFlowRelativePermeabilityBase::PorousFlowRelativePermeabilityBase(const InputParameters & parameters) :
    PorousFlowMaterialBase(parameters),
    _saturation_variable_name(_dictator.saturationVariableNameDummy()),
    _saturation_nodal(getMaterialProperty<std::vector<Real> >("PorousFlow_saturation_nodal")),
    _relative_permeability(declareProperty<Real>("PorousFlow_relative_permeability" + _phase)),
    _drelative_permeability_ds(declarePropertyDerivative<Real>("PorousFlow_relative_permeability" + _phase, _saturation_variable_name)),
    _s_res(getParam<Real>("s_jr")),
    _sum_s_res(getParam<Real>("sum_s_r"))
{
  // Sanity check on residual saturations when set by user
  if (parameters.isParamSetByUser("sum_s_r"))
    if (_sum_s_res < _s_res)
      mooseError("Sum of residual saturations sum_s_r cannot be smaller than s_jr in " << name());
}

void
PorousFlowRelativePermeabilityBase::computeQpProperties()
{
  // Effective saturation
  Real seff = effectiveSaturation(_saturation_nodal[_qp][_phase_num]);
  Real relperm, drelperm;

  if (seff < 0.0)
  {
    // Relative permeability is 0 for saturation less than residual
    relperm = 0.0;
    drelperm = 0.0;
  }
  else if (seff >= 0.0 && seff <= 1)
  {
    relperm = relativePermeability(seff);
    drelperm = dRelativePermeability_dS(seff);
  }
  else // seff > 1
  {
    // Relative permeability is 1 when fully saturated
    relperm = 1.0;
    drelperm = 0.0;
  }

  _relative_permeability[_qp] = relperm;
  _drelative_permeability_ds[_qp] = drelperm;
}

Real
PorousFlowRelativePermeabilityBase::effectiveSaturation(Real saturation) const
{
  return (saturation - _s_res) / (1.0 - _sum_s_res);
}
