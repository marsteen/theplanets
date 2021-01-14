//---------------------------------------------------------------------------
//
// Klasse:    C3DGResourceButton
//
//---------------------------------------------------------------------------

class CG3DResourceOButton;
class CG3DResChild;

class CG3DResourceButton : public CG3DGroup, public CG3DResourceImgRef
{
    public:

        CG3DResourceButton();
        void Show(void);
        void Reset(int mode);
        void AddResRef(CG3DResource* res);
        void Adjust(SG3DDrawParams* dp);


        int UnscaledWidth(void);
        int UnscaledHeight(void);
        bool Inside(SG3DDrawParams* dp, CVector2<int>* Mouse);
        void ResetStatus(void);
        void ClickAction(void);

        // void SetStrRef(CG3DResourceString* str) { mStrRef = str; }
        void SetBoxRef(CG3DResourceBox* box) { mBoxRef = box; }
        void SetOButton(CG3DResourceOButton* ob)    { mObutton = ob; }
        void SetContent(CG3DResChild* rc) { mContent = rc; }
        void SetButtonStatus(EG3DButtonStatus bst);

        int GetButtonStatus() { return mBtStatus; }
        void SetGroupParent(CG3DResource* gp) { mGroupParent = gp; }
        void KlappEin(void);
        void DisableRadioGroup(void);

        void Draw(SG3DDrawParams* dp);
        void DrawButton(SG3DDrawParams* dp);

    protected:

        void GetGroupParent(CG3DResource* pr);
        void ResetStringColor(void);
        void SetStatusRollover(void);

        CG3DResourceBox* mBoxRef;       // Box-Reference
        CG3DResourceButton* mJoinRef;   // Join Button
        int mBtStatus;                  // Button Status
        CG3DResourceOButton* mObutton;  // Option-Button
        float* mStringColor;
        CG3DResChild* mContent;
};
