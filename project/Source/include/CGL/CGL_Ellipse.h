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

#ifndef CGL_ELLIPSE_H
#define CGL_ELLIPSE_H

#include <CGL_Object.h>
#include <Math/CVector3T.h>

class CGL_Ellipse : public CGL_Object
{
    public:

        void MakeObject();

        CVector3<float> mOrigin;
        int mSegments;
        float mRadiusX;
        float mRadiusY;
};

#endif
