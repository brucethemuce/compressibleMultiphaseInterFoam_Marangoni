{
    fvScalarMatrix TEqn
    (
        fvm::ddt(rho, T) //ddt of (rho*T)
      + fvm::div(mixture.rhoPhi(), T)//convection term
      - fvm::laplacian(mixture.alphaEff(turbulence->mut()), T) //conduction
      + (   fvc::div(fvc::absolute(phi, U), p) //compressibility
          + fvc::ddt(rho, K)
          + fvc::div(mixture.rhoPhi(), K)
        )*mixture.rCv()
    );

    TEqn.relax();
    // fvOptions.constrain(TEqn);

    TEqn.solve();
    // fvOptions.correct(T);

    mixture.correct();
}
