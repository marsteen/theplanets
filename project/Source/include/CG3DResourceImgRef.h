class CG3DResourceImgRef : public  CG3DResource
{
	public:

		CG3DResourceImgRef()
		{
			mImgRef   = NULL;
			mStdImage = 0;     // Standard-Image
		}

		bool Check() { return mImgRef != NULL; }

		CG3DResourceImage* mImgRef;   // Image reference

		int UnscaledWidth(void);
		int UnscaledHeight(void);

		int mStdImage;

};
