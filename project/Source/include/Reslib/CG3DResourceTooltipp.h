//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceTooltipp.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DResourceTooltipp_H
#define CG3DResourceTooltipp_H

class CG3DResourceTooltipp : public CG3DResourceBox
{
    public:

        CG3DResourceTooltipp(void);

        int UnscaledWidth()
        {
            return mContent->UnscaledWidth();
        }


        int UnscaledHeight()
        {
            return mContent->UnscaledHeight();
        }


        void AddResRef(CG3DResource* res);
        void Draw(SG3DDrawParams* dp);


    protected:

        CG3DResourceString* mContent;
};

#endif
