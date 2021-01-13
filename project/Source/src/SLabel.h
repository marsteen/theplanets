#ifndef SLABEL_H
#define SLABEL_H

#include <CVector3T.h>


enum ELabelType
{
	ELABELTYPE_UNDEFINED,     // undefiniert
	ELABELTYPE_MARE,          // Mondmeer (Mare)
	ELABELTYPE_APOLLO,        // Apollo-Landestelle (la)
	ELABELTYPE_KRATER,        // Krater (kr)
	ELABELTYPE_BERG,          // Berg (bg)
	ELABELTYPE_MEER,          // Meer (me)
  ELABELTYPE_STADT,         // Stadt (st)
};

struct SLabel
{
	std::string  mBody;
	std::string  mLabel;
	ELabelType   mTyp;
	float        mLong;
	float        mLati;
	float        mRot;

	void LongLatiToSphere(float Radius, int sx);

	mutable CVector3<float>  mVec3D;
	mutable CVector3<double> mScreenKoor;
};

#endif
