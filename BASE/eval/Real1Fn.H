/* GANG Software
 * BASE/eval/Real1Fn.H
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

#ifndef eval_Real1Fn_INCLUDED
#define eval_Real1Fn_INCLUDED


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

//
struct float_fn
{
  //
  static void cat( float & );
  //
  static void e( float & );
  //
  static void euler( float & );
  //
  static void gold( float & );
  //
  static void pi( float & );

  //
  static void abs( float &, float const & );
  //
  static void acos( float &, float const & );
  //
  static void acosh( float &, float const & );
  //
  static void asin( float &, float const & );
  //
  static void asinh( float &, float const & );
  //
  static void atan( float &, float const & );
  //
  static void atanh( float &, float const & );
  //
  static void cbrt( float &, float const & );
  //
  static void ceil( float &, float const & );
  //
  static void cos( float &, float const & );
  //
  static void cosh( float &, float const & );
  //
  static void erf( float &, float const & );
  //
  static void erfc( float &, float const & );
  //
  static void exp( float &, float const & );
  //
  static void expm1( float &, float const & );
  //
  static void floor( float &, float const & );
  //
  static void gamma( float &, float const & );
  //
  static void j0( float &, float const & );
  //
  static void j1( float &, float const & );
  //
  static void lgamma( float &, float const & );
  //
  static void log( float &, float const & );
  //
  static void log10( float &, float const & );
  //
  static void log1p( float &, float const & );
  //
  static void logb( float &, float const & );
  //
  static void neg( float &, float const & );
  //
  static void pos( float &, float const & );
  //
  static void rint( float &, float const & );
  //
  static void sin( float &, float const & );
  //
  static void sinh( float &, float const & );
  //
  static void sqrt( float &, float const & );
  //
  static void tan( float &, float const & );
  //
  static void tanh( float &, float const & );
  //
  static void trunc( float &, float const & );
  //
  static void y0( float &, float const & );
  //
  static void y1( float &, float const & );

  //
  static void atan2( float &, float const &, float const & );
  //
  static void pow( float &, float const &, float const & );
  //
  static void sub( float &, float const &, float const & );
  //
  static void mul( float &, float const &, float const & );
  //
  static void div( float &, float const &, float const & );
  //
  static void add( float &, float const &, float const & );
};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_Real1Fn_INCLUDED
