/* GANG Software
 * BASE/eval/Complex3Fn.C
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
#include "Complex3Fn.H"
#include "math/Elliptic.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

static const std::complex<double long> I(0.0, 1.0);
static const std::complex<double long> zero(0.0, 0.0);
static const std::complex<double long> half(0.5, 0.0);
static const std::complex<double long> one(1.0, 0.0);

#ifdef PLATFORM_IRIX_NEW
#define HAVE_CPX_FN_EXT // have extended set of std::complex functions
#endif

/*
  ----------------------------------------------------------------
  Arithmetic Functions
  ----------------------------------------------------------------
  */

void
cpx_double_long_fn::
pos( std::complex<double long> &r, std::complex<double long> const &x )
{
  r = x;
}

void
cpx_double_long_fn::
neg( std::complex<double long> &r, std::complex<double long> const &x )
{
  r = -x;
}

void
cpx_double_long_fn::
add( std::complex<double long> &r, std::complex<double long> const &x, std::complex<double long> const &y )
{
  r = x + y;
}

void
cpx_double_long_fn::
sub( std::complex<double long> &r, std::complex<double long> const &x, std::complex<double long> const &y )
{
  r = x - y;
}

void
cpx_double_long_fn::
mul( std::complex<double long> &r, std::complex<double long> const &x, std::complex<double long> const &y )
{
  r = x * y;
}

void
cpx_double_long_fn::
div( std::complex<double long> &r, std::complex<double long> const &x, std::complex<double long> const &y )
{
  r = x / y;
}

void
cpx_double_long_fn::
sqr( std::complex<double long> &r, std::complex<double long> const &x )
{
  r = x * x;
}

void
cpx_double_long_fn::
cube( std::complex<double long> &r, std::complex<double long> const &x )
{
  r = x * x * x;
}

void
cpx_double_long_fn::
inv( std::complex<double long> &r, std::complex<double long> const &x )
{
  r = one / x;
}

void
cpx_double_long_fn::
pow( std::complex<double long> &r, std::complex<double long> const &x, std::complex<double long> const &y )
{
  if ( x == zero )
  {
    r = zero;
  }
  else if ( y == std::complex<double long>(2.0) )
  {
    r = x * x;
  }
  else if ( y == std::complex<double long>(3.0) )
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
cpx_double_long_fn::
cat( std::complex<double long> &r )
{
  r = std::complex<double long>(0.9159655941772190150546035149324);
}

void
cpx_double_long_fn::
e( std::complex<double long> &r )
{
  r = ::exp(1.0);
}

void
cpx_double_long_fn::
euler( std::complex<double long> &r )
{
  r = std::complex<double long>(0.5772156649015328606065120900824);
}

void
cpx_double_long_fn::
gold( std::complex<double long> &r )
{
  r = std::complex<double long>(1.6180339887498948482045868343656);
}

void
cpx_double_long_fn::
i( std::complex<double long> &r )
{
  r = std::complex<double long>(0.0,1.0);
}

void
cpx_double_long_fn::
pi( std::complex<double long> &r )
{
  r = std::complex<double long>(4.0 * ::atan(1.0));
}



/*
  ----------------------------------------------------------------
  Quasi-aritmetic functions
  ----------------------------------------------------------------
  */



void
cpx_double_long_fn::
real( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = z.real();
}


void
cpx_double_long_fn::
imag( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = z.imag();
}

void
cpx_double_long_fn::
conj( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::conj(z);
}

void
cpx_double_long_fn::
norm( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::norm(z);
}

void
cpx_double_long_fn::
abs( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::abs(z);
}

void
cpx_double_long_fn::
sqrt( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::sqrt( z );
}


/*
  ----------------------------------------------------------------
  exp/circular/hyperbolic functions and inverses
  ----------------------------------------------------------------
  */

void
cpx_double_long_fn::
exp( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::exp( z );
}


void
cpx_double_long_fn::
log( std::complex<double long> &r, std::complex<double long> const &z )
{
//#ifdef __GNUC__
//  r = std::log_gcc( z );
//#else
  r = std::log( z );
//#endif
}

void
cpx_double_long_fn::
log10( std::complex<double long> &r, std::complex<double long> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = std::log10( z );
#else
  r = std::log( z ) / std::log(std::complex<double long>(10.0));
#endif
}

void
cpx_double_long_fn::
logb( std::complex<double long> &r, std::complex<double long> const &z, std::complex<double long> const &b )
{
  r = std::log( z ) / std::log(b);
}


void
cpx_double_long_fn::
cos( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::cos( z );
}

void
cpx_double_long_fn::
sin( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::sin( z );
}

void
cpx_double_long_fn::
tan( std::complex<double long> &r, std::complex<double long> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = std::tan( z );
#else
  r = std::sin( z ) / std::cos(z);
#endif
}

void
cpx_double_long_fn::
sec( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = one / std::cos(z);
}

void
cpx_double_long_fn::
csc( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = one / std::sin(z);
}

void
cpx_double_long_fn::
cot( std::complex<double long> &r, std::complex<double long> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = one / std::tan(z);
#else
  r = std::cos(z) / std::sin(z);
#endif
}

void
cpx_double_long_fn::
acos( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = -I * std::log( z + I * std::sqrt(one-z*z ) );
}

void
cpx_double_long_fn::
asin( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = -I * std::log( std::sqrt(one-z*z) + I*z );
}

void
cpx_double_long_fn::
atan( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = half * I * std::log((I+z)/(I-z));
}


void
cpx_double_long_fn::
asec( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = -I * std::log( (one + I * std::sqrt(z*z-one)) / z );
}

void
cpx_double_long_fn::
acsc( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = -I * std::log( (std::sqrt(z*z-one) + I)/z );
}

void
cpx_double_long_fn::
acot( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = half * I * std::log((z-I)/(z+I));
}

void
cpx_double_long_fn::
cosh( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::cosh( z );
}

void
cpx_double_long_fn::
sinh( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::sinh( z );
}

void
cpx_double_long_fn::
tanh( std::complex<double long> &r, std::complex<double long> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = std::tanh( z );
#else
  r = std::sinh( z ) / std::cosh(z);
#endif
}

void
cpx_double_long_fn::
sech( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = one / std::cosh(z);
}

void
cpx_double_long_fn::
csch( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = one / std::sinh(z);
}

void
cpx_double_long_fn::
coth( std::complex<double long> &r, std::complex<double long> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = one / std::tanh( z );
#else
  r = std::cosh( z ) / std::sinh(z);
#endif
}


void
cpx_double_long_fn::
acosh( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::log( z + std::sqrt( z*z-one ) );
}


void
cpx_double_long_fn::
asinh( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::log( z + std::sqrt( z*z+one ) );
}

void
cpx_double_long_fn::
atanh( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = half * std::log( (one+z) / (one-z) );
}

void
cpx_double_long_fn::
asech( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::log( (one + std::sqrt(one-z*z) ) / z );
}

void
cpx_double_long_fn::
acsch( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = std::log( (one + std::sqrt(one+z*z) ) / z );
}

void
cpx_double_long_fn::
acoth( std::complex<double long> &r, std::complex<double long> const &z )
{
  r = half * std::log( (z+one) / (z-one) );
}

#ifdef __sgi
#pragma set woff 3201 // parameter never referenced
#endif

/*
  ----------------------------------------------------------------
  Theta Functions
  ----------------------------------------------------------------
  */

void
cpx_double_long_fn::
theta(std::complex<double long> &r, std::complex<double long> const &u,
      std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta( u, tau );
}

void
cpx_double_long_fn::
theta_p(std::complex<double long> &r, std::complex<double long> const &u,
                    std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta_p( u, tau );
}

void
cpx_double_long_fn::
theta_pp(std::complex<double long> &r, std::complex<double long> const &u,
                     std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta_pp( u, tau );
}

void
cpx_double_long_fn::
theta_ppp(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta_ppp( u, tau );
}

void
cpx_double_long_fn::
theta1(std::complex<double long> &r, std::complex<double long> const &u,
                   std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta1( u, tau );
}

void
cpx_double_long_fn::
theta1_p(std::complex<double long> &r, std::complex<double long> const &u,
                     std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta1_p( u, tau );
}

void
cpx_double_long_fn::
theta1_pp(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta1_pp( u, tau );
}

void
cpx_double_long_fn::
theta1_ppp(std::complex<double long> &r, std::complex<double long> const &u,
                       std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta1_ppp( u, tau );
}

void
cpx_double_long_fn::
theta2(std::complex<double long> &r, std::complex<double long> const &u,
                   std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta2( u, tau );
}

void
cpx_double_long_fn::
theta2_p(std::complex<double long> &r, std::complex<double long> const &u,
                     std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta2_p( u, tau );
}

void
cpx_double_long_fn::
theta3(std::complex<double long> &r, std::complex<double long> const &u,
                   std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta3( u, tau );
}

void
cpx_double_long_fn::
theta3_p(std::complex<double long> &r, std::complex<double long> const &u,
                     std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta3_p( u, tau );
}

void
cpx_double_long_fn::
theta4(std::complex<double long> &r, std::complex<double long> const &u,
                   std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta4( u, tau );
}

void
cpx_double_long_fn::
theta4_p(std::complex<double long> &r, std::complex<double long> const &u,
                     std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::theta4_p( u, tau );
}


/*
  ----------------------------------------------------------------
  Weierstrass Elliptic Functions
  ----------------------------------------------------------------
  */

// weierstrass elliptic functions
void
cpx_double_long_fn::
weierstrass_P( std::complex<double long> &r, std::complex<double long> const &u,
                           std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::weierstrass_P( u, one, tau );
}

void
cpx_double_long_fn::
weierstrass_P_p( std::complex<double long> &r, std::complex<double long> const &u,
                             std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::weierstrass_P_p( u, one, tau );
}

void
cpx_double_long_fn::
weierstrass_e1( std::complex<double long> &r, std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::weierstrass_e1( one, tau );
}

void
cpx_double_long_fn::
weierstrass_e2( std::complex<double long> &r, std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::weierstrass_e2( one, tau );
}

void
cpx_double_long_fn::
weierstrass_e3( std::complex<double long> &r, std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::weierstrass_e3( one, tau );
}

void
cpx_double_long_fn::
weierstrass_zeta( std::complex<double long> &r, std::complex<double long> const &u,
                              std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::weierstrass_zeta( u, one, tau );
}

void
cpx_double_long_fn::
weierstrass_sigma( std::complex<double long> &r, std::complex<double long> const &u,
                               std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::weierstrass_sigma( u, one, tau );
}

void
cpx_double_long_fn::
weierstrass_g2( std::complex<double long> &r, std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::weierstrass_g2( one, tau );
}

void
cpx_double_long_fn::
weierstrass_g3( std::complex<double long> &r, std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::weierstrass_g3( one, tau );
}

void
cpx_double_long_fn::
weierstrass_eta1( std::complex<double long> &r, std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::weierstrass_eta1( one, tau );
}

void
cpx_double_long_fn::
weierstrass_eta2( std::complex<double long> &r, std::complex<double long> const &tau )
{
  DIE();
  // r = elliptic::weierstrass_eta2( one, tau );
}

/*
  ----------------------------------------------------------------
  Jacobi Elliptic Functions
  ----------------------------------------------------------------
  */
void
cpx_double_long_fn::
jacobi_am(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::am( u.real(), m.real() );
}

void
cpx_double_long_fn::
jacobi_sn(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::sn( u, m.real() );
}

void
cpx_double_long_fn::
jacobi_cn(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::cn( u, m.real() );
}

void
cpx_double_long_fn::
jacobi_dn(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::dn( u, m.real() );
}

void
cpx_double_long_fn::
jacobi_ns(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::ns( u, m.real() );
}

void
cpx_double_long_fn::
jacobi_cs(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::cs( u, m.real() );
}

void
cpx_double_long_fn::
jacobi_ds(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::ds( u, m.real() );
}

void
cpx_double_long_fn::
jacobi_nc(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::nc( u, m.real() );
}

void
cpx_double_long_fn::
jacobi_sc(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::sc( u, m.real() );
}

void
cpx_double_long_fn::
jacobi_dc(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::dc( u, m.real() );
}

void
cpx_double_long_fn::
jacobi_nd(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::nd( u, m.real() );
}

void
cpx_double_long_fn::
jacobi_sd(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::sd( u, m.real() );
}

void
cpx_double_long_fn::
jacobi_cd(std::complex<double long> &r, std::complex<double long> const &u,
                      std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::cd( u, m.real() );
}


// elliptic integrals
void
cpx_double_long_fn::
elliptic_K(std::complex<double long> &r, std::complex<double long> const &m )
{
  DIE();
  // r = elliptic::K( m.real() );
}
#ifdef __sgi
#pragma reset woff 3201 // parameter never referenced
#endif


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif
