

#ifndef CGL_CIRCLE_H
#define CGL_CIRCLE_H


class CGL_Circle : public CGL_Object
{
	public:

		void MakeObject(void);

		CVector3<float> mOrigin;
		int             mSegments;
		float           mRadius;

};

#endif
