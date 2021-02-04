#ifndef CMond_H
#define CMond_h

#include <CGL_EllipsoidPatched.h>

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

#endif

