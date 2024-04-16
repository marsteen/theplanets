//---------------------------------------------------------------------------
//
// PROJECT : Imagon
//
//
// AUTOR   : Martin Steen
//           email: martin@martin-steen.de
//
//
//----------------------------------------------------------------------------

#include <cstdlib>

template<typename T>
T CRandom<T>::Get01()
{
    return T(rand()) / T(RAND_MAX);
}


//---------------------------------------------------------------------------
//
// KLASSE        : CRandom
// METHODE       : Get
//
//
//
//---------------------------------------------------------------------------

template<typename T>
T CRandom<T>::Get(T Low, T High)
{
    return (Get01() * (High - Low)) + Low;
}


//---------------------------------------------------------------------------
//
// KLASSE        : CRandom
// METHODE       : GetInt
//
//
//
//---------------------------------------------------------------------------

template<typename T>
int CRandom<T>::GetInt(int Low, int High)
{
    return (int)((Get01() * (High - Low + 1)) + Low);
}
