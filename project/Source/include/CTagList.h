#ifndef STAG_H
#define STAG_H

//---------------------------------------------------------------------------
//
// Struktur:    STag
//
//---------------------------------------------------------------------------

struct STag
{
	int          mTag;
	const char*  mTagString;
};

//---------------------------------------------------------------------------
//
// Klasse:    CTagList
//
//---------------------------------------------------------------------------

class CTagList
{
	public:

		int Find(string& SearchTag, STag* Tags);
};
#endif
