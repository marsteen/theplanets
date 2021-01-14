//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CVector3T.hpp
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <cmath>

//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
CVector3<T> CVector3<T>::operator=(CVector3<T> v2)
{
    x = v2.x;
    y = v2.y;
    z = v2.z;

    return *this;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
CVector3<T> CVector3<T>::operator-(CVector3<T> v2)
{
    CVector3<T> v1;

    v1.x = x - v2.x;
    v1.y = y - v2.y;
    v1.z = z - v2.z;

    return v1;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
CVector3<T> CVector3<T>::operator+(CVector3<T> v2)
{
    CVector3<T> v1;

    v1.x = x + v2.x;
    v1.y = y + v2.y;
    v1.z = z + v2.z;

    return v1;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
CVector3<T> CVector3<T>::operator*(CVector3<T> v2)
{
    CVector3<T> v1;

    v1.x = (y * v2.z) - (z * v2.y);
    v1.y = (z * v2.x) - (x * v2.z);
    v1.z = (x * v2.y) - (y * v2.x);

    return v1;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
CVector3<T> CVector3<T>::operator*(T c)
{
    CVector3<T> v1;

    v1.x = x * c;
    v1.y = y * c;
    v1.z = z * c;

    return v1;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
CVector3<T> CVector3<T>::operator/(T c)
{
    CVector3<T> v1;

    v1.x = x / c;
    v1.y = y / c;
    v1.z = z / c;

    return v1;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
CVector3<T> CVector3<T>::operator+=(CVector3<T> v2)
{
    x += v2.x;
    y += v2.y;
    z += v2.z;

    return *this;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
CVector3<T> CVector3<T>::operator+=(CVector2<T> v2)
{
    x += v2.x;
    y += v2.y;

    return *this;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
CVector3<T> CVector3<T>::operator-=(CVector3<T> v2)
{
    x -= v2.x;
    y -= v2.y;
    z -= v2.z;

    return *this;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
CVector3<T> CVector3<T>::operator/=(T c)
{
    x /= c;
    y /= c;
    z /= c;

    return *this;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
void CVector3<T>::Print()
{
    std::cout << "x=" << x << "\ty=" << y << "\tz=" << z << std::endl;
}


//-------------------------::--------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
T CVector3<T>::Betrag()
{
    return std::sqrt((x * x) + (y * y) + (z * z));
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
void CVector3<T>::Normalize()
{
    T Lenght = Betrag();

    if (Lenght > 0)
    {
        x /= Lenght;
        y /= Lenght;
        z /= Lenght;
    }
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
void CVector3<T>::NormalVector(CVector3<T>* v1, CVector3<T>* v2)
{
    x = (v1->y * v2->z) - (v1->z * v2->y);
    y = (v1->z * v2->x) - (v1->x * v2->z);
    z = (v1->x * v2->y) - (v1->y * v2->x);

    Normalize();
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
void CVector3<T>::SubtractVector(CVector3<T>* v1, CVector3<T>* v2)
{
    x = v1->x - v2->x;
    y = v1->y - v2->y;
    z = v1->z - v2->z;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
T CVector3<T>::SkalarProdukt(CVector3<T>* v1)
{
    return (x * v1->x) + (y * v1->y) + (z * v1->z);
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
void CVector3<T>::Reverse()
{
    x = -x;
    y = -y;
    z = -z;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
void CVector3<T>::Set(T vx, T vy, T vz)
{
    x = vx;
    y = vy;
    z = vz;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
void CVector3<T>::RotationXZ(CVector3<T>* v2, T sinAlpha, T cosAlpha)
{
    float xerg, zerg;

    xerg = (cosAlpha * (x - v2->x)) - (sinAlpha * (z - v2->z));
    zerg = (sinAlpha * (x - v2->x)) + (cosAlpha * (z - v2->z));

    x = xerg + v2->x;
    z = zerg + v2->z;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
void CVector3<T>::RotationYZ(CVector3<T>* v2, T sinAlpha, T cosAlpha)
{
    float yerg, zerg;

    yerg = (cosAlpha * (y - v2->y)) - (sinAlpha * (z - v2->z));
    zerg = (sinAlpha * (y - v2->y)) + (cosAlpha * (z - v2->z));

    y = yerg + v2->y;
    z = zerg + v2->z;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector3<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template<class T>
void CVector3<T>::operator*=(T f)
{
    x *= f;
    y *= f;
    z *= f;
}
