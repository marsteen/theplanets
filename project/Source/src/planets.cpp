


namespace
{
    SPlanetDesc MerkurDesc[];
    
    
}

#include <SPlanetDesc.h>

namespace NPlanets
{
    // ---------------------------------------------------------------------------
    //
    //	PLANET Merkur
    //
    // ---------------------------------------------------------------------------

    #define SIZE_MERKUR    4809.0
    SPlanetDesc MerkurDesc[] =
    {
        {
            "planeten/4k/merkur.jpg",
            "Merkur",
            "Mercury",
            0.0, 0.0,         
            1.0, 1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	PLANET Venus
    //
    //---------------------------------------------------------------------------

    #define SIZE_VENUS    12103.0
    SPlanetDesc VenusDesc[] =
    {
        {
            "planeten/venus.jpg",
            "Venus",
            "Venus",
            0.0, 0.0,
            1.0, -1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	PLANET Erde
    //
    //---------------------------------------------------------------------------

    #define SIZE_ERDE    12756.0
    SPlanetDesc ErdeDesc[] =
    {
        {
            "planeten/4k/erde.jpg",
            "Erde",
            "Earth",
            1.0, 1.0, 1.0, 1.0, 1.0
        },
        {
            "planeten/monde/mond.jpg",
            "Mond",
            "Moon",
            (384400.0 / SIZE_ERDE) * 20,
            (363300.0 / SIZE_ERDE) * 20,
            3476.0 / SIZE_ERDE,
            0, 0.1 / 30.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	Planet Mars
    //
    //---------------------------------------------------------------------------

    #define SIZE_MARS    6794.0
    SPlanetDesc MarsDesc[] =
    {
        {
            "planeten/4k/mars.jpg",
            "Mars",
            "Mars",
            0.0, 0.0,
            1.0, 1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	Planet Jupiter
    //
    //---------------------------------------------------------------------------

    #define SIZE_JUPITER    142984.0
    SPlanetDesc JupiterDesc[] =
    {
        {
            "planeten/4k/jupiter.jpg",
            "Jupiter",
            "Jupiter",
            0.0, 0.0,
            1.0, 1.0, 1.0
        },
        {
            // IO
            "planeten/monde/io.jpg",
            "Io",
            "Io",
            (420100.0 / SIZE_JUPITER) * 20,
            (420100.0 / SIZE_JUPITER) * 20,
            3643.0 / SIZE_JUPITER,
            2.1,
            0.12
        },
        {
            // Europa
            "planeten/monde/europa.jpg",
            "Europa",
            "Europa",
            (664100.0 / SIZE_JUPITER) * 20,
            (664100.0 / SIZE_JUPITER) * 20,
            3121.0 / SIZE_JUPITER,
            1.2,
            0.06
        },
        {
            // Ganymed
            "planeten/monde/ganymed.jpg",
            "Ganymed",
            "Ganymede",
            (1069000.0 / SIZE_JUPITER) * 20,
            (1069000.0 / SIZE_JUPITER) * 20,
            5264.0 / SIZE_JUPITER,
            1.8,
            0.03
        },
        {
            // Kallisto
            "planeten/monde/kallisto.jpg",
            "Kallisto",
            "Callisto",
            (1869500.0 / SIZE_JUPITER) * 20,
            (1869500.0 / SIZE_JUPITER) * 20,
            4820.0 / SIZE_JUPITER,
            1.2,
            0.02
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	MOMD Mond (Erde)
    //
    //---------------------------------------------------------------------------

    SPlanetDesc MondDesc[] =
    {
        {
            "planeten/monde_gross/Moon5120x2560.jpg",
            "Mond",
            "Moon",
            0.0, 0.0,
            1.0, 1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	MOND Titan (Saturn)
    //
    //---------------------------------------------------------------------------

    SPlanetDesc TitanDesc[] =
    {
        {
            "planeten/monde_gross/titan.jpg",
            "Titan",
            "Titan",
            0.0, 0.0, 1.0, 1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	MOND Rhea (Saturn)
    //
    //---------------------------------------------------------------------------

    SPlanetDesc RheaDesc[] =
    {
        {
            "planeten/monde_gross/rhea.jpg",
            "Rhea",
            "Rhea",
            0.0, 0.0, 1.0, 1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	MOND Triton (Saturn)
    //
    //---------------------------------------------------------------------------

    SPlanetDesc TritonDesc[] =
    {
        {
            "planeten/monde_gross/triton.jpg",
            "Triton",
            "Triton",
            0.0, 0.0, 1.0, 1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	MOND Ganymed (Jupiter)
    //
    //---------------------------------------------------------------------------

    #define SIZE_GANYMED    6794.0
    SPlanetDesc GanymedDesc[] =
    {
        {
            "planeten/monde_gross/ganymed.jpg",
            "Ganymed",
            "Ganymede",
            0.0, 0.0, 1.0, 1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };
}
