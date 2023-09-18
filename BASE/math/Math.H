/* GANG Software
 * BASE/math/Math.H
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

#ifndef math_Math_INCLUDED
#define math_Math_INCLUDED

#include <iostream>
#include <complex>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "base/System.H"
#include "base/PrintNumber.H"

#undef isnan

namespace math {

// pi
extern double const pi;


// the number with absolute value x and sign of s.
template <class A> inline A adjust_sign( A, A );

#if 0
// maximum of two numbers.
template <class A> inline A max( A, A );

// maximum of three numbers.
template <class A> inline A max( A, A, A );

// minimum of two numbers.
template <class A> inline A min( A, A );

// minimum of three numbers.
template <class A> inline A min( A, A, A );
#endif

//
template <class A> inline A sqr( A );

// the cube of a number
template <class A> inline A cube( A );

// the average of two numbers.
template <class A> inline A midpoint( A, A );

//
template <class A> inline bool between( A, A, A );

//
template <class A> inline bool distinct( A, A, A );

//
template <class A> inline bool same_sign( A, A );

//
template <class A> inline int sign( A );

//
template <class A> inline void swap( A &, A & );

//
template <class A> inline void sort( A &, A & );

//
template <class A> inline A mod( A x, A n );

// set X to zero
template <class A> inline void zero( A *X, uint n );

// copy Y to X
template <class A> inline void copy( A *X, A const *Y, uint n );

inline int round(float);
inline int round(double);

// return the absolute value
inline short abs(short);
inline int abs(int);
inline long abs(long);

inline float abs(float);
inline double abs(double);
inline double long abs(double long);

template <class A> A norm( A, A );
template <class A> A norm( A, A, A );
template <class A> A norm( A, A, A, A );
template <class A> A abs( A, A );
template <class A> A abs( A, A, A );
template <class A> A abs( A, A, A, A );
template <class A> void normalize( A &, A & );
template <class A> void normalize( A &, A &, A & );
template <class A> void normalize( A &, A &, A &, A & );

// arctan
inline float arctan( float x, float y );
inline double arctan( double x, double y );
inline double long arctan( double long x, double long y );

// factorial
double factorial( uint n );

// chop: 0 if std::less than tolerance
inline float chop(
  float x, float tolerance = 1.0e-6f );
inline double chop(
  double x, double tolerance = 1.0e-10 );
inline double long chop(
  double long x, double long tolerance = 1.0e-30l );

// return true iff is a nan
inline bool isnan(float);
inline bool isnan(double);
inline bool isnan(double long);

// effectively_zero
inline bool effectively_zero(
  float x, float precision = 100.0f * FLT_MIN );
inline bool effectively_zero(
  double x, double precision = 100.0 * DBL_MIN );
inline bool effectively_zero(
  double long x, double long precisoin = 100.0l * LDBL_MIN );

// returns the fractional part in [0,1)
inline float frac(float);
inline double frac(double);
inline double long frac(double long);


inline std::complex<float>
chop( std::complex<float> x, float tolerance = 1.0e-6 );
inline std::complex<double>
chop( std::complex<double> x, double tolerance = 1.0e-10 );
inline std::complex<double long>
chop( std::complex<double long> x, double long tolerance = 1.0e-30 );

// return true iff is a nana
inline bool isnan( std::complex<float> const &x );
inline bool isnan( std::complex<double> const &x );
inline bool isnan( std::complex<double long> const &x );

// effectively_zero
inline bool effectively_zero(
  std::complex<float> x, float precision = 100.0 * FLT_MIN );
inline bool effectively_zero(
  std::complex<double> x, double precision = 100.0 * DBL_MIN );
inline bool effectively_zero(
  std::complex<double long> x, double long precision = 100.0 * LDBL_MIN );


inline int mod( uint x, uint n );
inline int mod( int x, uint n );


inline float sqrt(float x) { return ::sqrtf(x); }
inline double sqrt(double x) { return ::sqrt(x); }
inline double long sqrt(double long x) { return ::sqrtl(x); }

inline float exp(float x) { return ::expf(x); }
inline double exp(double x) { return ::exp(x); }
inline double long exp(double long x) { return ::expl(x); }

inline float log(float x) { return ::logf(x); }
inline double log(double x) { return ::log(x); }
inline double long log(double long x) { return ::logl(x); }

inline float cos(float x) { return ::cosf(x); }
inline double cos(double x) { return ::cos(x); }
inline double long cos(double long x) { return ::cosl(x); }

inline float sin(float x) { return ::sinf(x); }
inline double sin(double x) { return ::sin(x); }
inline double long sin(double long x) { return ::sinl(x); }

inline float tan(float x) { return ::tanf(x); }
inline double tan(double x) { return ::tan(x); }
inline double long tan(double long x) { return ::tanl(x); }

inline float acos(float x) { return ::acosf(x); }
inline double acos(double x) { return ::acos(x); }
inline double long acos(double long x) { return ::acosl(x); }

inline float asin(float x) { return ::asinf(x); }
inline double asin(double x) { return ::asin(x); }
inline double long asin(double long x) { return ::asinl(x); }

inline float atan(float x) { return ::atanf(x); }
inline double atan(double x) { return ::atan(x); }
inline double long atan(double long x) { return ::atanl(x); }


inline float cosh(float x) { return ::coshf(x); }
inline double cosh(double x) { return ::cosh(x); }
inline double long cosh(double long x) { return ::coshl(x); }

inline float sinh(float x) { return ::sinhf(x); }
inline double sinh(double x) { return ::sinh(x); }
inline double long sinh(double long x) { return ::sinhl(x); }

inline float tanh(float x) { return ::tanhf(x); }
inline double tanh(double x) { return ::tanh(x); }
inline double long tanh(double long x) { return ::tanhl(x); }

inline float acosh(float x) { return ::acosh(x); }
inline double acosh(double x) { return ::acosh(x); }
inline double long acosh(double long x) { return ::acosh(x); }

inline float asinh(float x) { return ::asinh(x); }
inline double asinh(double x) { return ::asinh(x); }
inline double long asinh(double long x) { return ::asinh(x); }

inline float atanh(float x) { return ::atanh(x); }
inline double atanh(double x) { return ::atanh(x); }
inline double long atanh(double long x) { return ::atanh(x); }

inline float pow(float x, float y) { return ::powf(x,y); }
inline double pow(double x, double y) { return ::pow(x,y); }
inline double long pow(double long x, double long y) { return ::powl(x,y); }

inline void random_seed(long a) { srand48(a); }
inline double random() { return drand48(); }
inline double random( double b ) { return b * drand48(); }
inline double random( double a, double b ) { return a + (b-a) * drand48(); }


#if 0
template <class A>
inline
A
max( A a, A b )
{
  return a >= b ? a : b;
}

template <class A>
inline
A
min( A a, A b )
{
  return a <= b ? a : b;
}

template <class A>
inline
A
max( A a, A b, A c )
{
  return a > b ? std::max(c,a) : std::max(c,b);
}

template <class A>
inline
A
min( A a, A b, A c )
{
  return b < a ? std::min(c,b) : std::min(c,a);
}
#endif

template <class A>
inline
A
sqr( A x )
{
  return x*x;
}

template <class A>
inline
A
cube( A x )
{
  return x*x*x;
}

template <class A>
inline
int
sign( A a )
{
  return ( a > 0 ? 1 : ( a < 0 ? -1 : 0 ) );
}

template <class A>
inline
bool
between( A a, A b, A c )
{
  return ( a < b && b < c );
}

template <class A>
inline
bool
distinct( A a, A b, A c )
{
  return ( a != b && a != c && b != c );
}

template <class A>
inline
bool
same_sign( A a, A b )
{
  return ( ( a > 0.0 && b > 0.0 ) || ( a < 0.0 && b < 0.0 ) ||
           ( a == 0.0 && b == 0.0 ) );
}

template <class A>
inline
A
midpoint( A a, A b )
{
  return 0.5 * ( a + b );
}

template <class A>
inline
A
adjust_sign( A x, A s )
{
  assert( s != 0.0 );
  return( s > 0.0 ? abs(x) : -abs(x) );
}


template <class A>
inline
void
swap( A &a, A &b )
{
  A tmp = a;
  a = b;
  b = tmp;
}

template <class A>
inline
void
sort( A &a, A &b )
{
  if ( a > b ) { swap( a, b ); }
}

template <class A>
inline
A
mod( A x, A n )
{
  A y = x % n;
  if (y < 0) { y += n; }
  return y;
}

template <class A>
inline
void
zero( A *X, uint n )
{
  // set an array to 0

  if (n == 0) { return; }

#if 0
  // slow
  uint i;
  for ( i = 0; i < n; i++ ) { X[i] = 0.0; }
#endif

  // fast
  memset( X, 0, n * sizeof(A) );
}

template <class A>
inline
void
copy( A *X, A const *Y, uint n )
{
  // copy Y to X

  if (n == 0) { return; }

#if 0
  // slow
  uint i;
  for ( i = 0; i < n; i++ ) { X[i] = Y[i]; }
#endif

  // fast
  memcpy( X, Y, n * sizeof(A) );
}

inline
int
round( float x )
{
  return (int)rint(x);
}

inline
int
round( double x )
{
  return (int)rint(x);
}


inline
short
abs(short x)
{
  return ( x >= (short)0 ? x : -x );
}

inline
int
abs(int x)
{
  return ::abs(x);
}

inline long
abs(long x)
{
  return ::labs(x);
}

inline
float
abs( float x )
{
  return ::fabsf(x);
}

inline
double
abs( double x )
{
  return ::fabs(x);
}

inline
double long
abs( double long x )
{
#if defined(__sgi) && !defined(__GNUG__) && defined(_COMPILER_VERSION)
#if _COMPILER_VERSION >= 730
  return ::fabsl(x);
#else
  return ::absl(x);
#endif
#else
  return ::fabsl(x);
#endif
}

inline
bool
isnan( float x )
{
  // ???
  return ::isnan(x);
}

inline
bool
isnan( double x )
{
  return ::isnan(x);
}

inline
bool
isnan( double long x )
{
#if defined(__sgi) && defined(_COMPILER_VERSION)
#if _COMPILER_VERSION >= 730
  return ::isnanl(x);
#else
  USE(x);
  DIE();
  return true;
#endif
#else
  return ::isnanl(x);
#endif
}

inline
bool
effectively_zero( float x, float precision )
{
  return abs(x) < precision;
}

inline
bool
effectively_zero( double x, double precision )
{
  return abs(x) < precision;
}

inline
bool
effectively_zero( double long x, double long precision )
{
  return abs(x) < precision;
}

inline
float
chop( float x, float tolerance )
{
  return abs(x) < tolerance ? 0.0 : x;
}

inline
double
chop( double x, double tolerance )
{
  return abs(x) < tolerance ? 0.0 : x;
}

inline
double long
chop( double long x, double long tolerance )
{
  return abs(x) < tolerance ? 0.0 : x;
}

inline
float
arctan( float x, float y )
{
  return atan2f(y, x);
}

inline
double
arctan( double x, double y )
{
  return atan2(y, x);
}

inline
double long
arctan( double long x, double long y )
{
  return atan2l(y, x);
}

inline
float
frac(float a)
{
  return a - floorf(a);
}

inline
double
frac(double a)
{
  return a - floor(a);
}

inline
double long
frac(double long a)
{
  return a - floorl(a);
}

inline
std::complex<float>
chop( std::complex<float> x, float tolerance )
{
  return std::complex<float>(
    chop(x.real(),tolerance), chop(x.imag(),tolerance) );
}

inline
std::complex<double>
chop( std::complex<double> x, double tolerance )
{
  return std::complex<double>(
    chop(x.real(),tolerance), chop(x.imag(),tolerance) );
}

inline
std::complex<double long>
chop( std::complex<double long> x, double long tolerance )
{
  return std::complex<double long>(
    chop(x.real(),tolerance), chop(x.imag(),tolerance) );
}

inline
bool
isnan( std::complex<float> const &x )
{
  return isnan(x.real()) || isnan(x.imag());
}

inline
bool
isnan( std::complex<double> const &x )
{
  return isnan(x.real()) || isnan(x.imag());
}

inline
bool
isnan( std::complex<double long> const &x )
{
  return isnan(x.real()) || isnan(x.imag());
}

inline
bool
effectively_zero( std::complex<float> x, float precision )
{
  return effectively_zero( std::abs(x), precision );
}

inline
bool
effectively_zero( std::complex<double> x, double precision )
{
  return effectively_zero( std::abs(x), precision );
}

inline
bool
effectively_zero( std::complex<double long> x, double long precision )
{
  return effectively_zero( std::abs(x), precision );
}

inline
int
mod( uint x, uint n )
{
  return x % n;
}

inline
int
mod( int x, uint n )
{
  int y = x % n;
  if (y < 0) { y += n; }
  return y;
}

template <class A>
A
norm( A x1, A x2 )
{
  return sqr(x1) + sqr(x2);
}

template <class A>
A
norm( A x1, A x2, A x3 )
{
  return sqr(x1) + sqr(x2) + sqr(x3);
}

template <class A>
A
norm( A x1, A x2, A x3, A x4 )
{
  return sqr(x1) + sqr(x2) + sqr(x3) + sqr(x4);
}

template <class A>
A
abs( A x1, A x2 )
{
  return math::sqrt(norm( x1, x2 ));
}

template <class A>
A
abs( A x1, A x2, A x3 )
{
  return math::sqrt(norm( x1, x2, x3 ));
}

template <class A>
A
abs( A x1, A x2, A x3, A x4 )
{
  return math::sqrt(norm( x1, x2, x3, x4 ));
}


template <class A>
void
normalize( A &x1, A &x2 )
{
  A a = abs(x1, x2);
  x1 /= a;
  x2 /= a;
}

template <class A>
void
normalize( A &x1, A &x2, A &x3 )
{
  A a = abs(x1, x2, x3);
  x1 /= a;
  x2 /= a;
  x3 /= a;
}

template <class A>
void
normalize( A &x1, A &x2, A &x3, A &x4 )
{
  A a = abs(x1, x2, x3, x4);
  x1 /= a;
  x2 /= a;
  x3 /= a;
  x4 /= a;
}

} // namespace math

#endif // math_Math_INCLUDED
