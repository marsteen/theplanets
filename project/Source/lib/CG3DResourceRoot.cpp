//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceRoot.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <CG3DResourceList.h>

extern CG3DGlobals* gGlobals;

//---------------------------------------------------------------------------
//
// Klasse:    CG3DResourceRoot
// Methode:		CalcAlignPosition
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CG3DResourceRoot::CalcAlignPosition()
{
    for (list<CG3DResChild>::iterator cld = mChilds.begin();
        cld != mChilds.end();
        cld++)
    {
        cld->CalcAlignPosition(&mDrawParams);
    }
}
