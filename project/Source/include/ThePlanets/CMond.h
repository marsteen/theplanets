#ifndef CMond_H
#define CMond_h

#include <CGL_Ellipse.h>
#include <CGL_EllipsoidPatched.h>
#include <SPlanetDesc.h>

class CMond : public CGL_EllipsoidPatched
{
    public:

        CMond();

        const SPlanetDesc* mPlanetDesc;

        float mUmlauf;
        float mRotation;
        CVector3<double> mScreenKoor;

        void SaveMatrixes(void);
        void GetScreenKoor(CVector3<float>* Vert);
        void InitOrbit(float radiusX, float radiusY);
        

        void Delete();
        void Umlauf(bool r, bool Retrograd);
        void Rotation(bool r, bool Retrograd);
        


        double mModelMatrix[16];
        double mProjectionMatrix[16];
        int mViewport[4];
        CGL_Ellipse mOrbit;
};

#endif

