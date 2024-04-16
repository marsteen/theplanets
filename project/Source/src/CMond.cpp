#include <CMond.h>


CMond::CMond()
{
    mUmlauf = 0.0; //rand() % 360;
    mRotation = rand() % 360;
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
