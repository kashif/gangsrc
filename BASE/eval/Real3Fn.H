/* GANG Software
 * BASE/eval/Real3Fn.H
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

#ifndef eval_Real3Fn_INCLUDED
#define eval_Real3Fn_INCLUDED


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

//
struct double_long_fn
{
  //
  static void cat( double long & );
  //
  static void e( double long & );
  //
  static void euler( double long & );
  //
  static void gold( double long & );
  //
  static void pi( double long & );

  //
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  static void abs( double long &, double long const & );
#endif
  //
  static void acos( double long &, double long const & );
  //
  static void acosh( double long &, double long const & );
  //
  static void asin( double long &, double long const & );
  //
  static void asinh( double long &, double long const & );
  //
  static void atan( double long &, double long const & );
  //
  static void atanh( double long &, double long const & );
  //
  static void cbrt( double long &, double long const & );
  //
  static void ceil( double long &, double long const & );
  //
  static void cos( double long &, double long const & );
  //
  static void cosh( double long &, double long const & );
  //
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  static void erf( double long &, double long const & );

  //
  static void erfc( double long &, double long const & );
#endif
  //
  static void exp( double long &, double long const & );
  //
  static void expm1( double long &, double long const & );
  //
  static void floor( double long &, double long const & );
  //
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  static void gamma( double long &, double long const & );
#endif
  //
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  static void j0( double long &, double long const & );
  //
  static void j1( double long &, double long const & );
#endif
  //
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  static void lgamma( double long &, double long const & );
#endif
  //
  static void log( double long &, double long const & );
  //
  static void log10( double long &, double long const & );
  //
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  static void log1p( double long &, double long const & );
#endif
  //
  static void logb( double long &, double long const & );
  //
  static void neg( double long &, double long const & );
  //
  static void pos( double long &, double long const & );
  //
  static void rint( double long &, double long const & );
  //
  static void sin( double long &, double long const & );
  //
  static void sinh( double long &, double long const & );
  //
  static void sqrt( double long &, double long const & );
  //
  static void tan( double long &, double long const & );
  //
  static void tanh( double long &, double long const & );
  //
  static void trunc( double long &, double long const & );
  //
#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
  static void y0( double long &, double long const & );
  //
  static void y1( double long &, double long const & );
#endif
  //
  static void atan2( double long &, double long const &, double long const & );
  //
  static void pow( double long &, double long const &, double long const & );
  //
  static void sub( double long &, double long const &, double long const & );
  //
  static void mul( double long &, double long const &, double long const & );
  //
  static void div( double long &, double long const &, double long const & );
  //
  static void add( double long &, double long const &, double long const & );
};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_Real3Fn_INCLUDED
