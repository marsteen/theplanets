
#ifndef CSTRINGCONVERTER
#define CSTRINGCONVERTER

class CStringConverter
{
	public:

		int   ToInt(string& s);
		float ToFloat(string& s);
		float ToDouble(string& s);

		string ToStr(int n);
};

#endif // CSTRINGCONVERTER
