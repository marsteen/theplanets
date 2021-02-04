//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	SFileReadInfo.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef SFILEREADINFO
#define SFILEREADINFO
struct SFileReadInfo
{
    CFileIO*		mFio;
    unsigned int	mFilePosition;
    unsigned int	mFileSize;
    void*			mData;
};
#endif
