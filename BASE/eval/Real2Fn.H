/* GANG Software
 * BASE/eval/Real2Fn.H
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

#ifndef eval_Real2Fn_INCLUDED
#define eval_Real2Fn_INCLUDED


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

//
struct double_fn
{
  //
  static void cat( double & );
  //
  static void e( double & );
  //
  static void euler( double & );
  //
  static void gold( double & );
  //
  static void pi( double & );

  //
  static void abs( double &, double const & );
  //
  static void acos( double &, double const & );
  //
  static void acosh( double &, double const & );
  //
  static void asin( double &, double const & );
  //
  static void asinh( double &, double const & );
  //
  static void atan( double &, double const & );
  //
  static void atanh( double &, double const & );
  //
  static void cbrt( double &, double const & );
  //
  static void ceil( double &, double const & );
  //
  static void cos( double &, double const & );
  //
  static void cosh( double &, double const & );
  //
  static void erf( double &, double const & );
  //
  static void erfc( double &, double const & );
  //
  static void exp( double &, double const & );
  //
  static void expm1( double &, double const & );
  //
  static void floor( double &, double const & );
  //
  static void gamma( double &, double const & );
  //
  static void j0( double &, double const & );
  //
  static void j1( double &, double const & );
  //
  static void lgamma( double &, double const & );
  //
  static void log( double &, double const & );
  //
  static void log10( double &, double const & );
  //
  static void log1p( double &, double const & );
  //
  static void logb( double &, double const & );
  //
  static void neg( double &, double const & );
  //
  static void pos( double &, double const & );
  //
  static void rint( double &, double const & );
  //
  static void sin( double &, double const & );
  //
  static void sinh( double &, double const & );
  //
  static void sqrt( double &, double const & );
  //
  static void tan( double &, double const & );
  //
  static void tanh( double &, double const & );
  //
  static void trunc( double &, double const & );
  //
  static void y0( double &, double const & );
  //
  static void y1( double &, double const & );

  //
  static void atan2( double &, double const &, double const & );
  //
  static void pow( double &, double const &, double const & );
  //
  static void sub( double &, double const &, double const & );
  //
  static void mul( double &, double const &, double const & );
  //
  static void div( double &, double const &, double const & );
  //
  static void add( double &, double const &, double const & );
};


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif

#endif // eval_Real2Fn_INCLUDED
