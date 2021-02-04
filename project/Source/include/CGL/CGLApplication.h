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

enum EPlanet
{
    EPLANET_MERKUR,
    EPLANET_VENUS,
    EPLANET_ERDE,
    EPLANET_MARS,
    EPLANET_JUPITER,
    EPLANET_SATURN,
    EPLANET_URANUS,
    EPLANET_NEPTUN
};

#include "SPlanetDesc.h"

class CMond : public CGL_EllipsoidPatched
{
    public:

        const SPlanetDesc* mPlanetDesc;

        float mUmlauf;
        float mRotation;

        void Umlauf(bool r)
        {
            glRotatef(mUmlauf, 0.0, 1.0, 0.0);
            if (r)
            {
                mUmlauf += mPlanetDesc->mOrbitSpeed;
            }
        }


        void Rotation(bool r)
        {
            glRotatef(mRotation, 0.0, 1.0, 0.0);
            if (r)
            {
                mRotation += mPlanetDesc->mRotSpeed;
            }
        }


        CMond()
        {
            mUmlauf = rand() % 360;
            mRotation = rand() % 360;
        }
};

class CPlanet : public CGL_EllipsoidPatched
{
    public:

        void LadeMonde(char** Monde);
        void Delete(void);
        void DrawMonde(bool AutoRotate);

        vector<CMond> mMonde;
};


class CGLApplication
{
    public:

        CGLApplication();

        void InitApplication(int argc, char* argv[]);
        void Draw3DObjects(void);
        void ManageInterface(CGL_Mouse* Mouse);
        void LeftMouseButtonDown(void);
        void MouseWheel(int d);
        void MouseMotion(int x, int y);
        void KeyboardAction(unsigned char key);
        void SetResolution(int w, int h);

    protected:

        void ActivatePlanet(EPlanet p);
        void InitPlanet(const SPlanetDesc* PlanetDesc);
        void InitResources(void);

        COpenGL* gOpenGL;
        CPlanet* gErde;
        //CGL_EllipsoidPatched* gErdeSmall;
        CG3DGlobals* gResGlobals;
        CG3DReslistInterface* gG3Dinterface;
        CGL_Disk gSaturnRing;
        SG3DcomData gSlider;
        EPlanet mPlanet;
        float mPlanetSize;
        float mScale;
        const char* mActInfobox;
        bool mInitFlag;
        bool mAutoScale;
        bool mAutoRotate;
};

#endif
