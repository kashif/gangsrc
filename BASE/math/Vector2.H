/* GANG Software
 * BASE/math/Vector2.H
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

#ifndef math_Vector2_INCLUDED
#define math_Vector2_INCLUDED

#include <iostream>
#include <math.h>
#include "Math.H"

#if defined(__sgi) && !defined(__GNUG__)
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
class Vector2;

template <class Number>
Vector2<Number>
operator*( Number, Vector2<Number> const & );

template <class Number>
Vector2<Number>
operator*( Vector2<Number> const &, Number );

template <class Number>
std::ostream &
operator<<( std::ostream &o, Vector2<Number> const &a );
#endif

/*
  Fixed-length base::vector class.
  Length N and entries in class Number.
*/

template <class Number>
class Vector2
{
public:

  // void constructor
  inline Vector2();

  // constructor
  inline Vector2( Number, Number );

  // constructor
  inline Vector2( Number * );

  // copy constructor
  inline Vector2( Vector2<Number> const &a );

  // destructor
  inline ~Vector2();

  // assignment operator
  inline Vector2<Number> &operator=( Vector2<Number> const &a );

  // get the i'th element
  inline Number &operator[](uint i);

  // get the i'th element
  inline Number const &operator[](uint i) const;

  // set to Number
  inline void set( Number );

  inline bool operator==( Vector2<Number> const &a );
  inline bool operator!=( Vector2<Number> const &a );
  static inline bool
  equal( Vector2<Number> const &a, Vector2<Number> const &b, Number epsilon );

  // math methods

  // negation: *this = - *this
  inline void neg();

  // negation: *this = - a
  inline void neg( Vector2<Number> const &a );

  // *this += a
  inline void add( Vector2<Number> const &a );

  // *this = a + b
  inline void add( Vector2<Number> const &a, Vector2<Number> const &b );

  // *this -= a
  inline void sub( Vector2<Number> const &a );

  // *this = a - b
  inline void sub( Vector2<Number> const &a, Vector2<Number> const &b );

  // *this *= a
  inline void mul( Number a );

  // *this = a * b
  inline void mul( Number a, Vector2<Number> const &b );

  // *this = a * b
  inline void mul( Vector2<Number> const &a, Number b );

  // *this = a + b * c
  inline void mul_add(
    Vector2<Number> const &a, Number b, Vector2<Number> const &c );

  // *this += a * b
  inline void mul_add( Number a, Vector2<Number> const &b );

  // *this /= a
  inline void div( Number a );

  // *this = a / b
  inline void div( Vector2<Number> const &a, Number b );

  // return dot_product( *this, a )
  static inline Number
  dot( Vector2<Number> const &a, Vector2<Number> const &b );

  //
  inline Number norm() const;

  //
  inline Number abs() const;

  inline void normalize();

  static inline Vector2<Number> midpoint(
    Vector2<Number> const &,
    Vector2<Number> const & );

  // operator versions

  inline void operator+=( Vector2<Number> const &a ) { this->add(a); }
  //
  inline void operator-=( Vector2<Number> const &a ) { this->sub(a); }
  //
  inline void operator*=( Number a ) { this->mul(a); }
  //
  inline void operator/=( Number a ) { this->div(a); }

  // inefficient versions

  inline Vector2<Number> operator+() const;
  //
  inline Vector2<Number> operator-() const;
  //
  inline Vector2<Number> operator+( Vector2<Number> const & ) const;
  //
  inline Vector2<Number> operator-( Vector2<Number> const & ) const;
  //

#if !defined(NO_TMPL_FRIENDS)
  friend Vector2<Number> operator* NULL_TMPL_ARGS
  ( Number, Vector2<Number> const & );

  friend Vector2<Number> operator* NULL_TMPL_ARGS
  ( Vector2<Number> const &, Number );
#endif

#if 0
  inline Vector2<Number> operator*( Number ) const;
#endif

  //
  inline Vector2<Number> operator/( Number ) const;

#if !defined(NO_TMPL_FRIENDS)
  friend std::ostream &operator<< NULL_TMPL_ARGS
  ( std::ostream &o, Vector2<Number> const &a );
#endif

  Number *data() { return &x; }
  Number const *data() const { return &x; }

  Number x, y;
};


template <class Number>
Vector2<Number>::
Vector2()
    :
    x(0),
    y(0)
{
}

template <class Number>
Vector2<Number>::
Vector2( Number x_, Number y_ )
    :
    x(x_),
    y(y_)
{
}

template <class Number>
Vector2<Number>::
Vector2( Number *p )
    :
    x(p[0]),
    y(p[1])
{
}

template <class Number>
Vector2<Number>::
Vector2( Vector2<Number> const &a )
    :
    x(a.x),
    y(a.y)
{
}

template <class Number>
Vector2<Number>::
~Vector2()
{
}

template <class Number>
Vector2<Number> &
Vector2<Number>::
operator=( Vector2<Number> const &a )
{
  if ( this == &a ) { return *this; }
  x = a.x;
  y = a.y;
  return *this;
}

template<class Number>
Number &
Vector2<Number>::
operator[](uint i)
{
  return (&x)[i];
}

template<class Number>
Number const &
Vector2<Number>::
operator[](uint i) const
{
  return (&x)[i];
}

template <class Number>
void
Vector2<Number>::
set( Number a )
{
  x = a;
  y = a;
}

template <class Number>
bool
Vector2<Number>::
operator==( Vector2<Number> const &a )
{
  return x == a.x && y == a.y;
}

template <class Number>
bool
Vector2<Number>::
operator!=( Vector2<Number> const &a )
{
  return x != a.x || y != a.y;
}

template <class Number>
bool
Vector2<Number>::
equal(
  Vector2<Number> const &a,
  Vector2<Number> const &b,
  Number epsilon )
{
  Number x = ::fabs(a.x - b.x);
  if ( x > epsilon ) { return false; }

  Number y = ::fabs(a.y - b.y);
  if ( y > epsilon ) { return false; }

  return math::sqr(x) + math::sqr(y) < math::sqr(epsilon);
}

template <class Number>
void
Vector2<Number>::neg()
{
  x = -x;
  y = -y;
}

template <class Number>
void
Vector2<Number>::
neg( Vector2<Number> const &a )
{
  x = -a.x;
  y = -a.y;
}

template <class Number>
void
Vector2<Number>::
add( Vector2<Number> const &a )
{
  x += a.x;
  y += a.y;
}

template <class Number>
void
Vector2<Number>::
add( Vector2<Number> const &a, Vector2<Number> const &b )
{
  x = a.x + b.x;
  y = a.y + b.y;
}

template <class Number>
void
Vector2<Number>::
sub( Vector2<Number> const &a )
{
  x -= a.x;
  y -= a.y;
}

template <class Number>
void
Vector2<Number>::
sub( Vector2<Number> const &a, Vector2<Number> const &b )
{
  x = a.x - b.x;
  y = a.y - b.y;
}

template <class Number>
void
Vector2<Number>::
mul( Number a )
{
  x *= a;
  y *= a;
}

template <class Number>
void
Vector2<Number>::
mul( Vector2<Number> const &a, Number b )
{
  x = a.x * b;
  y = a.y * b;
}

template <class Number>
void
Vector2<Number>::
mul( Number a, Vector2<Number> const &b )
{
  x = a * b.x;
  y = a * b.y;
}

template <class Number>
void
Vector2<Number>::
div( Number a )
{
  x /= a;
  y /= a;
}

template <class Number>
void
Vector2<Number>::
div( Vector2<Number> const &a, Number b )
{
  x = a.x / b;
  y = a.y / b;
}

template <class Number>
Number
Vector2<Number>::
dot( Vector2<Number> const &a, Vector2<Number> const &b )
{
  return a.x * b.x + a.y * b.y;
}

// return norm
template <class Number>
Number
Vector2<Number>::
norm() const
{
  return math::sqr(x) + math::sqr(y);
}

// return abs
template <class Number>
Number
Vector2<Number>::
abs() const
{
  return math::sqrt(norm());
}

template <class Number>
void
Vector2<Number>::
normalize()
{
  Number r = abs();
  x /= r;
  y /= r;
}

template <class Number>
void
Vector2<Number>::
mul_add( Vector2<Number> const &a, Number b, Vector2<Number> const &c )
{
  x = a.x + b * c.x;
  y = a.y + b * c.y;
}

template <class Number>
void
Vector2<Number>::
mul_add( Number a, Vector2<Number> const &b )
{
  x = a * b.x;
  y = a * b.y;
}

#if !defined(NO_TMPL_FRIENDS)
// write a to stream o
template <class Number>
inline
std::ostream &
operator<<( std::ostream &o, Vector2<Number> const &a )
{
  o << "{ " << a.x << ", " << a.y << "}";
  return o;
}
#endif

template <class Number>
Vector2<Number>
Vector2<Number>::
midpoint(
  Vector2<Number> const &a,
  Vector2<Number> const &b )
{
  return (a+b) * 0.5;
}

template <class Number>
Vector2<Number>
Vector2<Number>::
operator+() const
{
  return *this;
}

template <class Number>
Vector2<Number>
Vector2<Number>::
operator-() const
{
  Vector2<Number> tmp(*this);
  tmp.neg();
  return tmp;
}

template <class Number>
Vector2<Number>
Vector2<Number>::
operator+( Vector2<Number> const &a ) const
{
  Vector2<Number> tmp(*this);
  tmp.add(a);
  return tmp;
}

template <class Number>
Vector2<Number>
Vector2<Number>::
operator-( Vector2<Number> const &a ) const
{
  Vector2<Number> tmp(*this);
  tmp.sub(a);
  return tmp;
}

#if !defined(NO_TMPL_FRIENDS)
template <class Number>
Vector2<Number>
operator*( Number a, Vector2<Number> const &b )
{
  Vector2<Number> tmp(b);
  tmp.mul(a);
  return tmp;
}

template <class Number>
Vector2<Number>
operator*( Vector2<Number> const &b, Number a )
{
  Vector2<Number> tmp(b);
  tmp.mul(a);
  return tmp;
}
#endif

#if 0
template <class Number>
inline
Vector2<Number>
Vector2<Number>::
operator*( Number a ) const
{
  Vector2<Number> tmp(*this);
  tmp.mul(a);
  return tmp;
}
#endif

template <class Number>
Vector2<Number>
Vector2<Number>::
operator/( Number a ) const
{
  Vector2<Number> tmp(*this);
  tmp.div(a);
  return tmp;
}

} // namespace math

#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1375 // The destructor for class is not virtual.
#endif

#endif // math_Vector2_INCLUDED
