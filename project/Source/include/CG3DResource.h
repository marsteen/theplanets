//---------------------------------------------------------------------------
//
// Klasse:    CG3DResource
//
//---------------------------------------------------------------------------

class CG3DResourceButton;
class CG3DResourceKnot;

class CG3DResource
{
    public:

        CG3DResource()
        {
            mType = ERTYPE_VOID;
        }


        ~CG3DResource();



        bool IsButton()
        {
            return (mType == ERTYPE_BUTTON) ||
                   (mType == ERTYPE_OBUTTON) ||
                   (mType == ERTYPE_SLIDER);
        }


        bool Rollover(SG3DDrawParams* dp, CVector2<int>* Mouse, bool TestRollover);

        CG3DResChild* FindChild(EResourceType type);
        CG3DResRef*   FindRef(EResourceType type);

        float Width(SG3DDrawParams* dp);
        float Height(SG3DDrawParams* dp);
        void BackDraw(SG3DDrawParams* dp);
        void FrontDraw(SG3DDrawParams* dp);

        virtual void AddResRef(CG3DResource* res);
        virtual void Draw(SG3DDrawParams* dp);
        virtual void Show(void);
        virtual void Adjust(SG3DDrawParams* dp);

        virtual void Reset(int mode) { }
        virtual bool Inside(SG3DDrawParams* dp, CVector2<int>* Mouse);
        virtual int UnscaledWidth(void);
        virtual int UnscaledHeight(void);
        virtual bool Check(void);

        void Activate(bool v);
        void ActivateTooltipp(bool On);
        void Deactivate(void);
        void SetParents(CG3DResource* p);
        void DeactivateButtonGroup(CG3DResourceButton* GroupButton);
        void DeactivateKnotGroup(CG3DResourceKnot* GroupButton);

        void SearchChild(string& Name);

        const char* GetTypeName(void);
        bool ParseColor(string& ColorString, float* Color);

        string mName;
        EResourceType mType;
        list<CG3DResChild> mChilds;
        list<CG3DResRef> mRefs;
        CG3DResource* mParent;

    protected:

        float AdjustY(float y);
        void ShowColor(char* s, float* f);
        void SetColorWhite(void);
        void SetColorWhite(float** ColPtr);
        bool Showparams(SG3DDrawParams* dp);

        void GetChildParams(SG3DDrawParams* cdp, SG3DDrawParams* Parent, SG3DDrawParams* Child);
};
