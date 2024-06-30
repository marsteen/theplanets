

#include <iostream>
#include <GLinclude.h>
#include <CGL_Circle.h>
#include <CGL_Gradnetz.h>

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : drawLatitudeRing
//
// ---------------------------------------------------------------------------

static void drawLatitudeRing(const CGL_Circle& latitudering, const float latitude)
{
    const float scale = cos(DEG_TO_RAD(latitude));
    const float trans = 20.02f * scale * tan(DEG_TO_RAD(latitude));

    glPushMatrix();
    glTranslatef(0, trans, 0);
    glScalef(scale, 1.0f, scale);
    latitudering.Draw();
    glPopMatrix();
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : DrawGradnetz
//
// ---------------------------------------------------------------------------

void CGL_Gradnetz::draw()
{    
    static CGL_Circle longitudering;
    static CGL_Circle latitudering;
    static bool isInit = false;
    static bool first = true;
    if (!isInit)
    {        
        longitudering.mOrigin.Set(0.0, 0.0, 0.0);
        longitudering.mRadius = 20.02;
        longitudering.mSegments = 100;
        longitudering.SetCircleSegment(5.0, 175.0);
        longitudering.Init();

        latitudering.mOrigin.Set(0.0, 0.0, 0.0);
        latitudering.mRadius = 20.02;
        latitudering.mSegments = 100;
        latitudering.Init();
        isInit = true;
    }
    glDisable(GL_LIGHTING);
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    

    const int longitudeCount = 18;
    const int latitudeCount = 4;

    //
    // draw longitudes
    //
    for (int i = 0; i < longitudeCount; i++)
    {
        if (i == 0)
        {
            // 0. longitude in CYAN
            glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
        }
        else
        {
            // other longitudes in BLUE
            glColor4f(0.0f, 0.2f, 1.0f, 1.0f);
        }
        glPushMatrix();
        glRotatef(360.0 / longitudeCount * i - 90.0, 0.0f, 1.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        longitudering.Draw();
        glPopMatrix();
    }

    //
    // draw latitudes
    //
    for (int i = -latitudeCount + 1; i < latitudeCount; i++)
    {
        const float latitude = 90.0 / latitudeCount * i;
        if (i == 0)
        {
            glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
        }
        else
        {
            glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
        }
        drawLatitudeRing(latitudering, latitude);
    }
    drawLatitudeRing(latitudering, -85.0f);
    drawLatitudeRing(latitudering,  85.0f);
    first = false;
}

