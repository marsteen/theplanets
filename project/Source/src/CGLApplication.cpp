//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGLApplication.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#define APP_NAME    "Die Planeten"

#ifdef _WIN32
#include <windows.h>
#endif

#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>


#include <GLinclude.h>
#include <Math/CVector3T.h>
#include <CGL_GLU_Sphere.h>
#include <CGL_Object.h>
#include <CGL_Disk.h>
#include <CFileIO.h>
#include <CDatabase3.h>
#include <CStringTool.h>
#include <CGraflibJpeg.h>
#include <NPlanets.h>
#include "CGL_Ellipsoid.h"
#include "CG3DGlobals.h"
#include "CG3DReslistInterface.h"
#include "CGLApplication.h"

using namespace std;

static float sYrot;
static float sZrot;
static float sXrot;
static float sYrotAuto;

#define NUMBER_OF_STARS    10000

struct SMoonColor
{
    const float mColor[3];
};

static const SMoonColor sMoonColorTable[] =
{
    { 0.6, 0.6, 0.6 },  // Merkur / 1. Mond
    { 1.0, 0.0, 0.5 },  // Venus /  2. Mond
    { 0.2, 0.4, 0.8 },  // Erde  / 3. Mond
    { 0.9, 0.3, 0.3 },  // Mars / 4. Mond
    { 0.7, 0.7, 0.2 },  // Jupiter / 5. Mond

    { 0.3, 0.8, 0.4 },  // Saturn / 6. Mond
    { 0.9, 0.5, 0.6 },  // Uranus / 7. Mond
    { 0.2, 0.2, 0.8 },  // Neptun / 8, Mond
    { 0.5, 1.0, 0.5 },
    { 0.2, 0.5, 1.0 },
    { 0.5, 0.4, 1.0 },
};


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : CGLApplication
//
//
//
// ---------------------------------------------------------------------------

CGLApplication::CGLApplication()
{
    gErde = NULL;
    gSonne1 = NULL;
    mActInfobox = "";
    mInitFlag = false;
    mAutoScale = false;
    mAutoRotate = false;
    mFullscreen = false;
    mLame = false;
    mShowInterface = true;
    mShowOrbits = true;
    mScale = 1.0;
    mAnaglyph = false;

    gG3Dinterface = new CG3DReslistInterface;
    gResGlobals = new CG3DGlobals;
    mCamera.mStandort.z = -80.0;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : InitGame
//
//
//
// ---------------------------------------------------------------------------

const char* CGLApplication::AppName() const
{
    return "the planets";
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : InitGame
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::InitGame()
{
    cout << "CGLApplication::InitGame" << endl;
    SetResolution(mXres, mYres);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : CGLApplication
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::MouseMotion(int xabs, int yabs, int xrel, int yrel)
{
    //sOpenGL->mMouse.mButton = Button;
    //sOpenGL->mMouse.mState[Button] = State;
    mMouse.x = xabs;
    mMouse.y = yabs;

    if (mLeftMouseButton)
    {
        MouseMotionLeft(-xrel, -yrel);
    }
    if (mRightMouseButton)
    {
        MouseMotionRight(-xrel, -yrel);
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : GameLoop
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::GameLoop()
{
    GLfloat weiss[] = { 1.0, 1.0, 1.0, 1.0 };

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    StartModelView(0.1 / mScale, 30.0 / mScale);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, weiss);
    SetupLighting();


    if (mAnaglyph)
    {
#define S_XV	2
#define V_XV	0.3

        float StandOrtX = mCamera.mStandort.x;
        float VispointX = mCamera.mVispoint.x;

        mCamera.mStandort.x -= S_XV;
        mCamera.mVispoint.x -= V_XV;

        for (int v = 0; v < 2; v++)
        {
            glLoadIdentity();
            glClear(GL_DEPTH_BUFFER_BIT);

            mCamera.LookAt();
            mCamera.mStandort.x += S_XV*2;
            mCamera.mVispoint.x += V_XV*2;

            glDisable(GL_BLEND);

            if (v == 1)
            {
                float rot[] = { 1.0, 0.0, 0.0, 1.0 };

                glColor3f(1.0, 0.0, 0.0);
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rot);
                glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_FALSE);
            }
            else
            {
                float cyan[] = { 0.0, 1.0, 1.0, 1.0 };
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
                glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_FALSE);
            }
            Draw3DObjects();
        }
        mCamera.mStandort.x = StandOrtX;
        mCamera.mVispoint.x = VispointX;
    }
    else
    {
        glLoadIdentity();
        glClear(GL_DEPTH_BUFFER_BIT);
        mCamera.LookAt();
        glDisable(GL_BLEND);
        Draw3DObjects();
    }
    Animate();


    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    StartProjectionView();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, weiss);

    ManageInterface(&mMouse);

    SDL_GL_SwapWindow(mSdlWindow);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : MouseWheel
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::MouseWheel(bool up)
{
    if (up)
    {
        Zoom(0.03f);
    }
    else
    {
        Zoom(-0.03f);
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : ReadLabels
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::ReadLabels()
{
    CDatabase3 db3;
    list<CRecord> Records;

    string BasePath = "Resource/";
    string Filename = "Labels.txt";

    if (db3.Read(&Records, BasePath, Filename, '\t'))
    {
        for (list<CRecord>::iterator it = Records.begin();
            it != Records.end();
            ++it)
        {
            SLabel Label;
            CStringTool st;
            cout << "it->size()=" << it->size() << endl;

            if (it->size() == 4)
            {
                Label.mLabel = (*it)[0];
                Label.mTyp = ELABELTYPE_UNDEFINED;
                Label.mLong = st.StringTo<float>((*it)[2]);
                Label.mLati = st.StringTo<float>((*it)[3]);
                string LabelType = (*it)[1];

                if (LabelType == "ma")
                {
                    Label.mTyp = ELABELTYPE_MARE;
                }
                else
                if (LabelType == "la")
                {
                    Label.mTyp = ELABELTYPE_APOLLO;
                }
                else
                if (LabelType == "kr")
                {
                    Label.mTyp = ELABELTYPE_KRATER;
                }
                else
                if (LabelType == "bg")
                {
                    Label.mTyp = ELABELTYPE_BERG;
                }
                //Label.mLong -= 1.0 / 6.0;
                Label.mLong *= -DEG_TO_RAD(360.0);
                Label.mLati = -DEG_TO_RAD((Label.mLati - 0.5) * 180.0);
                mLabelList.push_back(Label);

                cout << "Label:" << Label.mLabel  << endl;
            }
        }
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : ReadLabels
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::ReadLabels(string Bodyname)
{
    CDatabase3 db3;
    list<CRecord> Records;

    CFileIO fio;
    string Filename = string("Resource/Label/") + Bodyname + "_krater.txt";
    string Basepath = "./";
    int Count = 0;

    mLabelList.clear();

    cout << "++++ READ LABELS:" << Filename << endl;

    if (db3.Read(&Records, Basepath, Filename, '\t'))
    {
        cout << "Records=" << Records.size() << endl;

        for (list<CRecord>::iterator it = Records.begin();
            it != Records.end();
            ++it)
        {
            SLabel Label;
            CStringTool st;
            cout << "it->size()=" << it->size() << endl;

            if (it->size() == 3)
            {
                Label.mLabel = (*it)[0];
                Label.mTyp = ELABELTYPE_KRATER;
                Label.mLong = -st.StringTo<float>((*it)[2]) + 180.0;
                Label.mLati = st.StringTo<float>((*it)[1]);
                string LabelType = (*it)[1];

                Label.mLong = DEG_TO_RAD(Label.mLong);
                Label.mLati = DEG_TO_RAD(Label.mLati);
                mLabelList.push_back(Label);

                cout << "Label:" << Label.mLabel  << endl;
            }
        }
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : InitLabels
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::InitLabels(float Radius, int sx)
{
    mAktLabelList.clear();

    for (list<SLabel>::iterator it = mLabelList.begin();
        it != mLabelList.end();
        ++it)
    {
        it->LongLatiToSphere(Radius, sx);
        //LongLatiToSphere(it->mVec3D, it->mLong, it->mLati, Radius);
        mAktLabelList.push_back(*it);
        cout << "Label found:" << it->mLabel << endl;
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : InitLabels
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::InitLabels(string BodyName, float Radius, int sx)
{
    mAktLabelList.clear();

    for (list<SLabel>::iterator it = mLabelList.begin();
        it != mLabelList.end();
        ++it)
    {
        if (it->mBody == BodyName)
        {
            it->LongLatiToSphere(Radius, sx);
            //LongLatiToSphere(it->mVec3D, it->mLong, it->mLati, Radius);
            mAktLabelList.push_back(*it);

            cout << "Label found:" << it->mLabel << endl;
        }
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : LongLatiToSphere
//
//
//
// ---------------------------------------------------------------------------

void SLabel::LongLatiToSphere(float Radius, int sx)
{
    //cout << "Long=" << RAD_TO_DEG(mLong) << " Lati=" << RAD_TO_DEG(mLati) << endl;

    float LongOff = mLong + DEG_TO_RAD(360.0 / sx);

    CVector3<float> Origin;

    mVec3D.x = cos(mLati) * Radius;
    mVec3D.y = sin(mLati) * Radius;
    mVec3D.z = 0;

    Origin.Set(0, 0, 0);

    mVec3D.RotationXZ(&Origin, sin(LongOff), cos(LongOff));
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : ReadSettings
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::ReadSettings()
{
    CDatabase3 db3;
    list<CRecord> Records;

    string Basepath = "./";
    string Filename = "settings.txt";

    gResGlobals->mLanguage = ELANG_GERMAN;
    mPlanet = EPLANET_ERDE;


    if (db3.Read(&Records, Basepath, Filename, '\t') > 0)
    {
        for (list<CRecord>::iterator li = Records.begin();
            li != Records.end();
            li++)
        {
            if (li->size() == 2)
            {
                if ((*li)[0] == "LANG")
                {
                    if ((*li)[1] == "DE")
                    {
                        gResGlobals->mLanguage = ELANG_GERMAN;
                    }
                    else
                    if ((*li)[1] == "EN")
                    {
                        gResGlobals->mLanguage = ELANG_ENGLISH;
                    }
                }
                else
                if ((*li)[0] == "PLNT")
                {
                    CStringTool st;
                    mPlanet = (EPlanet)st.StringTo<int>((*li)[1]);
                }
            }
        }
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : WriteSettings
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::WriteSettings()
{
    ofstream of("./settings.txt");

    if (of.good())
    {
        of << "LANG\t";

        switch (gResGlobals->mLanguage)
        {
            case ELANG_GERMAN:

                of << "DE\n";
                break;

            case ELANG_ENGLISH:

                of << "EN\n";
                break;
        }

        of << "PLNT\t" << mPlanet << endl;
        of.close();
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CPlanet
// METHODE       : Delete
//
//
//
// ---------------------------------------------------------------------------

void CPlanet::Delete()
{
    for (vector<CMond>::iterator im = mMonde.begin();
        im != mMonde.end();
        ++im)
    {
        im->Delete();
    }
    CGL_EllipsoidPatched::Delete();
    DeleteDisplayList();
    mMonde.clear();
}


#if 0
// ---------------------------------------------------------------------------
//
//	PLANET Merkur
//
// ---------------------------------------------------------------------------

#define SIZE_MERKUR    4809.0
static SPlanetDesc sMerkurDesc[] =
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
static SPlanetDesc sVenusDesc[] =
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
static SPlanetDesc sErdeDesc[] =
{
    {
        "planeten/erde.jpg",
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
static SPlanetDesc sMarsDesc[] =
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
static SPlanetDesc sJupiterDesc[] =
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

static SPlanetDesc sMondDesc[] =
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

static SPlanetDesc sTitanDesc[] =
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

static SPlanetDesc sRheaDesc[] =
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

static SPlanetDesc sTritonDesc[] =
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
static SPlanetDesc sGanymedDesc[] =
{
    {
        "planeten/monde_gross/ganymed.jpg",
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
static SPlanetDesc sEuropaDesc[] =
{
    {
        "planeten/monde_gross/europa.jpg",
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
static SPlanetDesc sKallistoDesc[] =
{
    {
        "planeten/monde_gross/kallisto.jpg",
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
static SPlanetDesc sIoDesc[] =
{
    {
        "planeten/monde_gross/io.jpg",
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
static SPlanetDesc sSaturnDesc[] =
{
    {
        "planeten/4k/saturn.jpg",
        "Saturn",
        "Saturn",
        1.0, 1.0, 1.0, 1.0, 1.0
    },
    {
        "planeten/monde/titan.jpg",
        "Titan",
        "Titan",
        (1221830.0 / SIZE_SATURN) * 20,
        (1221830.0 / SIZE_SATURN) * 20,
        5150.0 / SIZE_SATURN,
        0.2, 1.0 / 60
    },
    {
        "planeten/monde/rhea.jpg",
        "Rhea",
        "Rhea",
        (527040.0 / SIZE_SATURN) * 20,
        (527040.0 / SIZE_SATURN) * 20,
        1528.0 / SIZE_SATURN,
        0.2, 1.0 / 60
    },
    {
        "planeten/monde/dione.jpg",
        "Dione",
        "Dione",
        (377420.0 / SIZE_SATURN) * 20,
        (377420.0 / SIZE_SATURN) * 20,
        1118.0 / SIZE_SATURN,
        0.2, 1.0 / 60
    },
    {
        "planeten/monde/tethys.jpg",
        "Tethys",
        "Tethys",
        (294670.0 / SIZE_SATURN) * 20,
        (294670.0 / SIZE_SATURN) * 20,
        1060.0 / SIZE_SATURN,
        0.2, 1.0 / 60
    },
    {
        "planeten/monde/iapetus.jpg",
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
static SPlanetDesc sUranusDesc[] =
{
    {
        "planeten/uranus.jpg",
        "Uranus",
        "Uranus",
        0.0, 0.0, 1.0, 1.0, 1.0
    },
#ifdef USE_MOONS
    {
        "planeten/monde/titan.jpg",
        "Oberon",
        "Oberon",
        (583519.0 / SIZE_URANUS) * 20,
        (583519.0 / SIZE_URANUS) * 20,
        1523.0 / SIZE_URANUS,
        0.2, 1.0 / 60
    },
    {
        "planeten/monde/dummy.jpg",
        "Titania",
        "Titania",
        (463300.0 / SIZE_URANUS) * 20,
        (463300.0 / SIZE_URANUS) * 20,
        1578.0 / SIZE_URANUS,
        0.2, 1.0 / 60
    },
    {
        "planeten/monde/dummy.jpg",
        "Umbriel",
        "Umbriel",
        (266300.0 / SIZE_URANUS) * 20,
        (266300.0 / SIZE_URANUS) * 20,
        1169.0 / SIZE_URANUS,
        0.2, 1.0 / 60
    },
    {
        "planeten/monde/dummy.jpg",
        "Ariel",
        "Ariel",
        (191020.0 / SIZE_URANUS) * 20,
        (191020.0 / SIZE_URANUS) * 20,
        1158.0 / SIZE_URANUS,
        0.2, 1.0 / 60
    },
    {
        "planeten/monde/dummy.jpg",
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
static SPlanetDesc sNeptunDesc[] =
{
    {
        "planeten/neptun.jpg",
        "Neptun",
        "Neptune",
        0.0, 1.0, 1.0, 1.0
    },
#ifdef USE_MOONS
    {
        "planeten/monde/dummy.jpg",
        "Triton",
        "Triton",
        (354800.0 / SIZE_NEPTUN) * 20,
        2707.0 / SIZE_NEPTUN,
        0.2, 1.0 / 60
    },
    {
        "planeten/monde/dummy.jpg",
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
static SPlanetDesc sSonneDesc[] =
{
    {
        "planeten/sonnensystem/sonne1.jpg",
        "Sonne",
        "Sun",
        1.0, 1.0, 1.0, 1.0, 1.0
    },
    {
        "planeten/sonnensystem/merkurk.jpg",
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


#endif

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : FileExists
//
//
//
// ---------------------------------------------------------------------------

static bool FileExists(const char* f)
{
    ifstream k(f, ios::binary);

    if (k.good())
    {
        k.close();
        return true;
    }
    cout << "***** File not found: " << f << endl;
    return false;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : InitSonne
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::InitSonne(const SPlanetDesc* PlanetDesc)
{
    //cout << "InitSonne START" << endl;

    CGL_Texture tx;
    int sx = 12;
    int sy = 6;
    float WasserMaterial[] = { 122.0 / 255, 219.0 / 255, 251.0 / 255, 1.0 };

    if (gSonne1 == NULL)
    {
        gSonne1 = new CPlanet;


        mPlanet = EPLANET_SONNE;
        mScale = 0.7;
        mPlanetSize = 0.7;
    }
    else
    {
        gSonne1->Delete();
    }


    gSonne1->CreateEllipsoid(sx * 10, 20.2 * PlanetDesc[0].mSize, sy * 10, 20.2 * PlanetDesc[0].mSize, WasserMaterial);

#define SUN_PHASES		32
#define SUN_SPEED		4

    if (gSonne1->mSunTexHandles != NULL)
    {
        glDeleteTextures(SUN_PHASES, gSonne1->mSunTexHandles);
        delete[] gSonne1->mSunTexHandles;
    }

    gSonne1->mSunTexHandles = new unsigned int[SUN_PHASES];

    for (int t = 0; t < SUN_PHASES; t++)
    {
        stringstream NoiseFile;

        NoiseFile << "sonne/noise" << t << ".tga";
        tx.LoadTextureTga8Bit2D(NoiseFile.str().c_str());

        //tx.LoadTextureTga("sonne/noise0-24.tga", false);


        gSonne1->mSunTexHandles[t] = tx.mTexHandle;
    }
    // Die Sonne besteht aus 6x3 Patches,
    // Jeder Patch besteht aus 10x10 Vertices



    gSonne1->SetMultiTextures(gSonne1->mSunTexHandles, sx, sy);
    gSonne1->InitDisplayList();

    mCamera.mStandort.z = -80.0;

    gErde = gSonne1;
#if 1
    for (int i = 1; PlanetDesc[i].mTextur != NULL; i++)
    {
        const char* TextureName = PlanetDesc[i].mTextur;
        CMond mond;
        CGL_EllipsoidPatched* thing;

        thing = &mond;
        sx = 2;
        sy = 1;

        thing->CreateEllipsoid(sx * 10, 20.0 * PlanetDesc[i].mSize, sy * 10, 20.0 * PlanetDesc[i].mSize, WasserMaterial);

        unsigned int* ErdeTexHandles = tx.CreateSplitTextures(TextureName, sx, sy, mAnaglyph);

        mond.InitOrbit(PlanetDesc[i].mDistanceMin, PlanetDesc[i].mDistanceMax);
        thing->SetMultiTextures(ErdeTexHandles, sx, sy);
        thing->InitDisplayList();
        mCamera.mStandort.z = -80.0;

        if (i > 0)
        {
            mond.mPlanetDesc = PlanetDesc + i;
            gErde->mMonde.push_back(mond);
        }
    }
#endif

    gSonne1->mPhase = 0;
    gSonne1->mPhaseCount = SUN_PHASES;
    gSonne1->mSpeedCount = SUN_SPEED;

    //cout << "InitSonne OK" << endl;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : InitPlanet
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::InitPlanet(const SPlanetDesc* PlanetDesc)
{
    cout << "InitPlanet START Name=" << PlanetDesc->mNameGer  << endl;



    CGL_Texture tx;

    if (gErde == NULL)
    {
        gErde = new CPlanet;

        mPlanet = EPLANET_ERDE;
        mScale = 0.7;
        mPlanetSize = 0.7;
    }
    else
    {
        gErde->Delete();
    }

    float WasserMaterial[] = { 122.0 / 255, 219.0 / 255, 251.0 / 255, 1.0 };

    gErde->mPhaseCount = 0;

    for (int i = 0; PlanetDesc[i].mTextur != NULL; i++)
    {
        const char* TextureName = PlanetDesc[i].mTextur;
        CMond mond;
        int xsegs, ysegs;
        CGL_EllipsoidPatched* thing;
        CGraflibJpeg jpeg;

        cout << "GetJpegSize START=" << TextureName << " i=" << i << endl;

        if (jpeg.GetJpegSize(TextureName))
        {
            xsegs = jpeg.mWidth  * 4 / 256;
            ysegs = jpeg.mHeight * 4 / 256;
            cout << "Texture w=" << jpeg.mWidth << " h=" << jpeg.mHeight << endl;
            cout << "xsegs=" << xsegs << " ysegs=" << ysegs << " bits=" << jpeg.mBits << endl;
        }
        else
        {
            cout << "***** Error while loading texture: " << TextureName << endl;
            exit(0);
        }

        cout << "GetJpegSize OK" << endl;


        if (i == 0)
        {
            thing = gErde;

            ReadLabels(PlanetDesc->mNameGer);
            InitLabels(20, xsegs);

            mLongSegOffset = 360.0 / xsegs;
        }
        else
        {
            thing = &mond;
        }

        thing->CreateEllipsoid(xsegs * 10, 20.0 * PlanetDesc[i].mSize, ysegs * 10, 20.0 * PlanetDesc[i].mSize, WasserMaterial);
        unsigned int* ErdeTexHandles = tx.CreateSplitTextures(TextureName, xsegs, ysegs, mAnaglyph);

        if (i > 0)
        {
            mond.InitOrbit(PlanetDesc[i].mDistanceMin, PlanetDesc[i].mDistanceMax);
        }
        thing->SetMultiTextures(ErdeTexHandles, xsegs, ysegs);
        thing->InitDisplayList();
        mCamera.mStandort.z = -80.0;

        if (i > 0)
        {
            mond.mPlanetDesc = PlanetDesc + i;
            gErde->mMonde.push_back(mond);
        }
    }
    cout << "InitPlanet OK" << endl;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       :
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::SetResolution(int w, int h)
{
    gResGlobals->mWindowWidth = w;
    gResGlobals->mWindowHeight = h;

    if (!mInitFlag)
    {
        InitResources();
        //gG3Dinterface->SendCommand(EG3DcomAdjust);
        mInitFlag = true;
    }
    else
    {
        //gG3Dinterface->SendCommand(EG3DcomReload);
        gG3Dinterface->SendCommand(EG3DcomAdjust);
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : SaveMatrixes
//
//
//
// ---------------------------------------------------------------------------

void CMond::SaveMatrixes()
{
    glGetDoublev(GL_MODELVIEW_MATRIX, mModelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, mProjectionMatrix);
    glGetIntegerv(GL_VIEWPORT, mViewport);
}


/*
 * // ---------------------------------------------------------------------------
 * //
 * // KLASSE        : CGLApplication
 * // METHODE       : GetScreenKoor
 * //
 * //
 * //
 * // ---------------------------------------------------------------------------
 *
 * void CPlanet::GetScreenKoor(CVector3<float>* Vert, CVector3<double>* ScreenKoor)
 * {
 *  double ModelMatrix[16];
 *  double ProjectionMatrix[16];
 *  int    Viewport[4];
 *  double dx, dy, dz;
 *  float  Zval;
 *
 *  glGetDoublev(GL_MODELVIEW_MATRIX,  ModelMatrix);
 *  glGetDoublev(GL_PROJECTION_MATRIX, ProjectionMatrix);
 *  glGetIntegerv(GL_VIEWPORT,         Viewport);
 *
 *  gluProject(
 *       Vert->x, Vert->y, Vert->z,
 *       ModelMatrix,
 *       ProjectionMatrix,
 *       Viewport,
 *       &ScreenKoor->x, &ScreenKoor->y, &ScreenKoor->z);
 *
 *  glReadPixels(ScreenKoor->x, ScreenKoor->y, 1, 1, GL_DEPTH_COMPONENT,GL_FLOAT, &Zval);
 *
 *  cout << "Zval=" << Zval << " ScreenKoor->z=" << ScreenKoor->z << endl;
 *
 *  if (Zval > ScreenKoor->z)
 *  {
 *      ScreenKoor->x	= 0;
 *  }
 * }
 */

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : GetScreenKoor
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::GetScreenKoor(SLabel& Label)
{
    float Zval;
    CVector3<float> Origin;
    CVector3<float> TestVec = Label.mVec3D;

    Origin.Set(0, 0, 0);



    // ,,
    TestVec.RotationXZ(&Origin, mSinYrot, mCosYrot);
    TestVec.RotationYZ(&Origin, mSinXrot, mCosXrot);



    gluProject(
        Label.mVec3D.x, Label.mVec3D.y, Label.mVec3D.z,
        mModelMatrix,
        mProjectionMatrix,
        mViewport,
        &Label.mScreenKoor.x, &Label.mScreenKoor.y, &Label.mScreenKoor.z);

    //glReadPixels((int) Label.mScreenKoor.x, (int) Label.mScreenKoor.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Zval);

/*
 *  cout << "sx=" << Label.mScreenKoor.x << " sy=" << Label.mScreenKoor.y;
 *  cout << " zv=" << Zval << " z="
 *     <<  Label.mScreenKoor.z
 *     << " s=" << mScale
 *     << " d=" << (Zval -  Label.mScreenKoor.z) <<  endl;
 */

    //cout << "TestVec.z=" << TestVec.z << endl;

    if (TestVec.z > -5.0)
    {
        Label.mScreenKoor.z = 2;
    }

    /*
     * float p10 = pow(mScale, 4.0);
     *
     * if (Zval - Label.mScreenKoor.z < -0.00001 * p10)
     * {
     *  Label.mScreenKoor.z = 2;
     * }
     *
     * Label.mScreenKoor.z  = 0;
     */
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : GetLabelsScreenKoor
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::GetLabelsScreenKoor()
{
    glPushMatrix();
    glRotatef(sXrot, 1.0, 0.0, 0.0);    // Rotation um X-Achse,,,
    glRotatef(sYrot +  sYrotAuto, 0.0, 1.0, 0.0);    

    for (list<SLabel>::iterator it = mAktLabelList.begin();
        it != mAktLabelList.end();
        ++it)
    {
        GetScreenKoor(*it);
        //cout << "GetLabelsScreenKoor:" << it->mLabel << endl;
    }
    glPopMatrix();

}


// ---------------------------------------------------------------------------
//
// KLASSE        : CMond
// METHODE       : GetScreenKoor
//
//
//
// ---------------------------------------------------------------------------

void CMond::GetScreenKoor(CVector3<float>* Vert)
{
    float Zval;

    glPushMatrix();
    Rotation();

    gluProject(
        Vert->x, Vert->y, Vert->z,
        mModelMatrix,
        mProjectionMatrix,
        mViewport,
        &mScreenKoor.x, &mScreenKoor.y, &mScreenKoor.z);

    glReadPixels((int)mScreenKoor.x, (int)mScreenKoor.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Zval);

    //cout << "Zval=" << Zval << " ScreenKoor->z=" << mScreenKoor.z << endl;

    if (Zval < mScreenKoor.z - 0.0001)
    {
       mScreenKoor.z = 2;
    }
    glPopMatrix();
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : InitResources
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::InitResources()
{
    float Scale = 0.7;

    bool b = gG3Dinterface->Init("Resource/resource0.r3d", gResGlobals);

    if (b)
    {
        //cout << "gG3Dinterface->Init OK" << endl;
    }
    else
    {
        cout << "***** gG3Dinterface->Init failed" << endl;
    }

    //gResourceList->Read("Resource/GlobusResource.r3d");

    if (b)  //gResourceList->mErrCode == EPERR_NOERROR)
    {
        CFileIO fio;

        //cout << "- NO Errors - " << endl;

        //gResourceList->Show();

        const char* SaturnRingFile = "planeten/saturnring.tga";
        const char* SaturnRingMask = "planeten/A_saturnring.tga";
        const char* UranusRingFile = "planeten/uranusring.tga";
        const char* UranusRingMask = "planeten/A_uranusring.tga";
        const char* SonneHaloFile = "planeten/sonnehalo2.tga";
        const char* SonneHaloMask = "planeten/A_sonnehalo2.tga";

        if (!FileExists(SaturnRingFile))
        {
            exit(0);
        }
        if (!FileExists(SaturnRingMask))
        {
            exit(0);
        }

        mSaturnRing.LoadTextureTga2D(SaturnRingFile, SaturnRingMask, false, mAnaglyph);
        mSaturnRing.mSegments = 256;
        mSaturnRing.mRadius = 60.0 * Scale;
        mSaturnRing.Init();

        mUranusRing.LoadTextureTga2D(UranusRingFile, UranusRingMask, false, mAnaglyph);
        mUranusRing.mSegments = 256;
        mUranusRing.mRadius = 2 * 20;
        mUranusRing.Init();


        mSonneHalo.LoadTextureTga2D(SonneHaloFile, SonneHaloMask, false, mAnaglyph);
        mSonneHalo.mSegments = 256;
        mSonneHalo.mRadius = 2 * 13;
        mSonneHalo.Init();

        mStarField = new CGL_StarField(NUMBER_OF_STARS);
        mStarField->Init();

        ReadSettings();

        InterfaceSetButton("RotationBt", true);
        InterfaceSetButton("OrbitBt", true);

        gG3Dinterface->SendCommand(EG3DcomAdjust);



        ActivatePlanet(mPlanet);
        //ReadLabels();

        mMondName.mName = "MondName";
        gG3Dinterface->SendCommand(EG3DcomSearchChild, &mMondName);

        mLabelName.mName = "LabelName";
        gG3Dinterface->SendCommand(EG3DcomSearchChild, &mLabelName);



        //cout << "InitResources OK" << endl;
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        :
// METHODE       :
//
//
//
// ---------------------------------------------------------------------------

inline float sq2(float a)
{
    return a * a;
}


float ellipseRadius(float rmax, float rmin, float angle)
{
    return (rmax * rmin) / sqrt(sq2(rmin) * sq2(sin(angle)) + sq2(rmax) * sq2(cos(angle)));
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CPlanet
// METHODE       : DrawMonde
//
//
//
// ---------------------------------------------------------------------------

void CPlanet::DrawMonde(bool AutoRotate, bool ShowOrbits, bool Retrograd)
{
    float sWhiteColor[3] = { 1.0, 1.0, 1.0 };
    CVector3<float> Origin;

    Origin.Set(0, 0, 0);
    int m = 0;


    for (auto im = mMonde.begin(); im != mMonde.end(); ++im)
    {
        glDisable(GL_LIGHTING);
        glColor3fv(sMoonColorTable[m++].mColor);

        glPushMatrix();

        if (ShowOrbits)
        {
            im->mOrbit.Draw();
        }
        im->Umlauf(AutoRotate, Retrograd);
        glColor3fv(sWhiteColor);
        glEnable(GL_LIGHTING);


        float f = ellipseRadius(im->mPlanetDesc->mDistanceMax, im->mPlanetDesc->mDistanceMin, DEG_TO_RAD(im->mUmlauf));

        //cout << "f=" << f << endl;
        //glTranslatef(im->mPlanetDesc->mDistanceMin, 0, 0);
        glTranslatef(f, 0, 0);

        im->Rotation(AutoRotate, Retrograd);
        im->SaveMatrixes();

        im->DrawDisplayList();
        glPopMatrix();
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CPlanet
// METHODE       : GetMondScreenKoor
//
//
//
// ---------------------------------------------------------------------------

void CPlanet::GetMondScreenKoor()
{
    CVector3<float> Origin;

    Origin.Set(0, 0, 0);

    for (vector<CMond>::iterator im = mMonde.begin();
        im != mMonde.end();
        im++)
    {
        im->GetScreenKoor(&Origin);
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : DrawCross
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::DrawCross(float xc, float yc)
{
    glLineWidth(1.6);
    glBegin(GL_LINES);
    glVertex2f(xc - 4, yc - 4);
    glVertex2f(xc + 4, yc + 4);
    glVertex2f(xc - 4, yc + 4);
    glVertex2f(xc + 4, yc - 4);
    glEnd();
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : DrawTriangle
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::DrawTriangle(float xc, float yc)
{
    glLineWidth(1.6);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xc, yc + 4);
    glVertex2f(xc + 4, yc - 4);
    glVertex2f(xc - 4, yc - 4);
    glEnd();
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : DrawLabels
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::DrawLabels(CG3DReslistInterface* gi)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //SG3DcomData LabelCom;

    for (list<SLabel>::iterator il = mAktLabelList.begin();
        il != mAktLabelList.end();
        ++il)
    {
        if (il->mScreenKoor.z < 1.0)
        {
            mLabelName.mChrParam = il->mLabel.c_str();


            mLabelName.mPos.x = (int)il->mScreenKoor.x;
            mLabelName.mPos.y = (int)il->mScreenKoor.y - 6;

            //cout << LabelCom.mChrParam << " x=" << LabelCom.mPos.x << " y=" << LabelCom.mPos.y << endl;

            if ((il->mTyp == ELABELTYPE_APOLLO) ||
                (il->mTyp == ELABELTYPE_KRATER) ||
                (il->mTyp == ELABELTYPE_BERG))
            {
                mLabelName.mPos.x += 6;
            }


            glColor4f(0.0, 0.0, 0.0, 1.0);
            gi->SendCommand(EG3DcomDrawString, &mLabelName);

            mLabelName.mPos.x++;
            mLabelName.mPos.y++;

            switch (il->mTyp)
            {
                case ELABELTYPE_APOLLO:
                    glDisable(GL_TEXTURE_2D);
                    glColor4f(0.2, 0.8, 0.2, 1.0);
                    DrawCross(il->mScreenKoor.x, il->mScreenKoor.y);
                    glEnable(GL_TEXTURE_2D);
                    break;

                case ELABELTYPE_KRATER:
                    glDisable(GL_TEXTURE_2D);
                    glColor4f(0.8, 0.8, 0.2, 1.0);
                    DrawCross(il->mScreenKoor.x, il->mScreenKoor.y);
                    glEnable(GL_TEXTURE_2D);
                    break;

                case ELABELTYPE_BERG:
                    glDisable(GL_TEXTURE_2D);
                    glColor4f(0.4, 0.8, 0.2, 1.0);
                    DrawTriangle(il->mScreenKoor.x, il->mScreenKoor.y);
                    glEnable(GL_TEXTURE_2D);
                    break;


                default:

                    glColor4f(0.8, 0.8, 0.8, 1.0);
                    break;
            }

            gi->SendCommand(EG3DcomDrawString, &mLabelName);
        }
    }
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glLineWidth(1.0);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CPlanet
// METHODE       : DrawMondeNames
//
//
//
// ---------------------------------------------------------------------------

void CPlanet::DrawMondeNames(CG3DReslistInterface* gi, SG3DcomData* MondName, int Language)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int m = 0;

    for (vector<CMond>::iterator im = mMonde.begin();
        im != mMonde.end();
        im++)
    {
        if (im->mScreenKoor.z < 1.0)
        {
            if (Language == ELANG_GERMAN)
            {
                MondName->mChrParam = im->mPlanetDesc->mNameGer;
            }
            else
            {
                MondName->mChrParam = im->mPlanetDesc->mNameEng;
            }


            MondName->mPos.x = (int)im->mScreenKoor.x;
            MondName->mPos.y = (int)im->mScreenKoor.y;

            float cr = sMoonColorTable[m].mColor[0] * 1.5;
            float cg = sMoonColorTable[m].mColor[1] * 1.5;
            float cb = sMoonColorTable[m].mColor[2] * 1.5;
            if (cr > 1.0)
            {
                cr = 1.0;
            }
            if (cg > 1.0)
            {
                cg = 1.0;
            }
            if (cb > 1.0)
            {
                cb = 1.0;
            }

            glColor3f(cr, cg, cb);
            gi->SendCommand(EG3DcomDrawString, MondName);
        }
        m++;
    }

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : Animate
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::Animate()
{
    if (gSonne1 != NULL)
    {
        gSonne1->Animate();
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : SaveMatrices
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::SaveMatrices()
{
    glGetDoublev(GL_MODELVIEW_MATRIX, mModelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, mProjectionMatrix);
    glGetIntegerv(GL_VIEWPORT, mViewport);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       :
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::Draw3DObjects()
{
    //cout << "Draw3DObjects START" << endl;

    bool bRetrograd = false;

    if (!mInitFlag)
    {
        return;
    }

    glPushMatrix();

    mSinXrot = sin(DEG_TO_RAD(sXrot));
    mCosXrot = cos(DEG_TO_RAD(sXrot));
    mSinYrot = sin(DEG_TO_RAD(-sYrot));
    mCosYrot = cos(DEG_TO_RAD(-sYrot));

    glRotatef(sXrot, 1.0, 0.0, 0.0);    // Rotation um X-Achse
    //glRotatef(sZrot, 0.0, 0.0, 1.0); // Rotation um Z-Achse (entfaellt)
    glRotatef(sYrot, 0.0, 1.0, 0.0);    // Rotation um Y-Achse


    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    mStarField->Draw();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);


    glScalef(mScale, mScale, mScale);

    if ((mPlanet == EPLANET_VENUS) ||
        (mPlanet == EPLANET_URANUS))
    {
        bRetrograd = true;
    }
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);



#if 1
    if (mPlanet == EPLANET_SONNE)
    {
        // Sonne anzeigen
        if (gSonne1 != NULL)
        {
            glDisable(GL_BLEND);
            glDisable(GL_LIGHTING);

            if (mAnaglyph)
            {
                float SunMaterial[] = { 0.8, 0.8, 0.8, 1.0 };
                glColor3fv(SunMaterial);
            }
            else
            {
                float SunMaterial[] = { 1.0, 0.8, 0.5, 1.0 };
                glColor3fv(SunMaterial);
            }

            gSonne1->DrawDisplayList();
            glEnable(GL_LIGHTING);
        }
    }
    else
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);

        glPushMatrix();

        glRotatef(sYrotAuto, 0.0, 1.0, 0.0);
        SaveMatrices();


        gErde->DrawDisplayList();
        GetLabelsScreenKoor();

        glPopMatrix();
    }
#endif


    if (gErde != NULL)
    {
        gErde->GetMondScreenKoor();
        gErde->DrawMonde(mAutoRotate, mShowOrbits, bRetrograd);
    }


    CGL_Disk* PlanetRing;
    switch (mPlanet)
    {
        case EPLANET_SATURN:

            PlanetRing = &mSaturnRing;
            break;

        case EPLANET_URANUS:

            PlanetRing = &mUranusRing;
            break;

        default:

            PlanetRing = NULL;
            break;
    }

    if (PlanetRing != NULL)
    {
        glRotatef(270, 1.0, 0.0, 0.0);

        glDisable(GL_CULL_FACE);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        PlanetRing->Draw();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        glPopMatrix();
        glEnable(GL_CULL_FACE);
    }


    glPopMatrix();


#if 1
    // Halo der Sonne anzeigen
    if (mPlanet == EPLANET_SONNE)
    {
        float rx = 1.0 + (((float)rand()) / RAND_MAX) / 100;
        float ry = 1.0 + (((float)rand()) / RAND_MAX) / 100;
        float rz = 1.0;

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glPushMatrix();

        glScalef(mScale * rx, mScale * ry, mScale * rz);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //glPolygonMode(GL_FRONT, GL_LINE);

        mSonneHalo.Draw();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        glPopMatrix();

        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);

        //glPolygonMode(GL_FRONT, GL_FILL);
    }
#endif

    if (mAutoScale)
    {
        if (mScale < mPlanetSize)
        {
            mScale += 0.01;
            if (mScale >= mPlanetSize)
            {
                mAutoScale = false;
            }
        }
        if (mScale > mPlanetSize)
        {
            mScale -= 0.01;
            if (mScale <= mPlanetSize)
            {
                mAutoScale = false;
            }
        }
    }

    if (mAutoRotate)
    {
        if (bRetrograd)
        {
            sYrotAuto -= 0.1;
        }
        else
        {
            sYrotAuto += 0.1;
        }

        if (sYrotAuto < 0)
        {
            sYrotAuto += 360;
        }

        if (sYrotAuto > 360)
        {
            sYrotAuto -= 360;
        }
    }


    //cout << "Draw3DObjects OK" << endl;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : MouseMotionLeft
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::MouseMotionLeft(int dx, int dy)
{
    if (mScale >= 1.0)
    {
        sXrot += (float)dy / (mScale * mScale * 3);
        sYrot += (float)dx / (mScale * mScale * -3);
    }
    else
    {
        sXrot += (float)dy / 3;
        sYrot += (float)dx / -3;
    }

    if (sXrot > 85)
    {
        sXrot = 85;
    }
    if (sXrot < -85)
    {
        sXrot = -85;
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : MouseMotionRight
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::MouseMotionRight(int dx, int dy)
{
    Zoom((float)dy / 100);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : InterfaceSetString
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::InterfaceSetString(const char* StringName, const char* NewContent)
{
    SG3DcomData scom;

    scom.mName = StringName;
    gG3Dinterface->SendCommand(EG3DcomSearchChild, &scom);
    scom.mStrParam = NewContent;
    gG3Dinterface->SendCommand(EG3DcomChangeString, &scom);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : InterfaceSetString
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::InterfaceSetButton(const char* ButtonName, bool Status)
{
    SG3DcomData scom;

    scom.mName = ButtonName;
    gG3Dinterface->SendCommand(EG3DcomSearchChild, &scom);
    scom.mFlags = Status;
    gG3Dinterface->SendCommand(EG3DcomSetButton, &scom);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : SetPlanetName
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::SetPlanetName()
{
    const char* EngName[] =
    {
        "Mercury",
        "Venus",
        "Earth",
        "Mars",
        "Jupiter",
        "Saturn",
        "Uranus",
        "Neptune",
        "Sun",
        "Ganymede",
        "Europa",
        "Callisto",
        "Io",
        "Moon",
        "Titan",
        "Rhea",
        "Triton"
    };

    const char* GerName[] =
    {
        "Merkur",
        "Venus",
        "Erde",
        "Mars",
        "Jupiter",
        "Saturn",
        "Uranus",
        "Neptun",
        "Sonne",
        "Ganymed",
        "Europa",
        "Kallisto",
        "Io",
        "Mond",
        "Titan",
        "Rhea",
        "Triton"
    };

    //cout << "mPlanet=" << mPlanet << endl;

    if (gResGlobals->mLanguage == ELANG_GERMAN)
    {
        InterfaceSetString("PlanetNameStr", GerName[mPlanet]);
    }
    else
    {
        InterfaceSetString("PlanetNameStr", EngName[mPlanet]);
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : ActivateInfobox
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::ActivatePlanet(EPlanet p)
{
    const SPlanetDesc* pd;
    const char* PlanetNameStr = "PlanetNameStr";

    //cout << "ActivatePlanet START p=" << p << endl;

    if (mActInfobox != NULL)
    {
        gG3Dinterface->SendCommand(EG3DcomDeactivateKnot, (void*)mActInfobox);
    }

    switch (p)
    {
        case EPLANET_SONNE:

            InitSonne(NPlanets::SonneDesc);
            pd = NPlanets::SonneDesc;
            gG3Dinterface->SendCommand(EG3DcomDeactivateKnot, (void*)"Infobox");
            gG3Dinterface->SendCommand(EG3DcomActivateKnot, (void*)"InfoboxS");

            gG3Dinterface->SendCommand(EG3DcomActivateKnot, (void*)"InfoboxS");

            mActInfobox = NULL;

            //cout << "SendCommand OK" << endl;
            break;

        case EPLANET_MERKUR:

            mActInfobox = "MerkurInfoBox";

            pd = NPlanets::MerkurDesc;
            break;

        case EPLANET_VENUS:

            mActInfobox = "VenusInfoBox";
            pd = NPlanets::VenusDesc;
            break;

        case EPLANET_ERDE:

            mActInfobox = "EarthInfoBox";
            pd = NPlanets::ErdeDesc;
            break;

        case EPLANET_MARS:

            mActInfobox = "MarsInfoBox";
            pd = NPlanets::MarsDesc;
            break;

        case EPLANET_JUPITER:

            mActInfobox = "JupiterInfoBox";
            pd = NPlanets::JupiterDesc;
            break;

        case EPLANET_SATURN:

            mActInfobox = "SaturnInfoBox";
            pd = NPlanets::SaturnDesc;
            break;

        case EPLANET_URANUS:

            mActInfobox = "UranusInfoBox";
            pd = NPlanets::UranusDesc;
            break;

        case EPLANET_NEPTUN:

            mActInfobox = "NeptunInfoBox";
            pd = NPlanets::NeptunDesc;
            break;

        case EMOND_GANYMED:

            mActInfobox = "GanymedInfoBox";
            pd = NPlanets::GanymedDesc;
            break;

        case EMOND_EUROPA:

            mActInfobox = "EuropaInfoBox";
            pd = NPlanets::EuropaDesc;
            break;

        case EMOND_KALLISTO:

            mActInfobox = "KallistoInfoBox";
            pd = NPlanets::KallistoDesc;
            break;

        case EMOND_IO:

            mActInfobox = "IoInfoBox";
            pd = NPlanets::IoDesc;
            break;


        case EMOND_MOND:

            mActInfobox = "MondInfoBox";
            pd = NPlanets::MondDesc;
            break;

        case EMOND_TITAN:

            mActInfobox = "TitanInfoBox";
            pd = NPlanets::TitanDesc;
            break;

        case EMOND_RHEA:

            mActInfobox = "RheaInfoBox";
            pd = NPlanets::RheaDesc;
            break;

        case EMOND_TRITON:

            mActInfobox = "TritonInfoBox";
            pd = NPlanets::TritonDesc;
            break;
    }

    if (p != EPLANET_SONNE)
    {
        InitPlanet(pd);
    }
    if (mActInfobox != NULL)
    {
        gG3Dinterface->SendCommand(EG3DcomDeactivateKnot, (void*)"InfoboxS");
        gG3Dinterface->SendCommand(EG3DcomActivateKnot, (void*)"Infobox");
        gG3Dinterface->SendCommand(EG3DcomActivateKnot, (void*)mActInfobox);
    }
    //cout << "EG3DcomActivateKnot OK2" << endl;

    mPlanet = p;
    SetPlanetName();

    //cout << "ActivatePlanet OK" << endl;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : Zoom
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::Zoom(float f)
{
    mScale += f;
    if (mScale > 3)
    {
        mScale = 3;
    }
    if (mScale < 0.01)
    {
        mScale = 0.01;
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : LoadSaturnRing
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::LoadSaturnRing()
{
    const char* SaturnRingFile = "planeten/saturnring.tga";
    const char* SaturnRingMask = "planeten/A_saturnring.tga";

    mSaturnRing.LoadTextureTga2D(SaturnRingFile, SaturnRingMask, false, mAnaglyph);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : LoadUranusRing
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::LoadUranusRing()
{
    const char* UranusRingFile = "planeten/uranusring.tga";
    const char* UranusRingMask = "planeten/A_uranusring.tga";

    mUranusRing.LoadTextureTga2D(UranusRingFile, UranusRingMask, false, mAnaglyph);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : LeftMouseButtonAction
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::LeftMouseButtonAction(bool pressed)
{
    cout << "CGLApplication::LeftMouseButtonAction pressed=" << pressed << endl;
    if (pressed)
    {
        LeftMouseButtonDown();
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : LeftMouseButtonDown
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::LeftMouseButtonDown()
{
    SG3DcomData scom;

    if (gG3Dinterface->SendCommand(EG3DcomLeftMouseClick, &scom))
    {
        if (scom.mFlags & SPF_SLIDER)
        {
            gSlider.mName = scom.mName;
            gSlider.mObject = scom.mObject;
        }
        else
        {
            gSlider.mObject = NULL;
        }

        if (scom.mName == "RotationBt")
        {
            mAutoRotate = scom.mFlags;
        }
        else
        if (scom.mName == "OrbitBt")
        {
            mShowOrbits = scom.mFlags;
        }
        else
        if (scom.mName == "GermanButton")
        {
            gResGlobals->mLanguage = ELANG_GERMAN;
            gG3Dinterface->SendCommand(EG3DcomAdjust);
            SetPlanetName();
        }
        else
        if (scom.mName == "EnglishButton")
        {
            gResGlobals->mLanguage = ELANG_ENGLISH;
            gG3Dinterface->SendCommand(EG3DcomAdjust);
            SetPlanetName();
        }
        else
        if (scom.mName == "SonneButton")
        {
            ActivatePlanet(EPLANET_SONNE);
        }
        else
        if (scom.mName == "MerkurButton")
        {
            ActivatePlanet(EPLANET_MERKUR);
        }
        else
        if (scom.mName == "VenusButton")
        {
            ActivatePlanet(EPLANET_VENUS);
        }
        else
        if (scom.mName == "EarthButton")
        {
            ActivatePlanet(EPLANET_ERDE);
        }
        else
        if (scom.mName == "MarsButton")
        {
            ActivatePlanet(EPLANET_MARS);
        }
        else
        if (scom.mName == "JupiterButton")
        {
            ActivatePlanet(EPLANET_JUPITER);
        }
        else
        if (scom.mName == "SaturnButton")
        {
            ActivatePlanet(EPLANET_SATURN);
        }
        else
        if (scom.mName == "UranusButton")
        {
            ActivatePlanet(EPLANET_URANUS);
        }
        else
        if (scom.mName == "NeptunButton")
        {
            ActivatePlanet(EPLANET_NEPTUN);
        }
        else
        if (scom.mName == "GanymedBt")
        {
            ActivatePlanet(EMOND_GANYMED);
        }
        else
        if (scom.mName == "EuropaBt")
        {
            ActivatePlanet(EMOND_EUROPA);
        }
        else
        if (scom.mName == "KallistoBt")
        {
            ActivatePlanet(EMOND_KALLISTO);
        }
        else
        if (scom.mName == "IoBt")
        {
            ActivatePlanet(EMOND_IO);
        }
        else
        if (scom.mName == "MondBt")
        {
            ActivatePlanet(EMOND_MOND);
        }
        else
        if (scom.mName == "TitanBt")
        {
            ActivatePlanet(EMOND_TITAN);
        }
        else
        if (scom.mName == "RheaBt")
        {
            ActivatePlanet(EMOND_RHEA);
        }
        else
        if (scom.mName == "TritonBt")
        {
            ActivatePlanet(EMOND_TRITON);
        }
        else
        if (scom.mName == "QuitButton")
        {
            WriteSettings();
            exit(0);
        }
        else
        if (scom.mName == "AppInfoButton")
        {
            gG3Dinterface->SendCommand(EG3DcomActivateKnot, (void*)"AppInfoBox");
        }
        else
        if (scom.mName == "OkButton")
        {
            gG3Dinterface->SendCommand(EG3DcomDeactivateKnot, (void*)"AppInfoBox");
        }
        else
        if (scom.mName == "AnaglyphBt")
        {
            mAnaglyph = scom.mFlags;
            ActivatePlanet(mPlanet);
            LoadSaturnRing();
            LoadUranusRing();
        }
    }
    else
    {
        cout << "EG3DcomLeftMouseClick failed" << endl;
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : RightMouseButtonDown
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::RightMouseButtonDown()
{
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : ParseKeys
//
//
//
// ---------------------------------------------------------------------------


bool CGLApplication::ParseKeys(int key, bool down)
{
    if (down)
    {
        KeyboardAction(key);
    }
    return true;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : PositionLoad
//
// ---------------------------------------------------------------------------

void CGLApplication::PositionLoad(int pos)
{
    sXrot = mPositions[pos].mXrot;
    sYrot = mPositions[pos].mYrot;
    mScale = mPositions[pos].mScale;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : PositionSave
//
// ---------------------------------------------------------------------------

void CGLApplication::PositionSave(int pos)
{
    mPositions[pos].mXrot = sXrot;
    mPositions[pos].mYrot = sYrot;
    mPositions[pos].mScale = mScale;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : KeyboardAction
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::KeyboardAction(unsigned char key)
{
    if (gG3Dinterface->SendCommand(EG3DcomSendChar, &key) == 0)
    {
        switch (key)
        {
            case ' ':

                mShowInterface = !mShowInterface;
                break;

            case 's':

                ActivatePlanet(EPLANET_SONNE);
                break;

            case 'r':

                gG3Dinterface->SendCommand(EG3DcomReload);
                break;

            case 'e':

                gResGlobals->mLanguage = ELANG_ENGLISH;
                gG3Dinterface->SendCommand(EG3DcomAdjust);
                break;

            case 'd':

                gResGlobals->mLanguage = ELANG_GERMAN;
                gG3Dinterface->SendCommand(EG3DcomAdjust);
                break;

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                int pos = key - '0';
                if (mKeyState & EKeyFlag::CTRL_L_OR_R)
                {
                    cout << "PositionSave:" << pos << endl;
                    PositionSave(key - '0');
                }
                else
                {
                    cout << "PositionLoad:" << pos << endl;
                    PositionLoad(key - '0');
                }
            }
            break;
        }
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       :
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::Draw2DObjects()
{
    if (mInitFlag)
    {
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : ManageInterface
//
//
//
// ---------------------------------------------------------------------------

void CGLApplication::ManageInterface(CGL_Mouse* Mouse)
{
    if (mInitFlag)
    {
        if (mShowInterface)
        {
            gErde->DrawMondeNames(gG3Dinterface, &mMondName, gResGlobals->mLanguage);
            DrawLabels(gG3Dinterface);

            if (mShowInterface)
            {
                gG3Dinterface->SendCommand(EG3DcomRollover, Mouse);
                gG3Dinterface->SendCommand(EG3DcomDraw);
            }
        }
        else
        {
            gErde->DrawMondeNames(gG3Dinterface, &mMondName, gResGlobals->mLanguage);
        }
    }
}
