//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceImage.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DRESOURCEIMAGE_H
#define CG3DRESOURCEIMAGE_H

//---------------------------------------------------------------------------
//
// Klasse:    CG3DResourceImage
//
//---------------------------------------------------------------------------

class CG3DResourceImage : public CG3DResource
{
    public:

        bool InsideImage(int RectNr, SG3DDrawParams* dp, CVector2<int>* Mouse);

        CG3DResourceImage()
        {
            mTabRef = NULL;
            mIrect[0].Set(0, 0, 0, 0);
            mIrect[1].Set(0, 0, 0, 0);
            mIrect[2].Set(0, 0, 0, 0);
        }


        int UnscaledWidth()  { return mIrect[0].Width(); }
        int UnscaledHeight() { return mIrect[0].Height(); }

        int Width(int d)
        {
            return mIrect[d].Width();
        }


        int Height(int d)
        {
            return mIrect[d].Height();
        }


        int Width(int d, SG3DDrawParams* dp)
        {
            return (int)(Width(d) * dp->mScale.x);
        }


        int Height(int d, SG3DDrawParams* dp)
        {
            return (int)(Height(d) * dp->mScale.y);
        }


        void AddResRef(CG3DResource* res);
        void DrawImage(int RectNr, SG3DDrawParams* dp);
        void Draw(SG3DDrawParams* dp);

        CG3DResourceTableau* mTabRef;
        CRectT<int> mIrect[3];              // Normal, Active, Rollover-Image
        CRectT<float> mTrect[3];            // Textur-Koordinaten (0..1)

    protected:

        void CalcTextureKoors(void);
};

#endif
