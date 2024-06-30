//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_KraterCircle.cpp
// @DATE     :	30.1.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <GLinclude.h>
#include <CGL_Circle.h>
#include <CGL_KraterCircle.h>

static float offset = 1.0;

// ---------------------------------------------------------------------------
//
// KLASSE        : CGL_KraterCircle
// METHODE       : draw
//
// ---------------------------------------------------------------------------

void CGL_KraterCircle::draw(const SLabel& label)
{    
    static CGL_Circle kraterCircle;
    static bool isInit = false;
    if (!isInit)
    {        
        kraterCircle.mOrigin.Set(0.0, 0.0, 0.0);
        kraterCircle.mRadius = 0.1;
        kraterCircle.mSegments = 64;
        kraterCircle.Init();
        isInit = true;
    }
    glDisable(GL_LIGHTING);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f); 
    const float sf = label.mDiameter * 0.053f; 

    glPushMatrix();
    glRotatef(-90.0 + label.mLongDeg - 2.8, 0.0, 1.0, 0.0);
    glRotatef(90.0 - label.mLatiDeg, 1.0, 0.0, 0.0);
    glTranslatef(0, 20.002, 0);
    glScalef(sf, 1.0, sf);
    kraterCircle.Draw();
    glPopMatrix();
}

//Archimedes: 81.04 * x = 4.3
//            x = 4.3 / 81.04

void CGL_KraterCircle::drawAllCircles(const std::list<SLabel>& labelList)
{    

    int i = 0;
    //glDisable(GL_DEPTH_TEST);
    for (auto it = labelList.begin(); it != labelList.end(); it++)
    {
        //if ((it->mLabel == "Pallas") || (it->mLabel == "Godin") || (it->mLabel == "Dembowski"))
        //if (it->mLabel == "Pallas")
        {
            draw(*it);
        }
    }
    //offset += 0.001;
    //std::cout << "offset=" << offset << std::endl;

}



