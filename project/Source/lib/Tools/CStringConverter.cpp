//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CStringConverter.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <string>
#include <math.h>
#include <cstdlib>
#include <CStringConverter.h>

using namespace std;

int CStringConverter::ToInt(string& s)
{
    char* EndPtr;

    return strtol(s.c_str(), &EndPtr, 10);
}


float CStringConverter::ToFloat(string& s)
{
    return atof(s.c_str());
}


string CStringConverter::ToStr(int n)
{
    char StrBuffer[32];

    sprintf(StrBuffer, "%d", n);
    return string(StrBuffer);
}
