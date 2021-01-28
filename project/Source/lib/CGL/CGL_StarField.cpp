//***************************************************************************
//
//
// @PROJECT  :    Diercke Globus 4.0
// @VERSION  :    4.0
// @FILENAME :    CGL_StarField.cpp
// @DATE     :    18.8.2014
//
// @AUTHOR   :    Martin Steen
// @EMAIL    :    martin.steen@ksti.de
//
//
//***************************************************************************

#include <math.h>
#include <GLinclude.h>
#include <CRandom.h>
#include <CGL_StarField.h>



using namespace std;

// x2 + y2 + z2 = r2;
// z = sqrt
// http://matheplanet.com/matheplanet/nuke/html/viewtopic.php?rd2&topic=31865&start=0#p222570

#define NFIELDS		32

#define MAXSTAR		1.2
void CGL_StarField::MakeObject()
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);

    for (int n = 0; n < NFIELDS; n++)
    {
        float ps = CRandom<float>::Get(0.5, MAXSTAR) * 2.0f; //GlobalRetinaScaleFactor();
        float col = ps / MAXSTAR / 1.3;

        glColor3f(col, col, col);
        glPointSize(ps);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glBegin(GL_POINTS);
        for (int i = 0; i < mStars / NFIELDS; i++)
        {
            CVector3<float> vstar;

            double Alpha = CRandom<double>::Get(0, M_PI * 2);
            double Beta = acos(CRandom<double>::Get(-1.0, 1.0));

            vstar.x = cos(Alpha) * sin(Beta);
            vstar.y = sin(Alpha) * sin(Beta);
            vstar.z = sin(Beta);

            vstar.x = CRandom<float>::Get(-1.0, 1.0);
            vstar.y = CRandom<float>::Get(-1.0, 1.0);
            vstar.z = CRandom<float>::Get(-1.0, 1.0);

            if (vstar.Betrag() <= 1.0)
            {
                vstar.Normalize();
                vstar *= 500.0; // Radius of starfield

                glVertex3fv(vstar.v());
            }
        }
        glEnd();
    }
    glPointSize(1.0);
    glColor3f(1.0, 1.0, 1.0);
    glDisable(GL_BLEND);

    
}
