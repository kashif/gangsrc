/* GANG Software
 * BASE/eval/Real2Fn.C
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

#include <math.h>
#include "Real2Fn.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

#if defined(__sgi) && !defined(__GNUC__)
#define HAVE_REAL_FN_EXT // have extended set of std::complex functions
#endif

void
double_fn::
cat( double &r )
{
  r = double(0.9159655941772190150546035149324);
}

void
double_fn::
e( double &r )
{
  r = ::exp(1.0);
}

void
double_fn::
euler( double &r )
{
  r = double(0.5772156649015328606065120900824);
}

void
double_fn::
gold( double &r )
{
  r = double(1.6180339887498948482045868343656);
}

void
double_fn::
pi( double &r )
{
  r = 4.0 * ::atan(1.0);
}

void
double_fn::
pos( double &r, double const &x )
{
  r = x;
}

void
double_fn::
neg( double &r, double const &x )
{
  r = -x;
}


void
double_fn::
add( double &r, double const &x, double const &y )
{
  r = x + y;
}

void
double_fn::
sub( double &r, double const &x, double const &y )
{
  r = x - y;
}

void
double_fn::
mul( double &r, double const &x, double const &y )
{
  r = x * y;
}

void
double_fn::
div( double &r, double const &x, double const &y )
{
  r = x / y;
}


void
double_fn::
acos( double &r, double const &x )
{
  r = ::acos( x );
}

void
double_fn::
acosh( double &r, double const &x )
{
  r = ::acosh( x );
}

void
double_fn::
asin( double &r, double const &x )
{
  r = ::asin( x );
}

void
double_fn::
asinh( double &r, double const &x )
{
  r = ::asinh( x );
}

void
double_fn::
atan( double &r, double const &x )
{
  r = ::atan( x );
}

void
double_fn::
atanh( double &r, double const &x )
{
  r = ::atanh( x );
}

void
double_fn::
cbrt( double &r, double const &x )
{
  r = ::cbrt( x );
}

void
double_fn::
ceil( double &r, double const &x )
{
  r = ::ceil( x );
}

void
double_fn::
cos( double &r, double const &x )
{
  r = ::cos( x );
}

void
double_fn::
cosh( double &r, double const &x )
{
  r = ::cosh( x );
}

void
double_fn::
erf( double &r, double const &x )
{
  r = ::erf( x );
}

void
double_fn::
erfc( double &r, double const &x )
{
  r = ::erfc( x );
}

void
double_fn::
exp( double &r, double const &x )
{
  r = ::exp( x );
}

void
double_fn::
expm1( double &r, double const &x )
{
  r = ::expm1( x );
}

void
double_fn::
abs( double &r, double const &x )
{
  r = ::fabs( x );
}

void
double_fn::
floor( double &r, double const &x )
{
  r = ::floor( x );
}

void
double_fn::
gamma( double &r, double const &x )
{
  r = ::gamma( x );
}

void
double_fn::
j0( double &r, double const &x )
{
  r = ::j0( x );
}

void
double_fn::
j1( double &r, double const &x )
{
  r = ::j1( x );
}

void
double_fn::
lgamma( double &r, double const &x )
{
  r = ::lgamma( x );
}

void
double_fn::
log( double &r, double const &x )
{
  r = ::log( x );
}

void
double_fn::
log10( double &r, double const &x )
{
  r = ::log10( x );
}

void
double_fn::
log1p( double &r, double const &x )
{
  r = ::log1p( x );
}

void
double_fn::
logb( double &r, double const &x )
{
  r = ::logb( x );
}

void
double_fn::
rint( double &r, double const &x )
{
  r = ::rint( x );
}

void
double_fn::
sin( double &r, double const &x )
{
  r = ::sin( x );
}

void
double_fn::
sinh( double &r, double const &x )
{
  r = ::sinh( x );
}

void
double_fn::
sqrt( double &r, double const &x )
{
  r = ::sqrt( x );
}

void
double_fn::
tan( double &r, double const &x )
{
  r = ::tan( x );
}

void
double_fn::
tanh( double &r, double const &x )
{
  r = ::tanh( x );
}

void
double_fn::
y0( double &r, double const &x )
{
  r = ::y0( x );
}

void
double_fn::
y1( double &r, double const &x )
{
  r = ::y1( x );
}

void
double_fn::
trunc( double &r, double const &x )
{
#ifdef HAVE_REAL_FN_EXT
  r = ::trunc( x );
#else
  r = ( x >= 0.0 ? ::floor(x) : ::floor(x) + 1 );
#endif
}

void
double_fn::
atan2( double &r, double const &x, double const &y)
{
  r = ::atan2( x, y );
}

void
double_fn::
pow( double &r, double const &x, double const &y)
{
  if ( x == double(0.0) )
  {
    r = double(0.0);
  }
  else if ( y == int(y) )
  {
    if ( y == 2.0)
    {
      r = x*x;
    }
    else if (y == 3.0)
    {
      r = x*x*x;
    }
//    else if (y == 4.0)
//    {
//      double v = x*x;
//      r = v*v;
//    }
    else
    {
      r = ::pow( x, int(y) );
    }
  }
  else
  {
    r = ::pow(x, y);
  }
}


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif
