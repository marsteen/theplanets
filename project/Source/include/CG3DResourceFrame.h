


class CG3DResourceFrame : public CG3DResource
{
	public:

		int  UnscaledWidth()  { return mRect.Width(); }
		int  UnscaledHeight() { return mRect.Height(); }

		CRectT<int>	mRect;
};
