//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_Ellipse.cpp
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
#include <CGL_Ellipse.h>
#include <math.h>

using namespace std;

#if 1
void CGL_Ellipse::MakeObject()
{
    CVector3<float> CirclePoint;
    CVector3<float> Normal;
    float Alpha = 0.0f;
    float AlphaPlus = DEG_TO_RAD(360.0 / mSegments);

    CirclePoint.x = mRadiusX + mOrigin.x;
    CirclePoint.y = 0;
    CirclePoint.z = mOrigin.z;

    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(2.5f);


    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= mSegments; i++)
    {
        CirclePoint.x = (cos(Alpha) * mRadiusX) + mOrigin.x;
        CirclePoint.y = (sin(Alpha) * mRadiusY) + mOrigin.y;

        glVertex3fv(CirclePoint.v());
        Alpha += AlphaPlus;
    }
    glEnd();

    glPopMatrix();
}


#endif
