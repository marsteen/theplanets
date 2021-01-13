class CG3DResChild : public CG3DResRef
{
	public:

		CG3DResChild();

		CG3DStatus      mStatus;
		SG3DDrawParams  mDrawParams;
		SG3DDrawParams  mOrigParams;
		unsigned int    mAlignment;
		EG3DStretchMode mStretchMode;

		void GetDrawParams(SG3DDrawParams* Parent);
		void CalcAlignPosition(SG3DDrawParams* pa);
		void Draw(SG3DDrawParams* pa);
		void SetPosition(CVector2<float>* NewPos, unsigned int Flags=0);

		float Width(void);
		float Height(void);
		float Width(SG3DDrawParams* dp);
		float Height(SG3DDrawParams* dp);
		void  Adjust(SG3DDrawParams* dp);


	protected:

		void GetMaxY(SG3DDrawParams* pa, float* MaxY);
		void GetParams(SG3DDrawParams* pa, SG3DDrawParams* Parent);

};
