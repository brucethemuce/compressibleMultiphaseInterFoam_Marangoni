/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
Application
    cmiFoam_test

Description
    Solver for N compressible, non-isothermal immiscible fluids using a VOF
    (volume of fluid) phase-fraction based interface capturing approach.
    The momentum and other fluid properties are of the "mixture" and a single
    momentum equation is solved. Turbulence modelling is generic.
    Allows contact angle and surface tension effects. Allow constant or coded
    source terms in momentum or temperature equations via fvOptions.
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "multiphaseMixtureThermo.H"
#include "turbulentFluidThermoModel.H"
#include "pimpleControl.H"
#include "fvOptions.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Solver for N compressible, non-isothermal immiscible fluids"
        " using VOF phase-fraction based interface capturing and "
        " includes surface-tension and contact-angle effects for each phase."
    );

    #include "postProcess.H"

    #include "addCheckCaseOptions.H"
    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createControl.H"
    #include "createTimeControls.H"
    #include "createFields.H"
    #include "CourantNo.H"
    #include "setInitialDeltaT.H"

    volScalarField& p = mixture.p();
    volScalarField& T = mixture.T();

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
        #include "readTimeControls.H"
        #include "CourantNo.H"
        #include "alphaCourantNo.H"
        #include "setDeltaT.H"

        ++runTime;

        Info<< "Time = " << runTime.timeName() << nl << endl;
        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            mixture.solve();

            solve(fvm::ddt(rho) + fvc::div(mixture.rhoPhi()));

            #include "UEqn.H" 
            #include "TEqn.H" 

            // --- Pressure corrector loop
            while (pimple.correct())
            {
                #include "pEqn.H"
            }

            if (pimple.turbCorr())
            {
                turbulence->correct();
            }
        }
        
        runTime.write();

        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
