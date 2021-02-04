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
    mFullscreen        = false;
	//mMouseFaktor       = 10.0;
	mInitFlag          = false;
	mSdlWindow         = NULL;
	mLeftMouseButton   = false;
	mRightMouseButton  = false;
	mMiddleMouseButton = false;
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

/*
			case GL_TABLE_TOO_LARGE:

				ErrText = "OpenGL Error: GL_TABLE_TOO_LARGE";
				break;
*/
		}
		if (Titel != NULL)
		{
			ErrString = string(Titel) + " " + ErrText;
		}
		else
		{
			ErrString = ErrText;
		}

/*
		GlobalDebug("**********************************************************", DBG_INIT);
    GlobalDebug(ErrString.c_str(), DBG_INIT);
    GlobalDebug("**********************************************************", DBG_INIT);
*/

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

/*
			case GL_TABLE_TOO_LARGE:

				ErrText = "OpenGL Error: GL_TABLE_TOO_LARGE";
				break;
*/
		}
		if (Titel != NULL)
		{
			ErrString = string(Titel) + " " + ErrText;
		}
		else
		{
			ErrString = ErrText;
		}
/*
		GlobalDebug("**********************************************************", DBG_INIT);
    GlobalDebug(ErrString.c_str(), DBG_INIT);
    GlobalDebug("**********************************************************", DBG_INIT);
*/

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
	  /*
		if (ArgStr[i] == "-w800x600")
		{
			mFullscreen = false;
			mXres = 800;
			mYres = 600;
		}
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
	mFullscreen = true;
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
  cout << "CSDL_App::ParseWinArgs START Commandline=" << Commandline << endl;
    
  vector<string> SplitResult;

  mFullscreen = true;

  NStringTool::Split(Commandline, &SplitResult, ' ');

  if (SplitResult.size() == 0)
  {
		SplitResult.push_back(Commandline);
	}

  //GlobalDebugT("Commandline=", Commandline, DBG_INIT);
  //GlobalDebugT("args=", SplitResult.size(), DBG_INIT);



	ParseArgVec(SplitResult);
	/*
  for (int i = 0; i < SplitResult.size(); i++)
  {
		ParseArg(SplitResult[i]);
  }
  */
  
  cout << "CSDL_App::ParseWinArgs OK" << endl;
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
/*
  static int t;
  cout << "timer:"  << t << endl;
  t++;
*/

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
    cout << "CSDL_App::InitGame" << endl;
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
    cout << "CSDL_App::Init Start" << endl;
    bool r = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        //GlobalDebug("***** SDL konnte nicht initialisiert werden", DBG_INIT);
        r = false;
    }
    //    SDL_ShowCursor(false); // Mousecursor verstecken
    
    cout << "CSDL_App::Init OK" << endl;
    
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
	mWindowWidth  = w;
	mWindowHeight = h;

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//glViewport(0, 0, mWindowWidth, mWindowHeight);
	mAspect = ((float) mWindowWidth) / mWindowHeight;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
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
    mAspect = (float) mXres / mYres;
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
    mAspect = (float) mXres / mYres;
    glViewport(0, 0, mXres, mYres);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, mAspect, 0.1, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
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
    
    cout << "CSDL_App::InitScreen START" << endl;
    
    bool r = true;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mXres = 1920;
	mYres = 1080;

/*
	mSdlWindow = SDL_CreateWindow("theplanets",
                          0,
                          0,
                          mXres, 
                          mYres,
                          SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
*/

	mSdlWindow = SDL_CreateWindow("theplanets",
                          0,
                          0,
                          mXres, 
                          mYres,
                          SDL_WINDOW_OPENGL);


	SDL_GLContext maincontext = SDL_GL_CreateContext(mSdlWindow);

	{
		SDL_DisplayMode DisplayMode;
		SDL_GetCurrentDisplayMode(0, &DisplayMode);

		mXres = DisplayMode.w;
		mYres = DisplayMode.h;
	}


    if (mSdlWindow == NULL)
    {
        //GlobalDebug("***** mSdlWindow == NULL", DBG_INIT);
    }
    SDL_GL_SetSwapInterval(1);

    SetViewport(mXres, mYres);
    mInitFlag = true;

    if (mSdlWindow == NULL)
    {
        //GlobalDebugT("Fehler beim Umschalten der Aufloesung ", SDL_GetError(), DBG_INIT);
        r = false;
    }
    InitGame();
    //mTimer = SDL_AddTimer(100, sTimerCallback, this);
    
    cout << "CSDL_App::InitScreen OK" << endl;

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
// METHODE       : ParseMouseRel
//
//
//
// ---------------------------------------------------------------------------

void CSDL_App::ParseMouseRel(int xrel, int yrel)
{
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
    switch(event.type)
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
        break;

      case SDL_KEYUP:

        ParseKeys(event.key.keysym.sym, false);
        break;

			case SDL_MOUSEMOTION:
			{
				int xrel = event.motion.xrel;
				int yrel = event.motion.yrel;
				ParseMouseRel(xrel, yrel);


			}
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

      case SDL_QUIT:

          FinishGame();
          SDL_Quit();
          exit(0);
          //done = true;
          break;

      default:

        break;
    }   // End switch
  }   // End while
}



