/* GANG Software
 * BASE/eval/Complex2Fn.H
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

#ifndef eval_Complex2Fn_INCLUDED
#define eval_Complex2Fn_INCLUDED

#include <complex>


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

//
struct cpx_double_fn
{
  // arithmetic functions
  static void pos( std::complex<double> &, std::complex<double> const & );
  //
  static void neg( std::complex<double> &, std::complex<double> const & );
  //
  static void add( std::complex<double> &, std::complex<double> const &,
                   std::complex<double> const & );
  //
  static void sub( std::complex<double> &, std::complex<double> const &,
                   std::complex<double> const & );
  //
  static void mul( std::complex<double> &, std::complex<double> const &,
                   std::complex<double> const & );
  //
  static void div( std::complex<double> &, std::complex<double> const &,
                   std::complex<double> const & );
  //
  static void inv( std::complex<double> &, std::complex<double> const & );
  //
  static void sqr( std::complex<double> &, std::complex<double> const & );
  //
  static void cube( std::complex<double> &, std::complex<double> const & );
  //
  static void pow( std::complex<double> &, std::complex<double> const &,
                   std::complex<double> const & );

  // constants
  static void cat( std::complex<double> & );
  //
  static void e( std::complex<double> & );
  //
  static void euler( std::complex<double> & );
  //
  static void gold( std::complex<double> & );
  //
  static void i( std::complex<double> & );
  //
  static void pi( std::complex<double> & );

  // quasi-arithmetic functions
  static void real( std::complex<double> &, std::complex<double> const & );
  //
  static void imag( std::complex<double> &, std::complex<double> const & );
  //
  static void conj( std::complex<double> &, std::complex<double> const & );
  //
  static void norm( std::complex<double> &, std::complex<double> const & );
  //
  static void abs( std::complex<double> &, std::complex<double> const & );
  //
  static void sqrt( std::complex<double> &, std::complex<double> const & );

  // exp/circular/hyperbolic functions and inverses
  static void exp( std::complex<double> &, std::complex<double> const & );
  //
  static void log( std::complex<double> &, std::complex<double> const & );
  //
  static void log10( std::complex<double> &, std::complex<double> const & );
  //
  static void logb( std::complex<double> &, std::complex<double> const &,
                    std::complex<double> const & );

  //
  static void acos( std::complex<double> &, std::complex<double> const & );
  //
  static void asin( std::complex<double> &, std::complex<double> const & );
  //
  static void atan( std::complex<double> &, std::complex<double> const & );
  //
  static void asec( std::complex<double> &, std::complex<double> const & );
  //
  static void acsc( std::complex<double> &, std::complex<double> const & );
  //
  static void acot( std::complex<double> &, std::complex<double> const & );

  //
  static void cos( std::complex<double> &, std::complex<double> const & );
  //
  static void sin( std::complex<double> &, std::complex<double> const & );
  //
  static void tan( std::complex<double> &, std::complex<double> const & );
  //
  static void sec( std::complex<double> &, std::complex<double> const & );
  //
  static void csc( std::complex<double> &, std::complex<double> const & );
  //
  static void cot( std::complex<double> &, std::complex<double> const & );

  //
  static void cosh( std::complex<double> &, std::complex<double> const & );
  //
  static void sinh( std::complex<double> &, std::complex<double> const & );
  //
  static void tanh( std::complex<double> &, std::complex<double> const & );
  //
  static void csch( std::complex<double> &, std::complex<double> const & );
  //
  static void sech( std::complex<double> &, std::complex<double> const & );
  //
  static void coth( std::complex<double> &, std::complex<double> const & );

  //
  static void acosh( std::complex<double> &, std::complex<double> const & );
  //
  static void asinh( std::complex<double> &, std::complex<double> const & );
  //
  static void atanh( std::complex<double> &, std::complex<double> const & );
  //
  static void asech( std::complex<double> &, std::complex<double> const & );
  //
  static void acsch( std::complex<double> &, std::complex<double> const & );
  //
  static void acoth( std::complex<double> &, std::complex<double> const & );

  // theta functions
  static void theta(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta_p(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta_pp(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta_ppp(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta1(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta1_p(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta1_pp(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta1_ppp(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta2(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta2_p(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta3(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta3_p(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta4(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );
  //
  static void theta4_p(std::complex<double> &, std::complex<double> const &,
                     std::complex<double> const & );

  // weierstrass elliptic functions
  static void weierstrass_P(
    std::complex<double> &, std::complex<double> const &, std::complex<double> const & );
  //
  static void weierstrass_P_p(
    std::complex<double> &, std::complex<double> const &, std::complex<double> const & );
  //
  static void weierstrass_e1( std::complex<double> &, std::complex<double> const & );
  //
  static void weierstrass_e2( std::complex<double> &, std::complex<double> const & );
  //
  static void weierstrass_e3( std::complex<double> &, std::complex<double> const & );
  //
  static void weierstrass_zeta(
    std::complex<double> &, std::complex<double> const &, std::complex<double> const & );
  //
  static void weierstrass_sigma(
    std::complex<double> &, std::complex<double> const &, std::complex<double> const & );
  //
  static void weierstrass_g2( std::complex<double> &, std::complex<double> const & );
  //
  static void weierstrass_g3( std::complex<double> &, std::complex<double> const & );
  //
  static void weierstrass_eta1( std::complex<double> &, std::complex<double> const & );
  //
  static void weierstrass_eta2( std::complex<double> &, std::complex<double> const & );

  // jacobi elliptic functions
  static void jacobi_am(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_sn(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_cn(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_dn(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_ns(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_cs(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_ds(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_nc(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_sc(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_dc(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_nd(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_sd(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );
  //
  static void jacobi_cd(std::complex<double> &, std::complex<double> const &,
                        std::complex<double> const & );

  // elliptic integrals
  static void elliptic_K(std::complex<double> &, std::complex<double> const & );
};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_Complex2Fn_INCLUDED
