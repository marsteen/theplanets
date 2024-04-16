//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_Ring.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_Ring_H
#define CGL_Ring_H

class CGL_Ring : public CGL_Object
{
    public:

        void MakeObject(void);

        CVector3<float> mOrigin;
        int mSegments;
        float mRadius;
};

void CGL_Ring::MakeObject()
{
    CVector3<float> CirclePoint;
    float Alpha = 0;
    float AlphaPlus = 360.0 / mSegments;

    glBegin(GL_TRIANGLE_FAN);
    glVertex3fv(mOrigin.v());

    for (int i = 0; i <= mSegments; i++)
    {
        CirclePoint.x = (cos(Alpha) * mRadius) + mOrigin.x;
        CirclePoint.y = (sin(Alpha) * mRadius) + mOrigin.y;
        CirclePoint.z = mOrigin.z;
        glVertex3fv(CirclePoint.v());

        Alpha += AlphaPlus;
    }


    glEnd();
}


#endif
