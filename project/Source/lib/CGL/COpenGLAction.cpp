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

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <COpenGL.h>
#include <CGL_GLU_Sphere.h>
#include <CGL_Ellipsoid.h>

using namespace std;

extern CGL_GLU_Sphere* gGluSphere;

void COpenGL::Action()
{
    static float sYrot;
    static float s = 1.0;

    GLfloat WhiteMaterial[] = { 1.0, 1.0, 1.0, 1.0 };

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    StartModelView();

    mCamera.LookAt();


    glMaterialfv(GL_FRONT, GL_DIFFUSE, WhiteMaterial);

    glRotatef(sYrot, 0.0, 1.0, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    //gGluSphere->MakeObject();
    gErde->Draw();

    sYrot += 0.1;


    glFlush();
    glutSwapBuffers();
}
