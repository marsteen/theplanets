#include <cstdio>
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
            NULL,
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
            NULL,
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
            "planeten/erde.jpg",
            NULL,
            "Erde",
            "Earth",
            1.0, 1.0, 1.0, 1.0, 1.0
        },
        {
            "planeten/monde/mond.jpg",
            NULL,
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
            NULL,
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
            NULL,
            "Jupiter",
            "Jupiter",
            0.0, 0.0,
            1.0, 1.0, 1.0
        },
        {
            // IO
            "planeten/monde/io.jpg",
            NULL,
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
            NULL,
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
            NULL,
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
            NULL,
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
            "planeten/monde_gross/moonmap4k.jpg",
             nullptr,
//            "planeten/monde_gross/moon_dem.png",
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
            NULL,
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
            NULL,
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
            NULL,
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
            NULL,
            "Ganymed",
            "Ganymede",
            0.0, 0.0, 1.0, 1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    // MOND Europa (Jupiter)
    //
    //---------------------------------------------------------------------------

#define SIZE_EUROPA    6794.0
    SPlanetDesc EuropaDesc[] =
    {
        {
            "planeten/monde_gross/europa.jpg",
            NULL,
            "Europa",
            "Europa",
            0.0, 0.0, 1.0, 1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	MOND Kallisto (Jupiter)
    //
    //---------------------------------------------------------------------------

#define SIZE_KALLISTO    6794.0
    SPlanetDesc KallistoDesc[] =
    {
        {
            "planeten/monde_gross/kallisto.jpg",
            NULL,
            "Europa",
            "Europa",
            0.0, 0.0, 1.0, 1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };


    //---------------------------------------------------------------------------
    //
    // MOND Io (Jupiter)
    //
    //---------------------------------------------------------------------------

#define SIZE_IO    6794.0
    SPlanetDesc IoDesc[] =
    {
        {
            "planeten/monde_gross/io.jpg",
            NULL,
            "Europa",
            "Europa",
            0.0, 0.0, 1.0, 1.0, 1.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	PLANET Saturn
    //
    //---------------------------------------------------------------------------

#define SIZE_SATURN    120536.0
    SPlanetDesc SaturnDesc[] =
    {
        {
            "planeten/4k/saturn.jpg",
            NULL,
            "Saturn",
            "Saturn",
            1.0, 1.0, 1.0, 1.0, 1.0
        },
        {
            "planeten/monde/titan.jpg",
            NULL,
            "Titan",
            "Titan",
            (1221830.0 / SIZE_SATURN) * 20,
            (1221830.0 / SIZE_SATURN) * 20,
            5150.0 / SIZE_SATURN,
            0.2, 1.0 / 60
        },
        {
            "planeten/monde/rhea.jpg",
            NULL,
            "Rhea",
            "Rhea",
            (527040.0 / SIZE_SATURN) * 20,
            (527040.0 / SIZE_SATURN) * 20,
            1528.0 / SIZE_SATURN,
            0.2, 1.0 / 60
        },
        {
            "planeten/monde/dione.jpg",
            NULL,
            "Dione",
            "Dione",
            (377420.0 / SIZE_SATURN) * 20,
            (377420.0 / SIZE_SATURN) * 20,
            1118.0 / SIZE_SATURN,
            0.2, 1.0 / 60
        },
        {
            "planeten/monde/tethys.jpg",
            NULL,
            "Tethys",
            "Tethys",
            (294670.0 / SIZE_SATURN) * 20,
            (294670.0 / SIZE_SATURN) * 20,
            1060.0 / SIZE_SATURN,
            0.2, 1.0 / 60
        },
        {
            "planeten/monde/iapetus.jpg",
            NULL,
            "Iapetus",
            "Iapetus",
            (3561300.0 / SIZE_SATURN) * 20,
            (3561300.0 / SIZE_SATURN) * 20,
            1436.0 / SIZE_SATURN,
            0.2, 1.0 / 60
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };

    //---------------------------------------------------------------------------
    //
    //	Planet Uranus
    //
    //---------------------------------------------------------------------------

#define USE_MOONS
#define SIZE_URANUS    51118.0
    SPlanetDesc UranusDesc[] =
    {
        {
            "planeten/uranus.jpg",
            NULL,
            "Uranus",
            "Uranus",
            0.0, 0.0, 1.0, 1.0, 1.0
        },
#ifdef USE_MOONS
        {
            "planeten/monde/titan.jpg",
            NULL,
            "Oberon",
            "Oberon",
            (583519.0 / SIZE_URANUS) * 20,
            (583519.0 / SIZE_URANUS) * 20,
            1523.0 / SIZE_URANUS,
            0.2, 1.0 / 60
        },
        {
            "planeten/monde/dummy.jpg",
            NULL,
            "Titania",
            "Titania",
            (463300.0 / SIZE_URANUS) * 20,
            (463300.0 / SIZE_URANUS) * 20,
            1578.0 / SIZE_URANUS,
            0.2, 1.0 / 60
        },
        {
            "planeten/monde/dummy.jpg",
            NULL,
            "Umbriel",
            "Umbriel",
            (266300.0 / SIZE_URANUS) * 20,
            (266300.0 / SIZE_URANUS) * 20,
            1169.0 / SIZE_URANUS,
            0.2, 1.0 / 60
        },
        {
            "planeten/monde/dummy.jpg",
            NULL,
            "Ariel",
            "Ariel",
            (191020.0 / SIZE_URANUS) * 20,
            (191020.0 / SIZE_URANUS) * 20,
            1158.0 / SIZE_URANUS,
            0.2, 1.0 / 60
        },
        {
            "planeten/monde/dummy.jpg",
            NULL,
            "Miranda",
            "Miranda",
            (129872.0 / SIZE_URANUS) * 20,
            (129872.0 / SIZE_URANUS) * 20,
            472.0 / SIZE_URANUS,
            0.2, 1.0 / 60
        },
#endif
        {
            NULL, NULL, NULL, 0, 0, 0, 0, 0
        }
    };

    //---------------------------------------------------------------------------
    //
    //	Planet Neptun
    //
    //---------------------------------------------------------------------------

#define SIZE_NEPTUN    49528.0
    SPlanetDesc NeptunDesc[] =
    {
        {
            "planeten/neptun.jpg",
            NULL,
            "Neptun",
            "Neptune",
            0.0, 1.0, 1.0, 1.0
        },
#ifdef USE_MOONS
        {
            "planeten/monde/dummy.jpg",
            NULL,
            "Triton",
            "Triton",
            (354800.0 / SIZE_NEPTUN) * 20,
            2707.0 / SIZE_NEPTUN,
            0.2, 1.0 / 60
        },
        {
            "planeten/monde/dummy.jpg",
            NULL,
            "Nereid",
            "Nereid",
            (5513400.0 / SIZE_NEPTUN) * 20,
            340.0 / SIZE_NEPTUN,
            0.2, 1.0 / 60
        },
#endif
        {
            NULL, NULL, NULL, 0, 0, 0, 0, 0
        }
    };

    //---------------------------------------------------------------------------
    //
    // SONNE Sol
    //
    //---------------------------------------------------------------------------

#define SUN_SCALE		20
#define SIZE_SONNE		1391400.0
    SPlanetDesc SonneDesc[] =
    {
        {
            "planeten/sonnensystem/sonne1.jpg",
            NULL,
            "Sonne",
            "Sun",
            1.0, 1.0, 1.0, 1.0, 1.0
        },
        {
            "planeten/sonnensystem/merkurk.jpg",
            NULL,
            "Merkur",
            "Mercury",
            (57909175.0 / SIZE_SONNE) * 20.0 / SUN_SCALE,   // Abstand zu Sonne  * 20
            (57909175.0 / SIZE_SONNE) * 20.0 / SUN_SCALE,   // Abstand zu Sonne  * 20
            SIZE_MERKUR / SIZE_SONNE,                       // Groesse im Verhaeltnis zu Sonne
            0,
            1.0 / 30.0
        },
        {
            "planeten/sonnensystem/venusk.jpg",
            NULL,
            "Venus",
            "Venus",
            (108208930.0 / SIZE_SONNE) * 20.0 / SUN_SCALE,  // Abstand zu Sonne  * 20
            (108208930.0 / SIZE_SONNE) * 20.0 / SUN_SCALE,  // Abstand zu Sonne  * 20
            SIZE_VENUS / SIZE_SONNE,                        // Groesse im Verhaeltnis zu Sonne
            3.0,
            1.0 / 30.0
        },
        {
            "planeten/sonnensystem/erdek.jpg",
            NULL,
            "Erde",
            "Earth",
            (149597890.0 / SIZE_SONNE) * 20.0 / SUN_SCALE,  // Abstand zu Sonne  * 20
            (149597890.0 / SIZE_SONNE) * 20.0 / SUN_SCALE,  // Abstand zu Sonne  * 20
            SIZE_ERDE / SIZE_SONNE,                         // Groesse im Verhaeltnis zu Sonne
            3.0,
            1.0 / 120.0
        },
        {
            "planeten/sonnensystem/marsk.jpg",
            NULL,
            "Mars",
            "Mars",
            (227936640.0 / SIZE_SONNE) * 20.0 / SUN_SCALE,  // Abstand zu Sonne  * 20
            (227936640.0 / SIZE_SONNE) * 20.0 / SUN_SCALE,  // Abstand zu Sonne  * 20
            SIZE_MARS / SIZE_SONNE,                         // Groesse im Verhaeltnis zu Sonne
            3.0,
            1.0 / 240.0
        },
        {
            "planeten/sonnensystem/jupiterk.jpg",
            NULL,
            "Jupiter",
            "Jupiter",
            (778412020.0 / SIZE_SONNE) * 20.0 / SUN_SCALE,  // Abstand zu Sonne  * 20
            (778412020.0 / SIZE_SONNE) * 20.0 / SUN_SCALE,  // Abstand zu Sonne  * 20
            //28.0,
            SIZE_JUPITER / SIZE_SONNE,                      // Groesse im Verhaeltnis zu Sonne
            3.0,
            1.0 / 480.0
        },
        {
            "planeten/sonnensystem/saturnk.jpg",
            NULL,
            "Saturn",
            "Saturn",
            (1426725400.0 / SIZE_SONNE) * 20.0 / SUN_SCALE, // Abstand zu Sonne  * 20
            (1426725400.0 / SIZE_SONNE) * 20.0 / SUN_SCALE, // Abstand zu Sonne  * 20
            //33.0,
            SIZE_SATURN / SIZE_SONNE,                       // Groesse im Verhaeltnis zu Sonne
            3.0,
            1.0 / 960.0
        },
        {
            "planeten/sonnensystem/uranusk.jpg",
            NULL,
            "Uranus",
            "Uranus",
            (2870972200.0 / SIZE_SONNE) * 20.0 / SUN_SCALE, // Abstand zu Sonne  * 20
            (2870972200.0 / SIZE_SONNE) * 20.0 / SUN_SCALE, // Abstand zu Sonne  * 20
            //37.0,
            SIZE_URANUS / SIZE_SONNE,                       // Groesse im Verhaeltnis zu Sonne
            3.0,
            1.0 / 1920.0
        },
        {
            "planeten/sonnensystem/neptunk.jpg",
            NULL,
            "Neptun",
            "Neptune",
            //41.0,
            (4498252900.0 / SIZE_SONNE) * 20.0 / SUN_SCALE, // Abstand zu Sonne  * 20
            (4498252900.0 / SIZE_SONNE) * 20.0 / SUN_SCALE, // Abstand zu Sonne  * 20
            SIZE_NEPTUN / SIZE_SONNE,                       // Groesse im Verhaeltnis zu Sonne
            3.0,
            1.0 / 3840.0
        },
        { NULL, NULL, NULL, 0, 0, 0, 0, 0 }
    };
}
