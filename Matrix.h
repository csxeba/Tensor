#include <iostream>
#include <assert.h>

#include "Vector.h"

#ifndef MATRIX_H
#define MATRIX_H

template <typename T>
class Matrix: public Vector<T>
{
    public:
        Matrix(int M, int N, T defval=0);
        Matrix(int M, int N, Vector<T>&);
        Matrix(int M, int N, T**&);
        Matrix(Matrix<T>&);
        
        int* shape()                {return Dims;}
        void print();
        
        T at(int x, int y)  {return Vector<T>::Guts[y*Dims[0]+x];}
        T* atp(int x, int y) {return Vector<T>::Guts + y*Dims[0]+x;}
        virtual bool dimsmatch(Matrix<T>&);
        void transpose();
        void set(int x, int y, T val) {Vector<T>::Guts[y*Dims[0]+x] = val;}
        void set(int x, Vector<T>);
        
              T* operator[](int);
        const T* operator[](int) const;
        
    private:
        int Dims[2];
};

template <typename T>
Matrix<T>::Matrix(int M, int N, T defval) :
        Vector<T>::Vector(M*N, defval)
{
    Dims[0] = M;
    Dims[1] = N;
}

template <typename T>
Matrix<T>::Matrix(int M, int N, Vector<T> &vec) :
        Vector<T>::Vector(vec)
{
    assert(Vector<T>::size()==M*N);
    Dims[0] = M;
    Dims[1] = N;
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>& mat) :
        Vector<T>::Vector(mat)
{
    int* mshape = mat.shape();
    Dims[0] = mshape[0];
    Dims[1] = mshape[1];
}

template <typename T>
void Matrix<T>::print()
{
    for (int i=0; i<Dims[0]; i++) {
        for (int j=0; j<Dims[1]; j++) {
            std::cout << at(i, j) << ", ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
bool Matrix<T>::dimsmatch(Matrix<T>& mat)
{
    int* mshape = mat.shape();
    return (Dims[0]==mshape[0] and Dims[1]==mshape[1]);
}

template <typename T>
void Matrix<T>::transpose()
{
    int temp = Dims[0];
    Dims[0] = Dims[1];
    Dims[1] = temp;
}
template <typename T>
void Matrix<T>::set(int x, Vector<T> v)
{
    assert(v.size()==Dims[1]);
    for(int i=0;i<Dims[1];i++) {
        *atp(x)+i = v[i];
    }
}

template <typename T>
T* Matrix<T>::operator[](int y)
{
    return atp(y*Dims[0]);
}

template <typename T> const
T* Matrix<T>::operator[](int y) const
{
    return atp(y*Dims[0]);
}

#endif /* MATRIX_H */

