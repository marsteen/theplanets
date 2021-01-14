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

class CGL_Circle : public CGL_Object
{
    public:

        void MakeObject(void);

        CVector3<float> mOrigin;
        int mSegments;
        float mRadius;
};

#endif
