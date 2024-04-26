#ifndef CPlanet_H
#define CPlanet_H

#include <vector>
#include <CGL_EllipsoidPatched.h>
#include <CG3DReslistInterface.h>
#include <CMond.h>


class CPlanet : public CGL_EllipsoidPatched
{
    public:

        CPlanet()
        {
            mSunTexHandles = NULL;
        }


        void LadeMonde(char** Monde);
        void Delete();
        void DrawMonde(bool AutoRotate, bool ShowOrbits, bool Retrograd, const SMoonColor* moonColorTable);
        void DrawMondeNames(CG3DReslistInterface* gi, SG3DcomData* MondName, int Language, const SMoonColor* moonColorTable);
        void GetMondScreenKoor();

        std::vector<CMond> mMonde;



        unsigned int* mSunTexHandles;

        //void GetScreenKoor(CVector3<float>* Vert, CVector3<double>* ScreenKoor);
};


#endif
