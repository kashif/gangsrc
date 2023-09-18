/* GANG Software
 * BASE/eval/Real3Op.C
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
#include "Real3Fn.H"
#include "NumberOp.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

template<>
void
number_op<double long>::
from_string( double long &r, base::String const &s )
{
  s.to_number( r );
}

template<>
void
number_op<double long>::
to_string( base::String &, double long const & )
{
  DIE();
}

template<>
number_op<double long>::function0x_t const number_op<double long>::function0[] =
{
  { double_long_fn::cat, "cat" },
  { double_long_fn::e, "e" },
  { double_long_fn::euler, "euler" },
  { double_long_fn::gold, "gold" },
  { double_long_fn::pi, "pi" },
  { (function0_t)0, (char *)0 }
};

template<>
number_op<double long>::function1x_t const number_op<double long>::function1[] =
{
  { double_long_fn::acos, "acos" },
  { double_long_fn::acosh, "acosh" },
  { double_long_fn::asin, "asin" },
  { double_long_fn::asinh, "asinh" },
  { double_long_fn::atan, "atan" },
  { double_long_fn::atanh, "atanh" },
  { double_long_fn::cbrt, "cbrt" },
  { double_long_fn::ceil, "ceil" },
  { double_long_fn::cos, "cos" },
  { double_long_fn::cosh, "cosh" },
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  { double_long_fn::erf, "erv" },
  { double_long_fn::erfc, "erfc" },
#endif
  { double_long_fn::exp, "exp" },
  { double_long_fn::expm1, "expm1" },
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  { double_long_fn::abs, "abs" },
#endif
  { double_long_fn::floor, "floor" },
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  { double_long_fn::gamma, "gamma" },
#endif
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  { double_long_fn::j0, "j0" },
  { double_long_fn::j1, "j1" },
#endif
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  { double_long_fn::lgamma, "lgamma" },
#endif
  { double_long_fn::log, "log" },
  { double_long_fn::log10, "log10" },
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  { double_long_fn::log1p, "log1p" },
#endif
  { double_long_fn::logb, "logb" },  // is this a 2-arg fun?
  { double_long_fn::neg, "neg" },
  { double_long_fn::pos, "pos" },
  { double_long_fn::rint, "rint" },
  { double_long_fn::sin, "sin" },
  { double_long_fn::sinh, "sinh" },
  { double_long_fn::sqrt, "sqrt" },
  { double_long_fn::tan, "tan" },
  { double_long_fn::tanh, "tanh" },
  { double_long_fn::trunc, "trunc" },
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  { double_long_fn::y0, "y0" },
  { double_long_fn::y1, "y1" },
#endif
  { (function1_t)0, (char *)0 }
};

template<>
number_op<double long>::function2x_t const number_op<double long>::function2[] =
{
  { double_long_fn::add, "add" },
  { double_long_fn::atan2, "atan2" },
  { double_long_fn::div, "div" },
  { double_long_fn::mul, "mul" },
  { double_long_fn::sub, "sub" },
  { double_long_fn::pow, "pow" },
  { (function2_t)0, (char *)0 }
};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif
