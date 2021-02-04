#ifndef CRANDOM_H
#define CRANDOM_H

template<typename T>
class CRandom
{
    public:

        static T Get01();
        static T Get(T Low, T High);
        static int GetInt(int Low, int High);

        // Liefert 1 oder -1
        static int Sign()
        {
            return (GetInt(0, 1) == 0) ? 1 : -1;
        }
};

#include "CRandom.hpp"

#endif
