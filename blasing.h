#ifndef BLASING_H
#define BLASING_H

#include <assert.h>

#include "generic.h"

#define CI int*
#define CD double*
extern "C"
{
    //BLAS lvl 1
    
    /**
     * x := alpha * x
     */
    void dscal_(CI N, CD alpha, CD x, CI incx);
    
    /**
     * y := alpha * x + y
     */
    void daxpy_(CI N, CD alpha, CD x,
                CI incx, double* y, CI incy);
    
    /**
     * Inner product of 2 vectors.
     * Returns DOUBLE.
     */
    double ddot_(CI N, CD x, CI incx,
                 CD y, CI incy);
    
    /**
     * Sum of absolute values.
     * Returns DOUBLE.
     */
    double dasum_(CI N, CD x, CI incx);
    
    //BLAS lvl 2
    
    /**
     * General matrix X vector
     * y := alpha * A * x + beta * y
     */
    void dgemv_(char* trans, CI M, CI N, CD alpha, CD A, CI lda,
                CD x, CI incx, CD beta, CD y, CI incy);
    
    /**
     * Outer product (?)
     * A := xy**T + A
     */
    void dger_(CI M, CI N, CD alpha, CD x, CI incx, CD y, CI incy,
               double* A, CI lda);

    //BLAS lvl 3
    
    /**
     * General matrix X matrix
     * C := alpha*A . B + beta*C
     * A is assumed to be MxK, B is KxN, C is MxN
     */
    void dgemm_(char* transa, char* transb, 
                CI M, CI N, CI K,
                CD alpha, CD A, CI lda, CD B, CI ldb,
                CD beta, CD C, CI ldc);
}
#undef CI
#undef CD

//My wrappers for the BLAS routines

/**
 * a := alpha * a
 */
void dscal(Vector<double> &a, double alpha);

/**
 * y := alpha * x + y
 * params: x, y, (alpha)
 */
void daxpy(Vector<double> &x, Vector<double> &y, double alpha=1.0);

/**
 * Absolute sum of vector.
 * params: x
 * Returns DOUBLE
 */
double dasum(Vector<double> &x);

/**
 * Inner product of vectors a, b.
 * params: a, b
 * Returns DOUBLE
 */
double ddot(Vector<double> &a, Vector<double> &b);

/**
 * General matrix X vector.
 * y := alpha * A * x + beta * y
 * params: x, y, A, (alpha), (beta)
 */
void dgemv(Vector<double> x, Vector<double> y, Matrix<double> A,
           double alpha=0.0, double beta=0.0);

/**
 * Outer product (?) of two vectors.
 * A := x * y**T + A
 * params: x, y, A
 */
void dger(Vector<double> x, Vector<double> y, Matrix<double> A);

/**
 * General matrix X matrix
 * C := A * B + C
 * params: A, B, C
 */
void dgemm(Matrix<double> &A, Matrix<double> &B, Matrix<double> &C);

#endif /* BLASING_H */

