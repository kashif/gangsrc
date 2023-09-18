/* GANG Software
 * BASE/math/VectorX.H
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

#ifndef math_VectorX_INCLUDED
#define math_VectorX_INCLUDED

#include <iostream>
#include "base/ArrayX.H"

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

template <class Number, uint N>
class VectorX;

template <class Number, uint N>
VectorX<Number,N> operator*( Number const &, VectorX<Number,N> const & );

template <class Number, uint N>
VectorX<Number,N> operator*( VectorX<Number,N> const &, Number const & );

template <class Number, uint N>
std::ostream &operator<<( std::ostream &, VectorX<Number,N> const & );
#endif

/*
  Fixed-length base::vector class.
  Length N and entries in class Number.
*/

template <class Number, uint N>
class VectorX
  :
  public base::ArrayX<Number, N>
{
public:

  // void constructor
  inline VectorX();

  // copy constructor
  inline VectorX( VectorX<Number,N> const &a );

  // copy constructor
  inline VectorX( Number const *a );

  // destructor
  inline ~VectorX();

  // assignment operators
  inline VectorX<Number,N> &operator=( VectorX<Number,N> const &a );

  // set to A
  inline void set( Number );

  // negation: *this = - *this
  inline void neg();

  // negation: *this = - a
  inline void neg( VectorX<Number,N> const &a );

  // *this += a
  inline void add( VectorX<Number,N> const &a );

  // *this = a + b
  inline void add( VectorX<Number,N> const &a, VectorX<Number,N> const &b );

  // *this -= a
  inline void sub( VectorX<Number,N> const &a );

  // *this = a - b
  inline void sub( VectorX<Number,N> const &a, VectorX<Number,N> const &b );

  // *this *= a
  inline void mul( Number const &a );

  // *this = a * b
  inline void mul( Number const &a, VectorX<Number,N> const &b );

  // *this = a * b
  inline void mul( VectorX<Number,N> const &a, Number const &b );

#if 0
  // *this = a * b
  inline void mul( matrixX<Number, N> const &a, VectorX<Number,N> const &b );

  // *this = a * b
  inline void mul( VectorX<Number,N> const &a, matrixX<Number, N> const &b );
#endif

  // *this = a + b * c
  inline void mul_add(
    VectorX<Number,N> const &a, Number const &b, VectorX<Number, N> const &c );

  // *this += a * b
  inline void mul_add( Number const &a, VectorX<Number, N> const &b );

  // *this /= a
  inline void div( Number const &a );

  // *this = a / b
  inline void div( VectorX<Number,N> const &a, Number const &b );

  // return dot_product( *this, a )
  inline Number dot( VectorX<Number,N> const &a ) const;

  //
  inline Number norm() const;

  inline Number abs() const
    { return math::sqrt(norm()); }

  // operator versions

  inline void operator+=( VectorX<Number,N> const &a ) { this->add(a); }
  //
  inline void operator-=( VectorX<Number,N> const &a ) { this->sub(a); }
  //
  inline void operator*=( Number const &a ) { this->mul(a); }
  //
  inline void operator/=( Number const &a ) { this->div(a); }


  // inefficient versions

  inline VectorX<Number,N> operator+() const;
  //
  inline VectorX<Number,N> operator-() const;
  //
  inline VectorX<Number,N> operator+( VectorX<Number,N> const & ) const;
  //
  inline VectorX<Number,N> operator-( VectorX<Number,N> const & ) const;

#if !defined(NO_TMPL_FRIENDS)
  friend VectorX<Number,N> operator* NULL_TMPL_ARGS
  ( Number const &, VectorX<Number,N> const & );

  friend VectorX<Number,N> operator* NULL_TMPL_ARGS
  ( VectorX<Number,N> const &, Number const & );
#endif

#if 0
  //
  inline VectorX<Number,N> operator*( Number const & ) const;
#endif

  //
  inline VectorX<Number,N> operator/( Number const & ) const;

#if !defined(NO_TMPL_FRIENDS)
  friend std::ostream &operator<< NULL_TMPL_ARGS
  ( std::ostream &o, VectorX<Number,N> const &a );
#endif

protected:

};


// constructors and destructors
template <class Number, uint N>
VectorX<Number, N>::VectorX()
    :
    base::ArrayX<Number, N>()
{
}


template <class Number, uint N>
VectorX<Number, N>::VectorX( VectorX<Number, N> const &a )
    :
    base::ArrayX<Number, N>( a )
{
}

template <class Number, uint N>
VectorX<Number, N>::VectorX( Number const *a )
    :
    base::ArrayX<Number, N>( a )
{
}


template <class Number, uint N>
VectorX<Number, N>::~VectorX()
{
}


// assignment operator
template <class Number, uint N>
VectorX<Number, N> &
VectorX<Number, N>::operator=( VectorX<Number, N> const &a )
{
  ((base::ArrayX<Number,N> *)this)->operator=( a );
  return *this;
}


template <class Number, uint N>
void
VectorX<Number, N>::set( Number a )
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] = a;
  }
}


// negation: *this = - *this
template <class Number, uint N>
void
VectorX<Number, N>::neg()
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] = -_[i];
  }
}


// *this = - a
template <class Number, uint N>
void
VectorX<Number, N>::neg( VectorX<Number, N> const &a )
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] = -a._[i];
  }
}


// *this += a
template <class Number, uint N>
void
VectorX<Number, N>::add( VectorX<Number, N> const &a )
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] += a._[i];
  }
}


// *this = a + b
template <class Number, uint N>
void
VectorX<Number, N>::add( VectorX<Number, N> const &a, VectorX<Number, N> const &b )
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] = a._[i] + b._[i];
  }
}


// *this -= a
template <class Number, uint N>
void
VectorX<Number, N>::sub( VectorX<Number, N> const &a )
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] -= a._[i];
  }
}


// *this = a - b
template <class Number, uint N>
void
VectorX<Number, N>::sub( VectorX<Number, N> const &a, VectorX<Number, N> const &b )
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] = a._[i] - b._[i];
  }
}


// *this *= a
template <class Number, uint N>
void
VectorX<Number, N>::mul( Number const &a )
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] *= a;
  }
}


// *this = a * b
template <class Number, uint N>
void
VectorX<Number, N>::mul( VectorX<Number, N> const &a, Number const &b )
{
  uint i;

  for( i = 0;  i < N;  i++ )
  {
    _[i] = a._[i] * b;
  }
}


// *this = a * b
template <class Number, uint N>
void
VectorX<Number, N>::mul( Number const &a, VectorX<Number, N> const &b )
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] = a * b._[i];
  }
}

// this /= a
template <class Number, uint N>
void
VectorX<Number, N>::div( Number const &a )
{
  uint i;

  for( i = 0;  i < N;  i++ )
  {
    _[i] /= a;
  }
}


// *this = a / b
template <class Number, uint N>
void
VectorX<Number, N>::div( VectorX<Number, N> const &a, Number const &b )
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] = a._[i] / b;
  }
}

// return dot_product( *this, a )
template <class Number, uint N>
Number
VectorX<Number, N>::
dot( VectorX<Number, N> const &a ) const
{
  Number s( 0 );
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    s += _[i] * a._[i];
  }

  return s;
}

// return norm
template <class Number, uint N>
Number
VectorX<Number, N>::
norm() const
{
  Number s( 0 );
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    s += math::sqr(_[i]);
  }
  return s;
}


template <class Number, uint N>
void
VectorX<Number,N>::
mul_add(
  VectorX<Number,N> const &a,
  Number const &b,
  VectorX<Number, N> const &c )
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] = a[i] + b * c[i];
  }
}

template <class Number, uint N>
void
VectorX<Number,N>::
mul_add(
  Number const &a,
  VectorX<Number, N> const &b )
{
  uint i;
  for( i = 0;  i < N;  i++ )
  {
    _[i] += a * b[i];
  }
}


#if !defined(NO_TMPL_FRIENDS)
// write a to stream o
template <class Number, uint N>
inline
std::ostream &
operator<<( std::ostream &o, VectorX<Number, N> const &a )
{
  uint i;

  o << "{ ";
  for( i = 0; i < N; i++ )
  {
    o << a._[i];
    if( i < N - 1 )
    {
      o << ", ";
    }
  }
  o << "}";
  return o;
}
#endif

// inefficient versions

template <class Number, uint N>
VectorX<Number,N>
VectorX<Number,N>::
operator+() const
{
  return *this;
}


template <class Number, uint N>
VectorX<Number,N>
VectorX<Number,N>::
operator-() const
{
  VectorX<Number,N> tmp(*this);
  tmp.neg();
  return tmp;
}


template <class Number, uint N>
VectorX<Number,N>
VectorX<Number,N>::
operator+(
  VectorX<Number,N> const &a ) const
{
  VectorX<Number,N> tmp(*this);
  tmp.add(a);
  return tmp;
}


template <class Number, uint N>
VectorX<Number,N>
VectorX<Number,N>::
operator-(
  VectorX<Number,N> const & ) const
{
  VectorX<Number,N> tmp(*this);
  tmp.sub(a);
  return tmp;
}

#if !defined(NO_TMPL_FRIENDS)
template <class Number, uint N>
VectorX<Number,N>
operator*(
  Number const &a,
  VectorX<Number,N> const &b )
{
  VectorX<Number,N> tmp(b);
  tmp.mul(a);
  return tmp;
}

template <class Number, uint N>
VectorX<Number,N>
operator*(
  VectorX<Number,N> const &b,
  Number const &a )
{
  VectorX<Number,N> tmp(b);
  tmp.mul(a);
  return tmp;
}
#endif

#if 0
template <class Number, uint N>
inline
VectorX<Number,N>
VectorX<Number,N>::
operator*( Number const &a ) const
{
  VectorX<Number,N> tmp(*this);
  tmp.mul(a);
  return tmp;
}
#endif

template <class Number, uint N>
VectorX<Number,N>
VectorX<Number,N>::
operator/( Number const &a ) const
{
  VectorX<Number,N> tmp(*this);
  tmp.mul(a);
  return tmp;
}


#if 0
// *this = a * b
template <class Number, uint N>
void
VectorX<Number, N>::
mul(
  matrixX<Number, N> const &a,
  VectorX<Number,N> const &b )
{
  VectorX<Number, N> tmp;
  uint i, j;
  Number s;

  for( i = 0;  i < N;  i++ )
  {
    s = 0;
    for( j = 0; j < N; j++ )
    {
      s += a._[i][j] * b._[j];
    }
    tmp._[i] = s;
  }
  *this = tmp;
}


// *this = a * b
template <class Number, uint N>
void
VectorX<Number, N>::
mul(
  VectorX<Number,N> const &a,
  matrixX<Number, N> const &b )
{
  uint i, j;
  Number s;

  for( j = 0;  j < N;  j++ )
  {
    s = 0;
    for( i = 0; i < N; i++ )
      s += a._[i] * b._[i][j];
    _[i] = s;
  }
}
#endif

} // namespace math

#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1375 // The destructor for class is not virtual.
#endif

#endif // math_VectorX_INCLUDED
