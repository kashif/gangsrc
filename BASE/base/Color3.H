/* GANG Software
 * BASE/base/Color3.H
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

#ifndef base_Color3_INCLUDED
#define base_Color3_INCLUDED

#include "ArrayX.H"
#include "ColorBase.H"

namespace base {

class Color3
  :
    public ArrayX<float,3U>
{

public:
  // constructor
  Color3()
      :
      ArrayX<float,3U>()
    { set(0.0f); }

  // constructor
  Color3( float a0, float a1, float a2 )
      :
      ArrayX<float,3U>()
    { _[0] = a0; _[1] = a1; _[2] = a2; }

  // copy constructor
  Color3( Color3 const &a )
      :
      ArrayX<float,3U>(a) {}

  // copy constructor
  Color3( float const *a )
      :
      ArrayX<float,3U>(a) {}

  // destructor
  virtual ~Color3() {}

  // assignment operator
  Color3 &operator=( Color3 const &a )
    { ArrayX<float,3U>::operator=(a); return *this; }

  float &red() { return operator[](0); }
  float &green() { return operator[](1); }
  float &blue() { return operator[](2); }
  float &hue() { return operator[](0); }
  float &val() { return operator[](1); }
  float &sat() { return operator[](2); }

  float const &red() const { return operator[](0); }
  float const &green() const { return operator[](1); }
  float const &blue() const { return operator[](2); }
  float const &hue() const { return operator[](0); }
  float const &val() const { return operator[](1); }
  float const &sat() const { return operator[](2); }

protected:

private:
};

inline void hsv2rgb( Color3 &b, Color3 const &a )
{
  ::base::_hsv2rgb( b[0], b[1], b[2], a[0], a[1], a[2] );
}
inline void hsv2rgb( Color3 &a )
{
  hsv2rgb(a, a);
}
inline void rgb2hsv( Color3 &b, Color3 const &a )
{
  ::base::_rgb2hsv( b[0], b[1], b[2], a[0], a[1], a[2] );
}
inline void rgb2hsv( Color3 &a )
{
  rgb2hsv(a, a);
}

} // namespace base

#endif // base_Color3_INCLUDED
