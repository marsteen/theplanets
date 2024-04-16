//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	COpenGLAction.cpp
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
#include <fstream>
#include <sstream>
#include <vector>

#include <GLinclude.h>
//#include <COpenGL.h>
#include <CGL_GLU_Sphere.h>
#include <CGL_Object.h>
#include <CGL_Disk.h>
#include "CGL_Ellipsoid.h"
#include "CG3DGlobals.h"
#include "CG3DReslistInterface.h"

#include "CGLApplication.h"

using namespace std;

extern CGLApplication gApp;

#if 0
// ---------------------------------------------------------------------------
//
// KLASSE        : COpenGL
// METHODE       : ViewportAction
//
//
//
// ---------------------------------------------------------------------------

void COpenGL::ViewportAction(int w, int h)
{
    //cout << "ViewportAction w=" << w << " h=" << h << endl;

    gApp.SetResolution(w, h);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : COpenGL
// METHODE       : Action
//
//
//
// ---------------------------------------------------------------------------

void COpenGL::Action()
{
    GLfloat weiss[] = { 1.0, 1.0, 1.0, 1.0 };

    glClearColor(0, 0, 0, 0);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClear(GL_COLOR_BUFFER_BIT);

    //StartProjectionView();
    //gApp.Draw2DObjects();


    StartModelView(0.1 / gApp.mScale, 30.0 / gApp.mScale);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, weiss);


    if (mAnaglyph)
    {
#define S_XV	2
#define V_XV	0.3


        float StandOrtX = mCamera.mStandort.x;
        float VispointX = mCamera.mVispoint.x;

        mCamera.mStandort.x -= S_XV;
        mCamera.mVispoint.x -= V_XV;

        for (int v = 0; v < 2; v++)
        {
            glLoadIdentity();
            glClear(GL_DEPTH_BUFFER_BIT);

            mCamera.LookAt();
            mCamera.mStandort.x += S_XV*2;
            mCamera.mVispoint.x += V_XV*2;

            glDisable(GL_BLEND);

            if (v == 1)
            {
                float rot[] = { 1.0, 0.0, 0.0, 1.0 };

                glColor3f(1.0, 0.0, 0.0);
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rot);
                glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_FALSE);
            }
            else
            {
                float cyan[] = { 0.0, 1.0, 1.0, 1.0 };
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
                glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_FALSE);
            }
            gApp.Draw3DObjects();
        }
        mCamera.mStandort.x = StandOrtX;
        mCamera.mVispoint.x = VispointX;
    }
    else
    {
        glLoadIdentity();
        glClear(GL_DEPTH_BUFFER_BIT);
        mCamera.LookAt();
        glDisable(GL_BLEND);
        gApp.Draw3DObjects();
    }
    gApp.Animate();


    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    StartProjectionView();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, weiss);

    gApp.ManageInterface(&mMouse);

    // glutSwapBuffers();
}


// ---------------------------------------------------------------------------
//
// KLASSE        : COpenGL
// METHODE       : MouseButtonAction
//
//
//
// ---------------------------------------------------------------------------

void COpenGL::MouseButtonAction()
{
    string ClickedName;

    //cout << "mMouse.mButton=" << mMouse.mButton << endl;

#if 0
    switch (mMouse.mButton)
    {
        case GLUT_LEFT_BUTTON:

            if (mMouse.mState[GLUT_LEFT_BUTTON] == GLUT_DOWN)
            {
                gApp.LeftMouseButtonDown();
            }
            else
            {
                //gSlider.mObject = NULL;
            }
            break;

        case GLUT_RIGHT_BUTTON:

            if (mMouse.mState[GLUT_RIGHT_BUTTON] == GLUT_DOWN)
            {
                gApp.RightMouseButtonDown();
            }
            break;

        case 3: // Mousewheel up

            if (mMouse.mState[3] == GLUT_DOWN)
            {
                gApp.MouseWheel(0);
            }
            break;

        case 4: // Mousewheel down

            if (mMouse.mState[4] == GLUT_DOWN)
            {
                gApp.MouseWheel(1);
            }
            break;
    }
#endif
}


// ---------------------------------------------------------------------------
//
// KLASSE        : COpenGL
// METHODE       : MouseMotionAction
//
//
//
// ---------------------------------------------------------------------------

void COpenGL::MouseMotionAction()
{
    //gSlider.mPos.x = mMouse.x;
    //gSlider.mPos.y = mMouse.y;
    static CVector2<int> MousePos;

    int dx = MousePos.x - mMouse.x;
    int dy = MousePos.y - mMouse.y;

    MousePos.x = mMouse.x;
    MousePos.y = mMouse.y;


#if 0
    if (mMouse.mState[GLUT_LEFT_BUTTON] == GLUT_DOWN)
    {
        gApp.MouseMotionLeft(dx, dy);

/*
 *      if (gSlider.mObject != NULL)
 *      {
 *          gG3Dinterface->SendCommand(EG3DcomSetChildPos, &gSlider);
 *      }
 */
    }
    else
    if (mMouse.mState[GLUT_RIGHT_BUTTON] == GLUT_DOWN)
    {
        gApp.MouseMotionRight(dx, dy);
    }
#endif

    //cout << "MouseMotionAction X=" << mMouse.x << " Y=" << mMouse.y << endl;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : COpenGL
// METHODE       : KeyboardAction
//
//
//
// ---------------------------------------------------------------------------

void COpenGL::KeyboardAction(unsigned char key)
{
    gApp.KeyboardAction(key);
}


#endif
