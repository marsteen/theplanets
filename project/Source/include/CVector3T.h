//***************************************************************************
//
//
// @PROJECT  :	The Planets
// @VERSION  :	2.0
// @FILENAME :	CVector3T.h
// @DATE     :	13.1.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CVECTOR3T_H
#define CVECTOR3T_H


template<class T>
class CVector2
{
    public:

        T x;
        T y;

        CVector2() { }
        CVector2(T _x, T _y) { x = _x; y = _y; }

        void Set(T _x, T _y) { x = _x; y = _y; }

        T* v(int a = 0) { return &x + a; }

        CVector2<T> operator=(CVector2<T> v2);
        CVector2<T> operator+(CVector2<T> v2);
        CVector2<T> operator-(CVector2<T> v2);
        CVector2<T> operator*(CVector2<T> v2);
        CVector2<T> operator*(T f);
        void operator*=(T f);

        CVector2<T> operator+=(CVector2<T> v2);
        CVector2<T> operator-=(CVector2<T> v2);
        CVector2<T> operator/(T c);
        CVector2<T> operator/=(T c);

        T Betrag(void);
        void Normalize(void);
        void Reverse(void);
        void SubtractVector(CVector2<T>* v1, CVector2<T>* v2);
        void RotationXY(CVector2<T>* v2, T sinAlpha, T cosAlpha);


        bool operator==(CVector2<T>& v2)
        {
            return (x == v2.x) && (y == v2.y);
        }


        bool operator!=(CVector2<T>& v2)
        {
            return (x != v2.x) || (y != v2.y);
        }


        T Abstand(CVector2<T>* v1)
        {
            return (*this - *v1).Betrag();
        }


        T SkalarProdukt(CVector2<T>* v1);
};



template<typename T>
class CVector3
{
    public:

        T x, y, z;

        CVector3()
        {
            x = 0;
            y = 0;
            z = 0;
        }


        CVector3(T _x, T _y, T _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }


        T* v(int a = 0) { return &x + a; }
        CVector3<T> operator=(CVector3<T> v2);
        CVector3<T> operator+(CVector3<T> v2);
        CVector3<T> operator-(CVector3<T> v2);
        CVector3<T> operator*(CVector3<T> v2);
        CVector3<T> operator*(T f);
        void operator*=(T f);

        CVector3<T> operator+=(CVector3<T> v2);
        CVector3<T> operator-=(CVector3<T> v2);
        CVector3<T> operator+=(CVector2<T> v2);

        CVector3<T> operator/(T c);
        CVector3<T> operator/=(T c);



        void Print(void);

        void NormalVector(CVector3<T>* v1, CVector3<T>* v2);
        void SubtractVector(CVector3<T>* v1, CVector3<T>* v2);

        T Betrag(void);
        void Normalize(void);
        void Reverse(void);
        void Set(T vx, T vy, T vz);

        void RotationXZ(CVector3<T>* v2, T sinAlpha, T cosAlpha);
        void RotationYZ(CVector3<T>* v2, T sinAlpha, T cosAlpha);


        bool operator==(CVector3<T> v2)
        {
            return (CVector2<T>::x == v2.x) && (CVector2<T>::y == v2.y) && (z == v2.z);
        }


        T Abstand(CVector3<T>* v1)
        {
            return (*this - *v1).Betrag();
        }


        T SkalarProdukt(CVector3<T>* v1);
};

template<class T>
class CVector4 : public CVector3<T>
{
    public:

        T w;
};

#include <CVector2T.hpp>
#include <CVector3T.hpp>

#endif
