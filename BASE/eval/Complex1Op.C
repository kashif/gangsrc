/* GANG Software
 * BASE/eval/Complex1Op.C
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

#include "base/String.H"
#include "Complex1Fn.H"
#include "NumberOp.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

template<>
void
number_op<std::complex<float> >::
from_string( std::complex<float> &r, base::String const &s )
{
  // only converts real numbers
  float x;
  s.to_number( x );
  r = x;
}

template<>
void
number_op<std::complex<float> >::
to_string( base::String &s, std::complex<float> const &z )
{
  if ( z.real() != 0 )
  {
    to_string( s, z.real() );
    if ( z.imag() != 0.0 )
    {
      base::String t;
      to_string( t, z.imag() );
      s += "+";
      s += t;
      s += "i";
    }
  }
  else if ( z.imag() != 0 )
  {
    to_string( s, z.imag() );
    s += "i";
  }
  else
  {
    s = "0";
  }
}

template<>
number_op<std::complex<float> >::function0x_t const
number_op<std::complex<float> >::function0[] =
{
  { cpx_float_fn::cat, "cat" },
  { cpx_float_fn::e, "e" },
  { cpx_float_fn::euler, "euler" },
  { cpx_float_fn::gold, "gold" },
  { cpx_float_fn::pi, "pi" },
  { cpx_float_fn::i, "i" },
  { (function0_t)0, (char *)0 }
};

template<>
number_op<std::complex<float> >::function1x_t const
number_op<std::complex<float> >::function1[] =
{
  { cpx_float_fn::pos, "pos" },
  { cpx_float_fn::neg, "neg" },

  { cpx_float_fn::real, "re" },
  { cpx_float_fn::real, "real" },
  { cpx_float_fn::imag, "im" },
  { cpx_float_fn::imag, "imag" },
  { cpx_float_fn::norm, "norm" },
  { cpx_float_fn::abs, "abs" },
  { cpx_float_fn::abs, "conj" },

  { cpx_float_fn::sqr, "sqr" },
  { cpx_float_fn::cube, "cube" },
  { cpx_float_fn::inv, "inv" },
  { cpx_float_fn::sqrt, "sqrt" },

  { cpx_float_fn::exp, "exp" },
  { cpx_float_fn::log, "log" },
  { cpx_float_fn::log10, "log10" },

  { cpx_float_fn::cos, "cos" },
  { cpx_float_fn::sin, "sin" },
  { cpx_float_fn::tan, "tan" },
  { cpx_float_fn::sec, "sec" },
  { cpx_float_fn::csc, "csc" },
  { cpx_float_fn::cot, "cot" },

  { cpx_float_fn::acos, "acos" },
  { cpx_float_fn::asin, "asin" },
  { cpx_float_fn::atan, "atan" },
  { cpx_float_fn::asec, "asec" },
  { cpx_float_fn::acsc, "acsc" },
  { cpx_float_fn::acot, "acot" },

  { cpx_float_fn::acos, "arccos" },
  { cpx_float_fn::asin, "arcsin" },
  { cpx_float_fn::atan, "arctan" },
  { cpx_float_fn::asec, "arcsec" },
  { cpx_float_fn::acsc, "arccsc" },
  { cpx_float_fn::acot, "arccot" },

  { cpx_float_fn::cosh, "cosh" },
  { cpx_float_fn::sinh, "sinh" },
  { cpx_float_fn::tanh, "tanh" },
  { cpx_float_fn::sech, "sech" },
  { cpx_float_fn::csch, "csch" },
  { cpx_float_fn::coth, "coth" },

  { cpx_float_fn::acosh, "acosh" },
  { cpx_float_fn::acoth, "acoth" },
  { cpx_float_fn::acsch, "acsch" },
  { cpx_float_fn::asech, "asech" },
  { cpx_float_fn::asinh, "asinh" },
  { cpx_float_fn::atanh, "atanh" },

  { cpx_float_fn::acosh, "arccosh" },
  { cpx_float_fn::asinh, "arcsinh" },
  { cpx_float_fn::atanh, "arctanh" },
  { cpx_float_fn::asech, "arcsech" },
  { cpx_float_fn::acsch, "arccsch" },
  { cpx_float_fn::acoth, "arccoth" },

#if 0
  { cpx_float_fn::weierstrass_e1, "weierstrass_e1" },
  { cpx_float_fn::weierstrass_e2, "weierstrass_e2" },
  { cpx_float_fn::weierstrass_e3, "weierstrass_e3" },
  { cpx_float_fn::weierstrass_g2, "weierstrass_g2" },
  { cpx_float_fn::weierstrass_g3, "weierstrass_g3" },
  { cpx_float_fn::weierstrass_eta1, "weierstrass_eta1" },
  { cpx_float_fn::weierstrass_eta2, "weierstrass_eta2" },
  { cpx_float_fn::elliptic_K, "elliptic_K" },
#endif
  { (function1_t)0, (char *)0 }
};

template<>
number_op<std::complex<float> >::function2x_t const
number_op<std::complex<float> >::function2[] =
{
  { cpx_float_fn::add, "add" },
  { cpx_float_fn::div, "div" },
  { cpx_float_fn::mul, "mul" },
  { cpx_float_fn::sub, "sub" },
  { cpx_float_fn::pow, "pow" },
  { cpx_float_fn::logb, "logb" },

#if 0
  { cpx_float_fn::theta1, "theta1" },
  { cpx_float_fn::theta1_p, "theta1_p" },
  { cpx_float_fn::theta1_pp, "theta1_pp" },
  { cpx_float_fn::theta1_ppp, "theta1_ppp" },
  { cpx_float_fn::theta2, "theta2" },
  { cpx_float_fn::theta2_p, "theta2_p" },
  { cpx_float_fn::theta3, "theta3" },
  { cpx_float_fn::theta3_p, "theta3_p" },
  { cpx_float_fn::theta4, "theta4" },
  { cpx_float_fn::theta4_p, "theta4_p" },
  { cpx_float_fn::weierstrass_P, "weierstrass_P" },
  { cpx_float_fn::weierstrass_P_p, "weierstrass_P_p" },
  { cpx_float_fn::weierstrass_zeta, "weierstrass_zeta" },
  { cpx_float_fn::weierstrass_sigma, "weierstrass_sigma" },
  { cpx_float_fn::jacobi_am, "jacobi_am" },
  { cpx_float_fn::jacobi_sn, "jacobi_sn" },
  { cpx_float_fn::jacobi_cn, "jacobi_cn" },
  { cpx_float_fn::jacobi_dn, "jacobi_dn" },
  { cpx_float_fn::jacobi_ns, "jacobi_ns" },
  { cpx_float_fn::jacobi_cs, "jacobi_cs" },
  { cpx_float_fn::jacobi_ds, "jacobi_ds" },
  { cpx_float_fn::jacobi_nc, "jacobi_nc" },
  { cpx_float_fn::jacobi_sc, "jacobi_sc" },
  { cpx_float_fn::jacobi_dc, "jacobi_dc" },
  { cpx_float_fn::jacobi_nd, "jacobi_nd" },
  { cpx_float_fn::jacobi_sd, "jacobi_sd" },
  { cpx_float_fn::jacobi_cd, "jacobi_cd" },
#endif
  { (function2_t)0, (char *)0 }
};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif
