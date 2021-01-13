//---------------------------------------------------------------------------
//
// Klasse:    C3DGResourceDialog
//
//---------------------------------------------------------------------------

class CG3DResourceDialog : public CG3DResourceImgRef
{
	public:

		CG3DResourceDialog()
		{
			mBoxRef = NULL;
		}

		void Draw(SG3DDrawParams* dp);
		void AddResRef(CG3DResource* res);

		int UnscaledWidth(void);
		int UnscaledHeight(void);

	protected:

		CG3DResourceBox* mBoxRef;


};
