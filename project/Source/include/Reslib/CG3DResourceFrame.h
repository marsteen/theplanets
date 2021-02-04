//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceFrame.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DResourceFrame_H
#define CG3DResourceFrame_H

class CG3DResourceFrame : public CG3DResource
{
    public:

        int UnscaledWidth()  { return mRect.Width(); }
        int UnscaledHeight() { return mRect.Height(); }

        CRectT<int> mRect;
};

#endif
