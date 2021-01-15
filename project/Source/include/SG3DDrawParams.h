//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	SG3DDrawParams.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef SG3DDrawParams_H
#define SG3DDrawParams_H

struct SG3DDrawParams
{
    SG3DDrawParams()
    {
        mPos.Set(0, 0);
        mScale.Set(1.0f, 1.0f);
    }


    CVector2<float> mPos;
    CVector2<float> mScale;
    float			mParentWidth;
    float			mParentHeight;
};

#endif
