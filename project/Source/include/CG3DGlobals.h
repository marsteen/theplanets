enum ELanguage
{
    ELANG_GERMAN,
    ELANG_ENGLISH,
    ELANG_SPANISH,
    ELANG_FRENCH
};

class CG3DGlobals
{
    public:

        CG3DGlobals()
        {
            mLanguage = ELANG_GERMAN;
            mRolloverColor[0] = 1.0;
            mRolloverColor[1] = 1.0;
            mRolloverColor[2] = 0.0;
            mRolloverColor[3] = 1.0;
            mTooltippTime = 100;
        }


        int mWindowWidth;
        int mWindowHeight;
        int mTooltippTime;
        ELanguage mLanguage;
        void* mClickedObject;
        float mRolloverColor[4];
        float mTTframeColor[4];
        float mTTboxColor[4];
        float mTTfontColor[4];
};
