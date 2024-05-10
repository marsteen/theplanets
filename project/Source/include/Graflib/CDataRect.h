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

        void Swap16bit();


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

        void pixelFilter(void (*filter)(uint16_t*))
        {
            for (int y = 0; y < mHeight; y++)
            {
                for (int x = 0; x < mWidth; x++)
                {
                   uint16_t* data = ((uint16_t*) mData) + mWidth * y + x;
                   filter(data);
                }
            }
        }

        void swap16bit()
        {
            auto swap16bit = [](uint16_t* data)
            { 
                uint8_t* dataPtr8 = (uint8_t*) data;
                uint8_t swapbyte = dataPtr8[0];
                dataPtr8[0] = dataPtr8[1];
                dataPtr8[1] = swapbyte; 
            };
            pixelFilter(swap16bit);

        }

        unsigned char* mData;
        void* mPalette;
        int mWidth;
        int mHeight;
        int mBits;
};
#endif
