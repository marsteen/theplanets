#ifndef NULL
#define NULL    ((void*)0L)
#endif

#ifndef _Ios_Openmode
#define _Ios_Openmode    ios
#endif


#ifndef CFILEIO_H
#define CFILEIO_H

#include <fstream>

class CFileIO
{
    public:

        CFileIO()
        {
            mOpenRead = false;
            mOpenWrite = false;
            mFs = NULL;
        }


        void* ReadFile(const char* Filename, int* nBytes);
        bool OpenFileRead(const char* Filename, int type);
        bool OpenFileWrite(const char* Filename, int type);
        bool OpenFileAppend(const char* Filename, int type);
        bool ReadBytes(void* buffer, int nBytes);
        void*   ReadBytes(int nBytes);
        bool WriteBytes(void* buffer, int nBytes);
        bool WriteString(char* str);
        char* ReplaceAllStrings(char* SrcString, char* SearchString, char* SubString, int* Count);
        int GetChar(void);
        bool IsEof(void);
        void Clear(void);
        void SkipBytes(int nBytes);
        char* ReplaceApp(const char* Filename, const char* neuApp);
        char* NewString(const char* SrcString);

        void CloseFile(void);
        bool SetReadPos(int pos);
        int GetReadPos(void);

        int GetFileSize(const char* Filename);

    protected:

        std::fstream* mFs;
        bool mOpenWrite;
        bool mOpenRead;
};

#endif
