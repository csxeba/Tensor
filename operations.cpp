#include <iostream>
#include <cstring>
#include <assert.h>

#include "operations.h"
#include "blasing.h"

#define Tvec Vector<T>
#define Tmatrix2 Matrix<T>
#define Tmatrix3 Volume<T>
#define Tmatrix4 HVolume<T>

template <typename T>
inline bool matops::dimsmatch(Tmatrix2 &m1, Tmatrix2 &m2) {
    return (m1.dimsmatch(m2));
}

template <typename T>
inline bool matops::dimsmatch(Tmatrix3 &m1, Tmatrix3 &m2) {
    return (m1.dimsmatch(m2));
}

//  function  templates //

template <typename T>
inline int* matops::shapeof(Tmatrix2 &mat)
{
    return mat.shape();
}

template <typename T>
inline int* matops::shapeof(Tmatrix3 &mat)
{
    return mat.shape();
}

template <typename T>
int* matops::shapeof(Tmatrix4 &mat)
{
    int output[4];
    int* mshape = mat[0].shape();
    output[0] = mat.size();
    for (int i = 0; i < 3; i++) {
        output[i+1] = mshape[i];
    }
    return output;
}

template <typename T>
void matops::printm(Tvec &vec)
{
    vec.print();
}

template <typename T>
void matops::printm(Tmatrix2 &mat)
{
    mat.print();
}

template <typename T>
void matops::printm(Tmatrix3 &mat)
{
    mat.print();
}

template <typename T> Tmatrix2
matops::fold2(Tvec &vec, ivec &shape)
{
    Tmatrix2 output(shape[0], shape[1], vec);    
    return output;
}

template <typename T> Tmatrix3
matops::fold3(Tvec vec, ivec shape)
{
    Tmatrix3 output(shape[0], shape[1], shape[2], vec);    
    return output;
}

template <typename T> void
matops::invert(Tmatrix3 &mat)
{
    mat.invert();
}

template <typename T> void
matops::transpose(Tmatrix2 &mat)
{
    mat.transpose();
}

template <typename T> Tvec
matops::slice(Tvec& vec, int from, int to)
{

    Tvec output(to-from);
    int i=0;
    for(int y=from;y<to;y++, i++)
        *output.atp(i) = vec.at(y);
    return output;
}


template <typename T> Tmatrix2
matops::slice(Tmatrix2& mat, int* indices)
{
    Tmatrix2 output(indices[1]-indices[0], indices[3]-indices[2], 0.0);
    int i=0;
    for(int y=indices[0];y<indices[1];y++, i++) {
        int j=0;
        for(int x=indices[2];x<indices[3];x++, j++) {
            *output.atp(i, j) = mat.at(i, j); //one element gets passed!
        }
    }
    return output;
}

template <typename T> Tmatrix3
matops::slice(Tmatrix3 mat, ivec indices)
{
    //Warning! Assuming inverted matrix!
    int* matshape = mat.shape();
    Tmatrix3 output(indices[1]-indices[0], 
                    indices[3]-indices[2],
                    matshape[0]);
    for(int x=indices[0];x<indices[1];x++) {
        int i=0;
        for(int y=indices[2];y<indices[3];y++) {
            int j=0;
            for (int z=0; z<matshape[0]; z++) {
                //We invert it back!
                *output.atp(z, j, i) = mat.at(x, y, z);
            }
        }
    }
    return output;
}

double matops::dot(Vector<double> &vec1, Vector<double> &vec2)
{   
    assert(vec1.size()==vec2.size());
    return ddot(vec1, vec2);
} 

Matrix<double> matops::dot (Matrix<double> &mat1, Matrix<double> &mat2)
{
    int* sh1 = mat1.shape();
    int* sh2 = mat2.shape();

    assert(sh1[1]==sh2[1]);

    Matrix<double> output(sh1[0], sh2[1]);
    dgemm(mat1, mat2, output);

    return output;
}

double matops::frobenius(Matrix<double> &mat1, Matrix<double> &mat2)
{
    assert(mat1.dimsmatch(mat2));
    return ddot(mat1, mat2);
}

double matops::frobenius(Volume<double> &mat1, Volume<double> &mat2)
{
    assert(mat1.dimsmatch(mat2));
    return ddot(mat1, mat2);
}

void matops::elementwise_mult(Vector<double> &v, double r)
{
    dscal(v, r);
}

void matops::elementwise_add(Vector<double> &v, double r)
{
    Vector<double> broadcast(v.size(), r);
    daxpy(broadcast, v, 1.0);
}

void matops::overwrite(Vector<double> &v1, Vector<double> &v2)
{
    dscal(v2, 0.0);
    daxpy(v1, v2, 1.0);
}

ivec outshape(ivec inshape, ivec filtersize, int stride, int filters)
{
    ivec out(3);
    int x;
    
    out[0] = (filters == 0) ? inshape[0] : filters;
    
    for(int i=2;i>0;i--)
    {
        x = inshape[i]-filtersize[i-1];
        assert(x % stride==0);
        out[i] = (x / stride) + 1;
    }
   
    return out;
}

imatrix2 calcsteps(ivec inshape, ivec filtersize, int stride, int filters)
{
    ivec oshape(outshape(inshape, filtersize, stride, filters));
    //oshape = outshape(inshape, filtersize, stride, filters);

    ivec startxes(oshape[2]);
    ivec startys(oshape[1]);
    ivec endxes(oshape[2]);
    ivec endys(oshape[1]);
    imatrix2 steps(oshape[1], oshape[2]); // array of arrays!
    
    for(int i=0;i<oshape[2];i++) {
        *startxes.atp(i) = i*stride;
        *endxes.atp(i) = startxes[i]+filtersize[0];
    }
    for(int i=0;i<oshape[1];i++) {
        *startys.atp(i) = i*stride;
        *endys.atp(i) = startys[i]+filtersize[0];
    }
    for(int i=0;i<oshape[2];i++) {
        for(int j=0;j<oshape[1];j++) {
            int s[] = {startxes[i], endxes[i], startys[j], endys[j]};
            std::memcpy(steps.Vector<int>::atp(i*oshape[2] + j), s, sizeof s);
        }
    }
    
    //imatrix2 output(oshape[1], oshape[2], steps);
    
    return steps;
}

#undef Tvec
#undef Tmatrix2
#undef Tmatrix3
#undef Tmatrix4