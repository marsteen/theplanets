//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceImgRef.cpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <CG3DResourceList.h>

int CG3DResourceImgRef::UnscaledWidth()
{
    return (mImgRef != NULL) ? mImgRef->Width(mStdImage) : -1;
}


int CG3DResourceImgRef::UnscaledHeight()
{
    return (mImgRef != NULL) ? mImgRef->Height(mStdImage) : -1;
}
