//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CPixel32.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <CPixel32.h>

using namespace std;

//---------------------------------------------------------------------------
//
// KLASSE        : CPixel32
// METHODE       : operator ==
//
//
//
//---------------------------------------------------------------------------

bool CPixel32::operator==(CPixel32& p2)
{
    return (rgba[0] == p2.rgba[0]) &&
           (rgba[1] == p2.rgba[1]) &&
           (rgba[2] == p2.rgba[2]) &&
           (rgba[3] == p2.rgba[3]);
}


//---------------------------------------------------------------------------
//
// KLASSE        : CPixel32
// METHODE       :
//
//
//
//---------------------------------------------------------------------------

bool CPixel32::operator!=(CPixel32& p2)
{
    return (rgba[0] != p2.rgba[0]) ||
           (rgba[1] != p2.rgba[1]) ||
           (rgba[2] != p2.rgba[2]) ||
           (rgba[3] != p2.rgba[3]);
}


//---------------------------------------------------------------------------
//
// KLASSE        : CPixel32
// METHODE       :
//
//
//
//---------------------------------------------------------------------------

void CPixel32::SwapRedBlue()
{
    unsigned char swap = rgba[0];

    rgba[0] = rgba[2];
    rgba[2] = swap;
}


//---------------------------------------------------------------------------
//
// KLASSE        : CPixel32
// METHODE       :
//
//
//
//---------------------------------------------------------------------------

int CPixel32::Brightness()
{
    return rgba[0] + rgba[1] + rgba[2];
}
