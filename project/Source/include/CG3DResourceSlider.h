//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CG3DResourceSlider.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DResourceSlider_H
#define CG3DResourceSlider_H

class CG3DResourceSlider : public CG3DResourceButton
{
    public:

        void SetSliderLimits(float Slmin, float Slmax)
        {
            mSliderMin = Slmin;
            mSliderMax = Slmax;
        }


        EG3DSliderType mSliderType;
        float mSliderPos;
        float mSliderMin;
        float mSliderMax;
};

#endif
