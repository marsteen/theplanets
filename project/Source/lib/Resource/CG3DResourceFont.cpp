//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceFont.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************


#include <CG3DResourceList.h>

extern CG3DGlobals* gGlobals;

void CG3DResourceFont::Adjust(SG3DDrawParams* dp)
{
    //cout << "+++++ CG3DResourceFont::Adjust wh=" << mWindowHeight << endl;

    mWindowHeight = gGlobals->mWindowHeight;
}
