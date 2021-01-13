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
#include <GLinclude.h>
#include <math.h>

using namespace std;

#include "CGL_Ellipsoid.h"

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Ellipsoid
// Methode:		CreateEllipsoid
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_Ellipsoid::CreateEllipsoid(int Sseg, float Srad, int Tseg, float Trad, float* DiffuseMaterial)
{
	mTCircleSegs = Tseg;
	mTCircleRad  = Trad;
	mSCircleSegs = Sseg;
	mSCircleRad  = Srad;

	for (int i = 0; i < 4; i++)
	{
		mDiffuseMaterial[i] = DiffuseMaterial[i];
		mAmbientMaterial[i] = DiffuseMaterial[i];
	}
	mUseTexture = false;
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Ellipsoid
// Methode:   CGL_Ellipsoid
//
//
//---------------------------------------------------------------------------

CGL_Ellipsoid::CGL_Ellipsoid()
{
}



//---------------------------------------------------------------------------
//
// Klasse:    CGL_Ellipsoid
// Methode:   DrawWireFrame
//
//
//---------------------------------------------------------------------------

void CGL_Ellipsoid::DrawWireFrame()
{
	glPushMatrix();

	glRotatef(180, 1.0,0.0,0.0);

	float AngleStepS = (M_PI * 2) / mSCircleSegs;
	float AngleStepT = (M_PI) / mTCircleSegs;

	float AngleS1    = 0.0;

	CVector3<float> Origin(0,0,0);

	for (int s = 0; s < mSCircleSegs; s++)
	{
		glBegin(GL_LINE_STRIP);

		float AngleT = (M_PI / 2);
		float AngleS2 = AngleS1 + AngleStepS;

		for (int t = 0; t < mTCircleSegs+1; t++)
		{
			CVector3<float> vert;

			vert.x = cos(AngleT) * mSCircleRad;
			vert.y = sin(AngleT) * mTCircleRad;
			vert.z = 0;

			vert.RotationXZ(&Origin, sin(AngleS1), cos(AngleS1));

			SetSphereVertex(&Origin, &vert);

			vert.x = cos(AngleT) * mSCircleRad;
			vert.y = sin(AngleT) * mTCircleRad;
			vert.z = 0;

			vert.RotationXZ(&Origin, sin(AngleS2), cos(AngleS2));

			SetSphereVertex(&Origin, &vert);

			AngleT -= AngleStepT;
		}

		AngleS1 += AngleStepS;

		glEnd();
	}

	glPopMatrix();
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_Ellipsoid
// Methode:   MakeObject
//
//
//---------------------------------------------------------------------------

void CGL_Ellipsoid::MakeObject()
{
	glBindTexture(GL_TEXTURE_2D, mTexHandle);
	float AngleStepS = (M_PI * 2) / mSCircleSegs;
	float AngleStepT = (M_PI) / mTCircleSegs;
	float TexCoordStepS = 1.0 / mSCircleSegs;
	float TexCoordStepT = 1.0 / mTCircleSegs;

	float AngleS1 = 0.0;
	float TexCoordS1 = 0.0;

	glPushMatrix();
	glRotatef(180, 1.0,0.0,0.0);
	CVector3<float> Origin(0,0,0);

	for (int s = 0; s < mSCircleSegs; s++)
	{
		glBegin(GL_TRIANGLE_STRIP);

		float AngleT = (M_PI / 2);
		float TexCoordT = 0;

		float AngleS2    = AngleS1 + AngleStepS;
		float TexCoordS2 = TexCoordS1 + TexCoordStepS;

		for (int t = 0; t < mTCircleSegs+1; t++)
		{
			CVector3<float> vert;

			vert.x = cos(AngleT) * mSCircleRad;
			vert.y = sin(AngleT) * mTCircleRad;
			vert.z = 0;

			vert.RotationXZ(&Origin, sin(AngleS1), cos(AngleS1));

			glTexCoord2f(TexCoordS1, TexCoordT);

			SetSphereVertex(&Origin, &vert);

			vert.x = cos(AngleT) * mSCircleRad;
			vert.y = sin(AngleT) * mTCircleRad;
			vert.z = 0;

			vert.RotationXZ(&Origin, sin(AngleS2), cos(AngleS2));

			glTexCoord2f(TexCoordS2, TexCoordT);

			SetSphereVertex(&Origin, &vert);

			AngleT -= AngleStepT;
			TexCoordT += TexCoordStepT;
		}

		AngleS1 += AngleStepS;
		TexCoordS1 += TexCoordStepS;

		glEnd();
	}

	glPopMatrix();
}
//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:   Init
//
//
//---------------------------------------------------------------------------


void CGL_EllipsoidPatched::Init()
{

	MatInit();

	mRotY = 180.0 / mPatchesY;
	MatRotateY(mRotY);

/*
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	MakeObject();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
*/
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:   Init
//
//
//---------------------------------------------------------------------------


void CGL_EllipsoidPatched::InitDisplayList()
{
	MatInit();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	MakeObject();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:   MakeObject
//
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::MakeObject()
{
	//cout << "CGL_EllipsoidPatched::MakeObject start" << endl;

	int PsegS = mSCircleSegs / mPatchesX;
	int PsegT = mTCircleSegs / mPatchesY;

	//Debug2 << "  PsegS=" << PsegS << DBLF;
	//Debug2 << "  PsegT=" << PsegT << DBLF;

	float AngleStepS = (M_PI * 2) / mSCircleSegs;
	float AngleStepT = (M_PI) / mTCircleSegs;

	int ti = 0; // Texture-Index
	int n  = 0;

	float StartT = 0; // AngleStepT * PsegT;

	mDisplayListHandle = glGenLists(mPatchesX * mPatchesY);

	//mAngleList = new SAngleList[mPatchesX * mPatchesY];

	mRotY = 180.0 / mPatchesY;

	MatRotateY(mRotY);

	mWidthS  = AngleStepS * PsegS;
	mHeightT = AngleStepT * PsegT;

	for (int y = 0; y < mPatchesY; y++)
	{
		float StartS = M_PI * 2;

		for (int x = 0; x < mPatchesX; x++)
		{
			glNewList(mDisplayListHandle + n, GL_COMPILE);

			if (mPhaseCount > 0)
			{
				MakePatchDrawElementsST(StartS, StartT, AngleStepS, AngleStepT, PsegS, PsegT);
			}
			else
			{
				MakePatchDrawElements(StartS, StartT, AngleStepS, AngleStepT, PsegS, PsegT);
			}
			glEndList();

			StartS -= mWidthS;

			n++;
			ti++;
		}
		StartT -= mHeightT;
	}

	//cout << "CGL_EllipsoidPatched::MakeObject ok" << endl;
}





//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:   NextNumXY
//
//
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::NextNumXY(int n, int* nx, int* ny)
{
	int pktT = (n - 400000) % 1000;
	int pktS = (n - 400000) / 1000;

	if (pktS > 0)
	{
		*nx = n - 1000;
	}
	else
	{
		*nx = n + 1000;
	}

	if (pktT > 0)
	{
		*ny = n - 1;
	}
	else
	{
		*ny = n + 1;
	}
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:   GetLongLati
//
//
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::GetLongLati(int Name, float* Long, float* Lati)
{
	int pktT = (Name-400000) % 1000;
	int pktS = (Name-400000) / 1000;
	float AddLong = mPointsRS * mStepRS;


	*Lati = 90.0 + RAD_TO_DEG(mStartT - (mStepRT * pktT));
	*Long = 180.0 - RAD_TO_DEG(mStartS + (mStepRS * pktS) - AddLong);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:   GetLongLati
//
//
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::GetSegmentLongLati(int SegmentNr, float* Long, float* Lati, float* ns, float* nt)
{
	float StartT = 0;
	float StartS = 360.0;

	int SegT = SegmentNr / mPatchesX;
	int SegS = SegmentNr % mPatchesX;

	*ns = 360.0 / mPatchesX;
	*nt = 180.0 / mPatchesY;

	*Lati = 90.0 + (StartT - (SegT * (*nt)));
	*Long = 180.0 - (StartS - (SegS * (*ns)));
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		DrawSingleSegment
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::DrawSingleSegment(int PatchNr, float Anisotropic)
{
	int yseg = PatchNr / mPatchesX;
	int xseg = PatchNr % mPatchesX;

	int PsegS = mSCircleSegs / mPatchesX;
	int PsegT = mTCircleSegs / mPatchesY;

	float AngleStepS = (M_PI * 2) / mSCircleSegs;
	float AngleStepT = (M_PI) / mTCircleSegs;

	mStartT = -(AngleStepT * PsegT * yseg);
	mStartS =  (M_PI * 2) - (AngleStepS * PsegS * xseg);

  /*
	if (Anisotropic > 0)
	{
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, &Anisotropic);
	}
	*/

	MakePatchDrawElements(mStartS, mStartT, AngleStepS, AngleStepT, PsegS, PsegT);
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		SetPatches
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::SetPatches(int PatchesX, int PatchesY)
{
	mPatchesX = PatchesX;
	mPatchesY = PatchesY;

	mNumPatches = mPatchesX * mPatchesY;
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		SetMotionTextures
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::SetMotionTextures(unsigned int* TexHandles, int PatchesX, int PatchesY)
{
	SetPatches(PatchesX, PatchesY);
	mTexHandleList = TexHandles;
	mTexBitDepth = 8;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		SetMultiTextures
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::SetMultiTextures(unsigned int* TexHandles, int PatchesX, int PatchesY)
{
	SetPatches(PatchesX, PatchesY);
	mTexHandleList = TexHandles;
	mTexBitDepth = 24;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		Draw
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::Draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < mNumPatches; i++)
	{
		glBindTexture(GL_TEXTURE_2D, mTexHandleList[i]);
		DrawSingleSegment(i, 0);
	}
	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		Delete
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::Delete()
{
	if (mTexHandleList != NULL)
	{
		glDeleteTextures(mNumPatches, mTexHandleList);
		glDeleteLists(mDisplayListHandle, 1);
	}
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		DrawDisplayList
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::DrawDisplayList()
{
	if (mPhaseCount > 0)
	{
		DrawDisplayListMotion();
	}	
	else
	{
		glEnable(GL_TEXTURE_2D);
		for (int i = 0; i < mNumPatches; i++)
		{
			DrawPatch(i, mTexHandleList[i], 0);
		}
		glDisable(GL_TEXTURE_2D);
	}
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		DrawDisplayListMotion
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::DrawDisplayListMotion()
{
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, mTexHandleList[mPhase]);
	for (int i = 0; i < mNumPatches; i++)
	{
		DrawPatch(i);
	}

	glDisable(GL_TEXTURE_2D);
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		Animate
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::Animate()
{
	if (++mSpeed == mSpeedCount)
	{
    mSpeed = 0;
		if (++mPhase == mPhaseCount)
		{
			mPhase = 0;
		}
	}
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		DrawWithoutTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::DrawWithoutTexture(int Mode)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	if (Mode == GL_FEEDBACK)
	{
		//Debug2 << "CGL_EllipsoidPatched::DrawWithoutTexture=" << mNumPatches << DBLF;

		glDisable(GL_TEXTURE_2D);
		for (int i = 0; i < mNumPatches; i++)
		{
			glPassThrough(i);
			DrawSingleSegment(i, 0);
		}
	}
	else
	if (Mode == GL_SELECT)
	{
		glDisable(GL_TEXTURE_2D);
		for (int i = 0; i < mNumPatches; i++)
		{
			glLoadName(i);
			DrawSingleSegment(i, 0);
		}
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		DrawWithoutTexture
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::DrawWithoutTexture(int Mode, int* SegList)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	if (Mode == GL_FEEDBACK)
	{
		//Debug2 << "CGL_EllipsoidPatched::DrawWithoutTexture Mode=GL_FEEDBACK" << DBLF;

		//Debug2 << "CGL_EllipsoidPatched::DrawWithoutTexture=" << mNumPatches << DBLF;

		glDisable(GL_TEXTURE_2D);
		for (int i = 0; SegList[i] >= 0; i++)
		{
			//Debug2 << SegList[i] << DBLF;
			glPassThrough(SegList[i]);
			DrawSingleSegment(SegList[i], 0);
		}
	}
	else
	if (Mode == GL_SELECT)
	{
		//Debug2 << "CGL_EllipsoidPatched::DrawWithoutTexture Mode=GL_SELECT" << DBLF;

		glDisable(GL_TEXTURE_2D);
		for (int i = 0; SegList[i] >= 0; i++)
		{
			//Debug2 << SegList[i] << DBLF;
			glLoadName(SegList[i]);
			DrawSingleSegment(SegList[i], 0);
		}
	}

//	Debug2 << "CGL_EllipsoidPatched::DrawWithoutTexture OK" << DBLF;

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		DrawPatch
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::DrawPatch(int n, unsigned int TexHandle, GLfloat Anisotropic)
{
	if (TexHandle != 0)
	{
		glBindTexture(GL_TEXTURE_2D, TexHandle);

		if (Anisotropic > 0)
		{
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, &Anisotropic);
		}
		glCallList(mDisplayListHandle + n);
	}
}

//---------------------------------------------------------------------------
//
// Klasse:    CGL_EllipsoidPatched
// Methode:		DrawPatch
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CGL_EllipsoidPatched::DrawPatch(int n)
{
	glCallList(mDisplayListHandle + n);
}


