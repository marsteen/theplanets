#ifndef CGL_Mouse_H
#define CGL_Mouse_H

#include <Math/CVector3T.h>

class CGL_Mouse : public CVector3<int>
{
    public:

        CGL_Mouse()
        {
            mState[0] = 0;
            mState[1] = 0;
            mState[2] = 0;
            mState[3] = 0;
            mButton = 0;
        }


        int mButton;
        int mState[4];
};

#endif
