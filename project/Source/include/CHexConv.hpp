//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CHexConv.hpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CHEXCONV_HPP
#define CHEXCONV_HPP

#include <cstring>

// Konvertieren einer Hex-Ziffer 0..F
// in eine Integer-Zahl (0..15)

inline int CHexConv::NibbleToInt(char a)
{
    int b;

    if ((a >= 'a') && (a <= 'f'))
    {
        b = a - 'a' + 10;
    }
    else
    if ((a >= 'A') && (a <= 'F'))
    {
        b = a - 'A' + 10;
    }
    else
    if ((a >= '0') && (a <= '9'))
    {
        b = a - '0';
    }
    else
    {
        b = 0;
    }
    return b;
}


// Konvertieren eines Byte (00..FF)
// in eine Integer-Zahl (0..255)
// a = Hoeherwertiges Nibble
// b = niederwertiges Nibble

inline int CHexConv::ByteToInt(unsigned char a, unsigned char b)
{
    return (NibbleToInt(a) << 4) + NibbleToInt(b);
}


// Konvertieren eines Byte (00..FF)
// in eine Float-Zahl (0.0 .. 1.0)
// a = Hoeherwertiges Nibble
// b = niederwertiges Nibble

inline float CHexConv::ByteToFloat(unsigned char a, unsigned char b)
{
    return ((float)ByteToInt(a, b)) / 255.0;
}


//
// Konvertieren eines String in eine Integer-Zahl
//

inline int CHexConv::StringToInt(const char* s)
{
    int i = 0;
    int slen = strlen(s);
    const char* c = s + slen - 1;

    for (int j = 0; j < slen; j++)
    {
        i <<= 4;
        i += NibbleToInt(*(c++));
    }
    return i;
}


#endif
