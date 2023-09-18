/* GANG Software
 * BASE/math/Romberg.H
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

#ifndef math_Romberg_INCLUDED
#define math_Romberg_INCLUDED

#include "Math.H"

namespace math {

//
int
integrate_romberg( double x0, double x1,
                   double (*f)(double), double eps,
                   double &integral );

//
int
integrate_romberg( std::complex<double> &x0, std::complex<double> &x1,
                   std::complex<double> (*f)(std::complex<double>),
                   double eps,
                   std::complex<double> &integral );
/*
  Integration of a function f(x) from a to b via
  Romberg Integration.

  arguments:
    A const &a       (in) starting point of integration
    A const &b       (in) end point of integration
    A (*f)(A),       (in) function to be integrated
    double const h   (in) initial integration step size
    double eps       (in) accuracy bound for error estimate
    uint m   (in) maximum iteration
    A &integral      (out) value of integral
    double &error    (out) error estimate
    double &h_       (out) final step size
    uint &m_ (out) number of iterations taken

  Return values:
    0  ok
    1  accuracy not reached after m steps
    2  invalid value for m
    3  invalid value for eps
    4  out of memory
 */
template<class A>
int
integrate_romberg(
  A const &a,
  A const &b,
  A (*f)(A),
  double eps,
  double h,
  uint m,
  A &integral,
  double &error,
  double &h_,
  uint &m_
  );


static inline float romberg_abs(float x)
{ return math::abs(x); }
static inline double romberg_abs(double x)
{ return math::abs(x); }
static inline double long romberg_abs(double long x)
{ return math::abs(x); }

static inline float romberg_abs(std::complex<float> const &x)
{ return std::abs(x); }
static inline double romberg_abs(std::complex<double> const &x)
{ return std::abs(x); }
static inline double long romberg_abs(std::complex<double long> const &x)
{ return std::abs(x); }

template<class A>
int
integrate_romberg(
  A const &a,
  A const &b,
  A (*f)(A),
  double eps,
  double h,
  uint m,
  A &integral,
  double &error,
  double &h_,
  uint &m_
  )
{
  int err = 0;

  integral = 0.0;
  error = 0.0;

  m_ = 0;
  h_ = 0.0;

  A *L;
  uint count;

  // trival case a==b
  if (a == b) { err = 0; goto end; }

  // check for valid m
  if (m <= 1) { err = 2; goto end; }

  // check for valid eps
  if (eps <= 0.0) { err = 3; goto end; }

  // allocate tableau
  L = new A[m];
  if ( L == 0 ) { err = 4; goto end; } // error: out of memory

  // adjust step size

  // make sure h is no bigger than the interval
  h = std::min( math::abs(h), romberg_abs(b-a) );

  // if h is 0, set it to the interval
  if ( h == 0.0 ) { h = romberg_abs(b-a); }

  count = (uint)rint( romberg_abs(b-a) / h );

  // first Romberg row (one entry only)
  L[0] = 0.5 * ((*f)(a) + (*f)(b));

  uint k;
  for (k = 1; k < count; k++)
  {
    L[0] += (*f)(a + k * h);
  }

  L[0] *= h;

  // lower Romberg rows
  uint j;
  for (j = 1; j < m; j++)
  {
    h /= 2.0;
    A L0 = L[0];
    L[0] = 0.0;
    L[j] = 0.0;
    for (k = 0; k < count; k++)
    {
      L[0] += (*f)(a + (2 * k + 1) * h);
    }

    L[0] = 0.5 * L0 + h * L[0];
    uint r = 1;
    for (k = 1; k <= j; k++)
    {
      r *= 4;
      A Lk = L[k];
      L[k] = (A(r) * L[k-1] - L0) / (A(r) - A(1));
      L0 = Lk;
    }

    error = romberg_abs(L[j] - L[j-1]);   // error estimate
    integral = L[j];

    // stop if sufficient accuracy has been reached
    if (error < eps) { break; }
    count *= 2;
  }

  err = j == m ? 1 : 0;

  m_ = j;
  h_ = h;
  delete [] L;

  end:
  return err;
}

} // namespace math

#endif // math_Romberg_INCLUDED
