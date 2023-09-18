/* GANG Software
 * BASE/eval/Complex1Fn.C
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
#include "Complex1Fn.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

static const std::complex<float> I(0.0, 1.0);
static const std::complex<float> zero(0.0, 0.0);
static const std::complex<float> half(0.5, 0.0);
static const std::complex<float> one(1.0, 0.0);

#ifdef PLATFORM_IRIX_NEW
#define HAVE_CPX_FN_EXT // have extended set of std::complex functions
#endif

/*
  ----------------------------------------------------------------
  Arithmetic Functions
  ----------------------------------------------------------------
  */

void
cpx_float_fn::
pos( std::complex<float> &r, std::complex<float> const &x )
{
  r = x;
}

void
cpx_float_fn::
neg( std::complex<float> &r, std::complex<float> const &x )
{
  r = -x;
}

void
cpx_float_fn::
add( std::complex<float> &r, std::complex<float> const &x, std::complex<float> const &y )
{
  r = x + y;
}

void
cpx_float_fn::
sub( std::complex<float> &r, std::complex<float> const &x, std::complex<float> const &y )
{
  r = x - y;
}

void
cpx_float_fn::
mul( std::complex<float> &r, std::complex<float> const &x, std::complex<float> const &y )
{
  r = x * y;
}

void
cpx_float_fn::
div( std::complex<float> &r, std::complex<float> const &x, std::complex<float> const &y )
{
  r = x / y;
}

void
cpx_float_fn::
sqr( std::complex<float> &r, std::complex<float> const &x )
{
  r = x * x;
}

void
cpx_float_fn::
cube( std::complex<float> &r, std::complex<float> const &x )
{
  r = x * x * x;
}

void
cpx_float_fn::
inv( std::complex<float> &r, std::complex<float> const &x )
{
  r = one / x;
}

void
cpx_float_fn::
pow( std::complex<float> &r, std::complex<float> const &x, std::complex<float> const &y )
{
  if ( x == zero )
  {
    r = zero;
  }
  else if ( y == std::complex<float>(2.0) )
  {
    r = x * x;
  }
  else if ( y == std::complex<float>(3.0) )
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
cpx_float_fn::
cat( std::complex<float> &r )
{
  r = std::complex<float>(0.9159655941772190150546035149324);
}

void
cpx_float_fn::
e( std::complex<float> &r )
{
  r = std::exp(one);
}

void
cpx_float_fn::
euler( std::complex<float> &r )
{
  r = std::complex<float>(0.5772156649015328606065120900824);
}

void
cpx_float_fn::
gold( std::complex<float> &r )
{
  r = std::complex<float>(1.6180339887498948482045868343656);
}

void
cpx_float_fn::
i( std::complex<float> &r )
{
  r = I;
}

void
cpx_float_fn::
pi( std::complex<float> &r )
{
  r = std::complex<float>(4.0 * ::atan(1.0));
}



/*
  ----------------------------------------------------------------
  Quasi-aritmetic functions
  ----------------------------------------------------------------
  */



void
cpx_float_fn::
real( std::complex<float> &r, std::complex<float> const &z )
{
  r = z.real();
}


void
cpx_float_fn::
imag( std::complex<float> &r, std::complex<float> const &z )
{
  r = z.imag();
}

void
cpx_float_fn::
conj( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::conj(z);
}

void
cpx_float_fn::
norm( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::norm(z);
}

void
cpx_float_fn::
abs( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::abs(z);
}

void
cpx_float_fn::
sqrt( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::sqrt( z );
}


/*
  ----------------------------------------------------------------
  exp/circular/hyperbolic functions and inverses
  ----------------------------------------------------------------
  */

void
cpx_float_fn::
exp( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::exp( z );
}


void
cpx_float_fn::
log( std::complex<float> &r, std::complex<float> const &z )
{
//#ifdef __GNUC__
//  r = std::log_gcc( z );
//#else
  r = std::log( z );
//#endif
}

void
cpx_float_fn::
log10( std::complex<float> &r, std::complex<float> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = std::log10( z );
#else
  r = std::log( z ) / std::log(std::complex<float>(10.0));
#endif
}

void
cpx_float_fn::
logb( std::complex<float> &r, std::complex<float> const &z, std::complex<float> const &b )
{
  r = std::log( z ) / std::log(b);
}


void
cpx_float_fn::
cos( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::cos( z );
}

void
cpx_float_fn::
sin( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::sin( z );
}

void
cpx_float_fn::
tan( std::complex<float> &r, std::complex<float> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = std::tan( z );
#else
  r = std::sin( z ) / std::cos(z);
#endif
}

void
cpx_float_fn::
sec( std::complex<float> &r, std::complex<float> const &z )
{
  r = one / std::cos(z);
}

void
cpx_float_fn::
csc( std::complex<float> &r, std::complex<float> const &z )
{
  r = one / std::sin(z);
}

void
cpx_float_fn::
cot( std::complex<float> &r, std::complex<float> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = one / std::tan(z);
#else
  r = std::cos(z) / std::sin(z);
#endif
}

void
cpx_float_fn::
acos( std::complex<float> &r, std::complex<float> const &z )
{
  r = -I * std::log( z + I * std::sqrt(one-z*z ) );
}

void
cpx_float_fn::
asin( std::complex<float> &r, std::complex<float> const &z )
{
  r = -I * std::log( std::sqrt(one-z*z) + I*z );
}

void
cpx_float_fn::
atan( std::complex<float> &r, std::complex<float> const &z )
{
  r = half * I * std::log((I+z)/(I-z));
}


void
cpx_float_fn::
asec( std::complex<float> &r, std::complex<float> const &z )
{
  r = -I * std::log( (one + I * std::sqrt(z*z-one)) / z );
}

void
cpx_float_fn::
acsc( std::complex<float> &r, std::complex<float> const &z )
{
  r = -I * std::log( (std::sqrt(z*z-one) + I)/z );
}

void
cpx_float_fn::
acot( std::complex<float> &r, std::complex<float> const &z )
{
  r = half * I * std::log((z-I)/(z+I));
}

void
cpx_float_fn::
cosh( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::cosh( z );
}

void
cpx_float_fn::
sinh( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::sinh( z );
}

void
cpx_float_fn::
tanh( std::complex<float> &r, std::complex<float> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = std::tanh( z );
#else
  r = std::sinh( z ) / std::cosh(z);
#endif
}

void
cpx_float_fn::
sech( std::complex<float> &r, std::complex<float> const &z )
{
  r = one / std::cosh(z);
}

void
cpx_float_fn::
csch( std::complex<float> &r, std::complex<float> const &z )
{
  r = one / std::sinh(z);
}

void
cpx_float_fn::
coth( std::complex<float> &r, std::complex<float> const &z )
{
#ifdef HAVE_CPX_FN_EXT
  r = one / std::tanh( z );
#else
  r = std::cosh( z ) / std::sinh(z);
#endif
}


void
cpx_float_fn::
acosh( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::log( z + std::sqrt( z*z-one ) );
}


void
cpx_float_fn::
asinh( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::log( z + std::sqrt( z*z+one ) );
}

void
cpx_float_fn::
atanh( std::complex<float> &r, std::complex<float> const &z )
{
  r = half * std::log( (one+z) / (one-z) );
}

void
cpx_float_fn::
asech( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::log( (one + std::sqrt(one-z*z) ) / z );
}

void
cpx_float_fn::
acsch( std::complex<float> &r, std::complex<float> const &z )
{
  r = std::log( (one + std::sqrt(one+z*z) ) / z );
}

void
cpx_float_fn::
acoth( std::complex<float> &r, std::complex<float> const &z )
{
  r = half * std::log( (z+one) / (z-one) );
}


#if 0
/*
  ----------------------------------------------------------------
  Theta Functions
  ----------------------------------------------------------------
  */

void
cpx_float_fn::
theta(std::complex<float> &r, std::complex<float> const &u,
      std::complex<float> const &tau )
{
  r = elliptic::theta( u, tau );
}

void
cpx_float_fn::
theta_p(std::complex<float> &r, std::complex<float> const &u,
                    std::complex<float> const &tau )
{
  r = elliptic::theta_p( u, tau );
}

void
cpx_float_fn::
theta_pp(std::complex<float> &r, std::complex<float> const &u,
                     std::complex<float> const &tau )
{
  r = elliptic::theta_pp( u, tau );
}

void
cpx_float_fn::
theta_ppp(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &tau )
{
  r = elliptic::theta_ppp( u, tau );
}

void
cpx_float_fn::
theta1(std::complex<float> &r, std::complex<float> const &u,
                   std::complex<float> const &tau )
{
  r = elliptic::theta1( u, tau );
}

void
cpx_float_fn::
theta1_p(std::complex<float> &r, std::complex<float> const &u,
                     std::complex<float> const &tau )
{
  r = elliptic::theta1_p( u, tau );
}

void
cpx_float_fn::
theta1_pp(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &tau )
{
  r = elliptic::theta1_pp( u, tau );
}

void
cpx_float_fn::
theta1_ppp(std::complex<float> &r, std::complex<float> const &u,
                       std::complex<float> const &tau )
{
  r = elliptic::theta1_ppp( u, tau );
}

void
cpx_float_fn::
theta2(std::complex<float> &r, std::complex<float> const &u,
                   std::complex<float> const &tau )
{
  r = elliptic::theta2( u, tau );
}

void
cpx_float_fn::
theta2_p(std::complex<float> &r, std::complex<float> const &u,
                     std::complex<float> const &tau )
{
  r = elliptic::theta2_p( u, tau );
}

void
cpx_float_fn::
theta3(std::complex<float> &r, std::complex<float> const &u,
                   std::complex<float> const &tau )
{
  r = elliptic::theta3( u, tau );
}

void
cpx_float_fn::
theta3_p(std::complex<float> &r, std::complex<float> const &u,
                     std::complex<float> const &tau )
{
  r = elliptic::theta3_p( u, tau );
}

void
cpx_float_fn::
theta4(std::complex<float> &r, std::complex<float> const &u,
                   std::complex<float> const &tau )
{
  r = elliptic::theta4( u, tau );
}

void
cpx_float_fn::
theta4_p(std::complex<float> &r, std::complex<float> const &u,
                     std::complex<float> const &tau )
{
  r = elliptic::theta4_p( u, tau );
}


/*
  ----------------------------------------------------------------
  Weierstrass Elliptic Functions
  ----------------------------------------------------------------
  */

// weierstrass elliptic functions
void
cpx_float_fn::
weierstrass_P( std::complex<float> &r, std::complex<float> const &u,
                           std::complex<float> const &tau )
{
  r = elliptic::weierstrass_P( u, one, tau );
}

void
cpx_float_fn::
weierstrass_P_p( std::complex<float> &r, std::complex<float> const &u,
                             std::complex<float> const &tau )
{
  r = elliptic::weierstrass_P_p( u, one, tau );
}

void
cpx_float_fn::
weierstrass_e1( std::complex<float> &r, std::complex<float> const &tau )
{
  r = elliptic::weierstrass_e1( one, tau );
}

void
cpx_float_fn::
weierstrass_e2( std::complex<float> &r, std::complex<float> const &tau )
{
  r = elliptic::weierstrass_e2( one, tau );
}

void
cpx_float_fn::
weierstrass_e3( std::complex<float> &r, std::complex<float> const &tau )
{
  r = elliptic::weierstrass_e3( one, tau );
}

void
cpx_float_fn::
weierstrass_zeta( std::complex<float> &r, std::complex<float> const &u,
                              std::complex<float> const &tau )
{
  r = elliptic::weierstrass_zeta( u, one, tau );
}

void
cpx_float_fn::
weierstrass_sigma( std::complex<float> &r, std::complex<float> const &u,
                               std::complex<float> const &tau )
{
  r = elliptic::weierstrass_sigma( u, one, tau );
}

void
cpx_float_fn::
weierstrass_g2( std::complex<float> &r, std::complex<float> const &tau )
{
  r = elliptic::weierstrass_g2( one, tau );
}

void
cpx_float_fn::
weierstrass_g3( std::complex<float> &r, std::complex<float> const &tau )
{
  r = elliptic::weierstrass_g3( one, tau );
}

void
cpx_float_fn::
weierstrass_eta1( std::complex<float> &r, std::complex<float> const &tau )
{
  r = elliptic::weierstrass_eta1( one, tau );
}

void
cpx_float_fn::
weierstrass_eta2( std::complex<float> &r, std::complex<float> const &tau )
{
  r = elliptic::weierstrass_eta2( one, tau );
}

/*
  ----------------------------------------------------------------
  Jacobi Elliptic Functions
  ----------------------------------------------------------------
  */
void
cpx_float_fn::
jacobi_am(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::am( u.real(), m.real() );
}

void
cpx_float_fn::
jacobi_sn(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::sn( u, m.real() );
}

void
cpx_float_fn::
jacobi_cn(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::cn( u, m.real() );
}

void
cpx_float_fn::
jacobi_dn(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::dn( u, m.real() );
}

void
cpx_float_fn::
jacobi_ns(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::ns( u, m.real() );
}

void
cpx_float_fn::
jacobi_cs(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::cs( u, m.real() );
}

void
cpx_float_fn::
jacobi_ds(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::ds( u, m.real() );
}

void
cpx_float_fn::
jacobi_nc(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::nc( u, m.real() );
}

void
cpx_float_fn::
jacobi_sc(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::sc( u, m.real() );
}

void
cpx_float_fn::
jacobi_dc(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::dc( u, m.real() );
}

void
cpx_float_fn::
jacobi_nd(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::nd( u, m.real() );
}

void
cpx_float_fn::
jacobi_sd(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::sd( u, m.real() );
}

void
cpx_float_fn::
jacobi_cd(std::complex<float> &r, std::complex<float> const &u,
                      std::complex<float> const &m )
{
  r = elliptic::cd( u, m.real() );
}


// elliptic integrals
void
cpx_float_fn::
elliptic_K(std::complex<float> &r, std::complex<float> const &m )
{
  r = elliptic::K( m.real() );
}
#endif


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif
