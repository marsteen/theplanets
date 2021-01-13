//---------------------------------------------------------------------------
//
// PROJECT : Die Planeten
//
//
// AUTOR   : Martin Steen
//           email: martin@martin-steen.de
//
//
//----------------------------------------------------------------------------

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "CGL_GLU_Object.h"

static void CGL_GLU_ObjectError()
{
	cout << "CGL_GLU_Object Error ***" << endl;
}



void CGL_GLU_Object::SetParams(int Orient, int DrawStyle, int Normal, bool TextCoord)
{
	gluQuadricOrientation(mQuadObj, Orient);
	gluQuadricDrawStyle(mQuadObj, DrawStyle);
	gluQuadricNormals(mQuadObj, Normal);
	//gluQuadricCallback(mQuadObj, GLU_ERROR, CGL_GLU_ObjectError);
	gluQuadricTexture(mQuadObj, TextCoord);
}
