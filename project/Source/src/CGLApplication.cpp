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

#define NUMBER_OF_STARS 10000

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
// ---------------------------------------------------------------------------

CGLApplication::CGLApplication()
{
    mErde = NULL;
    mSonne = NULL;
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
    mLabels = new CLabels(&mTransformContext);
    mCamera.mStandort.z = -80.0;
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : InitGame
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
// ---------------------------------------------------------------------------

void CGLApplication::MouseMotion(int xabs, int yabs, int xrel, int yrel)
{
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
// ---------------------------------------------------------------------------

void CGLApplication::GameLoop()
{
    GLfloat planetMaterialLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    StartModelView(0.1 / mScale, 30.0 / mScale);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, planetMaterialLight);
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
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);

    ManageInterface(&mMouse);

    SDL_GL_SwapWindow(mSdlWindow);
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : MouseWheel
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
// METHODE       : LongLatiToSphere
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
// ---------------------------------------------------------------------------

void CGLApplication::InitSonne(const SPlanetDesc* PlanetDesc)
{
    //cout << "InitSonne START" << endl;

    CGL_Texture tx;
    int sx = 12;
    int sy = 6;
    float WasserMaterial[] = { 122.0 / 255, 219.0 / 255, 251.0 / 255, 1.0 };

    if (mSonne == NULL)
    {
        mSonne = new CPlanet;


        mPlanet = EPLANET_SONNE;
        mScale = 0.7;
        mPlanetSize = 0.7;
    }
    else
    {
        mSonne->Delete();
    }


    mSonne->CreateEllipsoid(sx * 10, 20.2 * PlanetDesc[0].mSize, sy * 10, 20.2 * PlanetDesc[0].mSize, WasserMaterial);

    #define SUN_PHASES		32
    #define SUN_SPEED		4

    if (mSonne->mSunTexHandles != NULL)
    {
        glDeleteTextures(SUN_PHASES, mSonne->mSunTexHandles);
        delete[] mSonne->mSunTexHandles;
    }

    mSonne->mSunTexHandles = new unsigned int[SUN_PHASES];

    for (int t = 0; t < SUN_PHASES; t++)
    {
        stringstream NoiseFile;

        NoiseFile << "sonne/noise" << t << ".tga";
        tx.LoadTextureTga8Bit2D(NoiseFile.str().c_str());

        //tx.LoadTextureTga("sonne/noise0-24.tga", false);


        mSonne->mSunTexHandles[t] = tx.mTexHandle;
    }
    // Die Sonne besteht aus 6x3 Patches,
    // Jeder Patch besteht aus 10x10 Vertices

    mSonne->SetMultiTextures(mSonne->mSunTexHandles, sx, sy);
    mSonne->InitDisplayList();

    mCamera.mStandort.z = -80.0;

    mErde = mSonne;
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
            mErde->mMonde.push_back(mond);
        }
    }

    mSonne->mPhase = 0;
    mSonne->mPhaseCount = SUN_PHASES;
    mSonne->mSpeedCount = SUN_SPEED;

    //cout << "InitSonne OK" << endl;
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : InitPlanet
//
// ---------------------------------------------------------------------------

void CGLApplication::InitPlanet(const SPlanetDesc* PlanetDesc)
{
    cout << "InitPlanet START Name=" << PlanetDesc->mNameGer  << endl;

    CGL_Texture tx;

    if (mErde == NULL)
    {
        mErde = new CPlanet;

        mPlanet = EPLANET_ERDE;
        mScale = 0.7;
        mPlanetSize = 0.7;
    }
    else
    {
        mErde->Delete();
    }

    float WasserMaterial[] = { 122.0 / 255, 219.0 / 255, 251.0 / 255, 1.0 };

    mErde->mPhaseCount = 0;

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
            thing = mErde;

            mLabels->ReadLabels(PlanetDesc->mNameGer);
            mLabels->InitLabels(gG3Dinterface, 20, xsegs);

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
            mErde->mMonde.push_back(mond);
        }
    }
    cout << "InitPlanet OK" << endl;
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : SetResolution
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
// METHODE       : InitResources
//
// ---------------------------------------------------------------------------

void CGLApplication::InitResources()
{
    float Scale = 0.7;

    bool b = gG3Dinterface->Init("Resource/resource0.r3d", gResGlobals);

    if (!b)
    {
        cout << "***** gG3Dinterface->Init failed" << endl;
    }

    if (b)  //gResourceList->mErrCode == EPERR_NOERROR)
    {
        CFileIO fio;

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

        mMondName.mName = "MondName";
        gG3Dinterface->SendCommand(EG3DcomSearchChild, &mMondName);
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : Animate
//
// ---------------------------------------------------------------------------

void CGLApplication::Animate()
{
    if (mSonne != NULL)
    {
        mSonne->Animate();
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : SaveMatrices
//
// ---------------------------------------------------------------------------

void CGLApplication::SaveMatrices()
{
    glGetDoublev(GL_MODELVIEW_MATRIX, mTransformContext.mModelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, mTransformContext.mProjectionMatrix);
    glGetIntegerv(GL_VIEWPORT, mTransformContext.mViewport);
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : drawLatitudeRing
//
// ---------------------------------------------------------------------------

void CGLApplication::drawLatitudeRing(const CGL_Circle& latitudering, const float latitude) const
{
    const float scale = cos(DEG_TO_RAD(latitude));
    const float trans = 20.02f * scale * tan(DEG_TO_RAD(latitude));

    glPushMatrix();
    glTranslatef(0, trans, 0);
    glScalef(scale, 1.0f, scale);
    latitudering.Draw();
    glPopMatrix();
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : DrawGradnetz
//
// ---------------------------------------------------------------------------

void CGLApplication::DrawGradnetz() const
{    
    static CGL_Circle longitudering;
    static CGL_Circle latitudering;
    static bool isInit = false;
    static bool first = true;
    if (!isInit)
    {        
        longitudering.mOrigin.Set(0.0, 0.0, 0.0);
        longitudering.mRadius = 20.02;
        longitudering.mSegments = 100;
        longitudering.SetCircleSegment(5.0, 175.0);
        longitudering.Init();

        latitudering.mOrigin.Set(0.0, 0.0, 0.0);
        latitudering.mRadius = 20.02;
        latitudering.mSegments = 100;
        latitudering.Init();
        isInit = true;
    }
    glDisable(GL_LIGHTING);
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    

    const int longitudeCount = 18;
    const int latitudeCount = 4;

    for (int i = 0; i < longitudeCount; i++)
    {
        if (i == 0)
        {
            // 0. longitude in CYAN
            glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
        }
        else
        {
            // other longitudes in BLUE
            glColor4f(0.0f, 0.2f, 1.0f, 1.0f);
        }
        glPushMatrix();
        glRotatef(-100.0 + 360.0 / longitudeCount * i, 0.0f, 1.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        longitudering.Draw();
        glPopMatrix();
    }

    //
    // draw latitudes
    //
    for (int i = -latitudeCount + 1; i < latitudeCount; i++)
    {
        const float latitude = 90.0 / latitudeCount * i;
        if (i == 0)
        {
            glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
        }
        else
        {
            glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
        }
        drawLatitudeRing(latitudering, latitude);
    }
    drawLatitudeRing(latitudering, -85.0f);
    drawLatitudeRing(latitudering,  85.0f);
    first = false;


}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : Draw3DObjects
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

    mTransformContext.mSinXrot = sin(DEG_TO_RAD(mTransformContext.mXrot));
    mTransformContext.mCosXrot = cos(DEG_TO_RAD(mTransformContext.mXrot));
    mTransformContext.mSinYrot = sin(DEG_TO_RAD(-(mTransformContext.mYrot + mTransformContext.mYrotAuto)));
    mTransformContext.mCosYrot = cos(DEG_TO_RAD(-(mTransformContext.mYrot + mTransformContext.mYrotAuto)));

    glRotatef(mTransformContext.mXrot, 1.0, 0.0, 0.0);    // Rotation um X-Achse
    //glRotatef(sZrot, 0.0, 0.0, 1.0); // Rotation um Z-Achse (entfaellt)
    glRotatef(mTransformContext.mYrot, 0.0, 1.0, 0.0);    // Rotation um Y-Achse


    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    mStarField->Draw();    
    glEnable(GL_DEPTH_TEST);
    
    glScalef(mScale, mScale, mScale);
    

    if ((mPlanet == EPLANET_VENUS) ||
        (mPlanet == EPLANET_URANUS))
    {
        bRetrograd = true;
    }
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glCullFace(GL_BACK);

    if (mPlanet == EPLANET_SONNE)
    {
        // Sonne anzeigen
        if (mSonne != NULL)
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

            mSonne->DrawDisplayList();
            glEnable(GL_LIGHTING);
        }
    }
    else
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);

        glPushMatrix();

        glRotatef(mTransformContext.mYrotAuto, 0.0, 1.0, 0.0);
        SaveMatrices();

        glColor3f(0.2f, 0.2f, 0.2f);
        mErde->DrawDisplayList();
        mLabels->GetLabelsScreenKoor();
        DrawGradnetz();

        glPopMatrix();
    }

    if (mErde != NULL)
    {
        mErde->GetMondScreenKoor();
        mErde->DrawMonde(mAutoRotate, mShowOrbits, bRetrograd, sMoonColorTable);
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
            mTransformContext.mYrotAuto -= 0.025;
        }
        else
        {
            mTransformContext.mYrotAuto += 0.025;
        }

        if (mTransformContext.mYrotAuto < 0)
        {
            mTransformContext.mYrotAuto += 360;
        }

        if (mTransformContext.mYrotAuto > 360)
        {
            mTransformContext.mYrotAuto -= 360;
        }
    }

}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : MouseMotionLeft
//
// ---------------------------------------------------------------------------

void CGLApplication::MouseMotionLeft(int dx, int dy)
{
    if (mScale >= 1.0)
    {
        mTransformContext.mXrot += (float)dy / (mScale * mScale * 3);
        mTransformContext.mYrot += (float)dx / (mScale * mScale * -3);
    }
    else
    {
        mTransformContext.mXrot += (float)dy / 3;
        mTransformContext.mYrot += (float)dx / -3;
    }

    if (mTransformContext.mXrot > 85)
    {
        mTransformContext.mXrot = 85;
    }
    if (mTransformContext.mXrot < -85)
    {
        mTransformContext.mXrot = -85;
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : MouseMotionRight
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
    mPlanet = p;
    SetPlanetName();
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : Zoom
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
// ---------------------------------------------------------------------------

void CGLApplication::RightMouseButtonDown()
{
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : ParseKeys
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
    mTransformContext.mXrot = mPositions[pos].mXrot;
    mTransformContext.mYrot = mPositions[pos].mYrot;
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
    mPositions[pos].mXrot = mTransformContext.mXrot;
    mPositions[pos].mYrot = mTransformContext.mYrot;
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
// METHODE       : Draw2DObjects
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
// ---------------------------------------------------------------------------

void CGLApplication::ManageInterface(CGL_Mouse* Mouse)
{
    if (mInitFlag)
    {
        if (mShowInterface)
        {
            mErde->DrawMondeNames(gG3Dinterface, &mMondName, gResGlobals->mLanguage, sMoonColorTable);
            mLabels->DrawLabels(gG3Dinterface);

            if (mShowInterface)
            {
                gG3Dinterface->SendCommand(EG3DcomRollover, Mouse);
                gG3Dinterface->SendCommand(EG3DcomDraw);
            }
        }
        else
        {
            mErde->DrawMondeNames(gG3Dinterface, &mMondName, gResGlobals->mLanguage, sMoonColorTable);
        }
    }
}
