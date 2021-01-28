//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	main.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifdef _WIN32
#include <windows.h>
#endif


#include <iostream>
#include <string>
#include <vector>



#include <GLinclude.h>

#include <math.h>
#include <CVector3T.h>
#include <COpenGL.h>
#include <CGL_GLU_Sphere.h>
#include <CGL_Object.h>
#include <CGL_Disk.h>
#include "CGL_Ellipsoid.h"
#include "CG3DGlobals.h"
#include "CG3DReslistInterface.h"
#include "CGLApplication.h"

using namespace std;

CGLApplication gApp;

int main(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-version") == 0)
        {
            cout << gApp.Name() << ": Version " << gApp.Version() << endl;
            return 0;
        }
        if (strcmp(argv[i], "-fullscreen") == 0)
        {
            gApp.mFullscreen = true;
        }
        if (strcmp(argv[i], "-lame") == 0)
        {
            gApp.mLame = true;
        }
        if (strcmp(argv[i], "-ni") == 0)
        {
            gApp.mShowInterface = false;
        }
    }

    if (argc <= 2)
    {
        gApp.InitApplication(argc, argv);
    }
    else
    {
        cout << "usage: " << gApp.Name() << " <-version> <-fullscreen> <-ni>" << endl;
        cout << "version: " << gApp.Version() << endl;
        cout << "  options: -version    = show version and quit" << endl;
        cout << "           -fullscreen = run in fullscreen-mode" << endl;
        cout << "           -ni         = no interface" << endl;
    }
    return 0;
}
