//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DStatus.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DStatus_H
#define CG3DStatus_H

class CG3DStatus
{
    public:

        CG3DStatus() { mStatus = 0; }

        void operator=(int Flag) { mStatus = Flag; }
        bool Get(int Flag) { return mStatus & Flag; }
        void Set(int Flag) { mStatus |= Flag; }
        void Clr(int Flag) { mStatus &= ~Flag; }
        void Set(int Flag, bool value)
        {
            (value) ? Set(Flag) : Clr(Flag);
        }


    protected:

        unsigned int mStatus;
};

#endif
