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

#include <iostream>

using namespace std;

#include <windows.h>
#include "CFilemapping.h"

//---------------------------------------------------------------------------
//
// Klasse:    CFilemapping
// Methode:		OpenRead
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void* CFilemapping::OpenRead(char* Filename)
{
	SECURITY_ATTRIBUTES sec;

	sec.nLength = sizeof(SECURITY_ATTRIBUTES);
	sec.lpSecurityDescriptor = NULL;
	sec.bInheritHandle = FALSE;

	mFileHandle = CreateFile(Filename,  GENERIC_READ, 0, &sec, OPEN_EXISTING, 0, 0);

	if (mFileHandle != NULL)
	{
		mFilesize = GetFileSize(mFileHandle, NULL);
		mMapHandle = CreateFileMapping(mFileHandle, NULL, PAGE_READONLY, 0,0, Filename);

		//mMapHandle = OpenFileMapping(FILE_MAP_READ, FALSE, Filename);
		if (mMapHandle != NULL)
		{
			mMapPointer = MapViewOfFile(mMapHandle, FILE_MAP_READ, 0,0,0);
		}
		else
		{
			cout << "Mapping failed in CFilemapping::OpenRead File=" << Filename << endl;
			mMapPointer = NULL;
		}
	}
	else
	{
		mFilesize = 0;
		mMapPointer = NULL;
	}

	return mMapPointer;
}

//---------------------------------------------------------------------------
//
// Klasse:    CFilemapping
// Methode:		Close
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CFilemapping::Close()
{
	UnmapViewOfFile(mMapPointer);
	CloseHandle(mMapHandle);
	CloseHandle(mFileHandle);
}
