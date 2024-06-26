//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceString.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DResourceString_H
#define CG3DResourceString_H

class CG3DResourceString : public CG3DResource
{
    public:

        CG3DResourceString()
        {
            static float sWhite[] = { 1.0, 1.0, 1.0, 1.0 };

            mFontRef = NULL;
            mColorRef = NULL;
            mOrigColor = sWhite;
        }


        int UnscaledWidth(void);
        int UnscaledHeight(void);

        void AddResRef(CG3DResource* res);
        void Draw(SG3DDrawParams* dp);
        void Draw(const char* str, CVector2<float>* Pos);
        void Draw(CVector2<float>* Pos);
        void Reset(int mode);


        string mText[8];
        CG3DResourceFont* mFontRef;     // Zeichensatz
        float* mColorRef;               // Farbe
        float* mOrigColor;              // Original-Farbe

    protected:

        char* GetText(void);
};

#endif
