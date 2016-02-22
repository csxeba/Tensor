#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstring>
#include <initializer_list>

#include "Tensor.h"

template <typename T>
class Vector : public Tensor<T>
{
    public:
        Vector(int N, T defval=0);
        Vector(int N, T*);
        Vector(std::initializer_list<T>);
        Vector(const Vector<T>&);
        //No need for Vector(Matrix&) and (Volume) and (HVolume),
        //because they are all subclasses of Vector and the above
        //Constructor has to be able to handle that case with size()!
        
        ~Vector()               {delete Guts;}

        virtual T* point()      {return Guts;}
        virtual int* shape()    {return &Size;}
        virtual int size()      {return Size;}       
        virtual T at(int x)     {return Guts[x];}
        virtual T* atp(int x)   {return Guts+x;}
        virtual void set(int x, T val) {Guts[x] = val;}
        
              T& operator[](int x)           {return Guts[x];}
        const T& operator[](int x) const     {return Guts[x];}
        
        virtual void print();        
        
    protected:
        T*  Guts;
        int Size;
};

template <typename T>
Vector<T>::Vector(int N, T defval)
{
    Size = N;
    Guts = new T[Size];
    for(int x=0;x<Size;x++) {
        Guts[x] = defval;
    }
}

template <typename T>
Vector<T>::Vector(int N, T* ar)
{
    Size = N;
    Guts = ar;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> l)
{
    Size = l.size();
    Guts = new T[Size];
    int i=0;
    for(auto x=l.begin();x!=l.end();x++, i++) {
        Guts[i] = *x;
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T> &v)
{
    Size = v.Size;
    Guts = v.Guts;
}

template <typename T>
void Vector<T>::print() 
{
    for (int i=0; i<Size; i++) {
        std::cout << Guts[i] << ", ";
    }
    std::cout << std::endl;
}

// Vector declarations end

#endif /* VECTOR_H */

