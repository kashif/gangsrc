/* GANG Software
 * BASE/math/Elliptic.H
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

#ifndef math_Elliptic_INCLUDED
#define math_Elliptic_INCLUDED

#include <complex>
#include <algorithm>
#include "Math.H"

namespace math {

class Elliptic1
{

public:

  // Common constants

  // errorCode is set when an error occurs
  static int errorCode;

  // errorFunctionName is set to the function causing the error
  static char const *errorFunctionName;

  // base::String detailing the error
  static char const * const errorMessage[];

  // return values
  enum ErrorCodes {
    ERR_DOMAIN = 1,   // argument domain error
    ERR_SING,         // argument singularity
    ERR_OVERFLOW,     // overflow range error
    ERR_UNDERFLOW,    // underflow range error
    ERR_TLOSS,        // total loss of precision
    ERR_PLOSS         // partial loss of precision
  };

  // Complete elliptic integral of the first kind
  static double K( double m1 );

  // Incomplete elliptic integral of the first kind
  static double F( double phi, double m );

  // Complete elliptic integral of the second kind
  static double E( double m1 );

  // Incomplete elliptic integral of the second kind
  static double E( double phi, double m );

  // Jacobian Elliptic1 Functions
  static int
  Jacobi( double &sn, double &cn, double &dn, double &am,
          double u, double m );

  private:

  // Evaluate polynomial
  static double evaluatePolynomial( double x, double const coef[], int N );

  // Error handler
  static void error( char const *functionName, int code );

  // constants used in K(double)
  static const double ellipticK_P[];
  static const double ellipticK_Q[];
  static const double C1;

  // constants used in E(double)
  static const double ellipticE_P[];
  static const double ellipticE_Q[];
};

/*
   elliptic functions.

  Elliptic Function library

  Theta functions:
    These differ from Mathematica's EllipticTheta[a,u,q] in the
    third argument: q = exp(i pi tau)

  Weierstrass P and related functions:
    w1, w2 are the half-periods
    e1 = P(w1), e2 = P(w2), e3 = P(w1+w2)

  Jacobi elliptic and related functions:
    jacobi_sn(u,m) takes std::complex u and real m
    m = k^2 as in Mathematica

  Elliptic integrals:
    K(m) takes real argument 0 <= m < 1.
    E(m) takes real argument 0 <= m < 1.
    F(u, m) takes real argument 0 <= m < 1.
*/

class Elliptic
{

public:

  // theta functions

  // generalized theta function
  static std::complex<double>
  theta( std::complex<double> const &u, std::complex<double> const &t );

  //
  static std::complex<double>
  theta_p( std::complex<double> const &u, std::complex<double> const &tau );

  //
  static std::complex<double>
  theta_pp( std::complex<double> const &u, std::complex<double> const &tau );

  //
  static std::complex<double>
  theta_ppp( std::complex<double> const &u, std::complex<double> const &tau );

  // traditional theta functions
  static std::complex<double>
  theta1( std::complex<double> const &u, std::complex<double> const &tau );

  //
  static std::complex<double>
  theta2( std::complex<double> const &u, std::complex<double> const &tau );

  //
  static std::complex<double>
  theta3( std::complex<double> const &u, std::complex<double> const &tau );

  //
  static std::complex<double>
  theta4( std::complex<double> const &u, std::complex<double> const &tau );

  //
  static std::complex<double>
  theta1_p( std::complex<double> const &v, std::complex<double> const &tau );

  //
  static std::complex<double>
  theta2_p( std::complex<double> const &v, std::complex<double> const &tau );

  //
  static std::complex<double>
  theta3_p( std::complex<double> const &v, std::complex<double> const &tau );

  //
  static std::complex<double>
  theta4_p( std::complex<double> const &v, std::complex<double> const &tau );

  //
  static std::complex<double>
  theta1_pp( std::complex<double> const &v, std::complex<double> const &tau );

  //
  static std::complex<double>
  theta1_ppp( std::complex<double> const &v, std::complex<double> const &tau );

  // weierstrass functions
  static std::complex<double>
  weierstrass_P( std::complex<double> const &, std::complex<double> const &w1,
                 std::complex<double> const &w2 );

  //
  static std::complex<double>
  weierstrass_P_p( std::complex<double> const &, std::complex<double> const &w1,
                       std::complex<double> const &w2 );

  //
  static std::complex<double>
  weierstrass_zeta( std::complex<double> const &, std::complex<double> const &w1,
                    std::complex<double> const &w2 );

  //
  static std::complex<double>
  weierstrass_sigma( std::complex<double> const &, std::complex<double> const &w1,
                     std::complex<double> const &w2 );

  //
  static std::complex<double>
  weierstrass_g2( std::complex<double> const &w1, std::complex<double> const &w2 );

  //
  static std::complex<double>
  weierstrass_g3( std::complex<double> const &w1, std::complex<double> const &w2 );

  //
  static std::complex<double>
  weierstrass_e1( std::complex<double> const &w1, std::complex<double> const &w2 );

  //
  static std::complex<double>
  weierstrass_e2( std::complex<double> const &w1, std::complex<double> const &w2 );

  //
  static std::complex<double>
  weierstrass_e3( std::complex<double> const &w1, std::complex<double> const &w2 );

  //
  static std::complex<double>
  weierstrass_eta1( std::complex<double> const &w1, std::complex<double> const &w2 );

  //
  static std::complex<double>
  weierstrass_eta2( std::complex<double> const &w1, std::complex<double> const &w2 );

  // Jacobian elliptic functions
  static inline std::complex<double> am( double u, double m );
  //
  static inline std::complex<double> sn( std::complex<double> const &u, double m );
  //
  static inline std::complex<double> cn( std::complex<double> const &u, double m );
  //
  static inline std::complex<double> dn( std::complex<double> const &u, double m );
  //
  static inline std::complex<double> ns( std::complex<double> const &u, double m );
  //
  static inline std::complex<double> cs( std::complex<double> const &u, double m );
  //
  static inline std::complex<double> ds( std::complex<double> const &u, double m );
  //
  static inline std::complex<double> nc( std::complex<double> const &u, double m );
  //
  static inline std::complex<double> sc( std::complex<double> const &u, double m );
  //
  static inline std::complex<double> dc( std::complex<double> const &u, double m );
  //
  static inline std::complex<double> nd( std::complex<double> const &u, double m );
  //
  static inline std::complex<double> sd( std::complex<double> const &u, double m );
  //
  static inline std::complex<double> cd( std::complex<double> const &u, double m );

  // elliptic integrals
  static inline double K( double m );
  //
  static inline double E( double m );
  //
  static inline double F( double u, double m );
  //
  static inline double nome_q( double m );


private:
  //
  static void
  Jacobi( std::complex<double> &sn_,
          std::complex<double> &cn_, std::complex<double> &dn_,
          std::complex<double> const &u, double m );

  static std::complex<double> const I;
  static uint const MAX_COUNT = 20;

  static inline
  double
  tolerance( double x )
    {
      static double const smallreal_double  = 100.0 * DBL_MIN;
      static double const rel_precision_double  = 4.0 * DBL_EPSILON;

      double t = math::abs(x) * rel_precision_double;
      return std::max( t, smallreal_double );
    }

};


std::complex<double>
Elliptic::
am( double u, double m )
{
  double sn, cn, dn, am;
  Elliptic1::Jacobi( sn, cn, dn, am, u, m );
  return am;
}


std::complex<double>
Elliptic::
sn( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return sn;
}


std::complex<double>
Elliptic::
ns( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return 1.0 / sn;
}


std::complex<double>
Elliptic::
cn( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return cn;
}


std::complex<double>
Elliptic::
nc( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return 1.0 / cn;
}


std::complex<double>
Elliptic::
dn( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return dn;
}


std::complex<double>
Elliptic::
nd( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return 1.0/ dn;
}


std::complex<double>
Elliptic::
sc( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return sn / cn;
}


std::complex<double>
Elliptic::
cs( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return cn / sn;
}


std::complex<double>
Elliptic::
sd( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return sn / dn;
}


std::complex<double>
Elliptic::
ds( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return dn / sn;
}


std::complex<double>
Elliptic::
cd( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return cn / dn;
}


std::complex<double>
Elliptic::
dc( std::complex<double> const &u, double m )
{
  std::complex<double> sn, cn, dn;
  Jacobi( sn, cn, dn, u, m );
  return dn / cn;
}


double
Elliptic::
K( double m )
{
  return Elliptic1::K( m );
}


double
Elliptic::
E( double m )
{
  return Elliptic1::E( m );
}


double
Elliptic::
F( double u, double m )
{
  return Elliptic1::F( u, m );
}

} // namespace math

#endif // math_Elliptic_INCLUDED
