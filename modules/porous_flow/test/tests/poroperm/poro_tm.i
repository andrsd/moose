# Test that porosity is correctly calculated.
# Porosity = 1 + (phi0 - 1) * exp(-vol_strain + thermal_exp_coeff * (temperature - ref_temperature))
# The parameters used are:
# phi0 = 0.5
# vol_strain = 0.5
# thermal_exp_coeff = 0.5
# temperature = 4
# ref_temperature = 3.5
# which yield porosity = 0.610599608464
[Mesh]
  type = GeneratedMesh
  dim = 3
[]

[GlobalParams]
  PorousFlowDictator = dictator
  displacements = 'disp_x disp_y disp_z'
[]

[Variables]
  [porepressure]
    initial_condition = 2
  []
  [temperature]
    initial_condition = 4
  []
  [disp_x]
  []
  [disp_y]
  []
  [disp_z]
  []
[]

[ICs]
  [disp_x]
    type = FunctionIC
    function = '0.5 * x'
    variable = disp_x
  []
[]

[Kernels]
  [dummy_p]
    type = TimeDerivative
    variable = porepressure
  []
  [dummy_t]
    type = TimeDerivative
    variable = temperature
  []
  [dummy_x]
    type = TimeDerivative
    variable = disp_x
  []
  [dummy_y]
    type = TimeDerivative
    variable = disp_y
  []
  [dummy_z]
    type = TimeDerivative
    variable = disp_z
  []
[]

[AuxVariables]
  [porosity]
    order = CONSTANT
    family = MONOMIAL
  []
[]

[AuxKernels]
  [porosity]
    type = PorousFlowPropertyAux
    property = porosity
    variable = porosity
  []
[]

[Postprocessors]
  [porosity]
    type = PointValue
    variable = porosity
    point = '0 0 0'
  []
[]

[UserObjects]
  [dictator]
    type = PorousFlowDictator
    porous_flow_vars = 'porepressure temperature'
    number_fluid_phases = 1
    number_fluid_components = 1
  []
  [pc]
    type = PorousFlowCapillaryPressureConst
  []
[]

[Modules]
  [FluidProperties]
    [simple_fluid]
      type = SimpleFluidProperties
    []
  []
[]

[Materials]
  [temperature]
    type = PorousFlowTemperature
    temperature = temperature
  []
  [eff_fluid_pressure]
    type = PorousFlowEffectiveFluidPressure
  []
  [vol_strain]
    type = PorousFlowVolumetricStrain
  []
  [ppss]
    type = PorousFlow1PhaseP
    porepressure = porepressure
    capillary_pressure = pc
  []
  [porosity]
    type = PorousFlowPorosity
    mechanical = true
    thermal = true
    ensure_positive = false
    porosity_zero = 0.5
    thermal_expansion_coeff = 0.5
    reference_temperature = 3.5
  []
[]

[Executioner]
  solve_type = Newton
  type = Transient
  num_steps = 1
[]

[Outputs]
  csv = true
[]
