//------------------------------------------------------------------------------
//
// PROJECT : 3D Globus
//
// FILE    : CVector2<T>.cpp
//
// VERSION : 1.0
//
// AUTOR   : Martin Steen
//           Imagon GmbH
//
//
//
//------------------------------------------------------------------------------
//
// Inhalt: Implementation von CVector2<T> Klassen
//
//------------------------------------------------------------------------------
// Revisionsgeschichte:
//
// 11.04.2005 erstellt - Martin Steen
//
//------------------------------------------------------------------------------


//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
CVector2<T> CVector2<T>::operator=(CVector2<T> v2)
{
	x = v2.x;
	y = v2.y;

	return *this;
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
CVector2<T> CVector2<T>::operator-(CVector2<T> v2)
{
	CVector2<T> v1;

	v1.x = x - v2.x;
	v1.y = y - v2.y;

	return v1;
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
CVector2<T> CVector2<T>::operator+(CVector2<T> v2)
{
	CVector2<T> v1;

	v1.x = x + v2.x;
	v1.y = y + v2.y;

	return v1;
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
CVector2<T> CVector2<T>::operator*(CVector2<T> v2)
{
	CVector2<T> v1;

	//v1.x = (y * v2.y) - (z * v2.y);
	//v1.y = (z * v2.x) - (x * v2.z);

	return v1;
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
CVector2<T> CVector2<T>::operator*(T c)
{
	CVector2<T> v1;

	v1.x = x * c;
	v1.y = y * c;

	return v1;
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
CVector2<T> CVector2<T>::operator/(T c)
{
	CVector2<T> v1;

	v1.x = x / c;
	v1.y = y / c;

	return v1;
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
CVector2<T> CVector2<T>::operator+=(CVector2<T> v2)
{
	x += v2.x;
	y += v2.y;

	return *this;
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
CVector2<T> CVector2<T>::operator-=(CVector2<T> v2)
{
	x -= v2.x;
	y -= v2.y;

	return *this;
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
CVector2<T> CVector2<T>::operator/=(T c)
{
	x /= c;
	y /= c;

	return *this;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
T CVector2<T>::Betrag()
{
	return sqrt((x * x) + (y * y ));
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
void CVector2<T>::Normalize()
{
	T Lenght = Betrag();

  if (Lenght > 0)
  {
		x /= Lenght;
		y /= Lenght;
	}
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
void CVector2<T>::SubtractVector(CVector2<T>* v1, CVector2<T>* v2)
{
	x = v1->x - v2->x;
	y = v1->y - v2->y;
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
T CVector2<T>::SkalarProdukt(CVector2<T>* v1)
{
	return (x * v1->x) + (y * v1->y);
}

//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
void CVector2<T>::Reverse()
{
	x = -x;
	y = -y;
}



//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

template <class T>
void CVector2<T>::operator*=(T f)
{
	x *= f;
	y *= f;
}


//---------------------------------------------------------------------------
//
// Klasse:		CVector2<T>
// Methode:
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

// Drehen des Vectors in der XY Ebene um den Punkt v2 und den
// Winkel Alpha

template <class T>
void CVector2<T>::RotationXY(CVector2<T>* v2, T sinAlpha, T cosAlpha)
{
	T xerg, yerg;

  xerg = (cosAlpha * (x - v2->x)) - (sinAlpha * (y - v2->y));
  yerg = (sinAlpha * (x - v2->x)) + (cosAlpha * (y - v2->y));

  x = xerg + v2->x;
  y = yerg + v2->y;
}
