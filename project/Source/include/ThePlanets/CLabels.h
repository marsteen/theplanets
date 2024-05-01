#ifndef CLabels_H
#define CLabels_H

#include <string>
#include <list>
#include <SLabel.h>
#include <STransformContext.h>
#include <SG3DcomData.h>

class CG3DReslistInterface;

class CLabels
{
    public:

        CLabels(STransformContext* mTransformContext);

        void ReadLabels(const std::string& Bodyname);
        void InitLabels(CG3DReslistInterface* gi, float Radius, int sx);
//        void InitLabels(const std::string& BodyName, float Radius, int sx);
        void GetLabelsScreenKoor();
        void DrawLabels(CG3DReslistInterface* gi);

    protected:
    
        void DrawCross(float xc, float yc) const;
        void DrawTriangle(float xc, float yc) const;
        void GetScreenKoor(SLabel& Label);

        std::list<SLabel> mLabelList;
        std::list<SLabel> mAktLabelList;
        SG3DcomData mLabelName;
        STransformContext* mTransformContext;

};

#endif

