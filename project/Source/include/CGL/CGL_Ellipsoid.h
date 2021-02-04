//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_Ellipsoid.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_ELLIPSOID_H
#define CGL_ELLIPSOID_H

#include <Math/cvector3T.h>
#include <CGL_Patch.h>

class CGL_Ellipsoid : public CGL_Patch
{
    public:

        void CreateEllipsoid(int Sseg, float Srad, int Tseg, float Trad, float* DiffuseMaterial);

        void DrawWireFrame(void);

        void MakeObject(void);

        CGL_Ellipsoid(void);

        float mXrot;
        float mYrot;


    protected:

        void SetVertex(CVector3<float>* Origin, CVector3<float>* cf);

        int mTCircleSegs;
        int mSCircleSegs;

        float mDiffuseMaterial[4];
        float mAmbientMaterial[4];
        bool mUseTexture;
};


#endif // CGL_ELLIPSOID
