/* GANG Software
 * BASE/eval/Real1Op.C
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
#include "Real1Fn.H"
#include "NumberOp.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

template<>
void
number_op<float>::
from_string( float &r, base::String const &s )
{
  s.to_number( r );
}


template<>
void
number_op<float>::
to_string( base::String &, float const & )
{
  DIE();
}

template<>
number_op<float>::function0x_t const number_op<float>::function0[] =
{
  { float_fn::cat, "cat" },
  { float_fn::e, "e" },
  { float_fn::euler, "euler" },
  { float_fn::gold, "gold" },
  { float_fn::pi, "pi" },
  { (function0_t)0, (char *)0 }
};

template<>
number_op<float>::function1x_t const number_op<float>::function1[] =
{
  { float_fn::acos, "acos" },
  { float_fn::acosh, "acosh" },
  { float_fn::asin, "asin" },
  { float_fn::asinh, "asinh" },
  { float_fn::atan, "atan" },
  { float_fn::atanh, "atanh" },
  { float_fn::cbrt, "cbrt" },
  { float_fn::ceil, "ceil" },
  { float_fn::cos, "cos" },
  { float_fn::cosh, "cosh" },
  { float_fn::erf, "erv" },
  { float_fn::erfc, "erfc" },
  { float_fn::exp, "exp" },
  { float_fn::expm1, "expm1" },
  { float_fn::abs, "abs" },
  { float_fn::floor, "floor" },
  { float_fn::gamma, "gamma" },
  { float_fn::j0, "j0" },
  { float_fn::j1, "j1" },
  { float_fn::lgamma, "lgamma" },
  { float_fn::log, "log" },
  { float_fn::log10, "log10" },
  { float_fn::log1p, "log1p" },
  { float_fn::logb, "logb" },  // is this a 2-arg fun?
  { float_fn::neg, "neg" },
  { float_fn::pos, "pos" },
  { float_fn::rint, "rint" },
  { float_fn::sin, "sin" },
  { float_fn::sinh, "sinh" },
  { float_fn::sqrt, "sqrt" },
  { float_fn::tan, "tan" },
  { float_fn::tanh, "tanh" },
  { float_fn::trunc, "trunc" },
  { float_fn::y0, "y0" },
  { float_fn::y1, "y1" },
  { (function1_t)0, (char *)0 }
};

template<>
number_op<float>::function2x_t const number_op<float>::function2[] =
{
  { float_fn::add, "add" },
  { float_fn::atan2, "atan2" },
  { float_fn::div, "div" },
  { float_fn::mul, "mul" },
  { float_fn::sub, "sub" },
  { float_fn::pow, "pow" },
  { (function2_t)0, (char *)0 }
};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif
