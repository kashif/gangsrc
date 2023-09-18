/* GANG Software
 * BASE/eval/Complex2Op.C
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

#include <complex>
#include "base/String.H"
#include "Complex2Fn.H"
#include "NumberOp.H"

#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

template<>
void
number_op<std::complex<double> >::
from_string( std::complex<double> &r, base::String const &s )
{
  // only converts real numbers
  double x;
  s.to_number( x );
  r = x;
}

template<>
void
number_op<std::complex<double> >::
to_string( base::String &s, std::complex<double> const &z )
{
  if ( z.real() != 0 )
  {
    s.to_string( z.real() );
    if ( z.imag() != 0.0 )
    {
      base::String t;
      t.to_string( z.imag() );
      s += "+";
      s += t;
      s += "i";
    }
  }
  else if ( z.imag() != 0 )
  {
    s.to_string( z.imag() );
    s += "i";
  }
  else
  {
    s = "0";
  }
}

template<>
number_op<std::complex<double> >::function0x_t const
number_op<std::complex<double> >::function0[] =
{
  { cpx_double_fn::cat, "cat" },
  { cpx_double_fn::e, "e" },
  { cpx_double_fn::euler, "euler" },
  { cpx_double_fn::gold, "gold" },
  { cpx_double_fn::pi, "pi" },
  { cpx_double_fn::i, "i" },
  { (function0_t)0, (char *)0 }
};

template<>
number_op<std::complex<double> >::function1x_t const
number_op<std::complex<double> >::function1[] =
{
  { cpx_double_fn::pos, "pos" },
  { cpx_double_fn::neg, "neg" },

  { cpx_double_fn::real, "re" },
  { cpx_double_fn::real, "real" },
  { cpx_double_fn::imag, "im" },
  { cpx_double_fn::imag, "imag" },
  { cpx_double_fn::norm, "norm" },
  { cpx_double_fn::abs, "abs" },
  { cpx_double_fn::abs, "conj" },

  { cpx_double_fn::sqr, "sqr" },
  { cpx_double_fn::cube, "cube" },
  { cpx_double_fn::inv, "inv" },
  { cpx_double_fn::sqrt, "sqrt" },

  { cpx_double_fn::exp, "exp" },
  { cpx_double_fn::log, "log" },
  { cpx_double_fn::log10, "log10" },

  { cpx_double_fn::cos, "cos" },
  { cpx_double_fn::sin, "sin" },
  { cpx_double_fn::tan, "tan" },
  { cpx_double_fn::sec, "sec" },
  { cpx_double_fn::csc, "csc" },
  { cpx_double_fn::cot, "cot" },

  { cpx_double_fn::acos, "acos" },
  { cpx_double_fn::asin, "asin" },
  { cpx_double_fn::atan, "atan" },
  { cpx_double_fn::asec, "asec" },
  { cpx_double_fn::acsc, "acsc" },
  { cpx_double_fn::acot, "acot" },

  { cpx_double_fn::acos, "arccos" },
  { cpx_double_fn::asin, "arcsin" },
  { cpx_double_fn::atan, "arctan" },
  { cpx_double_fn::asec, "arcsec" },
  { cpx_double_fn::acsc, "arccsc" },
  { cpx_double_fn::acot, "arccot" },

  { cpx_double_fn::cosh, "cosh" },
  { cpx_double_fn::sinh, "sinh" },
  { cpx_double_fn::tanh, "tanh" },
  { cpx_double_fn::sech, "sech" },
  { cpx_double_fn::csch, "csch" },
  { cpx_double_fn::coth, "coth" },

  { cpx_double_fn::acosh, "acosh" },
  { cpx_double_fn::acoth, "acoth" },
  { cpx_double_fn::acsch, "acsch" },
  { cpx_double_fn::asech, "asech" },
  { cpx_double_fn::asinh, "asinh" },
  { cpx_double_fn::atanh, "atanh" },

  { cpx_double_fn::acosh, "arccosh" },
  { cpx_double_fn::asinh, "arcsinh" },
  { cpx_double_fn::atanh, "arctanh" },
  { cpx_double_fn::asech, "arcsech" },
  { cpx_double_fn::acsch, "arccsch" },
  { cpx_double_fn::acoth, "arccoth" },


  { cpx_double_fn::weierstrass_e1, "weierstrass_e1" },
  { cpx_double_fn::weierstrass_e2, "weierstrass_e2" },
  { cpx_double_fn::weierstrass_e3, "weierstrass_e3" },
  { cpx_double_fn::weierstrass_g2, "weierstrass_g2" },
  { cpx_double_fn::weierstrass_g3, "weierstrass_g3" },
  { cpx_double_fn::weierstrass_eta1, "weierstrass_eta1" },
  { cpx_double_fn::weierstrass_eta2, "weierstrass_eta2" },
  { cpx_double_fn::elliptic_K, "elliptic_K" },

  { (function1_t)0, (char *)0 }
};

template<>
number_op<std::complex<double> >::function2x_t const
number_op<std::complex<double> >::function2[] =
{
  { cpx_double_fn::add, "add" },
  { cpx_double_fn::div, "div" },
  { cpx_double_fn::mul, "mul" },
  { cpx_double_fn::sub, "sub" },
  { cpx_double_fn::pow, "pow" },
  { cpx_double_fn::logb, "logb" },

  { cpx_double_fn::theta1, "theta1" },
  { cpx_double_fn::theta1_p, "theta1_p" },
  { cpx_double_fn::theta1_pp, "theta1_pp" },
  { cpx_double_fn::theta1_ppp, "theta1_ppp" },
  { cpx_double_fn::theta2, "theta2" },
  { cpx_double_fn::theta2_p, "theta2_p" },
  { cpx_double_fn::theta3, "theta3" },
  { cpx_double_fn::theta3_p, "theta3_p" },
  { cpx_double_fn::theta4, "theta4" },
  { cpx_double_fn::theta4_p, "theta4_p" },
  { cpx_double_fn::weierstrass_P, "weierstrass_P" },
  { cpx_double_fn::weierstrass_P_p, "weierstrass_P_p" },
  { cpx_double_fn::weierstrass_zeta, "weierstrass_zeta" },
  { cpx_double_fn::weierstrass_sigma, "weierstrass_sigma" },
  { cpx_double_fn::jacobi_am, "jacobi_am" },
  { cpx_double_fn::jacobi_sn, "jacobi_sn" },
  { cpx_double_fn::jacobi_cn, "jacobi_cn" },
  { cpx_double_fn::jacobi_dn, "jacobi_dn" },
  { cpx_double_fn::jacobi_ns, "jacobi_ns" },
  { cpx_double_fn::jacobi_cs, "jacobi_cs" },
  { cpx_double_fn::jacobi_ds, "jacobi_ds" },
  { cpx_double_fn::jacobi_nc, "jacobi_nc" },
  { cpx_double_fn::jacobi_sc, "jacobi_sc" },
  { cpx_double_fn::jacobi_dc, "jacobi_dc" },
  { cpx_double_fn::jacobi_nd, "jacobi_nd" },
  { cpx_double_fn::jacobi_sd, "jacobi_sd" },
  { cpx_double_fn::jacobi_cd, "jacobi_cd" },
  { (function2_t)0, (char *)0 }
};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif
