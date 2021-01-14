//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceFont.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DResourceFont_H
#define CG3DResourceFont_H

class CG3DResourceFont : public CG3DResource, public CGL_FontTableau
{
    public:

        void Adjust(SG3DDrawParams* dp);
};

#endif
