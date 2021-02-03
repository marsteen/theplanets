//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CStringConverter.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CSTRINGCONVERTER_H
#define CSTRINGCONVERTER_H

#include <string>

class CStringConverter
{
    public:

        int ToInt(std::string& s);
        float ToFloat(std::string& s);
        float ToDouble(std::string& s);

        std::string ToStr(int n);
};

#endif // CSTRINGCONVERTER
