/* GANG Software
 * BASE/eval/Real2Op.C
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
#include "Real2Fn.H"
#include "NumberOp.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

template<>
void
number_op<double>::
from_string( double &r, base::String const &s )
{
  s.to_number( r );
}


template<>
void
number_op<double>::
to_string( base::String &, double const & )
{
  DIE();
}

template<>
number_op<double>::function0x_t const number_op<double>::function0[] =
{
  { double_fn::cat, "cat" },
  { double_fn::e, "e" },
  { double_fn::euler, "euler" },
  { double_fn::gold, "gold" },
  { double_fn::pi, "pi" },
  { (function0_t)0, (char *)0 }
};

template<>
number_op<double>::function1x_t const number_op<double>::function1[] =
{
  { double_fn::acos, "acos" },
  { double_fn::acosh, "acosh" },
  { double_fn::asin, "asin" },
  { double_fn::asinh, "asinh" },
  { double_fn::atan, "atan" },
  { double_fn::atanh, "atanh" },
  { double_fn::cbrt, "cbrt" },
  { double_fn::ceil, "ceil" },
  { double_fn::cos, "cos" },
  { double_fn::cosh, "cosh" },
  { double_fn::erf, "erv" },
  { double_fn::erfc, "erfc" },
  { double_fn::exp, "exp" },
  { double_fn::expm1, "expm1" },
  { double_fn::abs, "abs" },
  { double_fn::floor, "floor" },
  { double_fn::gamma, "gamma" },
  { double_fn::j0, "j0" },
  { double_fn::j1, "j1" },
  { double_fn::lgamma, "lgamma" },
  { double_fn::log, "log" },
  { double_fn::log10, "log10" },
  { double_fn::log1p, "log1p" },
  { double_fn::logb, "logb" },  // is this a 2-arg fun?
  { double_fn::neg, "neg" },
  { double_fn::pos, "pos" },
  { double_fn::rint, "rint" },
  { double_fn::sin, "sin" },
  { double_fn::sinh, "sinh" },
  { double_fn::sqrt, "sqrt" },
  { double_fn::tan, "tan" },
  { double_fn::tanh, "tanh" },
  { double_fn::trunc, "trunc" },
  { double_fn::y0, "y0" },
  { double_fn::y1, "y1" },
  { (function1_t)0, (char *)0 }
};

template<>
number_op<double>::function2x_t const number_op<double>::function2[] =
{
  { double_fn::add, "add" },
  { double_fn::atan2, "atan2" },
  { double_fn::div, "div" },
  { double_fn::mul, "mul" },
  { double_fn::sub, "sub" },
  { double_fn::pow, "pow" },
  { (function2_t)0, (char *)0 }
};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif
