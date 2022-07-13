# cmiFoam with Marangoni convection

`Solver for N compressible, non-isothermal immiscible fluids using a VOF phase-fraction based interface capturing approach. Allows either phase to have any EOS, with variable or constant material properties. The momentum and other fluid properties are of the "mixture" and a single momentum equation and energy equation is solved. Turbulence modelling is generic. Allows contact angle (dynamic, static, and hysteresis).`

 Major changes from compressibleMultiphaseInterFoam from openFoam2106 are the addition of Marangoni convection in the surface tension force terms. This is done by including the tangential force components of surface tension and allow the surface tension coefficient (normal direction) to vary with temperature.
 
