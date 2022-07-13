    fvVectorMatrix UEqn
    (
        fvm::ddt(rho, U)
      + fvm::div(mixture.rhoPhi(), U)
      + turbulence->divDevRhoReff(U)
           ==
        fvOptions(rho, U)
    );

    UEqn.relax();
    // fvOptions.constrain(UEqn);

    if (pimple.momentumPredictor())
    {
        solve
        (
            UEqn
         ==
            fvc::reconstruct //change to cell "volume", (cell centers?)
            (
                ( //these are "surface" fields (cell faces?)
                      mixture.surfaceTensionForce()
                ) * mesh.magSf() //cell face Area
            )
            +
            fvc::reconstruct //change to volume?
            (
                ( //these are "surface" fields
                - ghf*fvc::snGrad(rho) //gravity term
                - fvc::snGrad(p_rgh) //pressure grad
                ) * mesh.magSf() //cell face Area
            )
        );

        // fvOptions.correct(U);

        K = 0.5*magSqr(U);
    }
