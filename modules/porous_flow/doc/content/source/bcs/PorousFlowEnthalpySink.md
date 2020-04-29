# PorousFlowEnthalpySink

`PorousFlowEnthalpySink` implements a sink that adds heat energy corresponding to
adding fluid at a mass flux rate (computed by a function) at a specified temperature.

This object should be used in conjunction with (PorousFlowSink)[PorousFlowSink.md]
that uses the same `flux_function`, so that the correct amount of fluid is injected into the system.

Note that the fluid property object used by this boundary condition should be the same one that is
used in the computational domain where this object is located.

Parameter [!param](/BCs/PorousFlowEnthalpySink/pressure)
(along with [!param](/BCs/PorousFlowEnthalpySink/T_in)) is used to calculate
the injected fluid enthalpy. Most frequently, it is the PorousFlow pressure variable (the porepressure
in the porous medium). This models the situation where fluid is injected at a specified rate and
temperature (using this BCs and a PorousFlowSink) which potentially
leads to changes in the porepressure. Alternately, it may be the pressure of the injected fluid, as
fixed by an external agent (such as a pump) which is stored in an AuxVariable.

For instance:

!listing modules/porous_flow/test/tests/sinks/s11.i block=BCs

!syntax parameters /BCs/PorousFlowEnthalpySink

!syntax inputs /BCs/PorousFlowEnthalpySink

!syntax children /BCs/PorousFlowEnthalpySink
