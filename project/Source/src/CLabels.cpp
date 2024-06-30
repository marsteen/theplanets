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

struct SLabelRows
{
    SLabelRows()
    {
        valid = false;
        featureName = -1;
        target = -1;
        diameter = -1;
        centerLatitude = -1;
        centerLongitude = -1;
        featureType = -1;
    }

    bool valid;
    int featureName;           // "Feature Name" 
    int target;                // "Target"
    int diameter;              // "Diameter"
    int centerLatitude;        // "Center Latitude"
    int centerLongitude;       // "Center Longitude
    int featureType;           // "Feature Type"
};

static void getLabelRows(SLabelRows& labelRows, const CRecord& record)
{
    int labelsFound = 0;
    for (int i = 0; i < record.size(); i++)
    {
        const std::string& text = record[i];
        std::cout << "label text=" << text << std::endl;
        if (text == "Feature Name")
        {
            labelRows.featureName = i;
            labelsFound++;
        }
        else
        if (text == "Target")
        {
            labelRows.target = i;
            labelsFound++;
        }
        else
        if (text == "Diameter")
        {
            labelRows.diameter = i;
            labelsFound++;
        }
        else
        if (text == "Center Latitude")
        {
            labelRows.centerLatitude = i;
            labelsFound++;
        }
        else
        if (text == "Center Longitude")
        {
            labelRows.centerLongitude = i;
            labelsFound++;
        }
        else
        if (text == "Feature Type")
        {
            labelRows.featureType = i;
            labelsFound++;
        }
    }
    labelRows.valid = (labelsFound == 6);
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
    const std::string Filename = std::string("Resource/Label/") + Bodyname + "_krater_tabs.csv";
    const std::string Basepath = "./";
    int Count = 0;

    mLabelList.clear();

    std::cout << "++++ READ LABELS:" << Filename << std::endl;

    if (db3.Read(&Records, Basepath, Filename, '\t'))
    {
        std::cout << "Records=" << Records.size() << std::endl;
        int line = 0;
        SLabelRows labelRows;

        for (std::list<CRecord>::const_iterator it = Records.begin();
            it != Records.end();
            ++it)
        {
            const CRecord& record = *it;
            SLabel Label;
            CStringTool st;
            if (line == 0)
            {
                getLabelRows(labelRows, record);
                std::cout << "labelRows.valid          :" << labelRows.valid << std::endl;
                std::cout << "labelRows.featureName    :" << labelRows.featureName << std::endl;
                std::cout << "labelRows.target         :" << labelRows.target << std::endl;
                std::cout << "labelRows.diameter       :" << labelRows.diameter << std::endl;
                std::cout << "labelRows.centerLatitude :" << labelRows.centerLatitude << std::endl;
                std::cout << "labelRows.centerLongitude:" << labelRows.centerLongitude << std::endl;
                std::cout << "labelRows.featureType    :" << labelRows.featureType << std::endl;
            }
            else
            {
                if ((it->size() >= 5) && (labelRows.valid))
                {                    
                    Label.mLabel = record[labelRows.featureName];
                    Label.mTyp = ELABELTYPE_KRATER;
                    Label.mLong = -st.StringTo<float>(record[labelRows.centerLongitude]) + 180.0;
                    Label.mLati = st.StringTo<float>(record[labelRows.centerLatitude]);
                    Label.mDiameter = st.StringTo<float>(record[labelRows.diameter]);
                    
                    Label.mLong = DEG_TO_RAD(Label.mLong);
                    Label.mLati = DEG_TO_RAD(Label.mLati);
                    mLabelList.push_back(Label);

                   // std::cout << "Label:" << Label.mLabel  << std::endl;
                }
            }
            line++;
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
//        std::cout << "Label found:" << it->mLabel << std::endl;
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

