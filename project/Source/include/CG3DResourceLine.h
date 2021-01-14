//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceLine.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DResourceLine_H
#define CG3DResourceLine_H

class CG3DResourceLine : public CG3DResource
{
    public:

        CG3DResourceLine()
        {
            mColor[0] = 1.0;
            mColor[1] = 1.0;
            mColor[2] = 1.0;
            mColor[3] = 1.0;
            mType = ERTYPE_LINE;
        }


        void Draw(SG3DDrawParams* dp);

        int UnscaledWidth()  { return abs(int(mLineStart.x - mLineEnd.x)); }
        int UnscaledHeight() { return abs(int(mLineStart.y - mLineEnd.y)); }


        CVector2<float> mLineStart;
        CVector2<float> mLineEnd;
        float mColor[4];


    protected:
};

#endif
