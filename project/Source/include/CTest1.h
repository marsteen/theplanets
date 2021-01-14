template<typename T>
class CTest1
{
    protected:

        T a;
};

template<typename T>
class CTest2 : public CTest1<T>
{
    public:

        void Function1()
        {
            //a = 0; // ERROR - a undeclared
        }


        void Function2()
        {
            CTest1<T>::a = 0; // WORKS
        }


        void Function3()
        {
            T(a) = 0; // WORKS
        }
};


template<typename T>
class B
{
    public:
        void f() {}
};

class A : public B<int>
{
    void Function1()
    {
        f();
    }
};
