/* GANG Software
 * BASE/math/Blas.H
 * Copyright (C) 2002 Nicholas Schmitt <nick@gang.umass.edu>
 * Wed Sep 18 16:39:46 2002
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef math_Blas_INCLUDED
#define math_Blas_INCLUDED

#include "base/System.H"
#include <complex>

namespace math {

// choose a BLAS API
#if defined(__sgi)
#  if defined(__GNUG__) || (_COMPILER_VERSION >= 730)
#    define BLAS_IRIX
#  else
#    define BLAS_IRIX_OLD
#  endif
#elif defined(__GNUG__)
#  define BLAS_LINUX
#else
# define BLAS_GENERIC
#endif

#if defined(BLAS_IRIX)
#define TEMPLATE_0 template <>
#else
#define TEMPLATE_0
#endif

/*
   Wrapper for BLAS (Basic Linear Algebra Subroutines)<br>

   BLAS (Basic Linear Algebra Subprograms)
   wrapper for inter-platform compatibility<br>

   supports: zcopy, zscal, zaxpy, zdotc
   supports only std::complex versions<br>

   Provides four versions, determined by the BLAS macro:<br>
   1. Generic, written with for-loops. BLAS undefined, or non float/double<br>
   2. IRIX blas and scsl_blas: defined(BLAS_IRIX)<br>
   3. IRIX older version:      defined(BLAS_IRIX_OLD)<br>
   4. Linux version:           defined(BLAS_LINUX)<br>

*/

template <class Real>
class blas
{
public:
  //
  static inline void
  zcopy( int n, std::complex<Real> const *x, int incx, std::complex<Real> *y,
         int incy );

  //
  static inline void
  zscal( int n, std::complex<Real> const &alpha, std::complex<Real> *x,
         int incx );

  //
  static inline void
  zdscal( int n, Real const &alpha, std::complex<Real> *x, int incx );

  //
  static inline void
  zaxpy( int n, std::complex<Real> const &a, std::complex<Real> const *x,
         int incx, std::complex<Real> *y, int incy );

  //
  static inline void
  zaxpby( int n, std::complex<Real> const &a, std::complex<Real> const *x,
          int incx, std::complex<Real> const &b, std::complex<Real> *y,
          int incy );

  //
  static inline std::complex<Real>
  zdotc( int n, std::complex<Real> const *x, int incx,
         std::complex<Real> const *y,
         int incy );

  //
  static inline std::complex<Real>
  zdotu( int n, std::complex<Real> const *x, int incx,
         std::complex<Real> const *y,
         int incy );
};

//TEMPLATE_0 class blas<float>;
//TEMPLATE_0 class blas<double>;
//TEMPLATE_0 class blas<long double>;

} // namespace math

#if defined(BLAS_IRIX)

extern "C"
{
//#include <cblas.h>
// cblas.h is not included because the C++ compiler can't handle it

typedef struct { float real; float imag; } CBLAS_COMPLEX;
typedef struct { double real; double imag; } CBLAS_ZOMPLEX;

extern void ccopy_( const int *, const void *, const int *, void *,
                    const int *);
extern void cscal_( const int *, const CBLAS_COMPLEX *,
                    CBLAS_COMPLEX *, const int *);
extern void caxpy_(const int *, const void *, const void *,
                   const int *, void *, const int *);
extern void caxpby_(const int *, const void *, const void *,
                    const int *, void const *, void *, const int *);
extern CBLAS_COMPLEX cdotc_(const int *, const CBLAS_COMPLEX *,
                            const int *, const CBLAS_COMPLEX *, const int *);
extern CBLAS_COMPLEX cdotu_(const int *, const CBLAS_COMPLEX *,
                            const int *, const CBLAS_COMPLEX *, const int *);

extern void zcopy_( const int *, const void *, const int *, void *,
                    const int *);
extern void zscal_( const int *, const CBLAS_ZOMPLEX *,
                    CBLAS_ZOMPLEX *, const int *);
extern void zaxpy_(const int *, const void *, const void *,
                   const int *, void *, const int *);
extern void zaxpby_(const int *, const void *, const void *,
                    const int *, void const *, void *, const int *);
extern CBLAS_ZOMPLEX zdotc_(const int *, const CBLAS_ZOMPLEX *,
                            const int *, const CBLAS_ZOMPLEX *, const int *);
extern CBLAS_ZOMPLEX zdotu_(const int *, const CBLAS_ZOMPLEX *,
                            const int *, const CBLAS_ZOMPLEX *, const int *);
} // extern "C"


// FLOAT VERSIONS

namespace math {

TEMPLATE_0
inline
void
blas<float>::
zcopy( int n, std::complex<float> const *x, int incx, std::complex<float> *y,
       int incy )
{
  // y = x
  ccopy_( &n, (void *)x, &incx, (void *)y, &incy);
}

TEMPLATE_0
inline
void
blas<float>::
zscal( int n, std::complex<float> const &a, std::complex<float> *x, int incx )
{
  // x *= a
  cscal_( &n, (CBLAS_COMPLEX *)&a, (CBLAS_COMPLEX *)x, &incx );
}

TEMPLATE_0
inline
void
blas<float>::
zaxpy( int n, std::complex<float> const &a, std::complex<float> const *x,
       int incx, std::complex<float> *y, int incy )
{
  // y += a x
  caxpy_( &n, (void *)&a, (void *)x, &incx, (void *)y, &incy);
}


TEMPLATE_0
inline
void
blas<float>::
zaxpby( int n, std::complex<float> const &a,
        std::complex<float> const *x,
        int incx, std::complex<float> const &b,
        std::complex<float> *y, int incy )
{
  // y = a x + b y
  caxpby_( &n, (void *)&a, (void *)x, &incx, &b, (void *)y, &incy);
}

TEMPLATE_0
inline
std::complex<float>
blas<float>::
zdotc( int n, std::complex<float> const *x, int incx,
       std::complex<float> const *y,
       int incy )
{
  // returns conj(x).y
  std::complex<float> r;
  *(CBLAS_COMPLEX *)&r =
    cdotc_( &n, (CBLAS_COMPLEX *)x, &incx, (CBLAS_COMPLEX *)y, &incy );
  return r;
}

TEMPLATE_0
inline
std::complex<float>
blas<float>::
zdotu( int n, std::complex<float> const *x, int incx,
       std::complex<float> const *y,
       int incy )
{
  // returns conj(x).y
  std::complex<float> r;
  *(CBLAS_COMPLEX *)&r =
    cdotu_( &n, (CBLAS_COMPLEX *)x, &incx, (CBLAS_COMPLEX *)y, &incy );
  return r;
}

// DOUBLE VERSIONS

TEMPLATE_0
inline
void
blas<double>::
zcopy( int n, std::complex<double> const *x, int incx,
       std::complex<double> *y, int incy )
{
  // y = x
  zcopy_( &n, (void *)x, &incx, (void *)y, &incy);
}

TEMPLATE_0
inline
void
blas<double>::
zscal( int n, std::complex<double> const &a, std::complex<double> *x,
       int incx )
{
  // x *= a
  zscal_( &n, (CBLAS_ZOMPLEX *)&a, (CBLAS_ZOMPLEX *)x, &incx );
}

TEMPLATE_0
inline
void
blas<double>::
zaxpy( int n, std::complex<double> const &a, std::complex<double> const *x,
       int incx, std::complex<double> *y, int incy )
{
  // y += a x
  zaxpy_( &n, (void *)&a, (void *)x, &incx, (void *)y, &incy);
}


TEMPLATE_0
inline
void
blas<double>::
zaxpby( int n, std::complex<double> const &a, std::complex<double> const *x,
        int incx, std::complex<double> const &beta, std::complex<double> *y,
        int incy )
{
  // y += a x
  zaxpby_( &n, (void *)&a, (void *)x, &incx, &beta, (void *)y, &incy);
}

TEMPLATE_0
inline
std::complex<double>
blas<double>::
zdotc( int n, std::complex<double> const *x, int incx,
       std::complex<double> const *y,
       int incy )
{
  // returns conj(x).y
  std::complex<double> r;
  *(CBLAS_ZOMPLEX *)&r =
    zdotc_( &n, (CBLAS_ZOMPLEX *)x, &incx, (CBLAS_ZOMPLEX *)y, &incy );
  return r;
}

TEMPLATE_0
inline
std::complex<double>
blas<double>::
zdotu( int n, std::complex<double> const *x, int incx,
       std::complex<double> const *y,
       int incy )
{
  // returns x.y
  std::complex<double> r;
  *(CBLAS_ZOMPLEX *)&r =
    zdotu_( &n, (CBLAS_ZOMPLEX *)x, &incx, (CBLAS_ZOMPLEX *)y, &incy );
  return r;
}

} // namespace math

#endif  // defined(BLAS_IRIX)



#if defined(BLAS_IRIX_OLD)
// Older Irix version

// CBLAS DECLARATIONS

extern "C"
{
#include <cblas.h>
}

// FLOAT VERSIONS

namespace math {

void
blas<float>::
zcopy( int n, std::complex<float> const *x, int incx, std::complex<float> *y,
       int incy )
{
  // y = x
  ::ccopy( (Integer)n, (std::complex<double> *)x, (Integer)incx,
           (std::complex<double> *)y, (Integer)incy);
}

void
blas<float>::
zscal( int n, std::complex<float> const &a, std::complex<float> *x, int incx )
{
  // x *= a
  ::cscal( (Integer)n, *(std::complex<double> *)&a,
           (std::complex<double> *)x, (Integer)incx );
}

void
blas<float>::
zaxpy( int n, std::complex<float> const &a, std::complex<float> const *x,
       int incx, std::complex<float> *y, int incy )
{
  // y += a x
  ::caxpy( (Integer)n, *(std::complex<double> *)&a,
           (std::complex<double> *)x, (Integer)incx,
           (std::complex<double> *)y, (Integer)incy);
}

std::complex<float>
blas<float>::
zdotc( int n, std::complex<float> const *x, int incx,
       std::complex<float> const *y,
       int incy )
{
  // returns conj(x).y
  std::complex<float> r;

  *(std::complex<double> *)&r =
    ::cdotc( (Integer)n, (std::complex<double> *)x, (Integer)incx,
             (std::complex<double> *)y, (Integer)incy );

  return r;
}

std::complex<float>
blas<float>::
zdotu( int n, std::complex<float> const *x, int incx,
       std::complex<float> const *y,
       int incy )
{
  // returns conj(x).y
  std::complex<float> r;

  *(std::complex<double> *)&r = ::cdotu(
    (Integer)n, (std::complex<double> *)x, (Integer)incx,
    (std::complex<double> *)y, (Integer)incy );

  return r;
}

// DOUBLE VERSIONS

void
blas<double>::
zcopy( int n, std::complex<double> const *x, int incx,
       std::complex<double> *y,
       int incy )
{
  // y = x
  ::zcopy( (Integer)n, (Zomplex *)x, (Integer)incx, (Zomplex *)y,
           (Integer)incy);
}

void
blas<double>::
zscal( int n, std::complex<double> const &a,
       std::complex<double> *x, int incx )
{
  // x *= a
  ::zscal( (Integer)n, *(Zomplex *)&a, (Zomplex *)x, (Integer)incx );
}

void
blas<double>::
zaxpy( int n, std::complex<double> const &a,
       std::complex<double> const *x,
       int incx, std::complex<double> *y, int incy )
{
  // y += a x
  ::zaxpy( (Integer)n, *(Zomplex *)&a, (Zomplex *)x, (Integer)incx,
           (Zomplex *)y, (Integer)incy);
}


std::complex<double>
blas<double>::
zdotc( int n, std::complex<double> const *x, int incx,
       std::complex<double> const *y,
       int incy )
{
  // returns conj(x).y
  std::complex<double> r;

  *(Zomplex *)&r =
    ::zdotc( (Integer)n, (Zomplex *)x, (Integer)incx, (Zomplex *)y,
             (Integer)incy );

  return r;
}

std::complex<double>
blas<double>::
zdotu( int n, std::complex<double> const *x, int incx,
       std::complex<double> const *y,
       int incy )
{
  // returns conj(x).y
  std::complex<double> r;

  *(Zomplex *)&r = ::zdotu( (Integer)n, (Zomplex *)x, (Integer)incx,
                            (Zomplex *)y, (Integer)incy );

  return r;
}

} // namespcae math

#endif  // defined(BLAS_IRIX_OLD)


#if defined(BLAS_LINUX)

// FORTRAN BLAS VERSION

// FORTRAN BLAS DECLARATIONS

typedef enum { NoTranspose, Transpose, ConjugateTranspose }  MatrixTranspose;
typedef enum { UpperTriangle, LowerTriangle }  MatrixTriangle;
typedef enum { UnitTriangular, NotUnitTriangular }  MatrixUnitTriangular;
typedef enum { LeftSide, RightSide }  OperationSide;


// FORTRAN BLAS FLOAT VERSIONS

extern "C"
{
struct blas_cpx_float { float x, y; };
struct blas_cpx_double { double x, y; };

extern void ccopy_( int *, blas_cpx_float *, int *, blas_cpx_float *, int *);
extern void cscal_( int *, blas_cpx_float *, blas_cpx_float *, int *);
extern void caxpy_( int *, blas_cpx_float *, blas_cpx_float *, int *,
                    blas_cpx_float *, int * );
extern void cdotc_( blas_cpx_float *, int *, blas_cpx_float *, int *,
                    blas_cpx_float *, int *);
extern void cdotu_( blas_cpx_float *, int *, blas_cpx_float *, int *,
                    blas_cpx_float *, int *);

extern void zcopy_( int *, blas_cpx_double *, int*, blas_cpx_double *, int *);
extern void zscal_( int *, blas_cpx_double *, blas_cpx_double *, int *);
extern void zaxpy_( int *, blas_cpx_double *, blas_cpx_double *, int *,
                    blas_cpx_double *, int * );
extern void zdotc_( blas_cpx_double *, int *, blas_cpx_double *, int *,
                    blas_cpx_double *, int *);
extern void zdotu_( blas_cpx_double *, int *, blas_cpx_double *, int *,
                    blas_cpx_double *, int *);
}

namespace math {

void
blas<float>::
zcopy( int n, std::complex<float> const *x, int incx, std::complex<float> *y,
       int incy )
{
  // y = x
  ccopy_( (int *)&n, (blas_cpx_float *)x, (int *)&incx, (blas_cpx_float *)y,
          &incy);
}

void
blas<float>::
zscal( int n, std::complex<float> const &a, std::complex<float> *x, int incx )
{
  // x *= a
  cscal_( (int *)&n, (blas_cpx_float *)&a, (blas_cpx_float *)x,
          (int *)&incx );
}

void
blas<float>::
zaxpy( int n, std::complex<float> const &a,
       std::complex<float> const *x,
       int incx, std::complex<float> *y, int incy )
{
  // y += a x
  caxpy_( (int *)&n, (blas_cpx_float *)&a, (blas_cpx_float *)x, (int *)&incx,
          (blas_cpx_float *)y, (int *)&incy);
}

std::complex<float>
blas<float>::
zdotc( int n, std::complex<float> const *x, int incx,
       std::complex<float> const *y,
       int incy )
{
  // returns conj(x).y
  std::complex<float> r;
  cdotc_( (blas_cpx_float *)&r, (int *)&n, (blas_cpx_float *)x, (int *)&incx,
          (blas_cpx_float *)y, (int *)&incy );
  return r;
}

std::complex<float>
blas<float>::
zdotu( int n, std::complex<float> const *x, int incx,
       std::complex<float> const *y,
       int incy )
{
  // returns conj(x).y
  std::complex<float> r;
  cdotu_( (blas_cpx_float *)&r, (int *)&n, (blas_cpx_float *)x, (int *)&incx,
          (blas_cpx_float *)y, (int *)&incy );
  return r;
}

// FORTRAN BLAS DOUBLE VERSIONS

void
blas<double>::
zcopy( int n, std::complex<double> const *x,
       int incx, std::complex<double> *y,
       int incy )
{
  // y = x
  zcopy_( (int *)&n, (blas_cpx_double *)x, (int *)&incx,
          (blas_cpx_double *)y, &incy);
}

void
blas<double>::
zscal( int n, std::complex<double> const &a,
       std::complex<double> *x, int incx )
{
  // x *= a
  zscal_( (int *)&n, (blas_cpx_double *)&a, (blas_cpx_double *)x,
          (int *)&incx );
}

void
blas<double>::
zaxpy( int n, std::complex<double> const &a,
       std::complex<double> const *x,
       int incx, std::complex<double> *y, int incy )
{
  // y += a x
  zaxpy_( (int *)&n, (blas_cpx_double *)&a, (blas_cpx_double *)x,
          (int *)&incx, (blas_cpx_double *)y, (int *)&incy);
}

std::complex<double>
blas<double>::
zdotc( int n, std::complex<double> const *x, int incx,
       std::complex<double> const *y,
       int incy )
{
  // returns conj(x).y
  std::complex<double> r;
  zdotc_( (blas_cpx_double *)&r, (int *)&n, (blas_cpx_double *)x,
          (int *)&incx, (blas_cpx_double *)y, (int *)&incy );
  return r;
}

std::complex<double>
blas<double>::
zdotu( int n, std::complex<double> const *x, int incx,
       std::complex<double> const *y,
       int incy )
{
  // returns conj(x).y
  std::complex<double> r;
  zdotu_( (blas_cpx_double *)&r, (int *)&n, (blas_cpx_double *)x,
          (int *)&incx, (blas_cpx_double *)y, (int *)&incy );
  return r;
}

} // namespace math

#endif // defined(BLAS_FORTRAN)

namespace math {

// GENERIC TEMPLATE VERSIONS
// These are used if no BLAS macro is not defined,
// and when Real is not of type
// float or double.

template <class Real>
void
blas<Real>::
zcopy( int n, std::complex<Real> const *x, int incx,
       std::complex<Real> *y, int incy )
{
  // y = x

  DIE_IF( n < 0 );

  if ( incx == 1 && incy == 1 )
  {
    int i;
    for (i = 0; i < n; i++)
    {
      y[i] = x[i];
    }
  }
  else
  {
    int xn = 0;
    int yn = 0;
    if (incx < 0) { xn = -incx*(n-1); }
    if (incy < 0) { yn = -incy*(n-1); }
    int i;
    for (i = 0; i < n; i++)
    {
      y[yn] = x[xn];
      xn += incx;
      yn += incy;
    }
  }
}

template <class Real>
void
blas<Real>::
zscal( int n, std::complex<Real> const &a, std::complex<Real> *x, int incx )
{
  // x *= a

  DIE_IF( n < 0 );

  if ( incx == 1 )
  {
    int i;
    for (i = 0; i < n; i++)
    {
      x[i] *= a;
    }
  }
  else
  {
    int i;
    int xn = 0;
    if (incx < 0) { xn = -incx*(n-1); }
    for (i = 0; i < n; i++)
    {
      x[xn] *= a;
      xn += incx;
    }
  }
}

template <class Real>
void
blas<Real>::
zdscal( int n, Real const &a, std::complex<Real> *x, int incx )
{
  // x *= a

  DIE_IF( n < 0 );

  if ( incx == 1 )
  {
    int i;
    for (i = 0; i < n; i++)
    {
      x[i] *= a;
    }
  }
  else
  {
    int i;
    int xn = 0;
    if (incx < 0) { xn = -incx*(n-1); }
    for (i = 0; i < n; i++)
    {
      x[xn] *= a;
      xn += incx;
    }
  }
}

template <class Real>
void
blas<Real>::
zaxpy(
  int n,
  std::complex<Real> const &a,
  std::complex<Real> const *x,
  int incx,
  std::complex<Real> *y,
  int incy )
{
  // y += a x

  DIE_IF( n < 0 );

  if (incx == 1 && incy == 1 )
  {
    int i;
    for (i = 0; i < n; i++)
    {
      y[i] += a * x[i];
    }
  }
  else
  {
    int xn = 0;
    int yn = 0;
    if (incx < 0) { xn = -incx*(n-1); }
    if (incy < 0) { yn = -incy*(n-1); }
    int i;
    for (i = 0; i < n; i++)
    {
      y[yn] += a * x[xn];
      xn += incx;
      yn += incy;
    }
  }
}

template <class Real>
void
blas<Real>::
zaxpby(
  int n,
  std::complex<Real> const &a,
  std::complex<Real> const *x,
  int incx,
  std::complex<Real> const &b,
  std::complex<Real> *y,
  int incy )
{
  // y = a x + b y

  DIE_IF( n < 0 );

  if (incx == 1 && incy == 1 )
  {
    int i;
    for (i = 0; i < n; i++)
    {
      y[i] = a * x[i] + b * y[i];
    }
  }
  else
  {
    int xn = 0;
    int yn = 0;
    if (incx < 0) { xn = -incx*(n-1); }
    if (incy < 0) { yn = -incy*(n-1); }
    int i;
    for (i = 0; i < n; i++)
    {
      y[yn] = a * x[xn] + b * y[yn];
      xn += incx;
      yn += incy;
    }
  }
}

template <class Real>
std::complex<Real>
blas<Real>::
zdotc(
  int n,
  std::complex<Real> const *x,
  int incx, std::complex<Real> const *y,
  int incy )
{
  // returns conj(x).y

  DIE_IF( n < 0 );

  std::complex<Real> r(0.0);

  if ( incx == 1 && incy == 1 )
  {
    int i;
    for (i = 0; i < n; i++)
    {
      r += conj(x[i]) * y[i];
    }
  }
  else
  {
    int xn = 0;
    int yn = 0;
    if (incx < 0) { xn = -incx*(n-1); }
    if (incy < 0) { yn = -incy*(n-1); }
    int i;
    for (i = 0; i < n; i++)
    {
      r += conj(x[xn]) * y[yn];
      xn += incx;
      yn += incy;
    }
  }
  return r;
}


template <class Real>
std::complex<Real>
blas<Real>::
zdotu(
  int n,
  std::complex<Real> const *x,
  int incx, std::complex<Real> const *y,
  int incy )
{
  // returns x.y

  DIE_IF( n < 0 );

  std::complex<Real> r(0.0);

  if ( incx == 1 && incy == 1 )
  {
    int i;
    for (i = 0; i < n; i++)
    {
      r += x[i] * y[i];
    }
  }
  else
  {
    int xn = 0;
    int yn = 0;
    if (incx < 0) { xn = -incx*(n-1); }
    if (incy < 0) { yn = -incy*(n-1); }
    int i;
    for (i = 0; i < n; i++)
    {
      r += x[xn] * y[yn];
      xn += incx;
      yn += incy;
    }
  }
  return r;
}

} // namespace math

#endif // math_Blas_INCLUDED
