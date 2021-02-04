//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_Texture.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_TEXTURE_H
#define CGL_TEXTURE_H

#include <CPixel24.h>
#include <CPixel32.h>
#include <CGraflib.h>

class CGL_Texture
{
    public:

        CGL_Texture()
        {
            mTexHandle = 0;
        }


        ~CGL_Texture();

        bool LoadTextureTga(const char* TextureFilename, bool CreateMipmap = false);
        bool LoadTextureTga2D(const char* TextureFilename, const char* AlphaFilename, bool CreateMipmap = false, bool GreyScale = false);
        bool LoadTextureTga8Bit2D(const char* TextureFilename);


        bool LoadTextureTga1D(const char* TextureFilename, const char* AlphaFilename, bool CreateMipmap = false);

        unsigned int* CreateSplitTextures(const char* TextureFile, int XPatches, int YPatches, bool GreyScale = false);
        unsigned int* CreateSplitTextures(const char* TextureFile, const char* AlphaFile, int XPatches, int YPatches, bool GreyScale = false);

        void DeleteTexture(void);
        void SetScaleMode(int sm);


        unsigned int mTexHandle;
        int mTexWidth;
        int mTexHeight;
        int mTexBitDepth;


    protected:

        CGraflib* CreateGlib(const char* TextureFilename);
};


#endif
