//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	SG3DcomData.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef SG3DCOMDATA_H
#define SG3DCOMDATA_H

struct SG3DcomData
{
    SG3DcomData()
    {
        mFlags = 0;
        mObject = NULL;
        mChrParam = NULL;
    }


    std::string		mName;
    void*			mObject;
    CVector2<float> mPos;
    unsigned int	mFlags;
    std::string		mStrParam;
    const char*		mChrParam;
};

#endif
