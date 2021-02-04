//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceTextfield.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DResourceTextfield_H
#define CG3DResourceTextfield_H

class CG3DResourceTextfield : public CG3DResourceImgRef
{
    public:

        CG3DResourceTextfield(void);

        void SendChar(unsigned char key);
        void Draw(SG3DDrawParams* dp);
        void AddResRef(CG3DResource* res);
        bool Inside(SG3DDrawParams* dp, CVector2<int>* Mouse);
        void SetTextParams(float x, float y, int tmax, int freq);

        float* mColorRef;              // Farbe
        bool mActive;

    protected:

        std::string mTextField;         // Eingabetext
        CG3DResourceFont* mFontRef;     // Zeichensatz
        CVector2<float> mTextPos;
        int mMaxSize;                   // Maximale Größe des Text-Feldes
        int mFrequency;
        int mBlinkCounter;
        bool mShowCursor;
};

#endif
