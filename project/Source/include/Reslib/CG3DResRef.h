//---------------------------------------------------------------------------
//
// Klasse:    C3DResRef
//
//---------------------------------------------------------------------------


#ifndef CG3DResource_H
#define CG3DResource_H

class CG3DResource;
class CG3DResRef
{
    public:

        CG3DResRef()
        {
            mRef = NULL;
        }


        string mName;
        CG3DResource* mRef;
};

#endif
