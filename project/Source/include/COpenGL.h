//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	COpenGL.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef COPENGL_H
#define COPENGL_H

#include <CVector3T.h>
#include <CGL_Camera.h>
#include <CGL_Mouse.h>

class COpenGL
{
    public:

        bool InitWindowGLUT(int argc, char** argv, const char* WindowName, int width, int height, bool Fullscreen);
        void Action(void);
        void MouseButtonAction(void);
        void MouseMotionAction(void);
        void KeyboardAction(unsigned char key);
        void StartModelView(void);
        void StartModelView(float near, float far);
        void StartProjectionView(void);
        void SaveGLStrings(char* filename);
        void InitGLUTCallback(int fq);
        unsigned int* CreateSplitTextures(std::string& TextureFile, int XPatches, int YPatches);
        void SetViewport(int w, int h);
        void ViewportAction(int w, int h);


        int mActionFrequency;
        CGL_Mouse mMouse;
        CVector3<float> mLightPosition;
        CGL_Camera mCamera;
        bool mAnaglyph;

    protected:

        int mWindowHandle;
        int mWidth;
        int mHeight;
        float mAspect;



        void SetupLighting(void);
        void SetPixelFormatDescriptorBitmap(void);
};

#endif
