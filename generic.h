/*Please refer to the LICENSE.txt file in this project's root
  for copyright informations!*/
#ifndef TYPES_H
#define TYPES_H

#include "Vector.h"
#include "Matrix.h"
#include "Volume.h"
#include "HVolume.h"

typedef double real;

typedef Vector<real> dvec;
typedef Vector<int> ivec;

typedef Matrix<real> dmatrix2;
typedef Matrix<int> imatrix2;

typedef Volume<real> dmatrix3;
typedef Volume<int> imatrix3;

typedef HVolume<real> dmatrix4;

/* Will do...
template<typename T>
using Tvec = std::vector<T>;

template<typename T>
using Tmatrix2 = std::vector<Tvec>;

template<typename T>
using Tmatrix3 = std::vector<Tmatrix2>;
*/

#endif /* TYPES_H */

