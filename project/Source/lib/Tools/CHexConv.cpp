//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CHexConv.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

inline int CHexConv::HexToInt(char a)
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


inline int CHexConv::ToInt(unsigned char a, unsigned char b)
{
    return (HexToInt(a) << 4) + HexToInt(b);
}


inline float CHexConv::ToFloat(unsigned char a, unsigned char b)
{
    return ((float)ToInt(a, b)) / 255.0;
}


unsigned int CHexConv::HexToInt(char* s)
{
    unsigned int i = 0;
    int slen = strlen(s);
    char* c = s + slen - 1;

    for (int j = 0; j < slen; j++)
    {
        i <<= 4;
        i += HexToInt(*(c++));
    }
    return i;
}
