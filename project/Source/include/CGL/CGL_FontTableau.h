//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_FontTableau.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_FONTTABLEAU_H
#define CGL_FONTTABLEAU_H

#include <CGL_Texture.h>
#include <CRectT.h>

class CGL_FontTableau : public CGL_Texture
{
    public:

        bool Load(const char* Folder, const char* FileBase, int wh);
        bool Load(const char* TabFile, const char* AlphaFile, const char* RectFile, int wh);
        bool LoadPng(const char* PngFile32, const char* RectFile, int wh);
        void DrawString(const char* Text, int x, int y);
        void DrawStringRaw(const char* Text, float x, float y);
        int FontWidth(const char* tx);
        int FontHeight(void);


    protected:

        int mWindowHeight;
        CRectT<int> mCharRect[256];
        CRectT<float> mTexRect[256];
};

#endif
