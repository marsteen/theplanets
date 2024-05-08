#ifndef STransformContext_H
#define STransformContext_H

struct STransformContext
{
    STransformContext():
        mXrot(0.0f),
        mYrot(0.0f),
        mZrot(0.0f),
        mYrotAuto(0.0f),
        mSinXrot(0.0f),
        mCosXrot(0.0f),
        mSinYrot(0.0f),
        mCosYrot(0.0f)
    {
    }

    float mXrot;
    float mYrot;
    float mZrot;
    float mYrotAuto;

    float mSinXrot;
    float mCosXrot;
    float mSinYrot;
    float mCosYrot;

    double mModelMatrix[16];
    double mProjectionMatrix[16];
    int mViewport[4];
};

#endif
