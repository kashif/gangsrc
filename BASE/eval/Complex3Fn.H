/* GANG Software
 * BASE/eval/Complex3Fn.H
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

#ifndef eval_Complex3Fn_INCLUDED
#define eval_Complex3Fn_INCLUDED

#include <complex>


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif


//
struct cpx_double_long_fn
{
  // arithmetic functions
  static void pos( std::complex<double long> &, std::complex<double long> const & );
  //
  static void neg( std::complex<double long> &, std::complex<double long> const & );
  //
  static void add( std::complex<double long> &, std::complex<double long> const &,
                   std::complex<double long> const & );
  //
  static void sub( std::complex<double long> &, std::complex<double long> const &,
                   std::complex<double long> const & );
  //
  static void mul( std::complex<double long> &, std::complex<double long> const &,
                   std::complex<double long> const & );
  //
  static void div( std::complex<double long> &, std::complex<double long> const &,
                   std::complex<double long> const & );
  //
  static void inv( std::complex<double long> &, std::complex<double long> const & );
  //
  static void sqr( std::complex<double long> &, std::complex<double long> const & );
  //
  static void cube( std::complex<double long> &, std::complex<double long> const & );
  //
  static void pow( std::complex<double long> &, std::complex<double long> const &,
                   std::complex<double long> const & );

  // constants
  static void cat( std::complex<double long> & );
  //
  static void e( std::complex<double long> & );
  //
  static void euler( std::complex<double long> & );
  //
  static void gold( std::complex<double long> & );
  //
  static void i( std::complex<double long> & );
  //
  static void pi( std::complex<double long> & );

  // quasi-arithmetic functions
  static void real( std::complex<double long> &, std::complex<double long> const & );
  //
  static void imag( std::complex<double long> &, std::complex<double long> const & );
  //
  static void conj( std::complex<double long> &, std::complex<double long> const & );
  //
  static void norm( std::complex<double long> &, std::complex<double long> const & );
  //
  static void abs( std::complex<double long> &, std::complex<double long> const & );
  //
  static void sqrt( std::complex<double long> &, std::complex<double long> const & );

  // exp/circular/hyperbolic functions and inverses
  static void exp( std::complex<double long> &, std::complex<double long> const & );
  //
  static void log( std::complex<double long> &, std::complex<double long> const & );
  //
  static void log10( std::complex<double long> &, std::complex<double long> const & );
  //
  static void logb( std::complex<double long> &, std::complex<double long> const &,
                    std::complex<double long> const & );

  //
  static void acos( std::complex<double long> &, std::complex<double long> const & );
  //
  static void asin( std::complex<double long> &, std::complex<double long> const & );
  //
  static void atan( std::complex<double long> &, std::complex<double long> const & );
  //
  static void asec( std::complex<double long> &, std::complex<double long> const & );
  //
  static void acsc( std::complex<double long> &, std::complex<double long> const & );
  //
  static void acot( std::complex<double long> &, std::complex<double long> const & );

  //
  static void cos( std::complex<double long> &, std::complex<double long> const & );
  //
  static void sin( std::complex<double long> &, std::complex<double long> const & );
  //
  static void tan( std::complex<double long> &, std::complex<double long> const & );
  //
  static void sec( std::complex<double long> &, std::complex<double long> const & );
  //
  static void csc( std::complex<double long> &, std::complex<double long> const & );
  //
  static void cot( std::complex<double long> &, std::complex<double long> const & );

  //
  static void cosh( std::complex<double long> &, std::complex<double long> const & );
  //
  static void sinh( std::complex<double long> &, std::complex<double long> const & );
  //
  static void tanh( std::complex<double long> &, std::complex<double long> const & );
  //
  static void csch( std::complex<double long> &, std::complex<double long> const & );
  //
  static void sech( std::complex<double long> &, std::complex<double long> const & );
  //
  static void coth( std::complex<double long> &, std::complex<double long> const & );

  //
  static void acosh( std::complex<double long> &, std::complex<double long> const & );
  //
  static void asinh( std::complex<double long> &, std::complex<double long> const & );
  //
  static void atanh( std::complex<double long> &, std::complex<double long> const & );
  //
  static void asech( std::complex<double long> &, std::complex<double long> const & );
  //
  static void acsch( std::complex<double long> &, std::complex<double long> const & );
  //
  static void acoth( std::complex<double long> &, std::complex<double long> const & );

  // theta functions
  static void theta(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta_p(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta_pp(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta_ppp(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta1(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta1_p(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta1_pp(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta1_ppp(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta2(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta2_p(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta3(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta3_p(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta4(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );
  //
  static void theta4_p(std::complex<double long> &, std::complex<double long> const &,
                     std::complex<double long> const & );

  // weierstrass elliptic functions
  static void weierstrass_P(
    std::complex<double long> &, std::complex<double long> const &, std::complex<double long> const & );
  //
  static void weierstrass_P_p(
    std::complex<double long> &, std::complex<double long> const &, std::complex<double long> const & );
  //
  static void weierstrass_e1( std::complex<double long> &, std::complex<double long> const & );
  //
  static void weierstrass_e2( std::complex<double long> &, std::complex<double long> const & );
  //
  static void weierstrass_e3( std::complex<double long> &, std::complex<double long> const & );
  //
  static void weierstrass_zeta(
    std::complex<double long> &, std::complex<double long> const &, std::complex<double long> const & );
  //
  static void weierstrass_sigma(
    std::complex<double long> &, std::complex<double long> const &, std::complex<double long> const & );
  //
  static void weierstrass_g2( std::complex<double long> &, std::complex<double long> const & );
  //
  static void weierstrass_g3( std::complex<double long> &, std::complex<double long> const & );
  //
  static void weierstrass_eta1( std::complex<double long> &, std::complex<double long> const & );
  //
  static void weierstrass_eta2( std::complex<double long> &, std::complex<double long> const & );

  // jacobi elliptic functions
  static void jacobi_am(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_sn(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_cn(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_dn(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_ns(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_cs(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_ds(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_nc(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_sc(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_dc(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_nd(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_sd(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );
  //
  static void jacobi_cd(std::complex<double long> &, std::complex<double long> const &,
                        std::complex<double long> const & );

  // elliptic integrals
  static void elliptic_K(std::complex<double long> &, std::complex<double long> const & );

};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_Complex3Fn_INCLUDED
