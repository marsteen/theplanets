//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_Patch.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_PATCH_H
#define CGL_PATCH_H

#include <Math/CVector3T.h>
#include <CGL_Object.h>
#include <CGL_MatObject.h>

class CGL_Patch : public CGL_Object, public CGL_MatObject
{
    public:

        void MakePatch(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT);
        void MakePatchDrawElements(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT);
        void MakePatchDrawElementsST(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT);
        void MakePatchNotTexture(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT);
        void MakePatchPoints(float StartS, float StartT, float StepS, float StepT, int PsegS, int PsegT);

    protected:

        void SetVertex(CVector3<float>* Origin, CVector3<float>* cf);
        void SetSphereVertex(CVector3<float>* Origin, CVector3<float>* cf);
        float getDemValueAngles(float AngleS, float AngleT) const;

        float mSCircleRad;
        float mTCircleRad;
        const CDataRect* mDEM;
};

#endif
