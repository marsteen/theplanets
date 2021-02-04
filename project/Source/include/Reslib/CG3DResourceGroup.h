//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceGroup.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DGroup_H
#define CG3DGroup_H

class CG3DGroup
{
    public:

        CG3DGroup()
        {
            mGroup = -1;
        }


        void CG3DResourceButton::DisableRadioGroup()
        {
            if (mGroup >= 0)
            {
                mGroupParent->DeactivateButtonGroup(this);
            }
        }


        void SetGroupParent(CG3DResource* gp) { mGroupParent = gp; }

        int mGroup;                     // Gruppe
        CG3DResource* mGroupParent;
};

#endif
