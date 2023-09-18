/* GANG Software
 * BASE/eval/Real3Fn.C
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
#include "Real3Fn.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

#if defined(__sgi) && !defined(__GNUC__)
#define HAVE_REAL_FN_EXT // have extended set of std::complex functions
#endif

void
double_long_fn::
cat( double long &r )
{
  r = (double long)0.9159655941772190150546035149324;
}

void
double_long_fn::
e( double long &r )
{
  r = ::expl(1.0);
}

void
double_long_fn::
euler( double long &r )
{
  r = (double long)0.5772156649015328606065120900824;
}

void
double_long_fn::
gold( double long &r )
{
  r = (double long)1.6180339887498948482045868343656;
}

void
double_long_fn::
pi( double long &r )
{
  r = 4.0 * ::atanl(1.0);
}

void
double_long_fn::
pos( double long &r, double long const &x )
{
  r = x;
}

void
double_long_fn::
neg( double long &r, double long const &x )
{
  r = -x;
}


void
double_long_fn::
add( double long &r, double long const &x, double long const &y )
{
  r = x + y;
}

void
double_long_fn::
sub( double long &r, double long const &x, double long const &y )
{
  r = x - y;
}

void
double_long_fn::
mul( double long &r, double long const &x, double long const &y )
{
  r = x * y;
}

void
double_long_fn::
div( double long &r, double long const &x, double long const &y )
{
  r = x / y;
}


void
double_long_fn::
acos( double long &r, double long const &x )
{
  r = ::acosl( x );
}

void
double_long_fn::
acosh( double long &r, double long const &x )
{
  r = ::acosh( x );
}

void
double_long_fn::
asin( double long &r, double long const &x )
{
  r = ::asinl( x );
}

void
double_long_fn::
asinh( double long &r, double long const &x )
{
  r = ::asinh( x );
}

void
double_long_fn::
atan( double long &r, double long const &x )
{
  r = ::atanl( x );
}

void
double_long_fn::
atanh( double long &r, double long const &x )
{
  r = ::atanh( x );
}

void
double_long_fn::
cbrt( double long &r, double long const &x )
{
  r = ::cbrt( x );
}

void
double_long_fn::
ceil( double long &r, double long const &x )
{
  r = ::ceill( x );
}

void
double_long_fn::
cos( double long &r, double long const &x )
{
  r = ::cosl( x );
}

void
double_long_fn::
cosh( double long &r, double long const &x )
{
  r = ::coshl( x );
}

#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
void
double_long_fn::
erf( double long &r, double long const &x )
{
  r = ::erfl( x );
}

void
double_long_fn::
erfc( double long &r, double long const &x )
{
  r = ::erfcl( x );
}
#endif

void
double_long_fn::
exp( double long &r, double long const &x )
{
  r = ::expl( x );
}

void
double_long_fn::
expm1( double long &r, double long const &x )
{
  r = ::expm1( x );
}

#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
void
double_long_fn::
abs( double long &r, double long const &x )
{
  r = ::fabsl( x );
}
#endif

void
double_long_fn::
floor( double long &r, double long const &x )
{
  r = ::floorl( x );
}

#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
void
double_long_fn::
gamma( double long &r, double long const &x )
{
  r = ::gammal( x );
}
#endif

#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
void
double_long_fn::
j0( double long &r, double long const &x )
{
  r = ::j0l( x );
}

void
double_long_fn::
j1( double long &r, double long const &x )
{
  r = ::j1l( x );
}
#endif

#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
void
double_long_fn::
lgamma( double long &r, double long const &x )
{
  r = ::lgammal( x );
}
#endif

void
double_long_fn::
log( double long &r, double long const &x )
{
  r = ::logl( x );
}

void
double_long_fn::
log10( double long &r, double long const &x )
{
  r = ::log10l( x );
}

#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
void
double_long_fn::
log1p( double long &r, double long const &x )
{
  r = ::log1pl( x );
}
#endif

void
double_long_fn::
logb( double long &r, double long const &x )
{
  r = ::logbl( x );
}

void
double_long_fn::
rint( double long &r, double long const &x )
{
  r = ::rintl( x );
}

void
double_long_fn::
sin( double long &r, double long const &x )
{
  r = ::sinl( x );
}

void
double_long_fn::
sinh( double long &r, double long const &x )
{
  r = ::sinhl( x );
}

void
double_long_fn::
sqrt( double long &r, double long const &x )
{
  r = ::sqrtl( x );
}

void
double_long_fn::
tan( double long &r, double long const &x )
{
  r = ::tanl( x );
}

void
double_long_fn::
tanh( double long &r, double long const &x )
{
  r = ::tanhl( x );
}

#if defined(__sgi) && !defined(__GNUG__) && \
  defined(_COMPILER_VERSION) && _COMPILER_VERSION >= 730
void
double_long_fn::
y0( double long &r, double long const &x )
{
  r = ::y0l( x );
}

void
double_long_fn::
y1( double long &r, double long const &x )
{
  r = ::y1l( x );
}
#endif

void
double_long_fn::
trunc( double long &r, double long const &x )
{
#ifdef HAVE_REAL_FN_EXT
  r = ::truncl( x );
#else
  r = ( x >= 0.0 ? ::floorl(x) : ::floorl(x) + 1 );
#endif
}

void
double_long_fn::
atan2( double long &r, double long const &x, double long const &y)
{
  r = ::atan2l( x, y );
}

void
double_long_fn::
pow( double long &r, double long const &x, double long const &y)
{
  if ( x == (double long)0.0 )
  {
    r = (double long)0.0;
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
//      double long v = x*x;
//      r = v*v;
//    }
    else
    {
      r = ::powl( x, int(y) );
    }
  }
  else
  {
    r = ::powl(x, y);
  }
}


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif
