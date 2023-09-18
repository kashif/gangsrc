/* GANG Software
 * BASE/math/Elliptic.C
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

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "base/Use.h"
#include "Math.H"
#include "Elliptic.H"

namespace math {

/*
  Some of these routines were adapted from the Cephes Math Library
*/
//-------------------------------------------------------------------------


std::complex<double> const Elliptic::I = std::complex<double>(0.0, 1.0);

/*
  -------------------------------------------------------------------
  Theta functions
  -------------------------------------------------------------------
  */
std::complex<double>
Elliptic::
theta( std::complex<double> const &u, std::complex<double> const &tau )
{
  uint n = 1;
  std::complex<double> sum = 1.0;
  std::complex<double> d;
  double nn;

  for(;;)
  {
    nn = double(n);
    d = std::exp( I*math::pi*nn*(nn*tau + 2.0*u) ) +
      std::exp( -I*math::pi*nn*(-nn*tau + 2.0*u) );
    sum += d;
    if ( std::abs(d) < tolerance(std::abs(sum)) || n >= MAX_COUNT ) { break; }
    n++;
  }
  return sum;
}


std::complex<double>
Elliptic::
theta_p( std::complex<double> const &u, std::complex<double> const &tau )
{
  uint n = 1;
  std::complex<double> sum = 0.0;
  std::complex<double> d;
  double nn;

  for(;;)
  {
    nn = double(n);
    d = 2.0*I*math::pi*nn * std::exp( I*math::pi*nn*(nn*tau + 2.0*u) ) +
      (-2.0*I*math::pi*nn) * std::exp( -I*math::pi*nn*(-nn*tau + 2.0*u) );
    sum += d;
    if ( std::abs(d) < tolerance(std::abs(sum)) || n >= MAX_COUNT ) { break; }
    n++;
  }
  return sum;
}


std::complex<double>
Elliptic::
theta_pp( std::complex<double> const &u, std::complex<double> const &tau )
{
  uint n = 1;
  std::complex<double> sum = 0.0;
  std::complex<double> d;
  double nn;

  for(;;)
  {
    nn = double(n);
    d = math::sqr(2.0*I*math::pi*nn) * std::exp( I*math::pi*nn*(nn*tau + 2.0*u) ) +
      math::sqr(-2.0*I*math::pi*nn) * std::exp( -I*math::pi*nn*(-nn*tau + 2.0*u) );
    sum += d;
    if ( std::abs(d) < tolerance(std::abs(sum)) || n >= MAX_COUNT ) { break; }
    n++;
  }
  return sum;
}


std::complex<double>
Elliptic::
theta_ppp( std::complex<double> const &u, std::complex<double> const &tau )
{
  uint n = 1;
  std::complex<double> sum = 0.0;
  std::complex<double> d;
  double nn;

  for(;;)
  {
    nn = double(n);
    d = math::cube(2.0*I*math::pi*nn) * std::exp( I*math::pi*nn*(nn*tau + 2.0*u) ) +
      math::cube(-2.0*I*math::pi*nn) * std::exp( -I*math::pi*nn*(-nn*tau + 2.0*u) );
    sum += d;
    if ( std::abs(d) < tolerance(std::abs(sum)) || n >= MAX_COUNT ) { break; }
    n++;
  }
  return sum;
}

std::complex<double>
Elliptic::
theta1( std::complex<double> const &u, std::complex<double> const &t )
{
  return -I * std::exp( I*(0.25*math::pi*t+u) ) * theta( u/math::pi + 0.5*(t+1.0), t );
}


std::complex<double>
Elliptic::
theta1_p( std::complex<double> const &u, std::complex<double> const &t )
{
  // inefficient
  std::complex<double> v = u/math::pi + 0.5*(t+1.0);
  return std::exp( I*(0.25*math::pi*t+u) ) *
    ( theta( v, t ) - I * theta_p( v, t )/math::pi );
}


std::complex<double>
Elliptic::
theta1_pp( std::complex<double> const &u, std::complex<double> const &t )
{
  // inefficient
  std::complex<double> v = u/math::pi + 0.5*(t+1.0);
  return std::exp( I*(0.25*math::pi*t+u) ) *
    ( I*theta(v,t) + (2.0/math::pi)*theta_p(v,t) +
      (-I/math::sqr(math::pi))*theta_pp(v,t) );
}


std::complex<double>
Elliptic::
theta1_ppp( std::complex<double> const &u, std::complex<double> const &t )
{
  // inefficient
  std::complex<double> v = u/math::pi + 0.5*(t+1.0);
  return std::exp( I*(0.25*math::pi*t+u) ) *
    ( -theta(v,t)+ (3.0*I/math::pi)*theta_p(v,t) +
      (3.0/math::sqr(math::pi))*theta_pp(v,t) -(I/math::cube(math::pi))*theta_ppp(v,t) );
}


std::complex<double>
Elliptic::
theta2( std::complex<double> const &u, std::complex<double> const &t )
{
  return std::exp( I*(0.25*math::pi*t+u) ) *
    theta(u/math::pi + 0.5*t, t );
}


std::complex<double>
Elliptic::
theta2_p( std::complex<double> const &u, std::complex<double> const &t )
{
  // inefficient
  std::complex<double> v = u/math::pi + 0.5*t;
  return std::exp( I*(0.25*math::pi*t+u) ) *
    ( I * theta( v, t ) + theta_p( v, t )/math::pi );
}


std::complex<double>
Elliptic::
theta3( std::complex<double> const &u, std::complex<double> const &t )
{
  return theta( u/math::pi, t );
}


std::complex<double>
Elliptic::
theta3_p( std::complex<double> const &u, std::complex<double> const &t )
{
  return theta_p( u/math::pi, t ) / math::pi;
}


std::complex<double>
Elliptic::
theta4( std::complex<double> const &u, std::complex<double> const &t )
{
  return theta( u/math::pi + 0.5, t );
}


std::complex<double>
Elliptic::
theta4_p( std::complex<double> const &u, std::complex<double> const &t )
{
  return theta_p( u/math::pi + 0.5, t ) / math::pi;
}


/*
  -------------------------------------------------------------------
  Weierstrass P and related functions
  -------------------------------------------------------------------
  */
std::complex<double>
Elliptic::
weierstrass_g2( std::complex<double> const &w1, std::complex<double> const &w2 )
{
  std::complex<double> tau = w2/w1;
  std::complex<double> t2, t3, t4;

  t2 = theta2( 0.0, tau );
  t3 = theta3( 0.0, tau );
  t4 = theta4( 0.0, tau );

  t2 *= t2; t2 *= t2; t2 *= t2;
  t3 *= t3; t3 *= t3; t3 *= t3;
  t4 *= t4; t4 *= t4; t4 *= t4;

  return 2.0 / 3.0 * math::sqr(math::sqr(math::pi/(2.0*w1))) * (t2+t3+t4);
}


std::complex<double>
Elliptic::
weierstrass_g3( std::complex<double> const &w1, std::complex<double> const &w2 )
{
  std::complex<double> tau = w2/w1;
  std::complex<double> t2, t3, t4;

  t2 = theta2( 0.0, tau );
  t3 = theta3( 0.0, tau );
  t4 = theta4( 0.0, tau );

  t2 *= t2; t2 *= t2;
  t3 *= t3; t3 *= t3;
  t4 *= t4; t4 *= t4;

  return 4.0 / 27.0 * math::cube(math::sqr(math::pi / (2.0 * w1))) * (t2+t3)*(t3+t4)*(t4-t2);
}


std::complex<double>
Elliptic::
weierstrass_e1( std::complex<double> const &w1, std::complex<double> const &w2 )
{
  std::complex<double> tau = w2/w1;
  std::complex<double> t3, t4;
  t3 = theta3( 0.0, tau );
  t3 *= t3;
  t3 *= t3;
  t4 = theta4( 0.0, tau );
  t4 *= t4;
  t4 *= t4;

  return math::sqr(math::pi) * ( t3 + t4 ) / ( 12.0 * math::sqr(w1) );
}


std::complex<double>
Elliptic::
weierstrass_e2( std::complex<double> const &w1, std::complex<double> const &w2 )
{
  std::complex<double> tau = w2/w1;
  std::complex<double> t1, t2;
  t1 = theta2( 0.0, tau );
  t1 *= t1;
  t1 *= t1;
  t2 = theta3( 0.0, tau );
  t2 *= t2;
  t2 *= t2;

  return -math::sqr(math::pi) * ( t1+t2 ) / ( 12.0 * math::sqr(w1) );
}


std::complex<double>
Elliptic::
weierstrass_e3( std::complex<double> const &w1, std::complex<double> const &w2 )
{
  std::complex<double> tau = w2/w1;
  std::complex<double> t1, t2;
  t1 = theta2( 0.0, tau );
  t1 *= t1;
  t1 *= t1;
  t2 = theta4( 0.0, tau );
  t2 *= t2;
  t2 *= t2;

  return math::sqr(math::pi) * ( t1-t2 ) / ( 12.0 * math::sqr(w1) );
}


std::complex<double>
Elliptic::
weierstrass_eta1( std::complex<double> const &w1, std::complex<double> const &w2 )
{
  /*
    std::complex<double> Q = exp( 2.0*I*math::pi*w2/w1 );
    // Mathematica:  Sum[DivisorSigma[1,n] Q^n,{n,1,10}]
    std::complex<double> sum =
      Q*(Q*(Q*(Q*(Q*(Q*(Q*(Q*(Q*(18.0*Q+13.0)+15.0)+8.0)+12.0)
    +6.0)+7.0)+4.0)+3.0)+1.0);
    return math::sqr(math::pi)*( 1.0 - 24.0* sum )/(12.0 * w1);
  */

  // alternate way to calculate eta1
  std::complex<double> tau = w2/w1;
  std::complex<double> t1, t2;
  t1 = theta1_ppp( 0.0, tau );
  t1 *= math::cube(math::pi);
  t2 = theta1_p( 0.0, tau );
  t2 *= math::pi;

  return -t1 / ( 12.0 * w1 * t2 );
}


std::complex<double>
Elliptic::
weierstrass_eta2( std::complex<double> const &w1, std::complex<double> const &w2 )
{
  std::complex<double> t;
  t = weierstrass_eta1( w1, w2 );

  return ( -0.5*I*math::pi + w2*t ) / w1;
}


std::complex<double>
Elliptic::
weierstrass_P( std::complex<double> const &z, std::complex<double> const &w1,
               std::complex<double> const &w2 )
{
  std::complex<double> v = math::pi * z / (2.0 * w1);
  std::complex<double> tau = w2/w1;
  std::complex<double> e1, t1, t2, t3, t4;
  e1 = weierstrass_e1( w1, w2 );
  t1 = theta1_p( 0.0, tau );
  t1 *= math::pi;
  t2 = theta2( v, tau );
  t3 = theta2( 0.0, tau );
  t4 = theta1( v, tau );

  return e1 + math::sqr( t1*t2 / ( 2.0*w1*t3*t4 ) );
}


std::complex<double>
Elliptic::
weierstrass_P_p( std::complex<double> const &z,
                 std::complex<double> const &w1, std::complex<double> const &w2 )
{
  std::complex<double> v = math::pi * z / (2.0 * w1);
  std::complex<double> tau = w2/w1;
  std::complex<double> t1, t2, t3, t4, t5, t6, t7, t8;

  t1 = theta2( v, tau );
  t2 = theta3( v, tau );
  t3 = theta4( v, tau );
  t4 = theta1_p( 0.0, tau );
  t4 *= math::pi;
  t4 = math::cube(t4);
  t5 = theta2( 0.0, tau );
  t6 = theta3( 0.0, tau );
  t7 = theta4( 0.0, tau );
  t8 = theta1( v, tau );
  t8 = math::cube(t8);

  return -( t1*t2*t3*t4 ) / ( 4.0*math::cube(w1) * t5*t6*t7*t8 );
}


std::complex<double>
Elliptic::
weierstrass_zeta( std::complex<double> const &z,
                 std::complex<double> const &w1, std::complex<double> const &w2 )
{
  std::complex<double> v = math::pi * z / (2.0 * w1);
  std::complex<double> tau = w2/w1;
  std::complex<double> eta1, t1, t2;

  eta1 = weierstrass_eta1( w1, w2 );
  t1 = theta1_p( v, tau );
  t1 *= math::pi;
  t2 = theta1( v, tau );

  return eta1 * z / w1 + t1 / ( 2.0 * w1 * t2 );
}


std::complex<double>
Elliptic::
weierstrass_sigma(
  std::complex<double> const &z,
  std::complex<double> const &w1,
  std::complex<double> const &w2 )
{
  std::complex<double> v = math::pi * z / (2.0 * w1);
  std::complex<double> tau = w2/w1;
  std::complex<double> eta1, t1, t2;

  eta1 = weierstrass_eta1( w1, w2 );
  t1 = theta1( v, tau );
  t2 = theta1_p( 0.0, tau );
  t2 *= math::pi;

  return 2.0 * w1 * std::exp( eta1 * math::sqr(z) / ( 2.0 * w1) ) * t1 / t2;
}


/*
  -------------------------------------------------------------------
  Jacobi elliptic sn, cn, dn and related functions

  - computes Jacobi elliptic functions sn(u,m), cn(u,m), dn(u,m)
  - adapted from Numerical Recipes in C, p 270 to allow complex u,
      and to match Mathematica's m
  - m must be real
  - implemented as two real computations rather than one complex for
      accuracy
-------------------------------------------------------------------
  */

// complex version
void
Elliptic::
Jacobi(
  std::complex<double> &sn, std::complex<double> &cn,
  std::complex<double> &dn,
  std::complex<double> const &u, double m )
{
  double x = u.real();
  double y = u.imag();
  double snx, cnx, dnx, amx;
  double sn_, cn_, dn_, am_;

  // call real version
  Elliptic1::Jacobi( snx, cnx, dnx, amx, x, m );
  Elliptic1::Jacobi( sn_, cn_, dn_, am_, y, 1.0 - m );

  double sny_i = sn_ / cn_;  // sny/i
  double cny = 1.0 / cn_;
  double dny = dn_ / cn_;

  std::complex<double> d = 1.0 + m * math::sqr( snx * sny_i );
  sn = std::complex<double>( snx * cny * dny, sny_i * cnx * dnx ) / d;
  cn = std::complex<double>( cnx * cny, -snx * sny_i * dnx * dny ) / d;
  dn = std::complex<double>( dnx * dny, -m * snx * sny_i * cnx * cny ) / d;
}

//=====================================================================
/*
  Java class implementing elliptic functions.

  SYNOPSIS:

  Complete elliptic integral of the first kind
  double K( double m1 );

  Incomplete elliptic integral of the first kind
  double F( double phi, double m );

  Complete elliptic integral of the first kind
  double E( double m1 );

  Incomplete elliptic integral of the first kind
  double E( double phi, double m );

  Jacobi elliptic functions
  int Jacobi( double u, double m, double x[] )


  DESCRIPTION:

  Complete elliptic integral of the first kind
  K[m_] := Integral[ 1/Sqrt[1 - (1-m)*Sin[t]^2], {t, 0, Pi/2} ]

  Incomplete elliptic integral of the first kind
  F[phi_, m_] := Integral[ 1 / Sqrt[1 - m*Sin[t]^2], {t, 0, phi}]

  Complete elliptic integral of the first kind
  E[m_] := Integral[ Sqrt[1 - (1-m)*Sin[t]], {t, 0, Pi/2}]

  Incomplete elliptic integral of the first kind
  double E( double phi, double m );
  E[phi, m] := Integral[ Sqrt[1 - m*Sin[t]^2, {t, 0, phi}]

  Jacobi elliptic functions
  int Jacobi( double u, double m, double x[] )
  x[0] <- JacobiSN[u,m]
  x[1] <- JacobiCN[u,m]
  x[2] <- JacobiDN[u,m]
  x[3] <- JacobiAmplitude[u,m]


  DIAGNOSTICS:

  If an error occurs in an elliptic function, errorCode is set to:

  1:  argument domain error
  2:  argument singularity
  3:  overflow range error
  4:  underflow range error
  5:  total loss of precision
  6:  partial loss of precision

  If no error occurs in an elliptic function, errorCode is not changed.
  This allows a single check of errorCode after multiple calls to elliptic
  functions. After an error, errorCode should be reset to 0.


  SOURCE:

  Converted to Java by Nicholas Schmitt May 16, 2000 from

  Cephes Math Library Release 2.1:  January, 1989
  Copyright 1984, 1987, 1989 by Stephen L. Moshier
  Direct inquiries to 30 Frost Street, Cambridge, MA 02140
  http://www.netlib.org/cephes
*/
//-----------------------------------------
// Common constants

// errorCode is set when an error occurs
int Elliptic1::errorCode = 0;

// errorFunctionName is set to the function causing the error
char const *Elliptic1::errorFunctionName;

// base::String detailing the error
char const * const Elliptic1::errorMessage[] = {
  "",
  "argument domain error",       // error code 1
  "argument singularity error",
  "overflow",
  "underflow",
  "total loss of precision",
  "partial loss of precision"
};

//-----------------------------------------
// Complete elliptic integral of the first kind

double
Elliptic1::
K(
  double m1 )
{
  if( m1 < 0.0 || m1 > 1.0 )
  {
    // domain error
    error( "Elliptic.K(double)", ERR_DOMAIN );
    return 0.0;
  }

  if( m1 > DBL_EPSILON )
  {
    // m is not 0
    return evaluatePolynomial( m1, ellipticK_P, 10) - math::log(m1) *
      evaluatePolynomial( m1, ellipticK_Q, 10);
  }
  else
  {
    // m1 is effectively 0
    if( m1 == 0.0 )
    {
      error( "Elliptic.K(double)", ERR_SING );
      return DBL_MAX;
    }
    else
    {
      return C1 - 0.5 * math::log(m1);
    }
  }
}


//-----------------------------------------
// Incomplete elliptic integral of the first kind

double
Elliptic1::
F(
  double phi,
  double m )
{
  double a, b, c, e, temp, t, K_;
  int d, mod, sign, npio2;

  if( m == 0.0 )
  {
    return phi;
  }
  a = 1.0 - m;
  if( a == 0.0 )
  {
    if( math::abs(phi) >= (0.5*math::pi) )
    {
      error( "Elliptic.F(double, double)", ERR_SING );
      return DBL_MAX;
    }
    return math::log(  math::tan( 0.5*((0.5*math::pi) + phi) )  );
  }
  npio2 = (int)floor( phi/(0.5*math::pi) );
  if( (npio2 & 1) != 0 )
  {
    npio2 += 1;
  }
  if( npio2 != 0 )
  {
    K_ = K( a );
    phi = phi - npio2 * (0.5*math::pi);
  }
  else
  {
    K_ = 0.0;
  }
  if( phi < 0.0 )
  {
    phi = -phi;
    sign = -1;
  }
  else
  {
    sign = 0;
  }
  b = math::sqrt(a);
  t = math::tan( phi );
  if( math::abs(t) > 10.0 )
  {
    // Transform the amplitude
    e = 1.0 / (b*t);
    // but avoid multiple recursions
    if( math::abs(e) < 10.0 )
    {
      e = math::atan(e);
      if( npio2 == 0 )
      {
        K_ = K( a );
      }
      temp = K_ - F( e, m );
      if( sign < 0 )
      {
        temp = -temp;
      }
      temp += npio2 * K_;
      return temp;
    }
  }
  a = 1.0;
  c = math::sqrt(m);
  d = 1;
  mod = 0;

  while ( math::abs(c/a) > DBL_EPSILON )
  {
    temp = b/a;
    phi = phi + math::atan(t*temp) + mod * math::pi;
    mod = (int)( (phi + (0.5*math::pi))/math::pi );
    t = t * ( 1.0 + temp )/( 1.0 - temp * t * t );
    c = 0.5 * ( a - b );
    temp = math::sqrt( a * b );
    a = 0.5 * ( a + b );
    b = temp;
    d += d;
  }

  temp = (math::atan(t) + mod * math::pi)/(d * a);

  if( sign < 0 )
  {
    temp = -temp;
  }
  temp += npio2 * K_;
  return temp;
}


//-----------------------------------------
// Complete elliptic integral of the second kind

double
Elliptic1::
E(
  double m1 )
{
  if ( m1 == 0.0 )
  {
    return 1.0;
  }
  if( m1 <= 0.0 || m1 > 1.0 )
  {
    error( "Elliptic.E(double)", ERR_DOMAIN );
    return 0.0;
  }
  return evaluatePolynomial( m1, ellipticE_P, 10 ) - math::log(m1) *
    (m1 * evaluatePolynomial( m1, ellipticE_Q, 9 ));
}


//-----------------------------------------
// Incomplete elliptic integral of the second kind

double
Elliptic1::
E(
  double phi,
  double m )
{
  double a, b, c, e, temp;
  double lphi, t, E_;
  int d, mod, npio2, sign;

  if ( m == 0.0 )
  {
    return phi;
  }
  lphi = phi;
  npio2 = (int)floor( lphi/(0.5*math::pi) );
  if( (npio2 & 1) != 0 )
  {
    npio2 += 1;
  }
  lphi = lphi - npio2 * (0.5*math::pi);
  if( lphi < 0.0 )
  {
    lphi = -lphi;
    sign = -1;
  }
  else
  {
    sign = 1;
  }
  a = 1.0 - m;
  E_ = E( a );
  if( a == 0.0 )
  {
    temp = math::sin( lphi );
    if( sign < 0 )
    {
      temp = -temp;
    }
    temp += npio2 * E_;
    return temp;
  }
  t = math::tan( lphi );
  b = math::sqrt(a);
  if( math::abs(t) > 10.0 )
  {
    // Transform the amplitude
    e = 1.0/(b*t);
    // but avoid multiple recursions
    if( math::abs(e) < 10.0 )
    {
      e = math::atan(e);
      temp = E_ + m * math::sin( lphi ) * math::sin( e ) - E( e, m );
      if( sign < 0 )
      {
        temp = -temp;
      }
      temp += npio2 * E_;
      return temp;
    }
  }
  c = math::sqrt(m);
  a = 1.0;
  d = 1;
  e = 0.0;
  mod = 0;

  while ( math::abs(c/a) > DBL_EPSILON )
  {
    temp = b/a;
    lphi = lphi + math::atan(t*temp) + mod * math::pi;
    mod = (int)( (lphi + (0.5*math::pi))/math::pi );
    t = t * ( 1.0 + temp )/( 1.0 - temp * t * t );
    c = 0.5*( a - b );
    temp = math::sqrt( a * b );
    a = 0.5*( a + b );
    b = temp;
    d += d;
    e += c * math::sin(lphi);
  }
  temp = E_ / K( 1.0 - m );
  temp *= (math::atan(t) + mod * math::pi)/(d * a);
  temp += e;

  if( sign < 0 )
  {
    temp = -temp;
  }
  temp += npio2 * E_;
  return temp;
}


//-----------------------------------------
// Jacobian Elliptic Functions

int
Elliptic1::
Jacobi(
  double &sn,
  double &cn,
  double &dn,
  double &am,
  double u,
  double m )
{
  // returns x = { sn, cn, dn, ph }

  double ai, b, phi, t, twon;
  double a[9];
  double c[9];
  int i;

  // Check for special cases

  if ( m < 0.0 || m > 1.0 )
  {
    // domain error
    error( "Elliptic.Jacobi()", ERR_DOMAIN );
    sn = 0.0;
    cn = 0.0;
    am = 0.0;
    dn = 0.0;
    return -1;
  }
  if( m < 1.0e-9 )
  {
    // m > 0 and near 0
    t = math::sin(u);
    b = math::cos(u);
    ai = 0.25 * m * (u - t*b);
    sn = t - ai*b;
    cn = b + ai*t;
    am = u - ai;
    dn = 1.0 - 0.5*m*t*t;
    return 0;
  }

  if( m >= 1.0 - 1.0e-10 )
  {
    // m < 1 and near 1
    ai = 0.25 * (1.0-m);
    b = math::cosh(u);
    t = math::tanh(u);
    phi = 1.0/b;
    twon = b * math::sinh(u);
    sn = t + ai * (twon - u)/(b*b);
    am = 2.0*math::atan(math::exp(u)) - (0.5*math::pi) + ai*(twon - u)/b;
    ai *= t * phi;
    cn = phi - ai * (twon - u);
    dn = phi + ai * (twon + u);
    return 0;
  }

  // AGM scale
  a[0] = 1.0;
  b = math::sqrt(1.0 - m);
  c[0] = math::sqrt(m);
  twon = 1.0;
  i = 0;

  while ( math::abs(c[i]/a[i]) > DBL_EPSILON )
  {
    if( i > 7 )
    {
      error( "Elliptic.Jacobi()", ERR_OVERFLOW );

      // backward recurrence
      phi = twon * a[i] * u;
      do
      {
        t = c[i] * math::sin(phi) / a[i];
        b = phi;
        phi = 0.5*(math::asin(t) + phi);
      }
      while ( --i != 0 );

      sn = math::sin(phi);
      t = math::cos(phi);
      cn = t;
      dn = t/math::cos(phi-b);
      am = phi;
      return 0;
    }
    ai = a[i];
    ++i;
    c[i] = 0.5*( ai - b );
    t = math::sqrt( ai * b );
    a[i] = 0.5*( ai + b );
    b = t;
    twon *= 2.0;
  }

  // backward recurrence
  phi = twon * a[i] * u;
  do
  {
    t = c[i] * math::sin(phi) / a[i];
    b = phi;
    phi = 0.5*(math::asin(t) + phi);
  }
  while ( --i != 0 );

  sn = math::sin(phi);
  t = math::cos(phi);
  cn = t;
  dn = t / math::cos(phi-b);
  am = phi;
  return 0;
}


//-----------------------------------------
// Private fields and methods

// Evaluate polynomial

double
Elliptic1::
evaluatePolynomial(
  double x,
  double const coef[],
  int N )
{
  double r;
  int i;

  int j = 0;
  r = coef[j++];
  i = N;

  do
  {
    r = r * x  +  coef[j++];
  }
  while ( --i != 0 );

  return r;
}


// Error handler

void
Elliptic1::
error(
  char const *const functionName,
  int code )
{
  errorCode = code;
  errorFunctionName = functionName;

#if 0
  std::cerr << errorFunctionName;
  std::cerr << ": ";
  std::cerr << errorMessage[code] << std::endl;
#endif
}


// constants used in K(double)
double const Elliptic1::
ellipticK_P[] =
{
  1.37982864606273237150e-04,
  2.28025724005875567385e-03,
  7.97404013220415179367e-03,
  9.85821379021226008714e-03,
  6.87489687449949877925e-03,
  6.18901033637687613229e-03,
  8.79078273952743772254e-03,
  1.49380448916805252718e-02,
  3.08851465246711995998e-02,
  9.65735902811690126535e-02,
  1.38629436111989062502e+00
};
double const Elliptic1::
ellipticK_Q[] =
{
  2.94078955048598507511e-05,
  9.14184723865917226571e-04,
  5.94058303753167793257e-03,
  1.54850516649762399335e-02,
  2.39089602715924892727e-02,
  3.01204715227604046988e-02,
  3.73774314173823228969e-02,
  4.88280347570998239232e-02,
  7.03124996963957469739e-02,
  1.24999999999870820058e-01,
  4.99999999999999999821e-01
};
double const Elliptic1::
C1 = math::log(4.0);

// constants used in E(double)
double const Elliptic1::
ellipticE_P[] = {
  1.53552577301013293365e-04,
  2.50888492163602060990e-03,
  8.68786816565889628429e-03,
  1.07350949056076193403e-02,
  7.77395492516787092951e-03,
  7.58395289413514708519e-03,
  1.15688436810574127319e-02,
  2.18317996015557253103e-02,
  5.68051945617860553470e-02,
  4.43147180560990850618e-01,
  1.00000000000000000299e+00
};
double const Elliptic1::
ellipticE_Q[] = {
  3.27954898576485872656e-05,
  1.00962792679356715133e-03,
  6.50609489976927491433e-03,
  1.68862163993311317300e-02,
  2.61769742454493659583e-02,
  3.34833904888224918614e-02,
  4.27180926518931511717e-02,
  5.85936634471101055642e-02,
  9.37499997197644278445e-02,
  2.49999999999888314361e-01
};

} // namespace math
