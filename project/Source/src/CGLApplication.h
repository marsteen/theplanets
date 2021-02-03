//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGLApplication.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGLAPPLICATION_H
#define CGLAPPLICATION_H

#include <list>
#include <CGL_Circle.h>
#include <CGL_StarField.h>
#include "SPlanetDesc.h"
#include "SLabel.h"
#include <CSDL/CSDL_App.h>


enum EPlanet
{
    EPLANET_MERKUR,
    EPLANET_VENUS,
    EPLANET_ERDE,
    EPLANET_MARS,
    EPLANET_JUPITER,
    EPLANET_SATURN,
    EPLANET_URANUS,
    EPLANET_NEPTUN,
    EPLANET_SONNE,
    EMOND_GANYMED,
    EMOND_EUROPA,
    EMOND_KALLISTO,
    EMOND_IO,
    EMOND_MOND,
    EMOND_TITAN,
    EMOND_RHEA,
    EMOND_TRITON
};


class CMond : public CGL_EllipsoidPatched
{
    public:

        const SPlanetDesc* mPlanetDesc;

        float mUmlauf;
        float mRotation;
        CVector3<double> mScreenKoor;

        void SaveMatrixes(void);
        void GetScreenKoor(CVector3<float>* Vert);
        void InitOrbit(float Radius);

        void Delete()
        {
            CGL_EllipsoidPatched::Delete();
            mOrbit.DeleteDisplayList();
        }


        void Umlauf(bool r, bool Retrograd)
        {
            glRotatef(mUmlauf, 0.0, 1.0, 0.0);
            if (r)
            {
                if (Retrograd)
                {
                    mUmlauf -= mPlanetDesc->mOrbitSpeed;
                }
                else
                {
                    mUmlauf += mPlanetDesc->mOrbitSpeed;
                }
            }
        }


        void Rotation(bool r, bool Retrograd)
        {
            glRotatef(mRotation, 0.0, 1.0, 0.0);
            if (r)
            {
                if (Retrograd)
                {
                    mRotation -= mPlanetDesc->mRotSpeed;
                }
                else
                {
                    mRotation += mPlanetDesc->mRotSpeed;
                }
            }
        }


        CMond()
        {
            mUmlauf = rand() % 360;
            mRotation = rand() % 360;
        }


        double mModelMatrix[16];
        double mProjectionMatrix[16];
        int mViewport[4];
        CGL_Circle mOrbit;
};

class CPlanet : public CGL_EllipsoidPatched
{
    public:

        CPlanet()
        {
            mSunTexHandles = NULL;
        }


        void LadeMonde(char** Monde);
        void Delete();
        void DrawMonde(bool AutoRotate, bool ShowOrbits, bool Retrograd);
        void DrawMondeNames(CG3DReslistInterface* gi, SG3DcomData* MondName, int Language);
        void GetMondScreenKoor();

        std::vector<CMond> mMonde;



        unsigned int* mSunTexHandles;

        //void GetScreenKoor(CVector3<float>* Vert, CVector3<double>* ScreenKoor);
};


class CGLApplication
{
    public:

        CGLApplication();

        const char* Name() { return "theplanets"; }
        const char* Version() { return "2.0.0"; }

        void InitApplication(int argc, char* argv[]);
        void Draw3DObjects();
        void Draw2DObjects();
        void ManageInterface(CGL_Mouse* Mouse);
        void LeftMouseButtonDown();
        void RightMouseButtonDown();
        void MouseWheel(int d);
        void Animate();

        void MouseMotionLeft(int x, int y);
        void MouseMotionRight(int x, int y);

        void KeyboardAction(unsigned char key);
        void SetResolution(int w, int h);

        bool mFullscreen;       // Fullscreen-Modus
        bool mLame;             // fuer lahme Maschinen
        bool mShowInterface;    // Interface anzeigen

    protected:

        void ActivatePlanet(EPlanet p);
        void InitPlanet(const SPlanetDesc* PlanetDesc);
        void InitSonne(const SPlanetDesc* PlanetDesc);
        void InitStarfield();
        void InitResources(void);
        void Zoom(float f);
        void LoadSaturnRing();
        void LoadUranusRing();
        void InterfaceSetString(const char* StringName, const char* NewContent);
        void InterfaceSetButton(const char* ButtonName, bool Status);

        void ReadLabels(void);                                          // ALT
        void InitLabels(std::string BodyName, float Radius, int sx);    // ALT

        void ReadLabels(std::string Bodyname);
        void InitLabels(float Radius, int sx);

        void LongLatiToSphere(CVector3<float>& vert, float Long, float Lati, float Radius);
        void GetScreenKoor(SLabel& Label);
        void GetLabelsScreenKoor();
        void DrawLabels(CG3DReslistInterface* gi);
        void SetPlanetName();
        void SaveMatrices();
        void DrawCross(float xc, float yc);
        void DrawTriangle(float xc, float yc);


        void ReadSettings(void);
        void WriteSettings(void);

        CSDL_App* mSdlApp;
        //COpenGL* gOpenGL;
        CPlanet* gErde;
        CPlanet* gSonne1;
        //CGL_EllipsoidPatched* gErdeSmall;
        CG3DGlobals* gResGlobals;
        CG3DReslistInterface* gG3Dinterface;
        std::list<SLabel> mLabelList;
        std::list<SLabel> mAktLabelList;
        CGL_Disk mSaturnRing;
        CGL_Disk mUranusRing;
        CGL_Disk mSonneHalo;
        CGL_StarField* mStarField;
        SG3DcomData gSlider;
        EPlanet mPlanet;
        float mPlanetSize;
        
    public: 
    
        float mScale;
        const char* mActInfobox;
        bool mInitFlag;
        bool mAutoScale;
        bool mAutoRotate;
        bool mShowOrbits;

        float mSinXrot;
        float mCosXrot;
        float mSinYrot;
        float mCosYrot;
        float mLongSegOffset;

        double mModelMatrix[16];
        double mProjectionMatrix[16];
        int mViewport[4];



        SG3DcomData mMondName;
        SG3DcomData mLabelName;
};

#endif
