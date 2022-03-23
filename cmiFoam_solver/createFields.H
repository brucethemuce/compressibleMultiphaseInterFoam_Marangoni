Info<< "Reading field p_rgh\n" << endl;
volScalarField p_rgh
(
    IOobject
    (
        "p_rgh",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

#include "createPhi.H"

Info<< "Constructing multiphaseMixtureThermo\n" << endl;
multiphaseMixtureThermo mixture(U, phi);

volScalarField rho
(
    IOobject
    (
        "rho",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mixture.rho()
);

dimensionedScalar pMin("pMin", dimPressure, mixture);

mesh.setFluxRequired(p_rgh.name());


#include "readGravitationalAcceleration.H"
#include "readhRef.H"
#include "gh.H"


// Construct compressible turbulence model
autoPtr<compressible::turbulenceModel> turbulence
(
    compressible::turbulenceModel::New
    (
        rho,
        U,
        mixture.rhoPhi(),
        mixture
    )
);

// volScalarField sigmaT //N/m
// (
//     IOobject
//     (
//         "sigmaT",
//         runTime.timeName(),
//         mesh,
//         IOobject::NO_READ,
//         IOobject::AUTO_WRITE
//     ),
//     mesh,dimensionedScalar("sigmaT", dimensionSet(1,0,-2,0,0,0,0),0.0 )
// );

#include "createK.H"
#include "createFvOptions.H"
