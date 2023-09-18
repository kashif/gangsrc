/* GANG Software
 * BASE/math/Vector.H
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

#ifndef math_Vector_INCLUDED
#define math_Vector_INCLUDED

#include <iostream>
#include "base/Array.H"

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

template <class A>
class Vector;

template <class A>
Vector<A> operator*( A const &, Vector<A> const & );

template <class A>
std::ostream &operator<<( std::ostream &, Vector<A> const & );
#endif

// NOTE: no virtual destructor in base class Array<>

template <class A>
class matrixA;

/*
  Primative vector class
  Uses allocate() and deallocate() (from Array<A>)
  Entries in class A.
*/

template <class A>
class Vector
  :
  public base::Array<A>
{
public:

  // void constructor
  inline Vector();

  // copy constructor
  inline Vector(Vector const &a);

  // constructor
  inline Vector(A const *a);

  // destructor
  virtual inline ~Vector();

  // assignment operators
  inline Vector &
  operator=(Vector const &a);

  //
  inline Vector &
  operator=(A const *a);

  // return reference to nth entry
  inline A &
  operator[](unsigned n);

  // return reference to nth entry
  inline A const &
  operator[](unsigned n) const;

  // set all entries of *this to a
  inline void
  set(A const &a);

  // negation: *this = - *this
  inline void
  neg();

  // negation: *this = - a
  inline void
  neg(Vector const &a);

  // *this += a
  inline void
  operator+=(Vector const &a);

  // *this = a + b
  inline void
  add(Vector const &a, Vector const &b);

  // *this -= a
  inline void
  operator-=(Vector const &a);

  // *this = a - b
  inline void
  sub(Vector const &a, Vector const &b);

  // *this *= a
  inline void
  operator*=(A const &a);

#if !defined(NO_TMPL_FRIENDS)
  friend Vector<A> operator* NULL_TMPL_ARGS
  ( A const &, Vector<A> const & );
#endif

  // *this = a * b
  inline void
  mul(A const &a, Vector const &b);

  // *this = a * b
  inline void
  mul(Vector const &a, A const &b);

  // *this = a * b
  inline void
  mul(matrixA<A> const &a, Vector const &b);

  // *this = a * b
  inline void
  mul(Vector const &a, matrixA<A> const &b);

  // *this /= a
  inline void
  operator /=(A const &a);

  // *this = a / b
  inline void
  div(Vector const &a, A const &b);

  // return dot_product(*this, a)
  inline A
  dot(Vector const &a) const;

  //
  inline A
  norm() const;

#if !defined(NO_TMPL_FRIENDS)
  // write a to stream o
  friend std::ostream &
  operator<< NULL_TMPL_ARGS
  (std::ostream &o, Vector const &a);
#endif
};


template <class A>
Vector<A>::
Vector()
    :
    base::Array<A>()
{
}


template <class A>
Vector<A>::
Vector(Vector<A> const &a)
    :
    base::Array<A>(a)
{
}


template <class A>
Vector<A>::
Vector(A const *a)
{
  *this = a;
}


template <class A>
Vector<A>::
~Vector()
{
}


// returns reference to nth entry
template <class A>
A &
Vector<A>::
operator[](unsigned n)
{
  return base::Array<A>::operator[](n);
}


// returns reference to nth entry
template <class A>
A const &
Vector<A>::
operator[](unsigned n) const
{
  return _data[n];
}


// assignment operator
template <class A>
Vector<A> &
Vector<A>::
operator=(Vector<A> const &a)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] = a._data[i];

  return *this;
}


template <class A>
Vector<A> &
Vector<A>::
operator=(A const *a)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] = a[i];

  return *this;
}


// set all entries of *this to a
template <class A>
void
Vector<A>::
set(A const &a)
{
  unsigned i;

  for (i = 0; i < _len; i++)
  {
    _data[i] = a;
  }
}


// negation: *this = - *this
template <class A>
void
Vector<A>::
neg()
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] = -_data[i];
}


// *this = - a
template <class A>
void
Vector<A>::
neg(Vector<A> const &a)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] = -a._data[i];
}


// *this += a
template <class A>
void
Vector<A>::
operator+=(Vector<A> const &a)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] += a._data[i];
}


// *this = a + b
template <class A>
void
Vector<A>::
add(Vector<A> const &a, Vector<A> const &b)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] = a._data[i] + b._data[i];
}


// *this -= a
template <class A>
void
Vector<A>::
operator-=(Vector<A> const &a)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] -= a._data[i];
}


// *this = a - b
template <class A>
void
Vector<A>::
sub(Vector<A> const &a, Vector<A> const &b)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] = a._data[i] - b._data[i];
}


// *this *= a
template <class A>
void
Vector<A>::
operator*=(A const &a)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] *= a;
}


// *this = a * b
template <class A>
void
Vector<A>::
mul(Vector<A> const &a, A const &b)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] = a._data[i] * b;
}


// *this = a * b
template <class A>
void
Vector<A>::
mul(A const &a, Vector<A> const &b)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] = a * b._data[i];
}


// *this = a * b
template <class A>
void
Vector<A>::
mul(matrixA<A> const &a, Vector const &b)
{
  Vector<A> tmp;
  unsigned i, j;
  A s;

  for (i = 0; i < _len; i++)
  {
    s = 0;
    for (j = 0; j < _len; j++)
      s += a._data[i][j] * b._data[j];
    tmp._data[i] = s;
  }
  *this = tmp;
}


// *this = a * b
template <class A>
void
Vector<A>::
mul(Vector const &a, matrixA<A> const &b)
{
  unsigned i, j;
  A s;

  for (j = 0; j < _len; j++)
  {
    s = 0;
    for (i = 0; i < _len; i++)
      s += a._data[i] * b._data[i][j];
    _data[i] = s;
  }
}


// this /= a
template <class A>
void
Vector<A>::
operator/=(A const &a)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] /= a;
}


// *this = a / b
template <class A>
void
Vector<A>::
div(Vector<A> const &a, A const &b)
{
  unsigned i;

  for (i = 0; i < _len; i++)
    _data[i] = a._data[i] / b;
}


// return dot_product(*this, a)
template <class A>
A
Vector<A>::
dot(Vector<A> const &a) const
{
  A s(0);
  unsigned i;

  for (i = 0; i < _len; i++)
    s += _data[i] * a._data[i];

  return s;
}


// return norm
template <class A>
A
Vector<A>::
norm() const
{
  A s(0);
  unsigned i;

  for (i = 0; i < _len; i++)
    s += _data[i] * _data[i];

  return s;
}

#if !defined(NO_TMPL_FRIENDS)
template <class A>
Vector<A>
operator*( A const &a, Vector<A> const &b )
{
  Vector<A> tmp(b);
  tmp.mul(a);
  return tmp;
}
#endif


#if !defined(NO_TMPL_FRIENDS)
// write a to stream o
template <class A>
std::ostream &
operator<<(std::ostream &o, Vector<A> const &a)
{
  unsigned i;

  o << "{ ";
  for (i = 0; i < a._len; i++)
  {
    o << a._data[i];
    if (i < a._len - 1)
    {
      o << ", ";
    }
  }
  o << "}";
  return o;
}
#endif

} // namespace math

#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1375 // The destructor for class is not virtual.
#endif

#endif // math_Vector_INCLUDED
