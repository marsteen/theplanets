//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_GLU_Object.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_GLU_OBJECT_H
#define CGL_GLU_OBJECT_H

#include <CGL_Object.h>

class CGL_GLU_Object : public CGL_Object
{
    protected:

        GLUquadricObj* mQuadObj;

        CGL_GLU_Object()
        {
            mQuadObj = gluNewQuadric();
        }


        ~CGL_GLU_Object()
        {
            gluDeleteQuadric(mQuadObj);
        }


        void SetParams(int Orient, int DrawStyle, int Normal, bool TextCoord);
};

#endif
