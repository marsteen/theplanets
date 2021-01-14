//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceKnot.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DResourceKnot_H
#define CG3DResourceKnot_H

class CG3DResourceKnot : public CG3DResource, public CG3DGroup
{
    public:

        void DisableRadioGroup()
        {
            if (mGroup >= 0)
            {
                mParent->DeactivateKnotGroup(this);
            }
        }


        int UnscaledWidth()  { return mParent->UnscaledWidth(); }
        int UnscaledHeight() { return mParent->UnscaledHeight(); }
};

#endif
