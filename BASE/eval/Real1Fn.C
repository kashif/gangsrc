/* GANG Software
 * BASE/eval/Real1Fn.C
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
#include "Real1Fn.H"


#if !defined(DISABLE_EVAL_NAMESPACE)
namespace eval {
#endif

#if defined(__sgi) && !defined(__GNUC__)
#define HAVE_REAL_FN_EXT // have extended set of std::complex functions
#endif

void
float_fn::
cat( float &r )
{
  r = float(0.9159655941772190150546035149324);
}

void
float_fn::
e( float &r )
{
  r = ::expf(1.0f);
}

void
float_fn::
euler( float &r )
{
  r = float(0.5772156649015328606065120900824);
}

void
float_fn::
gold( float &r )
{
  r = float(1.6180339887498948482045868343656);
}

void
float_fn::
pi( float &r )
{
  r = 4.0 * ::atanf(1.0);
}

void
float_fn::
pos( float &r, float const &x )
{
  r = x;
}

void
float_fn::
neg( float &r, float const &x )
{
  r = -x;
}


void
float_fn::
add( float &r, float const &x, float const &y )
{
  r = x + y;
}

void
float_fn::
sub( float &r, float const &x, float const &y )
{
  r = x - y;
}

void
float_fn::
mul( float &r, float const &x, float const &y )
{
  r = x * y;
}

void
float_fn::
div( float &r, float const &x, float const &y )
{
  r = x / y;
}


void
float_fn::
acos( float &r, float const &x )
{
  r = ::acosf( x );
}

void
float_fn::
acosh( float &r, float const &x )
{
  r = ::acosh( x );
}

void
float_fn::
asin( float &r, float const &x )
{
  r = ::asinf( x );
}

void
float_fn::
asinh( float &r, float const &x )
{
  r = ::asinh( x );
}

void
float_fn::
atan( float &r, float const &x )
{
  r = ::atanf( x );
}

void
float_fn::
atanh( float &r, float const &x )
{
  r = ::atanh( x );
}

void
float_fn::
cbrt( float &r, float const &x )
{
  r = ::cbrt( x );
}

void
float_fn::
ceil( float &r, float const &x )
{
  r = ::ceilf( x );
}

void
float_fn::
cos( float &r, float const &x )
{
  r = ::cosf( x );
}

void
float_fn::
cosh( float &r, float const &x )
{
  r = ::coshf( x );
}

void
float_fn::
erf( float &r, float const &x )
{
  r = ::erf( x );
}

void
float_fn::
erfc( float &r, float const &x )
{
  r = ::erfc( x );
}

void
float_fn::
exp( float &r, float const &x )
{
  r = ::expf( x );
}

void
float_fn::
expm1( float &r, float const &x )
{
  r = ::expm1f( x );
}

void
float_fn::
abs( float &r, float const &x )
{
  r = ::fabsf( x );
}

void
float_fn::
floor( float &r, float const &x )
{
  r = ::floorf( x );
}

void
float_fn::
gamma( float &r, float const &x )
{
  r = ::gamma( x );
}

void
float_fn::
j0( float &r, float const &x )
{
  r = ::j0( x );
}

void
float_fn::
j1( float &r, float const &x )
{
  r = ::j1( x );
}

void
float_fn::
lgamma( float &r, float const &x )
{
  r = ::lgamma( x );
}

void
float_fn::
log( float &r, float const &x )
{
  r = ::logf( x );
}

void
float_fn::
log10( float &r, float const &x )
{
  r = ::log10f( x );
}

void
float_fn::
log1p( float &r, float const &x )
{
  r = ::log1pf( x );
}

void
float_fn::
logb( float &r, float const &x )
{
  r = ::logb( x );
}

void
float_fn::
rint( float &r, float const &x )
{
  r = ::rint( x );
}

void
float_fn::
sin( float &r, float const &x )
{
  r = ::sinf( x );
}

void
float_fn::
sinh( float &r, float const &x )
{
  r = ::sinhf( x );
}

void
float_fn::
sqrt( float &r, float const &x )
{
  r = ::sqrtf( x );
}

void
float_fn::
tan( float &r, float const &x )
{
  r = ::tanf( x );
}

void
float_fn::
tanh( float &r, float const &x )
{
  r = ::tanhf( x );
}

void
float_fn::
y0( float &r, float const &x )
{
  r = ::y0( x );
}

void
float_fn::
y1( float &r, float const &x )
{
  r = ::y1( x );
}

void
float_fn::
trunc( float &r, float const &x )
{
#ifdef HAVE_REAL_FN_EXT
  r = ::truncf( x );
#else
  r = ( x >= 0.0 ? ::floorf(x) : ::floorf(x) + 1 );
#endif
}

void
float_fn::
atan2( float &r, float const &x, float const &y)
{
  r = ::atan2f( x, y );
}

void
float_fn::
pow( float &r, float const &x, float const &y)
{
  if ( x == float(0.0) )
  {
    r = float(0.0);
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
//      float v = x*x;
//      r = v*v;
//    }
    else
    {
      r = ::powf( x, int(y) );
    }
  }
  else
  {
    r = ::powf(x, y);
  }
}


#if !defined(DISABLE_EVAL_NAMESPACE)
} // namespace eval
#endif
