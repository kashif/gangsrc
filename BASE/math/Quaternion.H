/* GANG Software
 * BASE/math/Quaternion.H
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

#ifndef math_Quaternion_INCLUDED
#define math_Quaternion_INCLUDED

#include <math.h>
#include <iostream>
#include "Math.H"

namespace math {

#if !defined(NO_TMPL_FRIENDS)
#if (defined(__sgi) && _COMPILER_VERSION >= 730) || defined(__GNUG__)
#define NULL_TMPL_ARGS <>
#else
#define NULL_TMPL_ARGS
#endif

template <class A>
class Quaternion;

template <class A>
A real(Quaternion<A> const &);

template <class A>
A norm(Quaternion<A> const &);

template <class A>
A abs(Quaternion<A> const &);

template <class A>
Quaternion<A> conj(Quaternion<A> const &);

#if 0
template <class A>
Quaternion<A> inv(Quaternion<A> const &a);
#endif

template <class A>
Quaternion<A> operator+(Quaternion<A> const &, Quaternion<A> const &);

template <class A>
Quaternion<A> operator+(A, Quaternion<A> const &);

template <class A>
Quaternion<A> operator-(Quaternion<A> const &);

template <class A>
Quaternion<A> operator-(Quaternion<A> const &, Quaternion<A> const &);

template <class A>
Quaternion<A> operator*(Quaternion<A> const &, Quaternion<A> const &);

template <class A>
Quaternion<A> operator*(A, Quaternion<A> const &);

template <class A>
Quaternion<A> operator*(Quaternion<A> const &, A);

template <class A>
Quaternion<A> operator/(A, Quaternion<A> const &);

template <class A>
Quaternion<A> operator/(Quaternion<A> const &, A);

template <class A>
int operator==(Quaternion<A> const &, Quaternion<A> const &);

template <class A>
int operator!=(Quaternion<A> const &, Quaternion<A> const &);

template <class A>
std::ostream &operator<<( std::ostream &, Quaternion<A> const &);
#endif

/*
   Quaternions.
*/

template <class A>
class Quaternion
{
public:
  typedef A Real;

  inline Quaternion();
  inline Quaternion( A, A, A, A );
  inline Quaternion( A );

  inline Quaternion<A> &operator=( Quaternion<A> const &);
  inline Quaternion<A> &operator=( A );

  inline A &r() { return _w; }
  inline A &i() { return _x; }
  inline A &j() { return _y; }
  inline A &k() { return _z; }
  inline A const &r() const { return _w; }
  inline A const &i() const { return _x; }
  inline A const &j() const { return _y; }
  inline A const &k() const { return _z; }
  inline void r( A r ) { _w = r; }
  inline void i( A i ) { _x = i; }
  inline void j( A j ) { _y = j; }
  inline void k( A k ) { _z = k; }

#if !defined(NO_TMPL_FRIENDS)
  friend A real NULL_TMPL_ARGS
  (Quaternion<A> const &);

  friend A norm NULL_TMPL_ARGS
  (Quaternion<A> const &);
  friend A abs NULL_TMPL_ARGS
  (Quaternion<A> const &);
  friend Quaternion<A> conj NULL_TMPL_ARGS
  (Quaternion<A> const &);

#if 0
  friend Quaternion<A> inv NULL_TMPL_ARGS
  (Quaternion<A> const &a);
#endif
  friend Quaternion<A> operator+ NULL_TMPL_ARGS
  (Quaternion<A> const &, Quaternion<A> const &);
  friend Quaternion<A> operator+ NULL_TMPL_ARGS
  (A, Quaternion<A> const &);
  friend Quaternion<A> operator- NULL_TMPL_ARGS
  (Quaternion<A> const &);
  friend Quaternion<A> operator- NULL_TMPL_ARGS
  (Quaternion<A> const &, Quaternion<A> const &);
  friend Quaternion<A> operator* NULL_TMPL_ARGS
  (Quaternion<A> const &, Quaternion<A> const &);
  friend Quaternion<A> operator* NULL_TMPL_ARGS
  (A, Quaternion<A> const &);
  friend Quaternion<A> operator* NULL_TMPL_ARGS
  (Quaternion<A> const &, A);
  friend Quaternion<A> operator/ NULL_TMPL_ARGS
  (Quaternion<A> const &, A);
  friend Quaternion<A> operator/ NULL_TMPL_ARGS
  (A, Quaternion<A> const & );
  friend int operator== NULL_TMPL_ARGS
  (Quaternion<A> const &, Quaternion<A> const &);
  friend int operator!= NULL_TMPL_ARGS
  (Quaternion<A> const &, Quaternion<A> const &);
#endif

  inline void neg();
  inline void neg( Quaternion<A> const &a );
  inline void inv();
  inline void inv( Quaternion<A> const &a );
  inline void add( Quaternion<A> const &a, Quaternion<A> const &b );
  inline void add( Quaternion<A> const &a );
  inline void sub( Quaternion<A> const &a, Quaternion<A> const &b );
  inline void sub( Quaternion<A> const &a );
  inline void mul( Quaternion<A> const &, Quaternion<A> const &);
  inline void mul( Quaternion<A> const & );
  inline void mulleft( Quaternion<A> const & );
  inline void div( Quaternion<A> const &, Quaternion<A> const &);
  inline void div( Quaternion<A> const & );
  inline void operator+=(Quaternion<A> const &);
  inline void operator-=(Quaternion<A> const &);
  inline void operator*=(Quaternion<A> const &);
  inline void operator*=(A);
  inline void operator/=(Quaternion<A> const &);
  inline void operator/=(A);

#if 0
  // get rotation matrix from *this
  void rotation_matrix( A * ) const;
#endif

  // get 4-by-4 rotation matrix from *this
  void rotation_matrix4( A * ) const;

  // set *this from an angle and axis
  inline void from_angle_axis( A, A, A, A );
  inline void to_angle_axis( A &, A &, A &, A & );

  enum Uninitialized { UNINITIALIZED };
  inline Quaternion( Uninitialized );

#if !defined(NO_TMPL_FRIENDS)
  friend std::ostream &operator<< NULL_TMPL_ARGS
  ( std::ostream &, Quaternion<A> const &);
#endif

  A _w;
  A _x;
  A _y;
  A _z;
};


template <class A>
Quaternion<A>::
Quaternion( Uninitialized )
{
}


template <class A>
Quaternion<A>::
Quaternion()
    : _w(0),_x(0),_y(0),_z(0)
{
}


template <class A>
Quaternion<A>::
Quaternion(A ar, A ai, A aj, A ak)
    : _w(ar),_x(ai),_y(aj),_z(ak)
{
}


template <class A>
Quaternion<A>::
Quaternion(A a)
    : _w(a),_x(0),_y(0),_z(0)
{
}


template <class A>
Quaternion<A> &
Quaternion<A>::
operator=( Quaternion<A> const &a )
{
  _w = a._w;
  _x = a._x;
  _y = a._y;
  _z = a._z;
  return *this;
}


template <class A>
Quaternion<A> &
Quaternion<A>::
operator=( A a )
{
  _w = a;
  _x = 0;
  _y = 0;
  _z = 0;
  return *this;
}

#if !defined(NO_TMPL_FRIENDS)
template <class A>
inline
A
real(Quaternion<A> const &a)
{
  return a._w;
}


template <class A>
inline
A
norm(Quaternion<A> const &a)
{
  return a._w*a._w + a._x*a._x + a._y*a._y + a._z*a._z;
}


template <class A>
inline
A
abs(Quaternion<A> const &a)
{
  return math::sqrt(norm(a));
}


template <class A>
inline
Quaternion<A>
conj(Quaternion<A> const &a)
{
  return Quaternion<A>(a._w,-a._x,-a._y,-a._z);
}


template <class A>
inline
Quaternion<A>
operator+(Quaternion<A> const &a1, Quaternion<A> const &a2)
{
  return Quaternion<A>(a1._w + a2._w, a1._x + a2._x, a1._y + a2._y,
                    a1._z + a2._z);
}


template <class A>
inline
Quaternion<A>
operator+( A a, Quaternion<A> const &b)
{
  return Quaternion<A>(a + b._w,b._x,b._y,b._z);
}


template <class A>
inline
Quaternion<A>
operator-(Quaternion<A> const &a)
{
  return Quaternion<A>(-a._w,-a._x,-a._y,-a._z);
}


template <class A>
inline
Quaternion<A>
operator-(Quaternion<A> const &a1,Quaternion<A> const &a2)
{
  return Quaternion<A>(
    a1._w - a2._w, a1._x - a2._x, a1._y - a2._y, a1._z - a2._z);
}


template <class A>
inline
Quaternion<A>
operator*(Quaternion<A> const &a,Quaternion<A> const &b)
{
  A a1( (a._z - a._y)*(b._y - b._z) );
  A a2( (a._w + a._x)*(b._w + b._x) );
  A a3( (a._w - a._x)*(b._y + b._z) );
  A a4( (a._y + a._z)*(b._w - b._x) );
  A b1( -(a._x - a._z)*(b._x - b._y) );
  A b2( -(a._x + a._z)*(b._x + b._y) );
  A b3( (a._w + a._y)*(b._w - b._z) );
  A b4( (a._w - a._y)*(b._w + b._z) );

  return Quaternion<A>(
    a1 + 0.5*(b1 + b2 + b3 + b4),
    a2 + 0.5*(b1 + b2 - b3 - b4),
    a3 + 0.5*(b1 - b2 + b3 - b4),
    a4 + 0.5*(b1 - b2 - b3 + b4) );
}

template <class A>
inline
Quaternion<A>
operator*(A a, Quaternion<A> const &b)
{
  return Quaternion<A>( a*b._w, a*b._x, a*b._y, a*b._z );
}


template <class A>
inline
Quaternion<A>
operator*(Quaternion<A> const &b, A a)
{
  return Quaternion<A>( a*b._w, a*b._x, a*b._y, a*b._z );
}

template <class A>
inline
Quaternion<A>
operator/(A a, Quaternion<A> const &b)
{
  Quaternion<A> x = b;
  x.inv();
  return x * a;
}


template <class A>
inline
Quaternion<A>
operator/(Quaternion<A> const &b, A a)
{
  // NOTE: fails if A is an entry in b
  return Quaternion<A>( b._w/a, b._x/a, b._y/a, b._z/a );
}

#if 0
template <class A>
inline
Quaternion<A>
inv(Quaternion<A> const &a)
{
  return( conj(a)/norm(a) );
}
#endif

template <class A>
inline
int
operator==(Quaternion<A> const &a, Quaternion<A> const &b)
{
  return a._w==b._w && a._x==b._x && a._y==b._y && a._z==b._z;
}


template <class A>
inline
int
operator!=(Quaternion<A> const &a, Quaternion<A> const &b)
{
  return a._w!=b._w || a._x!=b._x || a._z!=b._z || a._y!=b._y;
}
#endif


template <class A>
void
Quaternion<A>::
operator+=(Quaternion<A> const &a)
{
  _w += a._w;
  _x += a._x;
  _y += a._y;
  _z += a._z;
}


template <class A>
void
Quaternion<A>::
operator-=(Quaternion<A> const &a)
{
  _w -= a._w;
  _x -= a._x;
  _y -= a._y;
  _z -= a._z;
}

template <class A>
void
Quaternion<A>::
mul( Quaternion<A> const &a, Quaternion<A> const &b )
{
  A a1( (a._z - a._y)*(b._y - b._z) );
  A a2( (a._w + a._x)*(b._w + b._x) );
  A a3( (a._w - a._x)*(b._y + b._z) );
  A a4( (a._y + a._z)*(b._w - b._x) );
  A b1( -(a._x - a._z)*(b._x - b._y) );
  A b2( -(a._x + a._z)*(b._x + b._y) );
  A b3( (a._w + a._y)*(b._w - b._z) );
  A b4( (a._w - a._y)*(b._w + b._z) );

  *this = Quaternion<A>(
    a1 + 0.5*(b1 + b2 + b3 + b4),
    a2 + 0.5*(b1 + b2 - b3 - b4),
    a3 + 0.5*(b1 - b2 + b3 - b4),
    a4 + 0.5*(b1 - b2 - b3 + b4) );
}


template <class A>
inline
void
Quaternion<A>::
mul( Quaternion<A> const &a )
{
  *this = *this * a;
}

template <class A>
inline
void
Quaternion<A>::
mulleft( Quaternion<A> const &a )
{
  *this = a * *this;
}

template <class A>
void
Quaternion<A>::
operator*=( A a )
{
  *this = a * *this;
}

template <class A>
void
Quaternion<A>::
operator*=( Quaternion<A> const &a )
{
  A a1( (_z - _y)*(a._y - a._z) );
  A a2( (_w + _x)*(a._w + a._x) );
  A a3( (_w - _x)*(a._y + a._z) );
  A a4( (_y + _z)*(a._w - a._x) );
  A b1( -(_x - _z)*(a._x - a._y) );
  A b2( -(_x + _z)*(a._x + a._y) );
  A b3( (_w + _y)*(a._w - a._z) );
  A b4( (_w - _y)*(a._w + a._z) );

  *this = Quaternion<A>(
    a1 + 0.5*(b1 + b2 + b3 + b4),
    a2 + 0.5*(b1 + b2 - b3 - b4),
    a3 + 0.5*(b1 - b2 + b3 - b4),
    a4 + 0.5*(b1 - b2 - b3 + b4) );
}


template <class A>
void
Quaternion<A>::
inv( Quaternion<A> const &a )
{
  using math::sqr;
  A d = sqr(a._w) + sqr(a._x) + sqr(a._y) + sqr(a._z);
  _w = a._w / d;
  _x = -a._x / d;
  _y = -a._y / d;
  _z = -a._z / d;
}


template <class A>
void
Quaternion<A>::
operator/=( Quaternion<A> const &a )
{
  DIE();
}

template <class A>
void
Quaternion<A>::
operator/=( A a )
{
  // NOTE: fails if a is a component of a
  *this = *this / a;
}


template <class A>
void
Quaternion<A>::
add(Quaternion<A> const &a, Quaternion<A> const &b)
{
  _w = a._w + b._w;
  _x = a._x + b._x;
  _y = a._y + b._y;
  _z = a._z + b._z;
}

template <class A>
void
Quaternion<A>::
div(Quaternion<A> const &a, Quaternion<A> const &b)
{
  *this = a / b;
}

template <class A>
void
Quaternion<A>::
div( Quaternion<A> const &b )
{
  *this = *this / b;
}

#if 0
template <class A>
void
Quaternion<A>::
rotation_matrix( A *a ) const
{
  a[0][0] = 1.0 - 2.0 * (_y * _y+_z * _z);
  a[0][1] = 2.0 * (_x * _y-_z * _w);
  a[0][2] = 2.0 * (_x * _z+_y * _w);
  a[1][0] = 2.0 * (_x * _y+_z * _w);
  a[1][1] = 1.0 -2.0 * (_x * _x+_z * _z);
  a[1][2] = 2.0 * (_y * _z-_x * _w);
  a[2][0] = 2.0 * (_x * _z-_y * _w);
  a[2][1] = 2.0 * (_y * _z+_x * _w);
  a[2][2] = 1.0 - 2.0 * (_x * _x+_y * _y)
}
#endif

template <class A>
void
Quaternion<A>::
rotation_matrix4( A *a ) const
{
  // in opengl order
  a[0] = 1.0 - 2.0 * (_y * _y + _z * _z);
  a[4] = 2.0 * (_x * _y-_z * _w);
  a[8] = 2.0 * (_x * _z +_y * _w);
  a[12]= 0;

  a[1] = 2.0 * (_x * _y +_z * _w);
  a[5] = 1.0 - 2.0 * (_x * _x + _z * _z);
  a[9] = 2.0 * (_y * _z - _x * _w);
  a[13]= 0;

  a[2] = 2.0 * (_x * _z - _y * _w);
  a[6] = 2.0 * (_y * _z + _x * _w);
  a[10]= 1.0 - 2.0 * (_x * _x + _y * _y);
  a[14]= 0;

  a[3] = 0;
  a[7] = 0;
  a[11]= 0;
  a[15]= 1.0;
}


template <class A>
void
Quaternion<A>::
from_angle_axis( A angle, A x1, A x2, A x3 )
{
  // q = cos(angle) + sin(angle) * v/|v|

  angle = 0.5 * angle;
  _w = math::cos(angle);
  A s = math::sin(angle) / math::abs(x1, x2, x3);
  _x = s * x1;
  _y = s * x2;
  _z = s * x3;
}


template <class A>
void
Quaternion<A>::
to_angle_axis( A &angle, A &x1, A &x2, A &x3 )
{
  angle = 2.0 * math::acos( _w );
  A s = math::sqrt( 1.0 - math::sqr(_w) );

  if ( effectively_zero(s) ) { x1 = 1; x2 = 0; x3 = 0; }
  else
  {
    x1 = _x / s;
    x2 = _y / s;
    x3 = _z / s;
  }
}


#if !defined(NO_TMPL_FRIENDS)
template<class A>
inline
std::ostream &
operator<<( std::ostream &o, Quaternion<A> const &q )
{
  o << "(" << q._w << ", " << q._x << ", " << q._y << ", " << q._z << ")";
  return o;
}
#endif

} // namespace math

#endif // math_Quaternion_INCLUDED
