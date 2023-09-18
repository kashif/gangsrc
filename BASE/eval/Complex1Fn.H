/* GANG Software
 * BASE/eval/Complex1Fn.H
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

#ifndef eval_Complex1Fn_INCLUDED
#define eval_Complex1Fn_INCLUDED

#include <complex>


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

//
struct cpx_float_fn
{
  // arithmetic functions
  static void pos( std::complex<float> &, std::complex<float> const & );
  //
  static void neg( std::complex<float> &, std::complex<float> const & );
  //
  static void add( std::complex<float> &, std::complex<float> const &,
                   std::complex<float> const & );
  //
  static void sub( std::complex<float> &, std::complex<float> const &,
                   std::complex<float> const & );
  //
  static void mul( std::complex<float> &, std::complex<float> const &,
                   std::complex<float> const & );
  //
  static void div( std::complex<float> &, std::complex<float> const &,
                   std::complex<float> const & );
  //
  static void inv( std::complex<float> &, std::complex<float> const & );
  //
  static void sqr( std::complex<float> &, std::complex<float> const & );
  //
  static void cube( std::complex<float> &, std::complex<float> const & );
  //
  static void pow( std::complex<float> &, std::complex<float> const &,
                   std::complex<float> const & );

  // constants
  static void cat( std::complex<float> & );
  //
  static void e( std::complex<float> & );
  //
  static void euler( std::complex<float> & );
  //
  static void gold( std::complex<float> & );
  //
  static void i( std::complex<float> & );
  //
  static void pi( std::complex<float> & );

  // quasi-arithmetic functions
  static void real( std::complex<float> &, std::complex<float> const & );
  //
  static void imag( std::complex<float> &, std::complex<float> const & );
  //
  static void conj( std::complex<float> &, std::complex<float> const & );
  //
  static void norm( std::complex<float> &, std::complex<float> const & );
  //
  static void abs( std::complex<float> &, std::complex<float> const & );
  //
  static void sqrt( std::complex<float> &, std::complex<float> const & );

  // exp/circular/hyperbolic functions and inverses
  static void exp( std::complex<float> &, std::complex<float> const & );
  //
  static void log( std::complex<float> &, std::complex<float> const & );
  //
  static void log10( std::complex<float> &, std::complex<float> const & );
  //
  static void logb( std::complex<float> &, std::complex<float> const &,
                    std::complex<float> const & );

  //
  static void acos( std::complex<float> &, std::complex<float> const & );
  //
  static void asin( std::complex<float> &, std::complex<float> const & );
  //
  static void atan( std::complex<float> &, std::complex<float> const & );
  //
  static void asec( std::complex<float> &, std::complex<float> const & );
  //
  static void acsc( std::complex<float> &, std::complex<float> const & );
  //
  static void acot( std::complex<float> &, std::complex<float> const & );

  //
  static void cos( std::complex<float> &, std::complex<float> const & );
  //
  static void sin( std::complex<float> &, std::complex<float> const & );
  //
  static void tan( std::complex<float> &, std::complex<float> const & );
  //
  static void sec( std::complex<float> &, std::complex<float> const & );
  //
  static void csc( std::complex<float> &, std::complex<float> const & );
  //
  static void cot( std::complex<float> &, std::complex<float> const & );

  //
  static void cosh( std::complex<float> &, std::complex<float> const & );
  //
  static void sinh( std::complex<float> &, std::complex<float> const & );
  //
  static void tanh( std::complex<float> &, std::complex<float> const & );
  //
  static void csch( std::complex<float> &, std::complex<float> const & );
  //
  static void sech( std::complex<float> &, std::complex<float> const & );
  //
  static void coth( std::complex<float> &, std::complex<float> const & );

  //
  static void acosh( std::complex<float> &, std::complex<float> const & );
  //
  static void asinh( std::complex<float> &, std::complex<float> const & );
  //
  static void atanh( std::complex<float> &, std::complex<float> const & );
  //
  static void asech( std::complex<float> &, std::complex<float> const & );
  //
  static void acsch( std::complex<float> &, std::complex<float> const & );
  //
  static void acoth( std::complex<float> &, std::complex<float> const & );

#if 0
  // theta functions
  static void theta(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta_p(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta_pp(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta_ppp(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta1(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta1_p(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta1_pp(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta1_ppp(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta2(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta2_p(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta3(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta3_p(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta4(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );
  //
  static void theta4_p(std::complex<float> &, std::complex<float> const &,
                     std::complex<float> const & );

  // weierstrass elliptic functions
  static void weierstrass_P(
    std::complex<float> &, std::complex<float> const &, std::complex<float> const & );
  //
  static void weierstrass_P_p(
    std::complex<float> &, std::complex<float> const &, std::complex<float> const & );
  //
  static void weierstrass_e1( std::complex<float> &, std::complex<float> const & );
  //
  static void weierstrass_e2( std::complex<float> &, std::complex<float> const & );
  //
  static void weierstrass_e3( std::complex<float> &, std::complex<float> const & );
  //
  static void weierstrass_zeta(
    std::complex<float> &, std::complex<float> const &, std::complex<float> const & );
  //
  static void weierstrass_sigma(
    std::complex<float> &, std::complex<float> const &, std::complex<float> const & );
  //
  static void weierstrass_g2( std::complex<float> &, std::complex<float> const & );
  //
  static void weierstrass_g3( std::complex<float> &, std::complex<float> const & );
  //
  static void weierstrass_eta1( std::complex<float> &, std::complex<float> const & );
  //
  static void weierstrass_eta2( std::complex<float> &, std::complex<float> const & );

  // jacobi elliptic functions
  static void jacobi_am(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_sn(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_cn(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_dn(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_ns(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_cs(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_ds(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_nc(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_sc(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_dc(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_nd(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_sd(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );
  //
  static void jacobi_cd(std::complex<float> &, std::complex<float> const &,
                        std::complex<float> const & );

  // elliptic integrals
  static void elliptic_K(std::complex<float> &, std::complex<float> const & );
#endif
};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_Complex1Fn_INCLUDED
