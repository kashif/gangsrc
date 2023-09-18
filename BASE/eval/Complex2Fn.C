/* GANG Software
 * BASE/eval/Complex2Fn.C
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

#include <math.h>
#include "math/Elliptic.H"
#include "Complex2Fn.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

static const std::complex<double> I(0.0, 1.0);
static const std::complex<double> zero(0.0, 0.0);
static const std::complex<double> half(0.5, 0.0);
static const std::complex<double> one(1.0, 0.0);

#ifdef PLATFORM_IRIX_NEW
#define HAVE_CPX_FN_EXT // have extended set of std::complex functions
#endif

/*
  ----------------------------------------------------------------
  Arithmetic Functions
  ----------------------------------------------------------------
  */

void
cpx_double_fn::
pos( std::complex<double> &r, std::complex<double> const &x )
{
  r = x;
}

void
cpx_double_fn::
neg( std::complex<double> &r, std::complex<double> const &x )
{
  r = -x;
}

void
cpx_double_fn::
add( std::complex<double> &r, std::complex<double> const &x, std::complex<double> const &y )
{
  r = x + y;
}

void
cpx_double_fn::
sub( std::complex<double> &r, std::complex<double> const &x, std::complex<double> const &y )
{
  r = x - y;
}

void
cpx_double_fn::
mul( std::complex<double> &r, std::complex<double> const &x, std::complex<double> const &y )
{
  r = x * y;
}

void
cpx_double_fn::
div( std::complex<double> &r, std::complex<double> const &x, std::complex<double> const &y )
{
  r = x / y;
}

void
cpx_double_fn::
sqr( std::complex<double> &r, std::complex<double> const &x )
{
  r = x * x;
}

void
cpx_double_fn::
cube( std::complex<double> &r, std::complex<double> const &x )
{
  r = x * x * x;
}

void
cpx_double_fn::
inv( std::complex<double> &r, std::complex<double> const &x )
{
  r = one / x;
}

void
cpx_double_fn::
pow( std::complex<double> &r, std::complex<double> const &x, std::complex<double> const &y )
{
  if ( x == zero )
  {
    r = zero;
  }
  else if ( y == std::complex<double>(2.0) )
  {
    r = x * x;
  }
  else if ( y == std::complex<double>(3.0) )
  {
    r = x * x * x;
  }
  else
  {
    r = std::pow(x, y);
  }
}

/*
  ----------------------------------------------------------------
  Constants
  ----------------------------------------------------------------
  */

void
cpx_double_fn::
cat( std::complex<double> &r )
{
  r = std::complex<double>(0.9159655941772190150546035149324);
}

void
cpx_double_fn::
e( std::complex<double> &r )
{
  r = ::exp(1.0);
}

void
cpx_double_fn::
euler( std::complex<double> &r )
{
  r = std::complex<double>(0.5772156649015328606065120900824);
}

void
cpx_double_fn::
gold( std::complex<double> &r )
{
  r = std::complex<double>(1.6180339887498948482045868343656);
}

void
cpx_double_fn::
i( std::complex<double> &r )
{
  r = std::complex<double>(0.0,1.0);
}

void
cpx_double_fn::
pi( std::complex<double> &r )
{
  r = std::complex<double>(4.0 * ::atan(1.0));
}



/*
  ----------------------------------------------------------------
  Quasi-aritmetic functions
  ----------------------------------------------------------------
  */



void
cpx_double_fn::
real( std::complex<double> &r, std::complex<double> const &z )
{
  r = z.real();
}


void
cpx_double_fn::
imag( std::complex<double> &r, std::complex<double> const &z )
{
  r = z.imag();
}

void
cpx_double_fn::
conj( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::conj(z);
}

void
cpx_double_fn::
norm( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::norm(z);
}

void
cpx_double_fn::
abs( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::abs(z);
}

void
cpx_double_fn::
sqrt( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::sqrt( z );
}


/*
  ----------------------------------------------------------------
  exp/circular/hyperbolic functions and inverses
  ----------------------------------------------------------------
  */

void
cpx_double_fn::
exp( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::exp( z );
}


void
cpx_double_fn::
log( std::complex<double> &r, std::complex<double> const &z )
{
//#ifdef __GNUC__
//  r = std::log_gcc( z );
//#else
  r = std::log( z );
//#endif
}

void
cpx_double_fn::
log10( std::complex<double> &r, std::complex<double> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = std::log10( z );
#else
  r = std::log( z ) / std::log(std::complex<double>(10.0));
#endif
}

void
cpx_double_fn::
logb( std::complex<double> &r, std::complex<double> const &z, std::complex<double> const &b )
{
  r = std::log( z ) / std::log(b);
}


void
cpx_double_fn::
cos( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::cos( z );
}

void
cpx_double_fn::
sin( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::sin( z );
}

void
cpx_double_fn::
tan( std::complex<double> &r, std::complex<double> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = std::tan( z );
#else
  r = std::sin( z ) / std::cos(z);
#endif
}

void
cpx_double_fn::
sec( std::complex<double> &r, std::complex<double> const &z )
{
  r = one / std::cos(z);
}

void
cpx_double_fn::
csc( std::complex<double> &r, std::complex<double> const &z )
{
  r = one / std::sin(z);
}

void
cpx_double_fn::
cot( std::complex<double> &r, std::complex<double> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = one / std::tan(z);
#else
  r = std::cos(z) / std::sin(z);
#endif
}

void
cpx_double_fn::
acos( std::complex<double> &r, std::complex<double> const &z )
{
  r = -I * std::log( z + I * std::sqrt(one-z*z ) );
}

void
cpx_double_fn::
asin( std::complex<double> &r, std::complex<double> const &z )
{
  r = -I * std::log( std::sqrt(one-z*z) + I*z );
}

void
cpx_double_fn::
atan( std::complex<double> &r, std::complex<double> const &z )
{
  r = half * I * std::log((I+z)/(I-z));
}


void
cpx_double_fn::
asec( std::complex<double> &r, std::complex<double> const &z )
{
  r = -I * std::log( (one + I * std::sqrt(z*z-one)) / z );
}

void
cpx_double_fn::
acsc( std::complex<double> &r, std::complex<double> const &z )
{
  r = -I * std::log( (std::sqrt(z*z-one) + I)/z );
}

void
cpx_double_fn::
acot( std::complex<double> &r, std::complex<double> const &z )
{
  r = half * I * std::log((z-I)/(z+I));
}

void
cpx_double_fn::
cosh( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::cosh( z );
}

void
cpx_double_fn::
sinh( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::sinh( z );
}

void
cpx_double_fn::
tanh( std::complex<double> &r, std::complex<double> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = std::tanh( z );
#else
  r = std::sinh( z ) / std::cosh(z);
#endif
}

void
cpx_double_fn::
sech( std::complex<double> &r, std::complex<double> const &z )
{
  r = 1.0 / std::cosh(z);
}

void
cpx_double_fn::
csch( std::complex<double> &r, std::complex<double> const &z )
{
  r = 1.0 / std::sinh(z);
}

void
cpx_double_fn::
coth( std::complex<double> &r, std::complex<double> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = 1.0 / std::tanh( z );
#else
  r = std::cosh( z ) / std::sinh(z);
#endif
}


void
cpx_double_fn::
acosh( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::log( z + std::sqrt( z*z-one ) );
}


void
cpx_double_fn::
asinh( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::log( z + std::sqrt( z*z+one ) );
}

void
cpx_double_fn::
atanh( std::complex<double> &r, std::complex<double> const &z )
{
  r = half * std::log( (one+z) / (one-z) );
}

void
cpx_double_fn::
asech( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::log( (one + std::sqrt(one-z*z) ) / z );
}

void
cpx_double_fn::
acsch( std::complex<double> &r, std::complex<double> const &z )
{
  r = std::log( (one + std::sqrt(one+z*z) ) / z );
}

void
cpx_double_fn::
acoth( std::complex<double> &r, std::complex<double> const &z )
{
  r = half * std::log( (z+one) / (z-one) );
}

/*
  ----------------------------------------------------------------
  Theta Functions
  ----------------------------------------------------------------
  */

void
cpx_double_fn::
theta(std::complex<double> &r, std::complex<double> const &u,
      std::complex<double> const &tau )
{
  r = math::Elliptic::theta( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta_p(std::complex<double> &r, std::complex<double> const &u,
                    std::complex<double> const &tau )
{
  r = math::Elliptic::theta_p( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta_pp(std::complex<double> &r, std::complex<double> const &u,
                     std::complex<double> const &tau )
{
  r = math::Elliptic::theta_pp( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta_ppp(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &tau )
{
  r = math::Elliptic::theta_ppp( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta1(std::complex<double> &r, std::complex<double> const &u,
                   std::complex<double> const &tau )
{
  r = math::Elliptic::theta1( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta1_p(std::complex<double> &r, std::complex<double> const &u,
                     std::complex<double> const &tau )
{
  r = math::Elliptic::theta1_p( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta1_pp(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &tau )
{
  r = math::Elliptic::theta1_pp( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta1_ppp(std::complex<double> &r, std::complex<double> const &u,
                       std::complex<double> const &tau )
{
  r = math::Elliptic::theta1_ppp( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta2(std::complex<double> &r, std::complex<double> const &u,
                   std::complex<double> const &tau )
{
  r = math::Elliptic::theta2( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta2_p(std::complex<double> &r, std::complex<double> const &u,
                     std::complex<double> const &tau )
{
  r = math::Elliptic::theta2_p( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta3(std::complex<double> &r, std::complex<double> const &u,
                   std::complex<double> const &tau )
{
  r = math::Elliptic::theta3( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta3_p(std::complex<double> &r, std::complex<double> const &u,
                     std::complex<double> const &tau )
{
  r = math::Elliptic::theta3_p( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta4(std::complex<double> &r, std::complex<double> const &u,
                   std::complex<double> const &tau )
{
  r = math::Elliptic::theta4( std::complex<double>(u), tau );
}

void
cpx_double_fn::
theta4_p(std::complex<double> &r, std::complex<double> const &u,
                     std::complex<double> const &tau )
{
  r = math::Elliptic::theta4_p( std::complex<double>(u), tau );
}


/*
  ----------------------------------------------------------------
  Weierstrass math::Elliptic Functions
  ----------------------------------------------------------------
  */

// weierstrass elliptic functions
void
cpx_double_fn::
weierstrass_P( std::complex<double> &r, std::complex<double> const &u,
                           std::complex<double> const &tau )
{
  r = math::Elliptic::weierstrass_P( std::complex<double>(u), one, tau );
}

void
cpx_double_fn::
weierstrass_P_p( std::complex<double> &r, std::complex<double> const &u,
                             std::complex<double> const &tau )
{
  r = math::Elliptic::weierstrass_P_p( std::complex<double>(u), one, tau );
}

void
cpx_double_fn::
weierstrass_e1( std::complex<double> &r, std::complex<double> const &tau )
{
  r = math::Elliptic::weierstrass_e1( one, tau );
}

void
cpx_double_fn::
weierstrass_e2( std::complex<double> &r, std::complex<double> const &tau )
{
  r = math::Elliptic::weierstrass_e2( one, tau );
}

void
cpx_double_fn::
weierstrass_e3( std::complex<double> &r, std::complex<double> const &tau )
{
  r = math::Elliptic::weierstrass_e3( one, tau );
}

void
cpx_double_fn::
weierstrass_zeta( std::complex<double> &r, std::complex<double> const &u,
                              std::complex<double> const &tau )
{
  r = math::Elliptic::weierstrass_zeta( std::complex<double>(u), one, tau );
}

void
cpx_double_fn::
weierstrass_sigma( std::complex<double> &r, std::complex<double> const &u,
                               std::complex<double> const &tau )
{
  r = math::Elliptic::weierstrass_sigma( std::complex<double>(u), one, tau );
}

void
cpx_double_fn::
weierstrass_g2( std::complex<double> &r, std::complex<double> const &tau )
{
  r = math::Elliptic::weierstrass_g2( one, tau );
}

void
cpx_double_fn::
weierstrass_g3( std::complex<double> &r, std::complex<double> const &tau )
{
  r = math::Elliptic::weierstrass_g3( one, tau );
}

void
cpx_double_fn::
weierstrass_eta1( std::complex<double> &r, std::complex<double> const &tau )
{
  r = math::Elliptic::weierstrass_eta1( one, tau );
}

void
cpx_double_fn::
weierstrass_eta2( std::complex<double> &r, std::complex<double> const &tau )
{
  r = math::Elliptic::weierstrass_eta2( one, tau );
}

/*
  ----------------------------------------------------------------
  Jacobi math::Elliptic Functions
  ----------------------------------------------------------------
  */
void
cpx_double_fn::
jacobi_am(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::am( u.real(), m.real() );
}

void
cpx_double_fn::
jacobi_sn(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::sn( std::complex<double>(u), m.real() );
}

void
cpx_double_fn::
jacobi_cn(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::cn( std::complex<double>(u), m.real() );
}

void
cpx_double_fn::
jacobi_dn(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::dn( std::complex<double>(u), m.real() );
}

void
cpx_double_fn::
jacobi_ns(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::ns( std::complex<double>(u), m.real() );
}

void
cpx_double_fn::
jacobi_cs(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::cs( std::complex<double>(u), m.real() );
}

void
cpx_double_fn::
jacobi_ds(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::ds( std::complex<double>(u), m.real() );
}

void
cpx_double_fn::
jacobi_nc(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::nc( std::complex<double>(u), m.real() );
}

void
cpx_double_fn::
jacobi_sc(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::sc( std::complex<double>(u), m.real() );
}

void
cpx_double_fn::
jacobi_dc(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::dc( std::complex<double>(u), m.real() );
}

void
cpx_double_fn::
jacobi_nd(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::nd( std::complex<double>(u), m.real() );
}

void
cpx_double_fn::
jacobi_sd(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::sd( std::complex<double>(u), m.real() );
}

void
cpx_double_fn::
jacobi_cd(std::complex<double> &r, std::complex<double> const &u,
                      std::complex<double> const &m )
{
  r = math::Elliptic::cd( std::complex<double>(u), m.real() );
}


// elliptic integrals
void
cpx_double_fn::
elliptic_K(std::complex<double> &r, std::complex<double> const &m )
{
  r = math::Elliptic::K( m.real() );
}


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif
