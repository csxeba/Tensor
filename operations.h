/*Please refer to the LICENSE.txt file in this project's root
  for copyright informations!*/
#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <assert.h>
#include <numeric>
#include <iostream>
#include <algorithm>

#include "generic.h"

//Heard this wasn't very ethical.
#define Tvec Vector<T>
#define Tmatrix2 Matrix<T>
#define Tmatrix3 Volume<T>
#define Tmatrix4 HVolume<T>
//Well, I'm lazy.

  //-----------------------  //
 // Definition of functions //
//  -----------------------//

namespace matops {

    template <typename T>
    inline bool dimsmatch(Tmatrix2 &m1, Tmatrix2 &m2);
    template <typename T>
    inline bool dimsmatch(Tmatrix3 &m1, Tmatrix3 &m2);

    template <typename T>
    inline int* shapeof(Tmatrix2 &mat);
    template <typename T>
    inline int* shapeof(Tmatrix3 &mat);
    template <typename T>    
    int*        shapeof(Tmatrix4 &mat);

    template <typename T>
    void printm(Tvec &vec);
    template <typename T>
    void printm(Tmatrix2 &mat);
    template <typename T>    
    void printm(Tmatrix3 &mat);

    template <typename T>
    Tmatrix2 fold2(Tvec &vec, ivec &shape);
    template <typename T>
    Tmatrix3 fold3(Tvec vec, ivec shape);

    template <typename T>
    void invert(Tmatrix3 &mat);

    template <typename T>
    void transpose(Tmatrix2 &mat);

    template <typename T>
    Tvec     slice(Tvec& vec, int from, int to);
    template <typename T>
    Tmatrix2 slice(Tmatrix2& mat, int* indices);
    template <typename T>
    Tmatrix3 slice(Tmatrix3 mat, ivec indices);


    double   dot(dvec &vec1, dvec &vec2);
    dmatrix2 dot (dmatrix2 &mat1, dmatrix2 &mat2);

    double frobenius(dmatrix2 &mat1, dmatrix2 &mat2);
    double frobenius(dmatrix3 &mat1, dmatrix3 &mat2);

    void elementwise_mult(dvec &v, double r);
    void elementwise_add(dvec &v, double r);

    void overwrite(dvec &v1, dvec &v2);

} //End namespace matops

//Calculation of step coordinates
//This is defined in the .cpp
imatrix2 calcsteps(ivec inshape, ivec filtersize, int stride, int filters);
ivec outshape(ivec inshape, ivec filtersize, int stride, int filters);

#undef Tvec
#undef Tmatrix2
#undef Tmatrix3
#undef Tmatrix4


#endif /* OPERATIONS_H */