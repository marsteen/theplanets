//---------------------------------------------------------------------------
//
// PROJECT : Die Planeten
//
//
// AUTOR   : Martin Steen
//           email: martin@martin-steen.de
//
//
//----------------------------------------------------------------------------

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <fstream>


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <CGraflibTga.h>
#include <CGraflibJpeg.h>
#include <CPixel24.h>
#include <CPixel8.h>
#include <CGL_Texture.h>


using namespace std;


static int mTexScaleMode = GL_LINEAR; // GL_NEAREST oder GL_LINEAR

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		LoadTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Texture::SetScaleMode(int sm)
{
	mTexScaleMode = sm;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		LoadTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Texture::DeleteTexture()
{
	if (mTexHandle != 0)
	{
		glDeleteTextures(1, &mTexHandle);
		mTexHandle = 0;
	}
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		~CGL_Texture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

CGL_Texture::~CGL_Texture()
{
//	DeleteTexture();
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		LoadTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

bool CGL_Texture::LoadTextureTga(const char* TextureFilename, bool CreateMipmap)
{
	bool Status = false;
	CGraflibTga tga;

	//cout << "CGL_Texture::LoadTextureTga START: " << TextureFilename << endl;

	tga.Read(TextureFilename);
	tga.SwapRedBlue();
	//tga.Write("test.tga", false);

	//cout << "CGL_Texture Width=" << tga.mWidth << " Height=" << tga.mHeight << endl;

	if (tga.mData != NULL)	//
	{
		glGenTextures(1, &mTexHandle);				// Create One Texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, (int) mTexHandle);

		if (CreateMipmap)
		{
			//cout << "Creating Texture with mipmap" << endl;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE); //
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE); //


			gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
												tga.mWidth,
												tga.mHeight,
												GL_RGB, GL_UNSIGNED_BYTE,
												tga.mData);
		}
		else
		{
			//       GL_LINEAR
			// oder  GL_NEAREST

			//cout << "Creating Texture without mipmap" << endl;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTexScaleMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTexScaleMode);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_CLAMP_TO_EDGE); //
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //GL_CLAMP_TO_EDGE); //

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tga.mWidth, tga.mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, tga.mData);
		}

		mTexWidth    = tga.mWidth;
		mTexHeight   = tga.mHeight;
		mTexBitDepth = 24;

		delete[] tga.mData;

		Status = true;
	}
	return Status;									// Return The Status
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		LoadTextureTga
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

bool CGL_Texture::LoadTextureTga2D(const char* TextureFilename, const char* AlphaFilename, bool CreateMipmap, bool GreyScale)
{
	bool Status = false;
	CGraflibTga tga;
	CGraflibTga tgaAlpha;

	//cout << "CGL_Texture::LoadTextureTga ALPHA START: " << TextureFilename << " Alpha=" << AlphaFilename << endl;

	tga.Read(TextureFilename);
	tga.SwapRedBlue();

	if (GreyScale)
	{
		tga.GreyScale24bit();
	}

	tgaAlpha.Read(AlphaFilename);
	//string tst = "test8bit.tga";
	//tgaAlpha.Write(tst, true);

	//cout << "CGL_Texture Width=" << tga.mWidth << " Height=" << tga.mHeight << endl;

	if ((tga.mData != NULL) && (tgaAlpha.mData != NULL))
	{
		tga.InterleaveAlpha(&tgaAlpha);

		glGenTextures(1, &mTexHandle);				// Create One Texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, (int) mTexHandle);

		if (CreateMipmap)
		{
			//cout << "Creating Texture with mipmap" << endl;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE); //
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE); //


			gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
												tga.mWidth,
												tga.mHeight,
												GL_RGBA, GL_UNSIGNED_BYTE,
												tga.mData);
		}
		else
		{
			//       GL_LINEAR
			// oder  GL_NEAREST

			//cout << "Creating Texture without mipmap" << endl;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTexScaleMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTexScaleMode);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tga.mWidth, tga.mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, tga.mData);
		}

		mTexWidth    = tga.mWidth;
		mTexHeight   = tga.mHeight;
		mTexBitDepth = 32;

		delete[] tga.mData;

		Status = true;
	}
	return Status;									// Return The Status
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		:LoadTextureTga8Bit2D
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

bool CGL_Texture::LoadTextureTga8Bit2D(const char* TextureFilename)
{
	bool Status = false;
	CGraflibTga tga;

	if (!tga.Read(TextureFilename))
	{
		cout << "***** CGL_Texture::LoadTextureTga8Bit2D Fehler: " << TextureFilename << endl;
	}
	if (tga.mData != NULL)
	{
		//cout << "w=" << tga.mWidth << " h=" << tga.mHeight;
		//cout << " bits=" << tga.mBits << endl;
		glGenTextures(1, &mTexHandle);				// Create One Texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, (int) mTexHandle);

		{
			//       GL_LINEAR
			// oder  GL_NEAREST

			//cout << "Creating Texture without mipmap" << endl;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTexScaleMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTexScaleMode);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //GL_CLAMP_TO_EDGE); //
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //GL_CLAMP_TO_EDGE); //

			glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, tga.mWidth, tga.mHeight, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, tga.mData);
		}

		mTexWidth    = tga.mWidth;
		mTexHeight   = tga.mHeight;
		mTexBitDepth = 8;

		delete[] tga.mData;

		Status = true;
	}


	return Status;									// Return The Status
}



//---------------------------------------------------------------------------
//
// Klasse:    CGL_Texture
// Methode:		LoadTextureTga1D
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

bool CGL_Texture::LoadTextureTga1D(const char* TextureFilename, const char* AlphaFilename, bool CreateMipmap)
{
	bool Status = false;
	CGraflibTga tga;
	CGraflibTga tgaAlpha;

	//cout << "CGL_Texture::LoadTextureTga1D ALPHA START: " << TextureFilename << " Alpha=" << AlphaFilename << endl;

	tga.Read(TextureFilename);
	tga.SwapRedBlue();
	tgaAlpha.Read(AlphaFilename);

	//cout << " TGAWidth=" << tga.mWidth << endl;

	if ((tga.mData != NULL) && (tgaAlpha.mData != NULL))
	{
		tga.InterleaveAlpha(&tgaAlpha);

		glGenTextures(1, &mTexHandle);				// Create One Texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_1D, (int) mTexHandle);

		if (CreateMipmap)
		{
			//cout << "Creating Texture with mipmap" << endl;

			glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE); //
			glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE); //


			gluBuild1DMipmaps(GL_TEXTURE_1D, 4,
												tga.mWidth,
												GL_RGBA, GL_UNSIGNED_BYTE,
												tga.mData);
		}
		else
		{
			//       GL_LINEAR
			// oder  GL_NEAREST


			//cout << "Creating Texture without mipmap" << endl;

			glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, mTexScaleMode);
			glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, mTexScaleMode);

			//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //
			//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //


			glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, tga.mWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, tga.mData);
		}

		mTexWidth    = tga.mWidth;
		mTexHeight   = tga.mHeight;
		mTexBitDepth = 32;

		delete[] tga.mData;

		Status = true;
	}
	else
	{
		if (tga.mData == NULL)
		{
			cout << "***** cannot load TGA file:" << TextureFilename << endl;
			exit(0);
		}
		if (tgaAlpha.mData == NULL)
		{
			cout << "***** cannot load TGA-Alpha file:" << AlphaFilename << endl;
			exit(0);
		}
	}



	return Status;									// Return The Status
}


//---------------------------------------------------------------------------
//
// Klasse:		CGL_Texture
// Methode:   CreateGlib
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

CGraflib* CGL_Texture::CreateGlib(const char* TextureFilename)
{
  CGraflib* glib = NULL;


  const char* pkt = strrchr(TextureFilename, '.');

  if (pkt != NULL)
  {
		if ((strcmp(pkt, ".tga") == 0) ||
		    (strcmp(pkt, ".TGA") == 0))
    {
      glib = new CGraflibTga;
      glib->Read(TextureFilename);

      if (glib->mBits == 24)
      {
      	glib->SwapRedBlue();
			}
		}
		else
		if ((strcmp(pkt, ".jpg") == 0) ||
		    (strcmp(pkt, ".JPG") == 0))
		{
			glib = new CGraflibJpeg;
			glib->Read(TextureFilename);

		}
	}
  return glib;
}


//---------------------------------------------------------------------------
//
// Klasse:		CGL_Texture
// Methode:   CreateSplitTextures
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

unsigned int* CGL_Texture::CreateSplitTextures(const char* TextureFile, int XPatches, int YPatches, bool GreyScale)
{
	//cout << "C3DGlobus::CreateSplitTextures start " << TextureFile << endl;

	CGraflib* glib = CreateGlib(TextureFile);
	unsigned int* TextureHandles = NULL;

	if (glib > 0)
	{
		TextureHandles = new unsigned int[XPatches * YPatches];

		int t = 0; // Zaehler fuer Texturen
		if (GreyScale)
		{
			glib->GreyScale24bit();
		}


		if (glib->mData != NULL)
		{
			int ColorModel;
			int PatchWidth  = glib->mWidth / XPatches;
			int PatchHeight = glib->mHeight / YPatches;

			void* Pixels = glib->mData;
			void* PatchBuffer;

			if (glib->mBits == 24)
			{
				ColorModel = GL_RGB;
				PatchBuffer = new CPixel24[PatchWidth * PatchHeight];
			}
			else
			if (glib->mBits == 8)
			{
				ColorModel = GL_LUMINANCE;
				PatchBuffer = new CPixel8[PatchWidth * PatchHeight];
			}

			for (int yp = 0; yp < YPatches; yp++)
			{
				for (int xp = 0; xp < XPatches; xp++)
				{
					if (glib->mBits == 24)
					{
						CPixel24* PatchBuffer24 = (CPixel24*) PatchBuffer;
						CPixel24* Pixels24      = (CPixel24*) Pixels;

						CPixel24* PixelsPtr = Pixels24 + (yp * glib->mWidth * PatchHeight) + (xp * PatchWidth);
						CPixel24* PatchBufferPtr = PatchBuffer24;

						for (int y = 0; y < PatchHeight; y++)
						{
							memcpy(PatchBufferPtr, PixelsPtr, sizeof(CPixel24) * PatchWidth);

							PatchBufferPtr += PatchWidth;
							PixelsPtr      += glib->mWidth;
						}
					}
					else
					if (glib->mBits == 8)
					{
						CPixel8* PatchBuffer8 = (CPixel8*) PatchBuffer;
						CPixel8* Pixels8      = (CPixel8*) Pixels;

						CPixel8* PixelsPtr = Pixels8 + (yp * glib->mWidth * PatchHeight) + (xp * PatchWidth);
						CPixel8* PatchBufferPtr = PatchBuffer8;

						for (int y = 0; y < PatchHeight; y++)
						{
							memcpy(PatchBufferPtr, PixelsPtr, sizeof(CPixel8) * PatchWidth);

							PatchBufferPtr += PatchWidth;
							PixelsPtr      += glib->mWidth;
						}
					}


					glGenTextures(1, TextureHandles + t);				// Create One Texture
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glBindTexture(GL_TEXTURE_2D, TextureHandles[t]);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTexScaleMode);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTexScaleMode);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //

					glTexImage2D(GL_TEXTURE_2D, 0, ColorModel, PatchWidth, PatchHeight, 0, ColorModel, GL_UNSIGNED_BYTE, PatchBuffer);

					t++;
				}
			}
			delete[] (char*) PatchBuffer;
		}
		else
		{
			//Debug2 << "***** File not found in  C3DGlobus::CreateSplitTextures: " << TextureFile << DBLF;
		}
		delete[] glib->mData;
		delete glib;
	}

	//cout << "C3DGlobus::CreateSplitTextures OK " << endl;

	return TextureHandles;
}





//---------------------------------------------------------------------------
//
// Klasse:		CGL_Texture
// Methode:   CreateSplitTextures
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

unsigned int* CGL_Texture::CreateSplitTextures(const char* TextureFile, const char* AlphaFile,
                                               int XPatches, int YPatches, bool GreyScale)
{
	//cout << "C3DGlobus::CreateSplitTextures start " << TextureFile << endl;

	CGraflib* glib = CreateGlib(TextureFile);
	CGraflib* alib = CreateGlib(AlphaFile);

	unsigned int* TextureHandles = NULL;

	if ((glib != NULL) && (alib != NULL))
	{
		cout << "CreateSplitTextures TextureFile READ: " << TextureFile << endl;
		cout << "CreateSplitTextures AlphaFile   READ: " << AlphaFile <<  endl;


		cout << "InterleaveAlpha OK" << endl;
		cout << "Xpatches=" << XPatches << endl;
		cout << "Ypatches=" << YPatches << endl;

		cout << "GW=" <<  glib->mWidth << endl;
		cout << "AW=" <<  alib->mWidth << endl;
		cout << "GH=" <<  glib->mHeight << endl;
		cout << "AH=" <<  alib->mHeight << endl;

		TextureHandles = new unsigned int[XPatches * YPatches];

		if ((alib->mWidth  != glib->mWidth)  ||
		    (alib->mHeight != glib->mHeight))
		{
			cout << "***** Alphafile doesnt fit!" << endl;
			return NULL;
		}

		if (glib->mBits != 24)
		{
			cout << "***** Grafics-file must be 24-bit format" << endl;
		}
		if (alib->mBits != 8)
		{
			cout << "***** Alpha-file must be 8-bit format" << endl;
		}


		glib->InterleaveAlpha(alib);



		int t = 0; // Z�hler f�r Texturen

		if (glib->mData != NULL)
		{
			int PatchWidth  = glib->mWidth / XPatches;
			int PatchHeight = glib->mHeight / YPatches;

			CPixel32* Pixels = (CPixel32*) glib->mData;
			CPixel32* PatchBuffer = new CPixel32[PatchWidth * PatchHeight];

			for (int yp = 0; yp < YPatches; yp++)
			{
				cout << "yp=" << yp << endl;

				for (int xp = 0; xp < XPatches; xp++)
				{
					CPixel32* PixelsPtr = Pixels + (yp * glib->mWidth * PatchHeight) + (xp * PatchWidth);
					CPixel32* PatchBufferPtr = PatchBuffer;

					cout << " copy" << endl;


					for (int y = 0; y < PatchHeight; y++)
					{
						memcpy(PatchBufferPtr, PixelsPtr, sizeof(CPixel32) * PatchWidth);

						PatchBufferPtr += PatchWidth;
						PixelsPtr      += glib->mWidth;
					}

					cout << " copy ok" << endl;

					glGenTextures(1, TextureHandles + t);				// Create One Texture
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glBindTexture(GL_TEXTURE_2D, TextureHandles[t]);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTexScaleMode);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTexScaleMode);

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, PatchWidth, PatchHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, PatchBuffer);

					t++;
				}
			}
			delete[] PatchBuffer;
		}
		else
		{
			cout << "***** File not found in  C3DGlobus::CreateSplitTextures: " << TextureFile << endl;
		}
		cout << "  3a" << endl;

		delete[] glib->mData;
		delete glib;
		delete alib;
	}

	cout << "C3DGlobus::CreateSplitTextures OK " << endl;

	return TextureHandles;
}
