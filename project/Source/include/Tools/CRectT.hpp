//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CRectT.hpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

template<class T>
T maxT(T a, T b)
{
    return (a > b) ? a : b;
}


template<class T>
T minT(T a, T b)
{
    return (a < b) ? a : b;
}


//---------------------------------------------------------------------------
//
// Klasse:    CRectT
// Methode:   IntersectLine
//
// Die Schnittmenge zweier eindimensionaler Linien  wird berechnet.
//
// Linie 1: von A1 nach B1
// Linie 2: von A2 nach B2
// Linie 3: von A3 nach B3
//
// Linie 3 ist die Schnittmenge der Linien 1 und 2. Für den Fall, dass
// die beiden Linien sich nicht überschneiden, ist das Ergebnis
// undefiniert und false wird zurückgegeben.
//
// Rückgabewert: true - Linien überschneiden sich, Linie 3 (A3/B3)
//                      enthält die Schnittmenge
//
//               false - Schnittmenge ist leer
//
//---------------------------------------------------------------------------

template<class T>
bool CRectT<T>::IntersectLine(T A1, T B1, T A2, T B2, T* A3, T* B3)
{
    *A3 = maxT(A1, A2);
    if ((*A3 > B1) || (*A3 > B2))
    {
        return false;
    }

    *B3 = minT(B1, B2);
    if ((*B3 < A1) || (*B3 < A2))
    {
        return false;
    }

    return true;
}


//---------------------------------------------------------------------------
//
// Klasse:    CRectT
// Methode:   InterSectRect
//
// Die Schnittmenge zweier Rechtecke wird berechnet.
//
// ri enthalt die Schnittmenge der Rechtecke r1 und r2
//
// Rückgabewert: true - r1 und r2 haben Schnittmenge
//
//               false - Schnittmenge leer
//
//---------------------------------------------------------------------------

template<class T>
bool CRectT<T>::InterSectRect(CRectT* r2, CRectT* ri)
{
    if (IntersectLine(left, right, r2->left, r2->right, &(ri->left), &(ri->right)))
    {
        if (IntersectLine(top, bottom, r2->top, r2->bottom, &(ri->top), &(ri->bottom)))
        {
            return true;
        }
    }
    return false;
}


//---------------------------------------------------------------------------
//
// Klasse:    CRectT
// Methode:   TrimRect
//
//---------------------------------------------------------------------------

template<class T>
void CRectT<T>::TrimRect()
{
    T SwapVal;

    if (right < left)
    {
        SwapVal = left;
        left = right;
        right = SwapVal;
    }
    if (bottom < top)
    {
        SwapVal = top;
        top = bottom;
        bottom = SwapVal;
    }
}


//---------------------------------------------------------------------------
//
// Klasse:    CRectT
// Methode:   InRect
//
// Rückgabewert: true - Punkt x,y ist im Rechteck
//
//               false - nicht im Rechteck
//---------------------------------------------------------------------------

template<class T>
bool CRectT<T>::InRect(T x, T y)
{
    return (x >= left) && (x <= right) &&
           (y >= top) && (y <= bottom);
}


//---------------------------------------------------------------------------
//
// Klasse:    CRectT
// Methode:   Show
//
//---------------------------------------------------------------------------

template<class T>
void CRectT<T>::Show(char* xstr)
{
    //Debug2 << xstr << left << ' ' << top << ' ' << right << ' ' << bottom << '\n';
}
