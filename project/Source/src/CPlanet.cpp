
#include <CPlanet.h>


static inline float sq2(float a)
{
    return a * a;
}


static float ellipseRadius(float rmax, float rmin, float angle)
{
    return (rmax * rmin) / sqrt(sq2(rmin) * sq2(sin(angle)) + sq2(rmax) * sq2(cos(angle)));
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CPlanet
// METHODE       : DrawMonde
//
//
//
// ---------------------------------------------------------------------------

void CPlanet::DrawMonde(bool AutoRotate, bool ShowOrbits, bool Retrograd, const SMoonColor* moonColorTable)
{
    float sWhiteColor[3] = { 1.0, 1.0, 1.0 };
    CVector3<float> Origin;

    Origin.Set(0, 0, 0);
    int m = 0;


    for (auto im = mMonde.begin(); im != mMonde.end(); ++im)
    {
        glDisable(GL_LIGHTING);
        glColor3fv(moonColorTable[m++].mColor);

        glPushMatrix();

        if (ShowOrbits)
        {
            im->mOrbit.Draw();
        }
        im->Umlauf(AutoRotate, Retrograd);
        glColor3fv(sWhiteColor);
        glEnable(GL_LIGHTING);


        float f = ellipseRadius(im->mPlanetDesc->mDistanceMax, im->mPlanetDesc->mDistanceMin, DEG_TO_RAD(im->mUmlauf));

        //cout << "f=" << f << endl;
        //glTranslatef(im->mPlanetDesc->mDistanceMin, 0, 0);
        glTranslatef(f, 0, 0);

        im->Rotation(AutoRotate, Retrograd);
        im->SaveMatrixes();

        im->DrawDisplayList();
        glPopMatrix();
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CPlanet
// METHODE       : GetMondScreenKoor
//
//
//
// ---------------------------------------------------------------------------

void CPlanet::GetMondScreenKoor()
{
    CVector3<float> Origin;

    Origin.Set(0, 0, 0);

    for (std::vector<CMond>::iterator im = mMonde.begin();
        im != mMonde.end();
        im++)
    {
        im->GetScreenKoor(&Origin);
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CPlanet
// METHODE       : DrawMondeNames
//
//
//
// ---------------------------------------------------------------------------

void CPlanet::DrawMondeNames(CG3DReslistInterface* gi, SG3DcomData* MondName, int Language, const SMoonColor* moonColorTable)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int m = 0;

    for (std::vector<CMond>::iterator im = mMonde.begin();
        im != mMonde.end();
        im++)
    {
        if (im->mScreenKoor.z < 1.0)
        {
            if (Language == ELANG_GERMAN)
            {
                MondName->mChrParam = im->mPlanetDesc->mNameGer;
            }
            else
            {
                MondName->mChrParam = im->mPlanetDesc->mNameEng;
            }


            MondName->mPos.x = (int)im->mScreenKoor.x;
            MondName->mPos.y = (int)im->mScreenKoor.y;

            float cr = moonColorTable[m].mColor[0] * 1.5;
            float cg = moonColorTable[m].mColor[1] * 1.5;
            float cb = moonColorTable[m].mColor[2] * 1.5;
            if (cr > 1.0)
            {
                cr = 1.0;
            }
            if (cg > 1.0)
            {
                cg = 1.0;
            }
            if (cb > 1.0)
            {
                cb = 1.0;
            }

            glColor3f(cr, cg, cb);
            gi->SendCommand(EG3DcomDrawString, MondName);
        }
        m++;
    }

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}
