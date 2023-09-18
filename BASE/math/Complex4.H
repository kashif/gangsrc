/* GANG Software
 * BASE/math/Complex4.H
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

#ifndef math_Complex4_INCLUDED
#define math_Complex4_INCLUDED

#include <iostream>
#include "base/Exception.H"
#include "Math.H"
#include "Complex2.H"

namespace math {

#if !defined(NO_TMPL_FRIENDS)
#if (defined(__sgi) && _COMPILER_VERSION >= 730) || defined(__GNUG__)
#define NULL_TMPL_ARGS <>
#else
#define NULL_TMPL_ARGS
#endif

template <class Real>
class complex4;

template <class Real>
std::ostream &operator<<( std::ostream &, complex4<Real> const & );
#endif

/*
  2-by-2 matrix of std::complex numbers
*/

template <class Real>
class
complex4
{
public:

  // void constructor
  complex4();

  // copy constructor
  complex4( complex4<Real> const & );

  // destructor
  ~complex4();

  // assignment operator
  complex4<Real> &operator=( complex4<Real> const & );

  // *this = 0
  inline void clear();
  inline void zero() { clear(); }
  inline void identity();


  // data access
  complex2<Real> &col1() { return _col1; }
  complex2<Real> const &col1() const  { return _col1; };
  complex2<Real> &col2() { return _col2; };
  complex2<Real> const &col2() const  { return _col2; };

  complex2<Real> &operator[](uint i)
    {
      DIE_IF( i >= 2 );
      return i==0 ? _col1 : _col2;
    };
  complex2<Real> const &operator[](uint i) const
    {
      DIE_IF( i >= 2 );
      return i==0 ? _col1 : _col2;
    };

  // *this = a + b
  inline void add( complex4<Real> const &A, complex4<Real> const &b );

  // *this += a
  inline void add( complex4<Real> const &a );

  // *this = a - b
  inline void sub( complex4<Real> const &a, complex4<Real> const &b );

  // *this -= a
  inline void sub( complex4<Real> const &a );

  // *this *= t
  inline void mul( std::complex<Real> const &t );

  // *this = t * b
  inline void mul( std::complex<Real> const &t, complex4<Real> const &a );

  // *this = a * b
  inline void mul( complex4<Real> const &A, complex4<Real> const &b );

  // *this = a + r * b
  inline void mul_add( complex4<Real> const &a,
                       std::complex<Real> const &r, complex4<Real> const &b );

  // *this += r * b
  inline void mul_add( std::complex<Real> const &r, complex4<Real> const &b );

  // *this = transpose(a)
  inline void transpose( complex4<Real> const &a );

  // *this = transpose(*this)
  inline void transpose();

  // *this = inv(a)
  inline void inv( complex4<Real> const &a );

  // *this = inv(*this)
  inline void inv();

  // t = det(*this)
  inline void det( std::complex<Real> &t ) const;

  // t = norm(*this) (L^2 norm)
  inline void norm( Real &t ) const;

#if !defined(NO_TMPL_FRIENDS)
  friend std::ostream &operator<< NULL_TMPL_ARGS
  ( std::ostream &, complex4<Real> const & );
#endif

private:
  // data
  complex2<Real> _col1;
  //
  complex2<Real> _col2;
};



// void constructor
template <class Real>
complex4<Real>::
complex4()
    :
    _col1(),
    _col2()
{
}


// copy constructor
template <class Real>
complex4<Real>::
complex4( complex4<Real> const &a )
    :
    _col1( a._col1 ),
    _col2( a._col2 )
{
}


// destructor
template <class Real>
complex4<Real>::
~complex4()
{
}


// assignment operator
template <class Real>
complex4<Real> &
complex4<Real>::
operator=( complex4<Real> const &a )
{
  if ( this != &a )
  {
    _col1 = a._col1;
    _col2 = a._col2;
  }
  return *this;
}


template <class Real>
void
complex4<Real>::
clear()
{
  _col1.clear();
  _col2.clear();
}

template <class Real>
void
complex4<Real>::
identity()
{
  col1().row1() = 1.0;
  col1().row2() = 0.0;
  col2().row1() = 0.0;
  col2().row2() = 1.0;
}

template <class Real>
void
complex4<Real>::
mul( std::complex<Real> const &r, complex4<Real> const &a )
{
  // *this = r * a  (scalar multiplication)
  _col1.mul( r, a._col1 );
  _col2.mul( r, a._col2 );
}


template <class Real>
void
complex4<Real>::
mul( std::complex<Real> const &r )
{
  // *this *= r  (scalar multiplication)
  _col1.mul( r );
  _col2.mul( r );
}


template <class Real>
void
complex4<Real>::
add( complex4<Real> const &a, complex4<Real> const &b )
{
  // *this = a + b
  _col1.add( a._col1, b._col1 );
  _col2.add( a._col2, b._col2 );
}


template <class Real>
void
complex4<Real>::
add( complex4<Real> const &a )
{
  // *this += a
  _col1.add( a._col1 );
  _col2.add( a._col2 );
}


template <class Real>
void
complex4<Real>::
sub( complex4<Real> const &a, complex4<Real> const &b )
{
  // *this = a - b
  _col1.sub( a._col1, b._col1 );
  _col2.sub( a._col2, b._col2 );
}


template <class Real>
void
complex4<Real>::
sub( complex4<Real> const &a )
{
  // *this -= a
  _col1.sub( a._col1 );
  _col2.sub( a._col2 );
}


template <class Real>
void
complex4<Real>::
mul( complex4<Real> const &a, complex4<Real> const &b )
{
  // *this = a * b
  complex4<Real> tmp;
  tmp._col1.row1() =
    a._col1.row1() * b._col1.row1() + a._col2.row1() * b._col1.row2();
  tmp._col2.row1() =
    a._col1.row1() * b._col2.row1() + a._col2.row1() * b._col2.row2();
  tmp._col1.row2() =
    a._col1.row2() * b._col1.row1() + a._col2.row2() * b._col1.row2();
  tmp._col2.row2() =
    a._col1.row2() * b._col2.row1() + a._col2.row2() * b._col2.row2();
  *this = tmp;
}


template <class Real>
void
complex4<Real>::
mul_add(
  complex4<Real> const &a,
  std::complex<Real> const &r,
  complex4<Real> const &b )
{
  // *this = a + r * b
  _col1.mul_add( a._col1, r, b._col1 );
  _col2.mul_add( a._col2, r, b._col2 );
}


template <class Real>
void
complex4<Real>::
mul_add(
  std::complex<Real> const &r,
  complex4<Real> const &a )
{
  // *this += r * b
  _col1.mul_add( r, a._col1 );
  _col2.mul_add( r, a._col2 );
}


template <class Real>
void
complex4<Real>::
transpose( complex4<Real> const &a )
{
  // *this = transpose(a)

  complex4<Real> tmp;

  tmp._col1.row1() = a._col1.row1();
  tmp._col2.row1() = a._col1.row2();
  tmp._col1.row2() = a._col2.row1();
  tmp._col2.row2() = a._col2.row2();

  *this = tmp;
}


template <class Real>
void
complex4<Real>::
transpose()
{
  // *this = transpose(*this)
  inv(*this);
}

template <class Real>
void
complex4<Real>::
inv( complex4<Real> const &a )
{
  // *this = inverse(a)

  std::complex<Real> d;
  a.det( d );

  if ( math::effectively_zero(d) )
  {
    WARN();
    throw base::Exception( "error in Complex4::inv()" );
  }

  complex4<Real> tmp;

  tmp._col1.row1() = a._col2.row2() / d;
  tmp._col2.row1() = -a._col2.row1() / d;
  tmp._col1.row2() = -a._col1.row2() / d;
  tmp._col2.row2() = a._col1.row1() / d;

  *this = tmp;
}


template <class Real>
void
complex4<Real>::
inv()
{
  // *this = inverse(*this)
  inv(*this);
}


template <class Real>
void
complex4<Real>::
det( std::complex<Real> &d ) const
{
  // d = det(*this)
  d = _col1.row1() * _col2.row2() - _col2.row1() * _col1.row2();
}


template <class Real>
void
complex4<Real>::
norm( Real &r ) const
{
  // r = norm(*this)
  r = std::norm(_col1.row1()) + std::norm(_col2.row1()) +
    std::norm(_col1.row2()) + std::norm(_col2.row2());
}


#if !defined(NO_TMPL_FRIENDS)
template <class Real>
inline
std::ostream &
operator<<( std::ostream &o, complex4<Real> const &a )
{
  o << a._col1.row1() << a._col2.row1()
    << a._col1.row2() << a._col2.row2() << std::endl;
  return o;
}
#endif

} // namespace math

#endif // math_Complex4_INCLUDED
