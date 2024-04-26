//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_Circle.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_CIRCLE_H
#define CGL_CIRCLE_H

#include <CGL_Object.h>
#include <Math/CVector3T.h>

class CGL_Circle : public CGL_Object
{
    public:

        CGL_Circle();

        void SetCircleSegment(float alphaStart, float alphaEnd);
        void MakeObject() override;

        CVector3<float> mOrigin;
        int mSegments;
        float mRadius;
        float mAlphaStart;
        float mAlphaEnd;
};

#endif
