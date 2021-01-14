//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CPixel32.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CPIXEL32_H
#define CPIXEL32_H

class CPixel32
{
    public:

        unsigned char rgba[4];

        void operator=(CPixel32& p2)
        {
            rgba[0] = p2.rgba[0];
            rgba[1] = p2.rgba[1];
            rgba[2] = p2.rgba[2];
        }


        void operator=(int i)
        {
            rgba[0] = i >> 16;
            rgba[1] = (i >> 8) & 0xFF;
            rgba[2] = i & 0xFF;
        }


        unsigned int GetInt()
        {
            return (rgba[2] << 16) | (rgba[1] << 8) | rgba[0];
        }


        bool operator==(CPixel32& p2);
        bool operator!=(CPixel32& p2);
        void Set(unsigned int b);
        void SwapRedBlue(void);
        int Brightness(void);
};

#endif
