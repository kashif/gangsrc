/* GANG Software
 * BASE/base/Color4.H
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

#ifndef base_Color4_INCLUDED
#define base_Color4_INCLUDED

#include "ArrayX.H"
#include "ColorBase.H"

namespace base {

class Color4
  :
    public ArrayX<float,4U>
{

public:
  // constructor
  Color4()
      :
      ArrayX<float,4U>()
    { set(0.0f); }

  // constructor
  Color4( float a0, float a1, float a2, float a3 )
      :
      ArrayX<float,4U>()
    { _[0] = a0; _[1] = a1; _[2] = a2; _[3] = a3; }

  // copy constructor
  Color4( Color4 const &a )
      :
      ArrayX<float,4U>(a) {}

  // copy constructor
  Color4( float const *a )
      :
      ArrayX<float,4U>(a) {}

  // destructor
  virtual ~Color4() {}

  // assignment operator
  Color4 &operator=( Color4 const &a )
    { ArrayX<float,4U>::operator=(a); return *this; }

  float &red() { return operator[](0); }
  float &green() { return operator[](1); }
  float &blue() { return operator[](2); }
  float &alpha() { return operator[](3); }
  float &hue() { return operator[](0); }
  float &val() { return operator[](1); }
  float &sat() { return operator[](2); }

  float const &red() const { return operator[](0); }
  float const &green() const { return operator[](1); }
  float const &blue() const { return operator[](2); }
  float const &alpha() const { return operator[](3); }
  float const &hue() const { return operator[](0); }
  float const &val() const { return operator[](1); }
  float const &sat() const { return operator[](2); }

protected:

private:

};

inline void hsv2rgb( Color4 &b, Color4 const &a )
{
  ::base::_hsv2rgb( b[0], b[1], b[2], a[0], a[1], a[2] );
  b[3] = a[3];
}
inline void hsv2rgb( Color4 &a )
{
  hsv2rgb(a, a);
}
inline void rgb2hsv( Color4 &b, Color4 const &a )
{
  ::base::_rgb2hsv( b[0], b[1], b[2], a[0], a[1], a[2] );
  b[3] = a[3];
}
inline void rgb2hsv( Color4 &a )
{
  rgb2hsv(a, a);
}

} // namespace base

#endif // base_Color4_INCLUDED
