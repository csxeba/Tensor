#ifndef HVOLUME_H
#define HVOLUME_H

#include <cstring>

#include "Vector.h"
#include "Volume.h"

template <typename T>
class HVolume: public Vector<T>
{
    public:
        HVolume(int M, int N, int O, int P, T defval=0);
        HVolume(int M, int N, int O, int P, Vector<T>&);
        HVolume(HVolume<T>&);

        int* shape()        {return Dims;}
        void print();
        
        T at(int x,int y, int z, int f)
            {return Vector<T>::Guts[f*Dims[0]+z*Dims[1]+y*Dims[2]+x];}
        T* atp(int x, int y, int z, int f)
            {return &Vector<T>::Guts[f*Dims[0]+z*Dims[1]+y*Dims[2]+x];}
        bool dimsmatch(HVolume<T>&);
        void set(int x, int y, int z, int f, T val)
            {Vector<T>::Guts[f*Dims[0]+z*Dims[1]+y*Dims[2]+x] = val;}
        
              T* operator[](int x);
        const T* operator[](int x) const;
        
    private:
        int Dims[4];
};

template <typename T>
HVolume<T>::HVolume(int M, int N, int O, int P, T defval) :
        Vector<T>::Vector(M*N*O*P, defval)
{
    Dims[0] = M;
    Dims[1] = N;
    Dims[2] = O;
    Dims[3] = P;
}

template <typename T>
HVolume<T>::HVolume(int M, int N, int O, int P, Vector<T> &vec) :
        Vector<T>::Vector(M*N*O*P, vec)
{
    Dims[0] = M;
    Dims[1] = N;
    Dims[2] = O;
    Dims[3] = P;
}

template <typename T>
bool HVolume<T>::dimsmatch(HVolume<T>& hvol)
{
    int* hvshape = hvol.shape();
    return (Dims[0]==hvshape[0] and Dims[1]==hvshape[1] and
            Dims[2]==hvshape[2] and Dims[3]==hvshape[3]);
}

template <typename T>
T* HVolume<T>::operator[](int x)
{
    Volume<T> output(Dims[1], Dims[2], Dims[3], Vector<T>::Guts[x]);
    return output;
}

template <typename T> const
T* HVolume<T>::operator[](int x) const
{
    Volume<T> output(Dims[1], Dims[2], Dims[3], Vector<T>::Guts[x]);
    return output;
}


#endif /* HVOLUME_H */

