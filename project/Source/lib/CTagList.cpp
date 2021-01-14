//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CTagList.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include "CG3DResourceList.h"

//---------------------------------------------------------------------------
//
// Klasse:    CTagList
// Methode:		Find
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

int CTagList::Find(string& SearchTag, STag* Tags)
{
    for (int i = 0; Tags[i].mTagString != NULL; i++)
    {
        if (SearchTag == string(Tags[i].mTagString))
        {
            return Tags[i].mTag;
        }
    }
    return -1;
}
