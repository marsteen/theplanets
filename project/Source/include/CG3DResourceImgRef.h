//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceImgRef.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DResourceImgRef_H
#define CG3DResourceImgRef_H

class CG3DResourceImgRef : public CG3DResource
{
    public:

        CG3DResourceImgRef()
        {
            mImgRef = NULL;
            mStdImage = 0;     // Standard-Image
        }


        bool Check() { return mImgRef != NULL; }

        CG3DResourceImage* mImgRef;   // Image reference

        int UnscaledWidth(void);
        int UnscaledHeight(void);

        int mStdImage;
};

#endif
