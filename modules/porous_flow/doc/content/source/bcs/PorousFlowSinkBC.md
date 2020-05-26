# PorousFlowSinkBC

Proxy class that allows users to use the BC syntax for specifying enthalphy sink.

Users are required to specify:

- `boundary` - The list of boundary IDs from the mesh where this boundary condition applies
- `pressure` - Pressure
- `T_in` - Inlet temperature
- `fp` - The name of the user object for fluid properties
- `flux_function` - The flux out of the medium

!listing modules/porous_flow/test/tests/sinks/s11_act.i block=/Modules/PorousFlow/BCs/left
