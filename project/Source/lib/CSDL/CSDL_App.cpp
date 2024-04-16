//***************************************************************************
//
//
// @PROJECT  :	Basic SDL
// @VERSION  :	1.0
// @FILENAME :	CSDL_App.cpp
// @DATE     :	8.1.2015
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************


#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif


#include <GLinclude.h>
#include <SDL2/SDL.h>
#include <NStringTool.h>
#include <CSDL/CSDL_App.h>

using namespace std;


// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : CSDL_App
//
//
//
// ---------------------------------------------------------------------------

CSDL_App::CSDL_App()
{
    mFullscreen = false;
    //mMouseFaktor       = 10.0;
    mInitFlag = false;
    mSdlWindow = NULL;
    mLeftMouseButton = false;
    mRightMouseButton = false;
    mMiddleMouseButton = false;
    mKeyState = 0;
}

//---------------------------------------------------------------------------
//
// METHODE       : GlobalShowOpenGLError
//
// KLASSE        : global
//
//---------------------------------------------------------------------------

void GlobalShowOpenGLError(const char* Titel)
{
    int GlError = glGetError();

    if (GlError != GL_NO_ERROR)
    {
        std::string ErrString;
        const char* ErrText = "?";


        switch (GlError)
        {
            case GL_INVALID_ENUM:

                ErrText = "OpenGL Error: GL_INVALID_ENUM";
                break;


            case GL_INVALID_VALUE:

                ErrText = "OpenGL Error: GL_INVALID_VALUE";
                break;

            case GL_INVALID_OPERATION:

                ErrText = "OpenGL Error: GL_INVALID_OPERATION";
                break;

            case GL_STACK_OVERFLOW:

                ErrText = "OpenGL Error: GL_STACK_OVERFLOW";
                break;

            case GL_STACK_UNDERFLOW:

                ErrText = "OpenGL Error: GL_STACK_UNDERFLOW";
                break;

            case GL_OUT_OF_MEMORY:

                ErrText = "OpenGL Error: GL_OUT_OF_MEMORY";
                break;

        }
        if (Titel != NULL)
        {
            ErrString = string(Titel) + " " + ErrText;
        }
        else
        {
            ErrString = ErrText;
        }
    }
}

//---------------------------------------------------------------------------
//
// METHODE       : ShowOpenGLError
//
// KLASSE        : CSDL_App
//
//---------------------------------------------------------------------------

void CSDL_App::ShowOpenGLError(const char* Titel)
{
    int GlError = glGetError();

    if (GlError != GL_NO_ERROR)
    {
        std::string ErrString;
        const char* ErrText = "?";


        switch (GlError)
        {
            case GL_INVALID_ENUM:

                ErrText = "OpenGL Error: GL_INVALID_ENUM";
                break;


            case GL_INVALID_VALUE:

                ErrText = "OpenGL Error: GL_INVALID_VALUE";
                break;

            case GL_INVALID_OPERATION:

                ErrText = "OpenGL Error: GL_INVALID_OPERATION";
                break;

            case GL_STACK_OVERFLOW:

                ErrText = "OpenGL Error: GL_STACK_OVERFLOW";
                break;

            case GL_STACK_UNDERFLOW:

                ErrText = "OpenGL Error: GL_STACK_UNDERFLOW";
                break;

            case GL_OUT_OF_MEMORY:

                ErrText = "OpenGL Error: GL_OUT_OF_MEMORY";
                break;

        }
        if (Titel != NULL)
        {
            ErrString = string(Titel) + " " + ErrText;
        }
        else
        {
            ErrString = ErrText;
        }
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : ParseArgVec
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::ParseArgVec(const vector<string>& ArgStr)
{
    for (int i = 0; i < ArgStr.size(); i++)
    {
        if (ArgStr[i] == "-fullscreen")
        {
            mFullscreen = true;
        }

        /*
         * if (ArgStr[i] == "-w800x600")
         * {
         *    mFullscreen = false;
         *    mXres = 800;
         *    mYres = 600;
         * }
         */
    }
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : ParseArgs
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::ParseArgs(int argc, char* argv[])
{
    mFullscreen = false;
    vector<string> ArgVec;

    for (int i = 1; i < argc; i++)
    {
        string ArgStr = string(argv[i]);
        ArgVec.push_back(ArgStr);
    }
    ParseArgVec(ArgVec);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : ParseWinArgs
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::ParseWinArgs(const char* Commandline)
{
    vector<string> SplitResult;

    mFullscreen = false;
    NStringTool::Split(Commandline, &SplitResult, ' ');

    if (SplitResult.size() == 0)
    {
        SplitResult.push_back(Commandline);
    }

    ParseArgVec(SplitResult);
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : GameLoop
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::GameLoop()
{
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       :
//
//
//
// ---------------------------------------------------------------------------

static Uint32 sTimerCallback(Uint32 interval, void* param)
{
    CSDL_App* SdlApp = (CSDL_App*) param;
    SdlApp->Timer();
    return interval;
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : Timer
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::Timer()
{
    GameLoop();
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : SetResolution
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::SetResolution(int w, int h)
{
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : InitGame
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::InitGame()
{
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : FinishGame
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::FinishGame()
{
    SDL_ShowCursor(true);
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       :
//
//
//
// ---------------------------------------------------------------------------

bool CSDL_App::Init()
{
    bool r = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "***** SDL konnte nicht initialisiert werden" << endl;
        r = false;
    }
    //    SDL_ShowCursor(false); // Mousecursor verstecken
    return r;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : SetViewport
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::SetViewport(int w, int h)
{
    mWindowWidth = w;
    mWindowHeight = h;

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //glViewport(0, 0, mWindowWidth, mWindowHeight);
    mAspect = ((float)mWindowWidth) / mWindowHeight;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}


//---------------------------------------------------------------------------
//
// Klasse:    COpenGL
// Methode:   StartProjectionView
//
//
//---------------------------------------------------------------------------

void CSDL_App::StartProjectionView()
{
    glViewport(0, 0, mXres, mYres);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, mXres, 0.0, mYres);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
}


//---------------------------------------------------------------------------
//
// Klasse:    CSDL_App
// Methode:   StartModelView
//
//
//---------------------------------------------------------------------------

void CSDL_App::StartModelView()
{
    mAspect = (float)mXres / mYres;
    glViewport(0, 0, mXres, mYres);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, mAspect, 0.1, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}


//---------------------------------------------------------------------------
//
// Klasse:    CSDL_App
// Methode:   StartModelView
//
//
//---------------------------------------------------------------------------

void CSDL_App::StartModelView(float near, float far)
{
    mAspect = (float)mXres / mYres;
    glViewport(0, 0, mXres, mYres);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, mAspect, 0.1, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}


//---------------------------------------------------------------------------
//
// Klasse:    CSDL_App
// Methode:   AppName
//
//
//---------------------------------------------------------------------------

const char* CSDL_App::AppName() const
{
    return "The Planets";
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : InitScreen
//
//
//
// ---------------------------------------------------------------------------

bool CSDL_App::InitScreen()
{
    bool r = true;

#ifdef _WIN32
    SetProcessDPIAware();
#endif

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_DisplayMode DisplayMode;
    SDL_GetCurrentDisplayMode(0, &DisplayMode);

    if (mFullscreen)
    {
        mXres = DisplayMode.w;
        mYres = DisplayMode.h;
        mSdlWindow = SDL_CreateWindow(
            AppName(),
            0,
            0,
            mXres,
            mYres,
            SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
    }
    else
    {
        mXres = DisplayMode.w * 0.75f;
        mYres = DisplayMode.h * 0.75f;


        mSdlWindow = SDL_CreateWindow(
            AppName(),
            100,
            100,
            mXres,
            mYres,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    }

    SDL_GLContext maincontext = SDL_GL_CreateContext(mSdlWindow);

    if (mSdlWindow == NULL)
    {
        std::cout << "***** mSdlWindow == NULL" << std::endl;
    }
    SDL_GL_SetSwapInterval(1);

    SetViewport(mXres, mYres);
    mInitFlag = true;

    if (mSdlWindow == NULL)
    {
        std::cout << "***** Fehler beim Umschalten der Aufloesung " << SDL_GetError() << std::endl;
        r = false;
    }
    InitGame();

    return r;
}


// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : DisableKeyRepeat
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::DisableKeyRepeat()
{
    //SDL_EnableKeyRepeat(0, 0);
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : ParseKeys
//
//
//
// ---------------------------------------------------------------------------

bool CSDL_App::ParseKeys(int key, bool down)
{
    return true;
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : MainLoop
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::MainLoop()
{
    while (1)
    {
        Uint32 StartTime = SDL_GetTicks();
        EventLoop();
        GameLoop();

        Uint32 EndTime = SDL_GetTicks();
        int DelayTime = 20 - (EndTime - StartTime);
        if (DelayTime > 0)
        {
            //cout << "DelayTime=" << DelayTime << endl;
            SDL_Delay(DelayTime);
        }
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : CheckCtrlKeys
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::CheckCtrlKeys(int keysym, bool down)
{
    switch (keysym)
    {
        case SDLK_RCTRL:

            if (down)
            {
                mKeyState |= EKeyFlag::CTRL_RIGHT;
            }
            else
            {
                mKeyState &= ~EKeyFlag::CTRL_RIGHT;
            }
            break;

        case SDLK_LCTRL:

            if (down)
            {
                mKeyState |= EKeyFlag::CTRL_LEFT;
            }
            else
            {
                mKeyState &= ~EKeyFlag::CTRL_LEFT;
            }
            break;
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CSDL_App
// METHODE       : EventLoop
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::EventLoop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_USEREVENT:

                //HandleUserEvents(&event);
                break;

            case SDL_KEYDOWN:

                if (!ParseKeys(event.key.keysym.sym, true))
                {
                    FinishGame();
                    SDL_Quit();
                    exit(0);
                }
                CheckCtrlKeys(event.key.keysym.sym, true);
                break;

            case SDL_KEYUP:

                ParseKeys(event.key.keysym.sym, false);
                CheckCtrlKeys(event.key.keysym.sym, false);
                break;

            case SDL_MOUSEMOTION:
                MouseMotion(
                    event.motion.x,
                    event.motion.y,
                    event.motion.xrel,
                    event.motion.yrel);
                break;

            case SDL_MOUSEWHEEL:

                MouseWheel(event.wheel.y < 0);
                break;


            case SDL_MOUSEBUTTONDOWN:

                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    mLeftMouseButton = true;
                    LeftMouseButtonAction(true);
                }
                else
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    mRightMouseButton = true;
                    RightMouseButtonAction(true);
                }
                else
                if (event.button.button == SDL_BUTTON_MIDDLE)
                {
                    mMiddleMouseButton = true;
                    MiddleMouseButtonAction(true);
                }

                // Handle mouse clicks here.
                break;

            case SDL_MOUSEBUTTONUP:

                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    mLeftMouseButton = false;
                    LeftMouseButtonAction(false);
                }
                else
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    mRightMouseButton = false;
                    RightMouseButtonAction(false);
                }
                else
                if (event.button.button == SDL_BUTTON_MIDDLE)
                {
                    mMiddleMouseButton = false;
                    MiddleMouseButtonAction(false);
                }
                break;

            case SDL_WINDOWEVENT:

                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) //SDL_WINDOWEVENT_RESIZED)
                {
                    mXres = event.window.data1;
                    mYres = event.window.data2;
                    SetViewport(mXres, mYres);
                    SetResolution(mXres, mYres);

                    //logFileStderr("MESSAGE:Resizing window...\n");
                    //resizeWindow(m_event.window.data1, m_event.window.data2);
                }
                break;

            case SDL_QUIT:

                FinishGame();
                SDL_Quit();
                exit(0);
                //done = true;
                break;

            default:

                break;
        }   // End switch
    }       // End while
}


// ---------------------------------------------------------------------------
//
// METHODE       : SetupLighting
//
// KLASSE        : CSDL_App
//
// ---------------------------------------------------------------------------

void CSDL_App::SetupLighting()
{
    GLfloat Position1[] = { -3000.0, 0.0, 6000.0, 0, 0 };

    GLfloat matSpecular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat matShininess[] = { 30.0 };

    GLfloat WhiteLight[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat LightAmbient[] = { 0.2, 0.2, 0.2, 1.0 };

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

    mLightPosition.Set(Position1[0], Position1[1], Position1[2]);

    glLightfv(GL_LIGHT0, GL_POSITION, Position1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, WhiteLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WhiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glEnable(GL_NORMALIZE);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbient);


    //glEnable(GL_DEPTH_TEST);

    // Rueckseiten der Polygone nicht zeichnen
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
