//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_Disk.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <Math/CVector3T.h>
#include <GLinclude.h>
#include <CGL_Object.h>
#include <CGL_Disk.h>
#include <cmath>

using namespace std;


void CGL_Disk::MakeObject()
{
    CVector3<float> CirclePoint;
    CVector3<float> Normal;
    double Alpha = 0;
    double AlphaPlus = DEG_TO_RAD(360.0 / mSegments);

    glBindTexture(GL_TEXTURE_2D, (int)mTexHandle);

    CirclePoint.x = mRadius + mOrigin.x;
    CirclePoint.y = 0;
    CirclePoint.z = mOrigin.z;

    glBegin(GL_TRIANGLE_FAN);
    //glTexCoord1f(1.0);
    glTexCoord2f(1.0, 0.0);

    SetNormalVertex(&CirclePoint, &mOrigin);
    glVertex3fv(mOrigin.v());


    for (int i = 0; i <= mSegments; i++)
    {
        CirclePoint.x = (cos(Alpha) * mRadius) + mOrigin.x;
        CirclePoint.y = (sin(Alpha) * mRadius) + mOrigin.y;
        SetNormalVertex(&mOrigin, &CirclePoint);
        glTexCoord2f(0.0, 0.0);
        //glTexCoord1f(0,0);

        glVertex3fv(CirclePoint.v());
        Alpha -= AlphaPlus;
    }
    glEnd();
}

