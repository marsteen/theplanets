//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceClipframe.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <CG3DResourceList.h>

void CG3DResourceClipframe::Draw(SG3DDrawParams* dp)
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(mRect.left, mRect.top, mRect.Width(), mRect.Height());
    CG3DResource::Draw(dp);
    glDisable(GL_SCISSOR_TEST);
}
