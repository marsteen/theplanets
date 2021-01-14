//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceDialog.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DResourceDialog_H
#define CG3DResourceDialog_H

class CG3DResourceDialog : public CG3DResourceImgRef
{
    public:

        CG3DResourceDialog()
        {
            mBoxRef = NULL;
        }


        void Draw(SG3DDrawParams* dp);
        void AddResRef(CG3DResource* res);

        int UnscaledWidth(void);
        int UnscaledHeight(void);

    protected:

        CG3DResourceBox* mBoxRef;
};

#endif
