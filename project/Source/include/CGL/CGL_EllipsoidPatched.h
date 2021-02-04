
//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_Ellipsoid.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_Ellipsoid_H
#define CGL_Ellipsoid_H

#include <CGL_Ellipsoid.h>

class CGL_EllipsoidPatched : public CGL_Ellipsoid
{
    public:

        CGL_EllipsoidPatched()
        {
            mPhase = 0;
            mPhaseCount = 0;
            mSpeed = 0;
            mSpeedCount = 0;
            mTexHandleList = NULL;
        }


        void Delete(void);
        void SetMultiTextures(unsigned int* TexHandles, int PatchesX, int PatchesY);
        void SetMotionTextures(unsigned int* TexHandles, int PatchesX, int PatchesY);
        char* GetFilename(int name);
        void SetPatches(int PatchesX, int PatchesY);
        void DrawPatch(int n, unsigned int TexHandle, GLfloat Anisotropic);
        void DrawPatch(int n);
        void DrawWithoutTexture(int Mode);
        void DrawWithoutTexture(int Mode, int* SegList);
        void MakePatch(int PatchX, int PatchY);
        void DrawPointSegment(int PatchNr, int pfaktor = 16);
        void GetLongLati(int Name, float* Long, float* Lati);
        void GetSegmentLongLati(int SegmentNr, float* Long, float* Lati, float* ns, float* nt);

        void NextNumXY(int n, int* nx, int* ny);

        void MakeObject(void);
        void DrawSingleSegment(int SegmentNr, float Anisotropic);
        void Init(void);
        void Draw(void);

        void InitDisplayList(void);
        void DrawDisplayList(void);
        void DrawDisplayListMotion(void);

        unsigned int* mTexHandleList;

        //SAngleList*   mAngleList;
        void Animate(void);

        float mRotY;
        int mPhase;                 // Zaehler für Animationsphasen
        int mPhaseCount;            // Anzahl der Animationsphasen
        int mSpeed;
        int mSpeedCount;

    protected:

        int mPatchesX;
        int mPatchesY;
        int mNumPatches;
        int mPointsRS;
        int mPointsRT;
        float mStepRS;
        float mStepRT;
        float mStartS;
        float mStartT;
        float mWidthS;  // Weite in Grad (rad)
        float mHeightT; // Hoehe in Grad (rad)


        char** mTextureFiles;
};

#endif