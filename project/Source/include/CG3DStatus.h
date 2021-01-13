class CG3DStatus
{
	public:

		CG3DStatus() { mStatus = 0; }

		void operator=(int Flag) { mStatus = Flag; }
    bool Get(int Flag) { return mStatus & Flag; }
		void Set(int Flag) { mStatus |= Flag; }
		void Clr(int Flag) { mStatus &= ~Flag; }
		void Set(int Flag, bool value)
		{
			(value) ? Set(Flag) : Clr(Flag);
		}

	protected:

		unsigned int mStatus;

};
