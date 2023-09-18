/* GANG Software
 * BASE/base/ColorBase.C
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
#include <algorithm>
#include "ColorBase.H"

namespace base {


template <class A>
A
max3( A a, A b, A c )
{ return a > b ? std::max(c,a) : std::max(c,b); }


template <class A>
A
min3( A a, A b, A c )
{ return b < a ? std::min(c,b) : std::min(c,a); }


void
_hsv2rgb( float &r_, float &g_, float &b_, float h_, float s_, float v_ )
{
  // copy so that output can point to input
  float h = h_;
  float s = s_;
  float v = v_;

  float r=0.0f, g=0.0f, b=0.0f;
  float ax, bx, cx, f;
  int i;

  // replace h by its fractional part
  h = h - floorf(h);

  // put s and v within the interval [0,1]
  s = std::max(0.0f, s);
  s = std::min(1.0f, s);
  v = std::max(0.0f, v);
  v = std::min(1.0f, v);

  if (s == 0)
  {
    r = g = b = v;
  }
  else
  {
    if (h == 1.0f) { h = 0.0f; }
    h *= 6.0f;
    i = (int)floor(h);
    f = h - i;
    ax = v * (1.0f - s);
    bx = v * (1.0f - (s * f));
    cx = v * (1.0f - (s * (1.0f - f)));
    if (i==0) { r = v;  g = cx; b = ax; }
    else if (i== 1) { r = bx; g = v;  b = ax; }
    else if (i== 2) { r = ax; g = v;  b = cx; }
    else if (i== 3) { r = ax; g = bx; b = v;  }
    else if (i== 4) { r = cx; g = ax; b = v;  }
    else if (i== 5) { r = v;  g = ax; b = bx; }
  }

  r_ = r;
  g_ = g;
  b_ = b;
}


void
_rgb2hsv( float &h_, float &s_, float &v_, float r_, float g_, float b_ )
{
  // copy so that output can point to input
  float r = r_;
  float g = g_;
  float b = b_;

  float h, s, v;
  float max_, min_, range;

  // put values within the interval [0,1]
  r = std::max(0.0f, r);
  r = std::min(1.0f, r);
  g = std::max(0.0f, g);
  g = std::min(1.0f, g);
  b = std::max(0.0f, b);
  b = std::min(1.0f, b);

  min_ = min3( r, g, b );
  max_ = max3( r, g, b );
  v = max_;

  range = max_ - min_;

  if ( max_ == 0.0f )
  {
    s = 0.0f;
  }
  else
  {
    s = ( max_ - min_ ) / max_;
  }
  if ( s == 0.0f )
  {
    h = 0.0f;
  }
  else
  {
    float rc = ( max_ - r ) / range;
    float gc = ( max_ - g ) / range;
    float bc = ( max_ - b ) / range;
    if ( r == max_ )
    {
      h = (1.0f/6.0f) * ( bc - gc );
    }
    else if ( g == max_ )
    {
      h = (1.0f/6.0f) * (2 + rc - bc );
    }
    else
    {
      h = (1.0f/6.0f) * (4 + gc - rc );
    }
    if ( h < 0.0f )
    {
      h += 1.0f;
    }
  }

  h_ = h;
  s_ = s;
  v_ = v;
}

} // namespace base
