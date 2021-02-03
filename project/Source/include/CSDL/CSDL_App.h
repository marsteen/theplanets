//***************************************************************************
//
//
// @PROJECT  :	Basic SDL
// @VERSION  :	1.0
// @FILENAME :	CSdlApp.h
// @DATE     :	8.1.2015
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************


#ifndef CSDLAPP_H
#define CSDLAPP_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <string>

#include <CGL_Mouse.h>
#include <CGL_Camera.h>


// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
//
// ---------------------------------------------------------------------------

class CSDL_App
{
    public:

        CSDL_App();
        bool Init();
        void ParseArgs(int argc, char* argv[]);
        void ParseWinArgs(const char* Commandline);
        bool InitScreen();
        void EventLoop();
        void MainLoop();
        void Finish();
        virtual void Timer();
        virtual void GameLoop();
        virtual void InitGame();
        virtual void FinishGame();

        static void ShowOpenGLError(const char* Titel);
        
        int mActionFrequency;
        CGL_Mouse mMouse;
        CVector3<float> mLightPosition;
        CGL_Camera mCamera;
        bool mAnaglyph;

    protected:

        void StartProjectionView();
        void StartModelView();
        void StartModelView(int width, int height);
        void SetViewport(int w, int h);
        void SetupLight();
        void DrawGeodaesic();

        virtual void ParseArgVec(const std::vector<std::string>& ArgStr);
        void DisableKeyRepeat();
        bool GetVideoModes(int* FirstW, int* FirstH, int n);
        virtual bool ParseKeys(int key, bool down);
        virtual void ParseMouseRel(int xrel, int yrel);
        virtual void SetResolution(int w, int h);
        virtual void LeftMouseButtonAction(bool pressed) { }
        virtual void RightMouseButtonAction(bool pressed) { }
        virtual void MiddleMouseButtonAction(bool pressed) { }
        virtual void MouseWheel(bool up) { };

        void InitOpenGL(int w, int h);
        void HandleUserEvents(SDL_Event* event);


        SDL_Window*  mSdlWindow;
        bool         mFullscreen;
        int          mXres;
        int          mYres;
        int          mWindowWidth;
        int          mWindowHeight;
        float        mAspect;
        bool         mInitFlag;
        bool         mLeftMouseButton;
        bool         mRightMouseButton;
        bool         mMiddleMouseButton;

};

#endif
