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
#include <CGL_Disk.h>
#include <CGL_StarField.h>
#include <SPlanetDesc.h>
#include <SLabel.h>

#include <EPlanet.h>
#include <CMond.h>
#include <CPlanet.h>
#include <CSDL/CSDL_App.h>

struct SPosition
{
    float	mXrot;
    float	mYrot;
    float	mScale;
};

class CGLApplication : public CSDL_App
{
    public:

        CGLApplication();

        const char* Name()    { return "theplanets"; }
        const char* Version() { return "2.0.0"; }

        // virtual from CSDL_App:
        void InitGame();
        void GameLoop();
        void MouseMotion(int xabs, int yabs, int xrel, int yrel);
        void LeftMouseButtonAction(bool pressed);
        void MouseWheel(bool up);
        bool ParseKeys(int key, bool down);
        const char* AppName() const;

    protected:

        void Draw3DObjects();
        void Draw2DObjects();
        void ManageInterface(CGL_Mouse* Mouse);
        void LeftMouseButtonDown();
        void RightMouseButtonDown();
        void Animate();
        void DrawGradnetz() const;
        void drawLatitudeRing(const CGL_Circle& latitudering, const float latitude) const;

        void MouseMotionLeft(int x, int y);
        void MouseMotionRight(int x, int y);

        void KeyboardAction(unsigned char key);
        void SetResolution(int w, int h);

        bool mFullscreen;       // Fullscreen-Modus
        bool mLame;             // fuer lahme Maschinen
        bool mShowInterface;    // Interface anzeigen

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


        void PositionLoad(int pos);
        void PositionSave(int pos);
        void ReadSettings(void);
        void WriteSettings(void);

        //CSDL_App* mSdlApp;
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


        SPosition mPositions[10];
        SG3DcomData mMondName;
        SG3DcomData mLabelName;
};

#endif
