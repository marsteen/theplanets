#ifndef CDATABASE3_H
#define CDATABASE3_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

enum ERecType
{
    ERT_INT,
    ERT_FLOAT,
    ERT_DOUBLE,
    ERT_STRING
};

struct CRecField
{
    char*	mTag;
    int		mTagType;
    void*	mVar;
    bool	mFound;
};

class CRecord : public std::vector<std::string>
{
    public:

        int mLineNumber;
        std::string mFilename;

        void Show(void);
        void AddString(std::string& as);
};


class CDatabase3 : public std::list<CRecord>
{
    public:

        int Read(std::list<CRecord>* db, std::string& BasePath, std::string& Filename, char SplitChar);

    protected:

        void AddRecord(CRecord& rc);
        bool IsValid(int c);
};


#endif // CDATABASE3
