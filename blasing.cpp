#include <assert.h>

#include "blasing.h"

void dscal(Vector<double> &a, double alpha)
{
    int N = a.size();
    int incx = 1;
    dscal_(&N, &alpha, a.point(), &incx);
}

void daxpy(Vector<double> &x, Vector<double> &y, double alpha)
{
    assert(x.size() == y.size());
    int N = x.size();
    int incx = 1, incy = 1;
    daxpy_(&N, &alpha, x.point(), &incx, y.point(), &incy);
}

double dasum(Vector<double> &x)
{
    int N = x.size(), incx = 1;
    return dasum_(&N, x.point(), &incx);
}

double ddot(Vector<double> &a, Vector<double> &b)
{
    assert(a.size()==b.size());
    int inca = 1, incb = 1;
    int N = a.size();
    return ddot_(&N, a.point(), &inca, b.point(), &incb);
}

void dgemv(Vector<double> x, Vector<double> y, Matrix<double> A,
           double alpha, double beta)
{
    int* mshape = A.shape();
    int M = mshape[0], N = mshape[1];
    char trans = 'N';
    int lda = M;
    int incx = 1, incy = 1;
    dgemv_(&trans, &M, &N, &alpha, A.point(), &lda, x.point(), &incx,
           &beta, y.point(), &incy);
}

void dger(Vector<double> x, Vector<double> y, Matrix<double> A)
{
    int M = x.size(), N = y.size();
    int incx = 1, incy = 1;
    int lda = M;
    double alpha = 1.0;
    
    dger_(&M, &N, &alpha, x.point(), &incx, y.point(), &incy,
               A.point(), &lda);
}

void dgemm(Matrix<double> &A, Matrix<double> &B, Matrix<double> &C)
{
    int* shape1 = A.shape();
    int* shape2 = B.shape();
    assert(shape1[1] == shape2[0]);
    int M = shape1[0], N = shape2[1], K = shape1[1];
    int lda = M, ldb = K, ldc = M;
    char transa = 'N', transb = 'N';
    double alpha = 1.0, beta=1.0;
        
    dgemm_(&transa, &transb, &M, &N, &K, &alpha, A.point(), &lda,
           B.point(), &ldb, &beta, C.point(), &ldc);
}
