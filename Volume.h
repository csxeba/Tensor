#ifndef VOLUME_H
#define VOLUME_H

#include <iostream>

#include "Vector.h"

template <typename T>
class Volume: public Vector<T>
{
    public:
        Volume(int M, int N, int O, T defval=0);
        Volume(int M, int N, int O, Vector<T>&);
        Volume(Volume<T>&);

        int* shape()        {return Dims;}
        void print();
        
        T at(int x,int y,int z)
            {return Vector<T>::Guts[z*Dims[0]+y*Dims[1]+x];}
        T* atp(int x,int y,int z)
            {return &Vector<T>::Guts[z*Dims[0]+y*Dims[1]+x];}
        bool dimsmatch(Volume<T>&);
        void invert();
        void set(int x, int y, int z, T val)
            {Vector<T>::Guts[z*Dims[0]+y*Dims[1]+x] = val;}
        
              T* operator[](int x);
        const T* operator[](int x) const;
        
    private:
        int Dims[3];
};

template <typename T>
Volume<T>::Volume(int M, int N, int O, T defval) :
        Vector<T>::Vector(M*N*O, defval)
{
    Dims[0] = M;
    Dims[1] = N;
    Dims[2] = O;
}

template <typename T>
Volume<T>::Volume(int M, int N, int O, Vector<T> &vec) :
        Vector<T>::Vector(M*N*O, vec)
{
    Dims[0] = M;
    Dims[1] = N;
    Dims[2] = O;
}

template <typename T>
void Volume<T>::print()
{
    for (int i=0; i<Dims[0]; i++) {
        for (int j=0; j<Dims[1]; j++) {
            for (int k = 0; k < Dims[2]; k++) {
                std::cout << Vector<T>::Guts[i*Dims[0]+j*Dims[1]+k] << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << "-------------------------" << std::endl;
    }
}

template <typename T>
bool Volume<T>::dimsmatch(Volume<T>& vol)
{
    int* vshape = vol.shape();
    return (Dims[0]==vshape[0] and Dims[1]==vshape[1] and Dims[2]==vshape[2]);
}

template <typename T>
void Volume<T>::invert()
{
    int temp = Dims[0];
    Dims[0] = Dims[2];
    Dims[2] = temp;
}

template <typename T>
T* Volume<T>::operator[](int x)
{
    return atp(x);
}

template <typename T> const
T* Volume<T>::operator[](int x) const
{
    return atp(x);
}


#endif /* VOLUME_H */

