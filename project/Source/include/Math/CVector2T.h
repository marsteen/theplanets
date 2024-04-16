//***************************************************************************
//
//
// @PROJECT  :	Basic SDL
// @VERSION  :	1.0
// @FILENAME :	CVector2T.h
// @DATE     :	8.1.2015
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************


#ifndef CVECTOR2T_H
#define CVECTOR2T_H

template<class T>
class CVector2
{
    public:

        T x;
        T y;

        CVector2() {  }
        CVector2(T _x, T _y) { x = _x; y = _y; }

        void Set(T _x, T _y) { x = _x; y = _y; }

        T* v(int a = 0) { return &x + a; }

        CVector2<T> operator=(const CVector2<T>& v2);
        CVector2<T> operator+(CVector2<T> v2) const;
        CVector2<T> operator-(CVector2<T> v2) const;
        CVector2<T> operator*(CVector2<T> v2) const;
        CVector2<T> operator*(T f) const;
        void operator*=(T f);

        CVector2<T> operator+=(CVector2<T> v2);
        CVector2<T> operator-=(CVector2<T> v2);
        CVector2<T> operator/(T c) const;
        CVector2<T> operator/=(T c);

        T Betrag() const;
        void Normalize();
        void Reverse();
        void SubtractVector(CVector2<T>* v1, CVector2<T>* v2);
        void RotationXY(const CVector2<T>* v2, T sinAlpha, T cosAlpha);
        void RotationXY(T sinAlpha, T cosAlpha);
        void DriftVector(CVector2<T>* v2, T drift, T sinAlpha, T cosAlpha) const;
        void DriftVector(CVector2<T>* v2, T drift, T deg_angle) const;
        T GetAngleDeg(const CVector2<T>* v2) const;


        bool operator==(CVector2<T>& v2)
        {
            return (x == v2.x) && (y == v2.y);
        }


        bool operator!=(CVector2<T>& v2)
        {
            return (x != v2.x) || (y != v2.y);
        }


        T Abstand(const CVector2<T>* v1) const
        {
            return (*this - *v1).Betrag();
        }


        T SkalarProdukt(const CVector2<T>* v1) const;
};

#include "CVector2T.hpp"

#endif
