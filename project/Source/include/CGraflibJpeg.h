//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGraflibJpeg.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGRAFLIBJPEG_H
#define CGRAFLIBJPEG_H

#include <CFileIO.h>
#include <SFileReadInfo.h>
#include <CDataRect.h>
#include <CGraflib.h>

class CGraflibJpeg : public CGraflib
{
    public:

        CGraflibJpeg()
        {
            mJpegInterface = NULL;
            mJpegQuality = 80;
        }


        bool Read(const char* Filename, SFileReadInfo* fri = NULL);
        int Write(const char* Filename, bool bCompFlag, CFileIO* fio = NULL);

        bool OpenReadLine(const char* Filename);
        void ReadLine(void* LineBuffer);
        void CloseReadLine(void);

        bool OpenWriteLine(const char* Filename);
        void WriteLine(void* LineBuffer);
        void CloseWriteLine(void);

        void SetAppendMode(bool b);
        bool GetJpegSize(const char* fname);

        int mJpegQuality;

    protected:

        void* mJpegInterface;
};

#endif
