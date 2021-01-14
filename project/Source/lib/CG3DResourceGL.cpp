//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceGL.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <CG3DResourceList.h>

//---------------------------------------------------------------------------
//
// Klasse:    CGL_RectPatch
// Methode:		Draw
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CG3DResourceImage::DrawPatch(int RectNr)
{
    if ((mStatus & CGL_STATUS_ACTIVE) && (mStatus & CGL_STATUS_VISIBLE))
    {
        CVector3<float> Vertex;

        CRectT<int>* rc = mIrect + RectNr;

        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, mTexHandle);

        glBegin(GL_TRIANGLE_STRIP);

        Vertex.x = mPosition.x;
        Vertex.y = mPosition.y;
        Vertex.z = 0;
        glTexCoord2f(left, top);
        glVertex3fv(Vertex.v());

        Vertex.x = mPosition.x + rc->Width();
        Vertex.y = mPosition.y;
        Vertex.z = 0;
        glTexCoord2f(right, top);
        glVertex3fv(Vertex.v());

        Vertex.x = mPosition.x;
        Vertex.y = mPosition.y + rc->Height();
        Vertex.z = 0;
        glTexCoord2f(left, bottom);
        glVertex3fv(Vertex.v());

        Vertex.x = mPosition.x  + rc->Width();
        Vertex.y = mPosition.y + rc->Height();
        Vertex.z = 0;
        glTexCoord2f(right, bottom);
        glVertex3fv(Vertex.v());

        glEnd();

        glDisable(GL_TEXTURE_2D);
    }

/*
 *  for (CGL_PatchChild* pc = mChildList->GetFirst(); pc != NULL; pc = mChildList->GetNext())
 *  {
 *      pc->DrawPatch();
 *  }
 */
}
