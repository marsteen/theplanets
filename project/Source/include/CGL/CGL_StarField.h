#ifndef CGL_StarField_H
#define CGL_StarField_H

#include <CGL_Object.h>

class CGL_StarField : public CGL_Object
{
    public:

        CGL_StarField(int Stars)
        {
            mStars = Stars;
        }


    protected:


        void MakeObject();

        int mStars;
};

#endif
