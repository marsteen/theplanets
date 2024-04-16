//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGraflibJpeg.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <setjmp.h>
#include <CFileIO.h>
#include <CGraphicsJpeg.h>
#include <CGraflibJpeg.h>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    CGraflibJpeg
// Methode:   GetJpegSize
//
//
//---------------------------------------------------------------------------

bool CGraflibJpeg::GetJpegSize(const char* fname)
{
    CGraphicsJpeg jpeg;
    int Channels;

    bool r = jpeg.GetJpegSize(fname, &mWidth, &mHeight, &Channels);

    mBits = Channels * 8;
    return r;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGraflibJpeg
// Methode:   Read
//
//
//---------------------------------------------------------------------------

bool CGraflibJpeg::Read(const char* Filename, SFileReadInfo* fri)
{
    CGraphicsJpeg jpeg;
    int ByteProPixel;

    if (fri != NULL)
    {
        jpeg.SetFileOffset(fri->mFilePosition, fri->mFileSize);
    }

    mData = (unsigned char*)jpeg.ReadJpeg(Filename, &mWidth, &mHeight, &ByteProPixel);
    mBits = ByteProPixel * 8;

    if (mData == NULL)
    {
        throw(CGraflibException(EGLIB_OPENREAD, Filename));
    }

    return mData != NULL;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGraflibJpeg
// Methode:		Write
//
//
//---------------------------------------------------------------------------

int CGraflibJpeg::Write(const char* Filename, bool bCompare, CFileIO* fio)
{
    CGraphicsJpeg jpeg;

    if (!jpeg.WriteJpeg(Filename, mWidth, mHeight, (unsigned char*)mData, mJpegQuality))
    {
        throw(CGraflibException(EGLIB_OPENWRITE, Filename));
        return false;
    }

    return true;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGraflibJpeg
// Methode:		OpenRead
//
//
//---------------------------------------------------------------------------

bool CGraflibJpeg::OpenReadLine(const char* Filename)
{
    CGraphicsJpeg* jpeg = new CGraphicsJpeg;

    mJpegInterface = jpeg;
    int ByteProPixel;


    if (!jpeg->OpenJpegRead(Filename, &mWidth, &mHeight, &ByteProPixel))
    {
        throw(CGraflibException(EGLIB_OPENREAD, Filename));
        return false;
    }
    mBits = ByteProPixel * 8;
    return true;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGraflibJpeg
// Methode:		ReadLine
//
//
//---------------------------------------------------------------------------

void CGraflibJpeg::ReadLine(void* LineBuffer)
{
    CGraphicsJpeg* jpeg = (CGraphicsJpeg*)mJpegInterface;

    jpeg->ReadJpegLine(LineBuffer);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGraflibJpeg
// Methode:		CloseRead
//
//
//---------------------------------------------------------------------------

void CGraflibJpeg::CloseReadLine()
{
    CGraphicsJpeg* jpeg = (CGraphicsJpeg*)mJpegInterface;

    jpeg->CloseJpegLines();
}


//---------------------------------------------------------------------------
//
// Klasse:    CGraflibJpeg
// Methode:		OpenWrite
//
//
//---------------------------------------------------------------------------

bool CGraflibJpeg::OpenWriteLine(const char* Filename)
{
    CGraphicsJpeg* jpeg;

    if (mJpegInterface == NULL)
    {
        jpeg = new CGraphicsJpeg;
        mJpegInterface = jpeg;
    }
    else
    {
        jpeg = (CGraphicsJpeg*)mJpegInterface;
    }

    if (!jpeg->OpenJpegWrite(Filename, mWidth, mHeight, mJpegQuality))
    {
        throw(CGraflibException(EGLIB_OPENWRITE, Filename));
        return false;
    }
    return true;
}


//---------------------------------------------------------------------------
//
// Klasse:    CGraflibJpeg
// Methode:		SetAppendMode
//
//
//---------------------------------------------------------------------------

void CGraflibJpeg::SetAppendMode(bool b)
{
    CGraphicsJpeg* jpeg;

    if (mJpegInterface == NULL)
    {
        jpeg = new CGraphicsJpeg;
        mJpegInterface = jpeg;
    }
    else
    {
        jpeg = (CGraphicsJpeg*)mJpegInterface;
    }

    jpeg->SetAppendMode(b);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGraflibJpeg
// Methode:		WriteLine
//
//
//---------------------------------------------------------------------------

void CGraflibJpeg::WriteLine(void* LineBuffer)
{
    CGraphicsJpeg* jpeg = (CGraphicsJpeg*)mJpegInterface;

    jpeg->WriteJpegLine(LineBuffer);
}


//---------------------------------------------------------------------------
//
// Klasse:    CGraflibJpeg
// Methode:		CloseWriteLine
//
//
//---------------------------------------------------------------------------

void CGraflibJpeg::CloseWriteLine()
{
    CGraphicsJpeg* jpeg = (CGraphicsJpeg*)mJpegInterface;

    jpeg->CloseJpegWrite();
    delete jpeg;
    mJpegInterface = NULL;
}
