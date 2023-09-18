/* GANG Software
 * BASE/math/Vector3.H
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

#ifndef math_Vector3_INCLUDED
#define math_Vector3_INCLUDED

#include <iostream>
#include "Math.H"

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1174
#pragma set woff 1375 // The destructor for class is not virtual.
#endif

namespace math {

#if !defined(NO_TMPL_FRIENDS)
#if (defined(__sgi) && _COMPILER_VERSION >= 730) || defined(__GNUG__)
#define NULL_TMPL_ARGS <>
#else
#define NULL_TMPL_ARGS
#endif

template <class Number>
class Vector3;

template <class Number>
inline Vector3<Number> operator*( Number , Vector3<Number> const & );

template <class Number>
std::ostream &operator<<( std::ostream &o, Vector3<Number> const &a );
#endif

/*
  Fixed-length base::vector class.
  Length N and entries in class Number.
*/

template <class Number>
class Vector3
{
public:

  // void constructor
  inline Vector3();

  // constructor
  inline Vector3( Number, Number, Number );

  // constructor
  inline Vector3( Number * );

  // copy constructor
  inline Vector3( Vector3<Number> const &a );

  // destructor
  inline ~Vector3();

  // assignment operators
  inline Vector3<Number> &operator=( Vector3<Number> const &a );

  // get the i'th element
  inline Number &operator[](uint i);

  // get the i'th element
  inline Number const &operator[](uint i) const;

  // set to Number
  inline void set( Number );

  // comparison
  inline bool operator==( Vector3<Number> const &a );
  inline bool operator!=( Vector3<Number> const &a );

  // fuzzy comparison
  static inline bool equal(
    Vector3<Number> const &a,
    Vector3<Number> const &b,
    Number epsilon );

  // negation: *this = - *this
  inline void neg();

  // negation: *this = - a
  inline void neg( Vector3<Number> const &a );

  // *this += a
  inline void add( Vector3<Number> const &a );

  // *this = a + b
  inline void add( Vector3<Number> const &a, Vector3<Number> const &b );

  // *this -= a
  inline void sub( Vector3<Number> const &a );

  // *this = a - b
  inline void sub( Vector3<Number> const &a, Vector3<Number> const &b );

  // *this *= a
  inline void mul( Number a );

  // *this = a * b
  inline void mul( Number a, Vector3<Number> const &b );

  // *this = a * b
  inline void mul( Vector3<Number> const &a, Number b );

  // *this = a + b * c
  inline void mul_add(
    Vector3<Number> const &a, Number b, Vector3<Number> const &c );

  // *this += a * b
  inline void mul_add( Number a, Vector3<Number> const &b );

  // *this /= a
  inline void div( Number a );

  // *this = a / b
  inline void div( Vector3<Number> const &a, Number b );

  //
  inline void operator+=( Vector3<Number> const &a ) { this->add(a); }
  //
  inline void operator-=( Vector3<Number> const &a ) { this->sub(a); }
  //
  inline void operator*=( Number a ) { this->mul(a); }
  //
  inline void operator/=( Number a ) { this->div(a); }

  inline Vector3<Number> operator+() const;
  //
  inline Vector3<Number> operator-() const;
  //
  inline Vector3<Number> operator+( Vector3<Number> const & ) const;
  //
  inline Vector3<Number> operator-( Vector3<Number> const & ) const;

  //
  inline Vector3<Number> operator/( Number ) const;

#if !defined(NO_TMPL_FRIENDS)
  friend Vector3<Number> operator* NULL_TMPL_ARGS
  ( Number, Vector3<Number> const & );

  friend Vector3<Number> operator* NULL_TMPL_ARGS
  ( Vector3<Number> const &, Number );
#endif

#if 0
  //
  inline Vector3<Number> operator*( Number ) const;
#endif

  inline Number norm() const;

  inline Number abs() const;

  // *this := *this/|*this|
  // returns 0/1 on success/failure
  inline int normalize();

  static inline Vector3<Number> midpoint(
    Vector3<Number> const &,
    Vector3<Number> const & );

  // |a-b|
  static inline Number
  length( Vector3<Number> const &a, Vector3<Number> const &b );

  // a.b
  static inline Number
  dot( Vector3<Number> const &a, Vector3<Number> const &b );

#if !defined(NO_TMPL_FRIENDS)
  // write to stream
  friend std::ostream &operator<< NULL_TMPL_ARGS
  ( std::ostream &o, Vector3<Number> const &a );
#endif

  Number *data() { return &x; }
  Number const *data() const { return &x; }

  // public data
  Number x, y, z;
};


template <class Number>
Vector3<Number>::
Vector3()
    :
    x(0),
    y(0),
    z(0)
{
}

template <class Number>
Vector3<Number>::
Vector3( Number x_, Number y_, Number z_ )
    :
    x(x_),
    y(y_),
    z(z_)
{
}

template <class Number>
Vector3<Number>::
Vector3( Number *p )
    :
    x(p[0]),
    y(p[1]),
    z(p[2])
{
}

template <class Number>
Vector3<Number>::
Vector3( Vector3<Number> const &a )
    :
    x(a.x),
    y(a.y),
    z(a.z)
{
}

template <class Number>
Vector3<Number>::
~Vector3()
{
}

template <class Number>
Vector3<Number> &
Vector3<Number>::
operator=( Vector3<Number> const &a )
{
  if ( this == &a ) { return *this; }
  x = a.x;
  y = a.y;
  z = a.z;
  return *this;
}

template<class Number>
Number &
Vector3<Number>::
operator[](uint i)
{
  return (&x)[i];
}

template<class Number>
Number const &
Vector3<Number>::
operator[](uint i) const
{
  return (&x)[i];
}

template <class Number>
void
Vector3<Number>::
set( Number a )
{
  x = a;
  y = a;
  z = a;
}

template <class Number>
bool
Vector3<Number>::
operator==( Vector3<Number> const &a )
{
  return x == a.x && y == a.y && z == a.z;
}

template <class Number>
bool
Vector3<Number>::
operator!=( Vector3<Number> const &a )
{
  return x != a.x || y != a.y || z != a.z;
}

template <class Number>
bool
Vector3<Number>::
equal(
  Vector3<Number> const &a,
  Vector3<Number> const &b,
  Number epsilon )
{
  Number x = ::abs(a.x - b.x);
  if ( x > epsilon ) { return false; }

  Number y = ::abs(a.y - b.y);
  if ( y > epsilon ) { return false; }

  Number z = ::abs(a.z - b.z);
  if ( z > epsilon ) { return false; }

  return math::sqr(x) + math::sqr(y) + math::sqr(z) < math::sqr(epsilon);
}

template <class Number>
void
Vector3<Number>::
neg()
{
  x = -x;
  y = -y;
  z = -z;
}

template <class Number>
void
Vector3<Number>::
neg( Vector3<Number> const &a )
{
  x = -a.x;
  y = -a.y;
  z = -a.z;
}

template <class Number>
void
Vector3<Number>::
add( Vector3<Number> const &a )
{
  x += a.x;
  y += a.y;
  z += a.z;
}

template <class Number>
void
Vector3<Number>::
add( Vector3<Number> const &a, Vector3<Number> const &b )
{
  x = a.x + b.x;
  y = a.y + b.y;
  z = a.z + b.z;
}

template <class Number>
void
Vector3<Number>::
sub( Vector3<Number> const &a )
{
  x -= a.x;
  y -= a.y;
  z -= a.z;
}

template <class Number>
void
Vector3<Number>::
sub( Vector3<Number> const &a, Vector3<Number> const &b )
{
  x = a.x - b.x;
  y = a.y - b.y;
  z = a.z - b.z;
}

template <class Number>
void
Vector3<Number>::
mul( Number a )
{
  x *= a;
  y *= a;
  z *= a;
}

template <class Number>
void
Vector3<Number>::
mul( Vector3<Number> const &a, Number b )
{
  x = a.x * b;
  y = a.y * b;
  z = a.z * b;
}

template <class Number>
void
Vector3<Number>::
mul( Number a, Vector3<Number> const &b )
{
  x = a * b.x;
  y = a * b.y;
  z = a * b.z;
}

template <class Number>
void
Vector3<Number>::
div( Number a )
{
  x /= a;
  y /= a;
  z /= a;
}

template <class Number>
void
Vector3<Number>::
div( Vector3<Number> const &a, Number b )
{
  x = a.x / b;
  y = a.y / b;
  z = a.z / b;
}

template <class Number>
Number
Vector3<Number>::
norm() const
{
  return math::sqr(x) + math::sqr(y) + math::sqr(z);
}

template <class Number>
Number
Vector3<Number>::
abs() const
{
  return math::sqrt(norm());
}

template <class Number>
int
Vector3<Number>::
normalize()
{
  Number r = abs();
  if (math::effectively_zero(r))
  {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    return 1;
  }
  x /= r;
  y /= r;
  z /= r;
  return 0;
}

template <class Number>
void
Vector3<Number>::
mul_add(
  Vector3<Number> const &a,
  Number b,
  Vector3<Number> const &c )
{
  x = a.x + b * c.x;
  y = a.y + b * c.y;
  z = a.z + b * c.z;
}

template <class Number>
void
Vector3<Number>::
mul_add(
  Number a, Vector3<Number> const &b )
{
  x = a * b.x;
  y = a * b.y;
  z = a * b.z;
}

#if !defined(NO_TMPL_FRIENDS)
// write a to stream o
template <class Number>
inline
std::ostream &
operator<<( std::ostream &o, Vector3<Number> const &a )
{
  o << "{ " << a.x << ", " << a.y << ", " << a.z << "}";
  return o;
}
#endif

template <class Number>
Vector3<Number>
Vector3<Number>::
midpoint(
  Vector3<Number> const &a,
  Vector3<Number> const &b )
{
  Vector3<Number> tmp(a);
  tmp.add(b);
  tmp.mul(0.5);
  return tmp;
}

template <class Number>
Vector3<Number>
Vector3<Number>::
operator+() const
{
  // unitary +
  return *this;
}

template <class Number>
Vector3<Number>
Vector3<Number>::
operator-() const
{
  // unitary -
  Vector3<Number> tmp(*this);
  tmp.neg();
  return tmp;
}

template <class Number>
Vector3<Number>
Vector3<Number>::
operator+( Vector3<Number> const &a ) const
{
  Vector3<Number> tmp(*this);
  tmp.add(a);
  return tmp;
}

template <class Number>
Vector3<Number>
Vector3<Number>::
operator-( Vector3<Number> const &a ) const
{
  Vector3<Number> tmp(*this);
  tmp.sub(a);
  return tmp;
}

#if !defined(NO_TMPL_FRIENDS)
template <class Number>
Vector3<Number>
operator*( Number a, Vector3<Number> const &v )
{
  Vector3<Number> tmp(v);
  tmp.mul(a);
  return tmp;
}

template <class Number>
Vector3<Number>
operator*( Vector3<Number> const &v, Number a )
{
  Vector3<Number> tmp(v);
  tmp.mul(a);
  return tmp;
}
#endif

#if 0
template <class Number>
Vector3<Number>
Vector3<Number>::
operator*( Number a ) const
{
  Vector3<Number> tmp(*this);
  tmp.mul(a);
  return tmp;
}
#endif

#if !defined(NO_TMPL_FRIENDS)
template <class Number>
inline
Vector3<Number>
operator*(
  Vector3<Number> const &a,
  Vector3<Number> const &b )
{
  Vector3<Number> tmp(b);
  tmp.mul(a);
  return tmp;
}
#endif

template <class Number>
Vector3<Number>
Vector3<Number>::
operator/( Number a ) const
{
  Vector3<Number> tmp(*this);
  tmp.div(a);
  return tmp;
}

template<class Number>
Number
Vector3<Number>::
length(
  Vector3<Number> const &a,
  Vector3<Number> const &b )
{
  return (a-b).abs();
}

template <class Number>
Number
Vector3<Number>::
dot( Vector3<Number> const &a, Vector3<Number> const &b )
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

} // namespace math

#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#pragma reset woff 1375 // The destructor for class is not virtual.
#endif

#endif // math_Vector3_INCLUDED
