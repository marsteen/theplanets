//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_MatObject.cpp
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
#include <GLinclude.h>
#include <math.h>

#include <Math/CVector3T.h>
#include <CGL_MatObject.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:		MatInit
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatInit()
{
    glPushMatrix();
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, mMat);
    glPopMatrix();
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:		Transform
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatTransform()
{
    glMultMatrixf(mMat);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:		MatRotateX
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatRotateX(GLfloat* mat, float angle)
{
    GLfloat mx[16];

    MatSetIdentity(mx);

    float cosA = cos(DEG_TO_RAD(angle));
    float sinA = sin(DEG_TO_RAD(angle));

    mx[5] = cosA;
    mx[6] = sinA;
    mx[9] = -sinA;
    mx[10] = cosA;

    glLoadMatrixf(mat);
    glMultMatrixf(mx);
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatRotateY(GLfloat* mat, float angle)
{
    GLfloat mx[16];

    MatSetIdentity(mx);

    float cosA = cos(DEG_TO_RAD(angle));
    float sinA = sin(DEG_TO_RAD(angle));

    mx[0] = cosA;
    mx[2] = -sinA;
    mx[8] = sinA;
    mx[10] = cosA;

    glLoadMatrixf(mat);
    glMultMatrixf(mx);
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatRotateZ(GLfloat* mat, float angle)
{
    GLfloat mx[16];

    MatSetIdentity(mx);

    float cosA = cos(DEG_TO_RAD(angle));
    float sinA = sin(DEG_TO_RAD(angle));

    mx[0] = cosA;
    mx[1] = sinA;
    mx[4] = -sinA;
    mx[5] = cosA;

    glLoadMatrixf(mat);
    glMultMatrixf(mx);
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatRotateX(float angle)
{
    MatRotateX(mMat, angle);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatRotateY(float angle)
{
    MatRotateY(mMat, angle);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatRotateZ(float angle)
{
    MatRotateZ(mMat, angle);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatCopy(GLfloat* SrcMat, GLfloat* DstMat)
{
    memcpy(DstMat, SrcMat, sizeof(GLfloat) * 16);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatRotateVector(CVector3<float>* v, float angle)
{
    GLfloat mx[16];

    MatSetIdentity(mx);

    float ca = cos(angle);
    float sa = sin(angle);
    float x = v->x;
    float y = v->y;
    float z = v->z;


    mx[0] = 1 + (1 - ca) * (x * x-1);
    mx[1] = -z * sa + (1 - ca) * x * y;
    mx[2] = y * sa + (1 - ca) * x * z;

    mx[4] = z * sa + (1 - ca) * x * y;
    mx[5] = 1 + (1 - ca) * (y * y - 1);
    mx[6] = -x * sa + (1 - ca) * y * z;

    mx[8] = -y * sa + (1 - ca) * x * z;
    mx[9] = x * sa + (1 - ca) * y * z;
    mx[10] = 1 + (1 - ca) * (z * z - 1);

    glLoadMatrixf(mMat);
    glMultMatrixf(mx);
    glGetFloatv(GL_MODELVIEW_MATRIX, mMat);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:		CalcRotationMatrix
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::CalcRotationMatrix(float mx[16], CVector3<float>* v, float angle)
{
    MatSetIdentity(mx);

    //float ca = cos(angle);
    //float sa = sin(angle);

    float c = cos(angle);
    float s = sin(angle);
    float u = 1 - c;

    float x = v->x;
    float y = v->y;
    float z = v->z;

/*
 *  mx[0]  = 1 + (1 - ca) * (x * x-1);
 *  mx[1]  = -z * sa + (1 - ca) * x * y;
 *  mx[2]  = y * sa + (1 - ca) * x * z;
 *
 *  mx[4]  = z * sa + (1 - ca) * x * y;
 *  mx[5]  = 1 + (1 - ca) * (y * y - 1);
 *  mx[6]  = -x * sa + (1 - ca) * y * z;
 *
 *  mx[8]  = -y * sa + (1 - ca) * x * z;
 *  mx[9]  = x * sa + (1 - ca) * y * z;
 *  mx[10] = 1 + (1 - ca) * (z * z - 1);
 */

    mx[0] = x * x * u + c;
    mx[4] = y * x * u - z * s;
    mx[8] = z * x * u + y * s;

    mx[1] = x * y * u + z * s;
    mx[5] = y * y * u + c;
    mx[9] = z * y * u - x * s;

    mx[2] = x * z * u - y * s;
    mx[6] = y * z * u + x * s;
    mx[10] = z * z * u + c;

/*
 *  mx[0] = (x * x) * u + c;
 *  mx[1] = y * x * u - z * s;
 *  mx[2] = z * x * u + y * s;
 *
 *  mx[4] = x * y * u + z * s;
 *  mx[5] = y * y * u + c;
 *  mx[6] = z * y * u - x * s;
 *
 *  mx[8] = x * z * u - y * s;
 *  mx[9] = y * z * u + x * s;
 *  mx[10] = z * z * u + c;
 */

/*
 *  mx[0]  = 1 + (1 - ca) * (x * x-1);
 *  mx[4]  = -z * sa + (1 - ca) * x * y;
 *  mx[8]  = y * sa + (1 - ca) * x * z;
 *
 *  mx[1]  = z * sa + (1 - ca) * x * y;
 *  mx[5]  = 1 + (1 - ca) * (y * y - 1);
 *  mx[9]  = -x * sa + (1 - ca) * y * z;
 *
 *  mx[2]  = -y * sa + (1 - ca) * x * z;
 *  mx[6]  = x * sa + (1 - ca) * y * z;
 *  mx[10] = 1 + (1 - ca) * (z * z - 1);
 */
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:		MatRotateVector
//
// Rotieren von Vektor v1 um Vektor v2
// angle: Winkel, um den rotiert wird (in Rad)
// Coutt: Anzahl der rotierenden Vektoren
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatRotateVector(CVector3<float>* v1, CVector3<float>* v2, float angle, int Count)
{
    CVector3<float> dv;
    float Mat[16];

    CalcRotationMatrix(Mat, v2, angle);

    for (int i = 0; i < Count; i++)
    {
        MatTransformVertex(Mat, v1 + i, &dv);
        v1[i] = dv;
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:		MatScale
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatScale(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat mx[16];

    MatSetIdentity(mx);

    mx[0] = x;
    mx[5] = y;
    mx[10] = z;

    glLoadMatrixf(mMat);
    glMultMatrixf(mx);
    glGetFloatv(GL_MODELVIEW_MATRIX, mMat);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:		MatScale
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatScale(GLfloat s)
{
    MatScale(s, s, s);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:		MatTranslate
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatTranslate(float x, float y, float z)
{
    GLfloat mx[16];

    MatSetIdentity(mx);

    mx[12] = x;
    mx[13] = y;
    mx[14] = z;

    glLoadMatrixf(mMat);
    glMultMatrixf(mx);
    glGetFloatv(GL_MODELVIEW_MATRIX, mMat);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:		MatApply
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatApply(GLfloat* mx)
{
    glLoadMatrixf(mx);
    glMultMatrixf(mMat);
    glGetFloatv(GL_MODELVIEW_MATRIX, mMat);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:   MatCopy
//
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatCopy(GLfloat* SrcMat)
{
    memcpy(mMat, SrcMat, sizeof(GLfloat) * 16);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatSetIdentity(GLfloat* mx)
{
    memset(mx, 0, sizeof(GLfloat) * 16);
    mx[0] = 1;
    mx[5] = 1;
    mx[10] = 1;
    mx[15] = 1;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatSetIdentity()
{
    MatSetIdentity(mMat);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_MatObject
// Methode:		MatTransformVertex
//
// Transformfieren eines Vectors durch eine Matrix in
// einen Zielvektor
//
// Mat : Transformationsmatrix
// sv  : Quellvektor
// dv  : Zielvektor
//
//---------------------------------------------------------------------------

void CGL_MatObject::MatTransformVertex(float Mat[16], CVector3<float>* sv, CVector3<float>* dv)
{
    dv->x = (Mat[0] * sv->x) + (Mat[4] * sv->y) + (Mat[8]  * sv->z) + Mat[12];
    dv->y = (Mat[1] * sv->x) + (Mat[5] * sv->y) + (Mat[9]  * sv->z) + Mat[13];
    dv->z = (Mat[2] * sv->x) + (Mat[6] * sv->y) + (Mat[10] * sv->z) + Mat[14];
}
