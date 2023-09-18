/* GANG Software
 * BASE/math/Vector2Math.H
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

#ifndef math_Vector2Math_INCLUDED
#define math_Vector2Math_INCLUDED

#include "Vector2.H"

namespace math {

template <class Number>
class Vector2Math
  :
    public Vector2<Number>
{
public:

  // void constructor
  inline Vector2Math();

  // constructor
  inline Vector2Math( Number, Number, Number );

  // constructor
  inline Vector2Math( Number * );

  // copy constructor
  inline Vector2Math( Vector2<Number> const &a );

  // destructor
  inline ~Vector2Math();

  // assignment operators
  inline Vector2Math<Number> &operator=( Vector2<Number> const &a );


  // R^2 OPERATIONS

  // returns perpendicular base::vector (rotated right 90 degrees)
  inline Vector2Math<Number> perp();

  static inline Number det(
    Vector2Math<Number> const &a,
    Vector2Math<Number> const &b );

  /*
     Returns twice the area of the oriented triangle (a, b, c), i.e., the
     area is positive if the triangle is oriented counterclockwise.
  */
  static inline Number det(
    Vector2Math<Number> const &a,
    Vector2Math<Number> const &b,
    Vector2Math<Number> const &c);

  // Returns true if the points a, b, c are in a counterclockwise order
  static inline bool ccw(
    Vector2Math<Number> const &a,
    Vector2Math<Number> const &b,
    Vector2Math<Number> const &c);

  // Returns true if the points a, b, c are in a clockwise order
  static inline bool cw(
    Vector2Math<Number> const &a,
    Vector2Math<Number> const &b,
    Vector2Math<Number> const &c);

  static inline Number angle(
    Vector2Math<Number> const &a,
    Vector2Math<Number> const &b );

  static inline Number angle(
    Vector2Math<Number> const &a,
    Vector2Math<Number> const &o,
    Vector2Math<Number> const &b );

  static bool inCircle(
    Vector2Math<Number> const & a,
    Vector2Math<Number> const & b,
    Vector2Math<Number> const & c,
    Vector2Math<Number> const & d);

  // Returns the center of the circle through points a, b, c.
  static Vector2Math<Number> circumcenter(
    Vector2Math<Number> const & a,
    Vector2Math<Number> const & b,
    Vector2Math<Number> const & c);

  static inline bool same_side(
    Vector2Math<Number> const &a,
    Vector2Math<Number> const &b,
    Vector2Math<Number> const &x,
    Vector2Math<Number> const &y );

  static inline bool opposite(
    Vector2Math<Number> const &a,
    Vector2Math<Number> const &b,
    Vector2Math<Number> const &x,
    Vector2Math<Number> const &y );

  static inline bool
  intersect(
    Vector2Math<Number> const &a1,
    Vector2Math<Number> const &a2,
    Vector2Math<Number> const &b1,
    Vector2Math<Number> const &b2 );

  // returns the intersection of a1<->a2, b1<->b2
  static inline Vector2Math<Number>
  intersection(
    Vector2Math<Number> const &a1,
    Vector2Math<Number> const &a2,
    Vector2Math<Number> const &b1,
    Vector2Math<Number> const &b2 );

};

template <class Number>
Vector2Math<Number>::
Vector2Math()
    :
    Vector2<Number>()
{
}

template <class Number>
Vector2Math<Number>::
Vector2Math(Number x, Number y, Number z)
    :
    Vector2<Number>(x, y, z)
{
}

template <class Number>
Vector2Math<Number>::
Vector2Math(Number *x)
    :
    Vector2<Number>(x)
{
}

template <class Number>
Vector2Math<Number>::
Vector2Math(Vector2<Number> const &a)
    :
    Vector2<Number>(a)
{
}

template <class Number>
Vector2Math<Number>::
~Vector2Math()
{
}

template <class Number>
Vector2Math<Number> &
Vector2Math<Number>::
operator=(Vector2<Number> const &a)
{
  if (this == &a) { return *this; }
  Vector2<Number>::operator=(a);
  return *this;
}

template <class Number>
Number
Vector2Math<Number>::
det(
  Vector2Math<Number> const &a,
  Vector2Math<Number> const &b )
{
  return a.x * b.y - a.y * b.x;
}

template <class Number>
Number
Vector2Math<Number>::
det(
  Vector2Math<Number> const &a,
  Vector2Math<Number> const &b,
  Vector2Math<Number> const &c)
{
  return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

template <class Number>
bool
Vector2Math<Number>::
ccw(
  Vector2Math<Number> const &a,
  Vector2Math<Number> const &b,
  Vector2Math<Number> const &c)
{
  return det(a, b, c) > 0.0;
}

template <class Number>
bool
Vector2Math<Number>::
cw(
  Vector2Math<Number> const &a,
  Vector2Math<Number> const &b,
  Vector2Math<Number> const &c)
{
  return det(a, b, c) < 0.0;
}


template <class Number>
bool
Vector2Math<Number>::
inCircle(Vector2Math<Number> const &a, Vector2Math<Number> const &b,
         Vector2Math<Number> const &c, Vector2Math<Number> const &d)
{
  Number az = a.norm();
  Number bz = b.norm();
  Number cz = c.norm();
  Number dz = d.norm();

  Number e = az * det(b, c, d) - bz * det(a, c, d) +
    cz * det(a, b, d) - dz * det(a, b, c);

  return (e > 0.0);
}


template <class Number>
Vector2Math<Number>
Vector2Math<Number>::
circumcenter(
  Vector2Math<Number> const &a,
  Vector2Math<Number> const &b,
  Vector2Math<Number> const &c)
{
  // From Graphics Gems I, p.22

  Number d1, d2, d3, c1, c2, c3;

  d1 = dot( b - a, c - a );
  d2 = dot( b - c, a - c );
  d3 = dot( a - b, c - b );
  c1 = d2 * d3;
  c2 = d3 * d1;
  c3 = d1 * d2;

  return ((c2 + c3)*a + (c3 + c1)*c + (c1 + c2)*b) / (2*(c1 + c2 + c3));
}

template <class Number>
Number
Vector2Math<Number>::
angle(
  Vector2Math<Number> const &a,
  Vector2Math<Number> const &b )
{
  return atan2( det(a,b), dot(a,b) );
}


template <class Number>
Number
Vector2Math<Number>::
angle(
  Vector2Math<Number> const &a,
  Vector2Math<Number> const &o,
  Vector2Math<Number> const &b )
{
  return angle( a-o, b-o );
}

template <class Number>
Vector2Math<Number>
Vector2Math<Number>::
perp()
{
  return Vector2Math<Number>( -y, x );
}

template <class Number>
bool
Vector2Math<Number>::
same_side(
  Vector2Math<Number> const &a,
  Vector2Math<Number> const &b,
  Vector2Math<Number> const &x,
  Vector2Math<Number> const &y )
{
  // returns true iff x, y are on the same side of the line thru a, b
  return cw(a,b,x) && cw(a,b,y) || cw(b,a,x) && cw(b,a,y);
}

template <class Number>
bool
Vector2Math<Number>::
opposite(
  Vector2Math<Number> const &a,
  Vector2Math<Number> const &b,
  Vector2Math<Number> const &x,
  Vector2Math<Number> const &y )
{
  // returns true iff x, y are on opposite sided of the line thru a, b
  return cw(a,b,x) && cw(b,a,y) || cw(a,b,y) && cw(b,a,x);
}

template <class Number>
bool
Vector2Math<Number>::
intersect(
  Vector2Math<Number> const &a1,
  Vector2Math<Number> const &a2,
  Vector2Math<Number> const &b1,
  Vector2Math<Number> const &b2 )
{
  // returns true iff the segements a1<->a2 and b1<->b2 intersect
  return opposite(a1,a2,b1,b2) && opposite(b1,b2,a1,a2);
}

template <class Number>
Vector2Math<Number>
Vector2Math<Number>::
intersection(
  Vector2Math<Number> const &a1,
  Vector2Math<Number> const &a2,
  Vector2Math<Number> const &b1,
  Vector2Math<Number> const &b2 )
{
  Vector2Math<Number> const &a = a2-a1;
  Vector2Math<Number> const &b = b1-a1;
  Vector2Math<Number> const &c = b2-a1;

  Number d = (-b.y*c.x + b.x*c.y) /
    (a.y*b.x - a.x*b.y - a.y*c.x + a.x*c.y);

  Vector2Math<Number> r;
  r.x = a.x * d;
  r.y = a.y * d;

  return r + a1;
}

} // namespace math

#endif // math_Vector2Math_INCLUDED
