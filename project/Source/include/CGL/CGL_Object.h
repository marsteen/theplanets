//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CGL_Object.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_OBJECT_H
#define CGL_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLinclude.h>
#include <CGL_Texture.h>
#include <Math/CVector3T.h>

enum ECGL_STATUS
{
    CGL_STATUS_ALPHA = 32
};

//#define DEG_TO_RAD(x)		((x) / 57.29577951)
//#define RAD_TO_DEG(x)		((x) * 57.29577951)

class CGL_Object : public CGL_Texture
{
    public:

        void Init();
        void DeleteDisplayList();
        virtual void MakeObject();
        virtual void Draw() const;

        CGL_Object();
        ~CGL_Object();

    protected:

        void SetNormalVertex(CVector3<float>* Origin, CVector3<float>* cf);

        GLuint mDisplayListHandle;
        GLfloat mMaterial[4];
        unsigned int mStatus;
};

#endif
