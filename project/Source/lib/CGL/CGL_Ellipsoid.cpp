//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_Ellipsoid.cpp
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
#include <GLinclude.h>
#include <math.h>
#include <CGL_Ellipsoid.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Ellipsoid
// Methode:	  CreateEllipsoid
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Ellipsoid::CreateEllipsoid(int Sseg, float Srad, int Tseg, float Trad, const float* DiffuseMaterial, const CDataRect* dem)
{
    mTCircleSegs = Tseg;
    mTCircleRad = Trad;
    mSCircleSegs = Sseg;
    mSCircleRad = Srad;
    mDEM = dem;

    for (int i = 0; i < 4; i++)
    {
        mDiffuseMaterial[i] = DiffuseMaterial[i];
        mAmbientMaterial[i] = DiffuseMaterial[i];
    }
    mUseTexture = false;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Ellipsoid
// Methode:   CGL_Ellipsoid
//
//
//---------------------------------------------------------------------------

CGL_Ellipsoid::CGL_Ellipsoid()
{
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Ellipsoid
// Methode:   DrawWireFrame
//
//
//---------------------------------------------------------------------------

void CGL_Ellipsoid::DrawWireFrame()
{
    glPushMatrix();

    glRotatef(180, 1.0, 0.0, 0.0);

    float AngleStepS = (M_PI * 2) / mSCircleSegs;
    float AngleStepT = (M_PI) / mTCircleSegs;

    float AngleS1 = 0.0;

    CVector3<float> Origin(0, 0, 0);

    for (int s = 0; s < mSCircleSegs; s++)
    {
        glBegin(GL_LINE_STRIP);

        float AngleT = (M_PI / 2);
        float AngleS2 = AngleS1 + AngleStepS;

        for (int t = 0; t < mTCircleSegs+1; t++)
        {
            CVector3<float> vert;

            vert.x = cos(AngleT) * mSCircleRad;
            vert.y = sin(AngleT) * mTCircleRad;
            vert.z = 0;

            vert.RotationXZ(&Origin, sin(AngleS1), cos(AngleS1));

            SetSphereVertex(&Origin, &vert);

            vert.x = cos(AngleT) * mSCircleRad;
            vert.y = sin(AngleT) * mTCircleRad;
            vert.z = 0;

            vert.RotationXZ(&Origin, sin(AngleS2), cos(AngleS2));

            SetSphereVertex(&Origin, &vert);

            AngleT -= AngleStepT;
        }

        AngleS1 += AngleStepS;

        glEnd();
    }

    glPopMatrix();
}


float CGL_Ellipsoid::getDemValue(float s, float t) const
{   
    const uint16_t* demData = (uint16_t*) mDEM->mData;
    const int xko = mDEM->mWidth * s;
    const int yko = mDEM->mHeight * t;
    return float(demData[mDEM->mWidth * yko + xko]) / 1000.0f;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Ellipsoid
// Methode:   MakeObject
//
//
//---------------------------------------------------------------------------

void CGL_Ellipsoid::MakeObject()
{
    glBindTexture(GL_TEXTURE_2D, mTexHandle);
    float AngleStepS = (M_PI * 2) / mSCircleSegs;
    float AngleStepT = (M_PI) / mTCircleSegs;
    float TexCoordStepS = 1.0 / mSCircleSegs;
    float TexCoordStepT = 1.0 / mTCircleSegs;

    float AngleS1 = 0.0;
    float TexCoordS1 = 0.0;

    glPushMatrix();
    glRotatef(180, 1.0, 0.0, 0.0);
    CVector3<float> Origin(0, 0, 0);

    for (int s = 0; s < mSCircleSegs; s++)
    {
        glBegin(GL_TRIANGLE_STRIP);

        float AngleT = (M_PI / 2);
        float TexCoordT = 0;

        float AngleS2 = AngleS1 + AngleStepS;
        float TexCoordS2 = TexCoordS1 + TexCoordStepS;

        for (int t = 0; t < mTCircleSegs+1; t++)
        {
            CVector3<float> vert;

            const float rf1 =  (mDEM == nullptr) ? 0.0f : getDemValue(TexCoordS1, TexCoordT);
            vert.x = cos(AngleT) * (mSCircleRad + rf1);
            vert.y = sin(AngleT) * (mTCircleRad + rf1);
            vert.z = 0;
            vert.RotationXZ(&Origin, sin(AngleS1), cos(AngleS1));
            glTexCoord2f(TexCoordS1, TexCoordT);
            SetSphereVertex(&Origin, &vert);
            cout << "rf1=" << rf1 << endl;

            const float rf2 =  (mDEM == nullptr) ? 1.0f : getDemValue(TexCoordS2, TexCoordT);
            vert.x = cos(AngleT) * (mSCircleRad + rf2);
            vert.y = sin(AngleT) * (mTCircleRad + rf2);
            vert.z = 0;
            vert.RotationXZ(&Origin, sin(AngleS2), cos(AngleS2));
            glTexCoord2f(TexCoordS2, TexCoordT);
            SetSphereVertex(&Origin, &vert);

            AngleT -= AngleStepT;
            TexCoordT += TexCoordStepT;
        }

        AngleS1 += AngleStepS;
        TexCoordS1 += TexCoordStepS;

        glEnd();
    }

    glPopMatrix();
}
