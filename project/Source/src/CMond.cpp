//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CMond.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <CMond.h>


CMond::CMond()
{
    mUmlauf = 0.0; //rand() % 360;
    mRotation = rand() % 360;
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CMond
// METHODE       : GetScreenKoor
//
//
//
// ---------------------------------------------------------------------------

void CMond::GetScreenKoor(CVector3<float>* Vert)
{
    float Zval;

    glPushMatrix();
    Rotation();

    gluProject(
        Vert->x, Vert->y, Vert->z,
        mModelMatrix,
        mProjectionMatrix,
        mViewport,
        &mScreenKoor.x, &mScreenKoor.y, &mScreenKoor.z);

    glReadPixels((int)mScreenKoor.x, (int)mScreenKoor.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Zval);

    //cout << "Zval=" << Zval << " ScreenKoor->z=" << mScreenKoor.z << endl;

    if (Zval < mScreenKoor.z - 0.0001)
    {
       mScreenKoor.z = 2;
    }
    glPopMatrix();
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : SaveMatrixes
//
//
//
// ---------------------------------------------------------------------------

void CMond::SaveMatrixes()
{
    glGetDoublev(GL_MODELVIEW_MATRIX, mModelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, mProjectionMatrix);
    glGetIntegerv(GL_VIEWPORT, mViewport);
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CMond
// METHODE       : InitOrbit
//
//
//
// ---------------------------------------------------------------------------

void CMond::InitOrbit(float radiusX, float radiusY)
{
    mOrbit.mRadiusX = radiusX;
    mOrbit.mRadiusY = radiusY;
    mOrbit.mSegments = 256;
    mOrbit.mOrigin.Set(0, 0, 0);
    mOrbit.Init();
}


void CMond::Delete()
{
    CGL_EllipsoidPatched::Delete();
    mOrbit.DeleteDisplayList();
}


void CMond::Umlauf(bool r, bool Retrograd)
{
    glRotatef(mUmlauf, 0.0, 1.0, 0.0);
    if (r)
    {
        if (Retrograd)
        {
            mUmlauf -= mPlanetDesc->mOrbitSpeed * 25;
        }
        else
        {
            mUmlauf += mPlanetDesc->mOrbitSpeed * 25;
        }
    }
}


void CMond::Rotation(bool r, bool Retrograd)
{
    glRotatef(mRotation, 0.0, 1.0, 0.0);
    if (r)
    {
        if (Retrograd)
        {
            mRotation -= mPlanetDesc->mRotSpeed;
        }
        else
        {
            mRotation += mPlanetDesc->mRotSpeed;
        }
    }
}


void CMond::Rotation()
{
    glRotatef(mRotation, 0.0, 1.0, 0.0);
}
