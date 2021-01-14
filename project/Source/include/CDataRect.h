#ifndef CDATARECT
#define CDATARECT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class CDataRect
{
    public:

        CDataRect()
        {
            mData = NULL;
            mPalette = NULL;
            mWidth = 0;
            mHeight = 0;
            mBits = 0;
        }


        void operator=(CDataRect& dr)
        {
            mPalette = dr.mPalette;
            mWidth = dr.mWidth;
            mHeight = dr.mHeight;
            mBits = dr.mBits;
        }


        void SetData(int b)
        {
            memset(mData, 0, mWidth * mHeight * (mBits/8));
        }


        void CopyDataFrom(CDataRect* dr)
        {
            mData = dr->mData;
            mPalette = dr->mPalette;
            mWidth = dr->mWidth;
            mHeight = dr->mHeight;
            mBits = dr->mBits;

            //mData = new unsigned char[mWidth * mHeight * (mBits/8)];
        }


        void DeleteData()
        {
            delete[] mData;
            mData = 0L;
        }


        unsigned char* mData;
        void* mPalette;
        int mWidth;
        int mHeight;
        int mBits;
};
#endif
