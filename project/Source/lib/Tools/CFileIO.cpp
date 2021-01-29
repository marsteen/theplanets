//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CFileIO.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <CFileIO.h>
#include <CList.h>
#include <CList.hpp>

using namespace std;

//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   GetChar
//
// Parameter: char* Filename - Name der Datei
//
// Return:    int - Groesse der Datei in Bytes
//
//---------------------------------------------------------------------------

int CFileIO::GetChar()
{
    char ch;

    mFs->get(ch);
    return ch;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   IsEof
//
//
//---------------------------------------------------------------------------

bool CFileIO::IsEof()
{
    if (mFs == NULL)
    {
        return true;
    }
    return mFs->eof();
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   Clear
//
//
//
//
//---------------------------------------------------------------------------

void CFileIO::Clear()
{
    if (mFs != NULL)
    {
        mFs->clear();
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   SkipBytes
//
// Parameter: int nBytes - Anzahl an Bytes �berspringen (Eingabedatei)
//
//
//---------------------------------------------------------------------------

void CFileIO::SkipBytes(int nBytes)
{
    mFs->seekg(nBytes, ios_base::cur);
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   GetFileSize
//
// Parameter: char* Filename - Name der Datei
//
// Return:    int - Groesse der Datei in Bytes
//
//---------------------------------------------------------------------------

int CFileIO::GetFileSize(const char* Filename)
{
    long FileSize;
    ifstream fin(Filename, ios::in | ios::binary);

    fin.seekg(0, ios::end);
    FileSize = fin.tellg();
    fin.close();
    return FileSize;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   OpenFileRead
//
// Parameter: char* Filename - Name der Datei
//
// Return:    true  - Datei wurde geoeffnet
//            false - Datei konnte nicht geoeffnet werden
//
// Oeffnen einer Datei zum Lesen
//
//---------------------------------------------------------------------------

bool CFileIO::OpenFileRead(const char* Filename, OPENMODE OpenMode)
{
    if (mFs != NULL)
    {
        delete mFs;
    }
    mFs = new fstream(Filename, ios::in | OpenMode);
    mOpenRead = mFs->good();
    return mOpenRead;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   OpenFileWrite
//
// Parameter: char* Filename - Name der Datei
//
// Return:    true  - Datei wurde geoeffnet
//            false - Datei konnte nicht geoeffnet werden
//
// Oeffnen einer Datei zum Lesen
//
//---------------------------------------------------------------------------

bool CFileIO::OpenFileWrite(const char* Filename, OPENMODE OpenMode)
{
    if (mFs != NULL)
    {
        delete mFs;
    }
    mFs = new fstream(Filename, ios::out | OpenMode);
    mOpenWrite = mFs->good();
    return mOpenWrite;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   OpenFileAppend
//
// Parameter: char* Filename - Name der Datei
//
// Return:    true  - Datei wurde geoeffnet
//            false - Datei konnte nicht geoeffnet werden
//
// Oeffnen einer Datei zum Lesen
//
//---------------------------------------------------------------------------

bool CFileIO::OpenFileAppend(const char* Filename, OPENMODE OpenMode)
{
    if (mFs != NULL)
    {
        delete mFs;
    }
    mFs = new fstream(Filename, ios::app | OpenMode);
    mOpenWrite = mFs->good();
    return mOpenWrite;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   ReadFile
//
// Parameter: char* Filename - Name der Datei
//
//            int* nBytes    - Anzahl der Bytes die gelesen wurden (Groesse
//                             der Datei).
//
// Return:    void* - Zeiger auf Puffer, in den die Daten gelesen wurden,
//                    oder NULL (Fehlerfall)
//
//
//
// Lesen des Inhalts einer Datei in einen Puffer. Der Speicher fuer den
// Puffer wird reserviert. Zurueckgegeben werden ein Zeiger auf den
// Puffer sowie die Anzahl der eingelesenen Bytes
//
//---------------------------------------------------------------------------

void* CFileIO::ReadFile(const char* Filename, int* nBytes)
{
    char* buffer = NULL;

    *nBytes = CFileIO::GetFileSize(Filename);
    if (nBytes > 0)
    {
        if (OpenFileRead(Filename, ios::binary))
        {
            buffer = new char[*nBytes+1];
            if (buffer != NULL)
            {
                ReadBytes(buffer, *nBytes);
                buffer[*nBytes] = 0;
            }
        }
        CloseFile();
    }
    return buffer;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:
//
//---------------------------------------------------------------------------

char* CFileIO::ReplaceApp(const char* Filename, const char* neuApp)
{
    char NameBuffer[512];
    char* NeuFilename;

    strcpy(NameBuffer, Filename);
    char* Punkt = strrchr(NameBuffer, '.');

    if (Punkt != NULL)
    {
        *Punkt = 0;
    }

    strcat(NameBuffer, neuApp);

    NeuFilename = new char[strlen(NameBuffer) + 1];

    strcpy(NeuFilename, NameBuffer);

    return NeuFilename;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   WriteBytes
//
//
//
// Einlesen einer Anzahl von Bytes aus einer geoeffneten Datei
//
//---------------------------------------------------------------------------

bool CFileIO::WriteBytes(void* buffer, int nBytes)
{
    if (mOpenWrite)
    {
        mFs->write((char*)buffer, nBytes);
    }
    return mOpenWrite;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   WriteString
//
//
//---------------------------------------------------------------------------

bool CFileIO::WriteString(char* str)
{
    return WriteBytes(str, strlen(str));
}


#if 0
//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   ReplaceAllStrings
//
//
//---------------------------------------------------------------------------

class CStrpos : public CListElem<CStrpos>
{
    public:

        char* mPos;
};

class CStrposList : public CList<CStrpos>
{
};


static void CopyStringBytes(char* dst, char* src, int num)
{
    int i;

    for (i = 0; (i < num) && (*src != 0); i++)
    {
        *(dst++) = *(src++);
    }
    *dst = 0;
}


char* CFileIO::ReplaceAllStrings(char* SrcString, char* SearchString, char* SubString, int* Count)
{
    CStrposList slist;
    int cnt = 0;
    char* pos;
    char* StartPos = SrcString;
    int LenSearch = strlen(SearchString);
    int LenSub = strlen(SubString);
    int LenNew;
    char* NewString = NULL;

    do
    {
        pos = strstr(StartPos, SearchString);
        if (pos != NULL)
        {
            CStrpos* se = slist.NewListElem();
            se->mPos = pos;
            StartPos = pos + LenSearch;
            cnt++;
        }
    } while (pos != NULL);

    *Count = cnt;

    if (cnt > 0)
    {
        LenNew = strlen(SrcString) + (cnt * (LenSub - LenSearch));

        NewString = new char[LenNew+1];
        char* NewStringPos = NewString;

        StartPos = SrcString;
        for (CStrpos* se = slist.GetFirst();
            se != NULL;
            se = slist.GetNext())
        {
            int len = se->mPos - StartPos;
            CopyStringBytes(NewStringPos, StartPos, len);
            NewStringPos += len;
            CopyStringBytes(NewStringPos, SubString, LenSub);
            NewStringPos += LenSub;

            StartPos = se->mPos + LenSearch;
        }
        CopyStringBytes(NewStringPos, StartPos, strlen(StartPos));
        slist.ClearList();
    }
    else
    {
        NewString = new char[strlen(SrcString) + 1];
        strcpy(NewString, SrcString);
    }

    return NewString;
}


#endif

//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   ReadBytes
//
// Parameter: void* buffer - Zeiger auf Puffer, in den die Datei eingelesen
//                           werden
//
//            int nBytes   - Anzahl der Bytes, die eingelesen werden sollen
//
// Return:    true  - Daten wurden eingelesen
//            false - Daten konnten nicht eingelesen werden
//
//
//
// Einlesen einer Anzahl von Bytes aus einer ge�ffneten Datei
//
//---------------------------------------------------------------------------

bool CFileIO::ReadBytes(void* buffer, int nBytes)
{
    if (mOpenRead)
    {
        mFs->read((char*)buffer, nBytes);
    }
    return mOpenRead;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   NewString
//
//---------------------------------------------------------------------------

char* CFileIO::NewString(const char* SrcString)
{
    char* ns = new char[strlen(SrcString) + 1];

    strcpy(ns, SrcString);
    return ns;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   ReadBytes
//
// Parameter:
//
// Return:
//
//
// Lesen von Bytes aus einer Datei
//
//---------------------------------------------------------------------------

void* CFileIO::ReadBytes(int nBytes)
{
    char* buffer = NULL;

    if (mOpenRead)
    {
        buffer = new char[nBytes];
        mFs->read(buffer, nBytes);
    }
    return buffer;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   CloseFile
//
// Parameter:
//
// Return:
//
//
// Schliessen einer Datei
//
//---------------------------------------------------------------------------

void CFileIO::CloseFile()
{
    if (mOpenWrite || mOpenRead)
    {
        mFs->close();
        mOpenRead = false;
        mOpenWrite = false;
        delete mFs;
        mFs = NULL;
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   SetReadPos
//
//
//
//
//---------------------------------------------------------------------------

bool CFileIO::SetReadPos(int pos)
{
    mFs->seekg(pos, ios::beg);
    return (int)mFs->tellg() == pos;
}


//---------------------------------------------------------------------------
//
// Klasse:    CFileIO
// Methode:   GetReadPos
//
//
//
//
//---------------------------------------------------------------------------

int CFileIO::GetReadPos()
{
    return mFs->tellg();
}
