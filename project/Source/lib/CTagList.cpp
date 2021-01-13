//---------------------------------------------------------------------------
//
// PROJECT : Die Planeten
//
//
// AUTOR   : Martin Steen
//           email: martin@martin-steen.de
//
//
//----------------------------------------------------------------------------

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
