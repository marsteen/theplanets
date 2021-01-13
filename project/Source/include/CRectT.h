

#ifndef CRECTT
#define CRECTT

template <class T>
class CRectT
{
	public:

		void Set(T _left, T _top, T _right, T _bottom)
		{
			left   = _left;
			top    = _top;
			right  = _right;
			bottom = _bottom;
		}
		bool InterSectRect(CRectT* r2, CRectT* ri);
		bool InRect(T x, T y);
		void TrimRect(void);
		void Show(char* str);

		T Width() { return right - left; }
		T Height() { return bottom - top; }

		T left;
		T top;
		T right;
		T bottom;

	protected:

		bool IntersectLine(T A1, T B1, T A2, T B2, T* A3, T* B3);



};

#include <CRectT.hpp>

#endif
