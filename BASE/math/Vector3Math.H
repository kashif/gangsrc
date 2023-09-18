/* GANG Software
 * BASE/math/Vector3Math.H
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

#ifndef math_Vector3Math_INCLUDED
#define math_Vector3Math_INCLUDED

#include "Vector3.H"

namespace math {

template <class Number>
class Vector3Math
  :
    public Vector3<Number>
{
public:
  // void constructor
  inline Vector3Math();

  // constructor
  inline Vector3Math( Number, Number, Number );

  // constructor
  inline Vector3Math( Number * );

  // copy constructor
  inline Vector3Math( Vector3<Number> const &a );

  // destructor
  inline ~Vector3Math();

  // assignment operators
  inline Vector3Math<Number> &operator=( Vector3<Number> const &a );

  // R^3 OPERATIONS


  // det(a, b, c)
  static inline Number
  det( Vector3Math<Number> const &a, Vector3Math<Number> const &b,
       Vector3Math<Number> const &c );

  /*
     area of (unoriented) triangle with vertices a, 0, b
     returns value in [0,infty)
  */
  static inline Number
  area( Vector3Math<Number> const &a, Vector3Math<Number> const &b );

  /*
     area of (unoriented) triangle with vertices a, b, c
     returns value in [0,infty)
  */
  static inline Number
  area( Vector3Math<Number> const &a, Vector3Math<Number> const &b,
        Vector3Math<Number> const &c );

  /*
     returns the (unoriented) angle from 0a to 0b (0=origin)
     returned value in [0,pi)
  */
  static inline Number
  angle( Vector3Math<Number> const &a, Vector3Math<Number> const &b );

  /*
     returns the (unoriented) angle from oa to ob
     returned value in [0,pi)
  */
  static inline Number
  angle( Vector3Math<Number> const &a, Vector3Math<Number> const &o,
         Vector3Math<Number> const &b );

  // c = oa cross ob
  inline void
  cross( Vector3Math<Number> const &a, Vector3Math<Number> const &b );

  // returns normal to plane containing points a, b, c
  inline int
  normal( Vector3Math<Number> const &, Vector3Math<Number> const &,
          Vector3Math<Number> const & );

  // norm(a)*norm(b) - (a.b)^2
  static inline Number
  cross_norm(Vector3Math<Number> const &, Vector3Math<Number> const & );

  /*
     returns the (unoriented) dihedral angle between the planes
     spanned by a,b,c and a,b,d
  */
  static inline Number
  dihedral_angle( Vector3Math<Number> const &a, Vector3Math<Number> const &b,
                  Vector3Math<Number> const &c, Vector3Math<Number> const &d );

};

template <class Number>
Vector3Math<Number>::
Vector3Math()
    :
    Vector3<Number>()
{
}

template <class Number>
Vector3Math<Number>::
Vector3Math(Number x, Number y, Number z)
    :
    Vector3<Number>(x, y, z)
{
}

template <class Number>
Vector3Math<Number>::
Vector3Math(Number *x)
    :
    Vector3<Number>(x)
{
}

template <class Number>
Vector3Math<Number>::
Vector3Math(Vector3<Number> const &a)
    :
    Vector3<Number>(a)
{
}

template <class Number>
Vector3Math<Number>::
~Vector3Math()
{
}

template <class Number>
Vector3Math<Number> &
Vector3Math<Number>::
operator=(Vector3<Number> const &a)
{
  if (this == &a) { return *this; }
  Vector3<Number>::operator=(a);
  return *this;
}

template <class Number>
Number
Vector3Math<Number>::
det(
  Vector3Math<Number> const &a,
  Vector3Math<Number> const &b,
  Vector3Math<Number> const &c)
{
  return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

template<class Number>
Number
Vector3Math<Number>::
area(
  Vector3Math<Number> const &a,
  Vector3Math<Number> const &b )
{
  return 0.5 * sqrt( cross_norm(a, b) );
}

template<class Number>
Number
Vector3Math<Number>::
area(
  Vector3Math<Number> const &a,
  Vector3Math<Number> const &b,
  Vector3Math<Number> const &c )
{
  return area( a-b, c-b );
}

template<class Number>
Number
Vector3Math<Number>::
angle(
  Vector3Math<Number> const &a,
  Vector3Math<Number> const &b)
{
  Number r = sqrt( a.norm() * b.norm() );
  if (math::effectively_zero(r))
  {
    return Number(0);
  }
  r = dot( a, b ) / r;
  if ( r >= 1.0 ) { return 0.0; }
  else if ( r <= -1.0 ) { return math::pi; }
  else { return acos(r); }
}

template<class Number>
Number
Vector3Math<Number>::
angle(
  Vector3Math<Number> const &a,
  Vector3Math<Number> const &o,
  Vector3Math<Number> const &b )
{
  return angle( a-o, b-o );
}

template<class Number>
void
Vector3Math<Number>::
cross(
  Vector3Math<Number> const &a,
  Vector3Math<Number> const &b )
{
  x = a.y*b.z - a.z*b.y;
  y = a.z*b.x - a.x*b.z;
  z = a.x*b.y - a.y*b.x;
}

template<class Number>
int
Vector3Math<Number>::
normal(
  Vector3Math<Number> const &a,
  Vector3Math<Number> const &b,
  Vector3Math<Number> const &c )
{
  Vector3Math<Number> u, v, w;
  u.cross( a, b );
  v.cross( b, c );
  w.cross( c, a );

  x = u.x + v.x + w.x;
  y = u.y + v.y + w.y;
  z = u.z + v.z + w.z;

  return normalize();
}

template<class Number>
Number
Vector3Math<Number>::
cross_norm(
  Vector3Math<Number> const &a,
  Vector3Math<Number> const &b)
{
  return a.norm() * b.norm() - math::sqr(dot(a,b));
}

template<class Number>
Number
Vector3Math<Number>::
dihedral_angle(
  Vector3Math<Number> const &a,
  Vector3Math<Number> const &b,
  Vector3Math<Number> const &c,
  Vector3Math<Number> const &d )
{
  // computes the dihedral angle as the angle between the normals

  Vector3Math<Number> n1, n2;
  n1.normal( a, b, c );
  n2.normal( a, d, b ); // note orientation
  return angle(n1, n2);
}

} // namespace math


#endif // math_Vector3Math_INCLUDED
