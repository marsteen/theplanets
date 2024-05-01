//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CLabels.cpp
// @DATE     :	1.5.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <iostream>
#include <GLinclude.h>
#include <CStringTool.h>
#include <CLabels.h>
#include "CG3DGlobals.h"
#include <CG3DReslistInterface.h>
#include <CFileIO.h>
#include <CDatabase3.h>


// ---------------------------------------------------------------------------
//
// KLASSE        : CLabels
// METHODE       : ReadLabels
//
// ---------------------------------------------------------------------------

CLabels::CLabels(STransformContext* transformContext) : 
    mTransformContext(transformContext)
{
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CLabels
// METHODE       : ReadLabels
//
// ---------------------------------------------------------------------------

void CLabels::ReadLabels(const std::string& Bodyname)
{
    CDatabase3 db3;
    std::list<CRecord> Records;

    CFileIO fio;
    std::string Filename = std::string("Resource/Label/") + Bodyname + "_krater.txt";
    std::string Basepath = "./";
    int Count = 0;

    mLabelList.clear();

    std::cout << "++++ READ LABELS:" << Filename << std::endl;

    if (db3.Read(&Records, Basepath, Filename, '\t'))
    {
        std::cout << "Records=" << Records.size() << std::endl;

        for (std::list<CRecord>::iterator it = Records.begin();
            it != Records.end();
            ++it)
        {
            SLabel Label;
            CStringTool st;
            std::cout << "it->size()=" << it->size() << std::endl;

            if (it->size() == 3)
            {
                Label.mLabel = (*it)[0];
                Label.mTyp = ELABELTYPE_KRATER;
                Label.mLong = -st.StringTo<float>((*it)[2]) + 180.0;
                Label.mLati = st.StringTo<float>((*it)[1]);
                std::string LabelType = (*it)[1];

                Label.mLong = DEG_TO_RAD(Label.mLong);
                Label.mLati = DEG_TO_RAD(Label.mLati);
                mLabelList.push_back(Label);

                std::cout << "Label:" << Label.mLabel  << std::endl;
            }
        }
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CLabels
// METHODE       : InitLabels
//
//
//
// ---------------------------------------------------------------------------

void CLabels::InitLabels(CG3DReslistInterface* gi, float Radius, int sx)
{

    mLabelName.mName = "LabelName";
    gi->SendCommand(EG3DcomSearchChild, &mLabelName);

    mAktLabelList.clear();

    for (std::list<SLabel>::iterator it = mLabelList.begin();
        it != mLabelList.end();
        ++it)
    {
        it->LongLatiToSphere(Radius, sx);
        //LongLatiToSphere(it->mVec3D, it->mLong, it->mLati, Radius);
        mAktLabelList.push_back(*it);
        std::cout << "Label found:" << it->mLabel << std::endl;
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CGLApplication
// METHODE       : GetScreenKoor
//
//
//
// ---------------------------------------------------------------------------

void CLabels::GetScreenKoor(SLabel& Label)
{
    float Zval;
    CVector3<float> Origin;
    CVector3<float> TestVec = Label.mVec3D;

    Origin.Set(0, 0, 0);

    TestVec.RotationXZ(&Origin, mTransformContext->mSinYrot, mTransformContext->mCosYrot);
    TestVec.RotationYZ(&Origin, mTransformContext->mSinXrot, mTransformContext->mCosXrot);

    gluProject(
        Label.mVec3D.x, Label.mVec3D.y, Label.mVec3D.z,
        mTransformContext->mModelMatrix,
        mTransformContext->mProjectionMatrix,
        mTransformContext->mViewport,
        &Label.mScreenKoor.x, &Label.mScreenKoor.y, &Label.mScreenKoor.z);

    if (TestVec.z > -10.0)
    {
        Label.mScreenKoor.z = 2;
    }
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CLabels
// METHODE       : GetLabelsScreenKoor
//
// ---------------------------------------------------------------------------

void CLabels::GetLabelsScreenKoor()
{
    glPushMatrix();
    glRotatef(mTransformContext->mXrot, 1.0, 0.0, 0.0);    // Rotation um X-Achse
    glRotatef(mTransformContext->mYrot, 0.0, 1.0, 0.0);    

    for (std::list<SLabel>::iterator it = mAktLabelList.begin();
        it != mAktLabelList.end();
        ++it)
    {
        GetScreenKoor(*it);
    }
    glPopMatrix();

}

// ---------------------------------------------------------------------------
//
// KLASSE        : CLabels
// METHODE       : DrawLabels
//
// ---------------------------------------------------------------------------

void CLabels::DrawLabels(CG3DReslistInterface* gi)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (std::list<SLabel>::iterator il = mAktLabelList.begin();
        il != mAktLabelList.end();
        ++il)
    {
        if (il->mScreenKoor.z < 1.0)
        {
            mLabelName.mChrParam = il->mLabel.c_str();
            mLabelName.mPos.x = (int) il->mScreenKoor.x;
            mLabelName.mPos.y = (int) il->mScreenKoor.y - 6;

            if ((il->mTyp == ELABELTYPE_APOLLO) ||
                (il->mTyp == ELABELTYPE_KRATER) ||
                (il->mTyp == ELABELTYPE_BERG))
            {
                mLabelName.mPos.x += 6;
            }

            glColor4f(0.0, 0.0, 0.0, 1.0);
            gi->SendCommand(EG3DcomDrawString, &mLabelName);

            mLabelName.mPos.x++;
            mLabelName.mPos.y++;

            switch (il->mTyp)
            {
                case ELABELTYPE_APOLLO:
                    glDisable(GL_TEXTURE_2D);
                    glColor4f(0.2, 0.8, 0.2, 1.0);
                    DrawCross(il->mScreenKoor.x, il->mScreenKoor.y);
                    glEnable(GL_TEXTURE_2D);
                    break;

                case ELABELTYPE_KRATER:
                    glDisable(GL_TEXTURE_2D);
                    glColor4f(0.8, 0.8, 1.0, 1.0);
                    DrawCross(il->mScreenKoor.x, il->mScreenKoor.y);
                    glEnable(GL_TEXTURE_2D);
                    break;

                case ELABELTYPE_BERG:
                    glDisable(GL_TEXTURE_2D);
                    glColor4f(0.4, 0.8, 0.2, 1.0);
                    DrawTriangle(il->mScreenKoor.x, il->mScreenKoor.y);
                    glEnable(GL_TEXTURE_2D);
                    break;

                default:

                    glColor4f(0.8, 0.8, 0.8, 1.0);
                    break;
            }

            gi->SendCommand(EG3DcomDrawString, &mLabelName);
        }
    }
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glLineWidth(1.0);
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CLabels
// METHODE       : DrawCross
//
// ---------------------------------------------------------------------------

void CLabels::DrawCross(float xc, float yc) const
{
    glLineWidth(1.6);
    glBegin(GL_LINES);
    glVertex2f(xc - 4, yc - 4);
    glVertex2f(xc + 4, yc + 4);
    glVertex2f(xc - 4, yc + 4);
    glVertex2f(xc + 4, yc - 4);
    glEnd();
}

// ---------------------------------------------------------------------------
//
// KLASSE        : CLabels
// METHODE       : DrawTriangle
//
// ---------------------------------------------------------------------------

void CLabels::DrawTriangle(float xc, float yc) const
{
    glLineWidth(1.6);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xc, yc + 4);
    glVertex2f(xc + 4, yc - 4);
    glVertex2f(xc - 4, yc - 4);
    glEnd();
}

