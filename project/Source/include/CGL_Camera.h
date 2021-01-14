//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_Camera.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_CAMERA_H
#define CGL_CAMERA_H

#include <CVector3T.h>

class CGL_Camera
{
    public:

        CGL_Camera()
        {
            Reset();
        }


        void Reset(void);

        void operator=(CGL_Camera& cam)
        {
            mStandort = cam.mStandort;
            mVispoint = cam.mVispoint;
            mUpvector = cam.mUpvector;
        }


        void LookAt(void);

        CVector3<float> mStandort;
        CVector3<float> mVispoint;
        CVector3<float> mUpvector;
};

#endif
