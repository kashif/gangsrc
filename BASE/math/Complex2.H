/* GANG Software
 * BASE/math/Complex2.H
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

#ifndef math_Complex2_INCLUDED
#define math_Complex2_INCLUDED

#include <iostream>
#include <complex>

namespace math {

#if !defined(NO_TMPL_FRIENDS)
#if (defined(__sgi) && _COMPILER_VERSION >= 730) || defined(__GNUG__)
#define NULL_TMPL_ARGS <>
#else
#define NULL_TMPL_ARGS
#endif

template <class Real>
class complex2;

template <class Real>
std::ostream &operator<<( std::ostream &, complex2<Real> const & );
#endif

/*
  Column of two std::complex numbers -- used with complex4.
*/

template <class Real>
class complex2
{
public:
  // void constructor
  complex2();

  // copy constructor
  complex2( complex2<Real> const & );

  // destructor
  ~complex2();

  // assignment operator
  complex2<Real> &operator=( complex2<Real> const & );

  // *this = 0
  inline void clear();
  inline void zero() { clear(); }


  // data access
  std::complex<Real> &row1() { return _row1; }
  std::complex<Real> const &row1() const  { return _row1; };
  std::complex<Real> &row2() { return _row2; };
  std::complex<Real> const &row2() const  { return _row2; };

  std::complex<Real> &operator[](uint i)
    {
      DIE_IF( i >= 2 );
      return i==0 ? _row1 : _row2;
    };
  std::complex<Real> const &operator[](uint i) const
    {
      DIE_IF( i >= 2 );
      return i==0 ? _row1 : _row2;
    };

  // *this = a * b  (scalar multiplication)
  inline void mul( std::complex<Real> const &a, complex2<Real> const &b );

  // *this *= a  (scalar multiplication)
  inline void mul( std::complex<Real> const &a );

  // *this = a + b
  inline void add( complex2<Real> const &a, complex2<Real> const &b );

  // *this += a
  inline void add( complex2<Real> const &a );

  // *this = a - b
  inline void sub( complex2<Real> const &a, complex2<Real> const &b );

  // *this -= a
  inline void sub( complex2<Real> const &a );

  // *this = a + r * b
  inline void mul_add( complex2<Real> const &a, std::complex<Real> const &r,
                       complex2<Real> const &b );

  // *this += r * a
  inline void mul_add( std::complex<Real> const &r,
                       complex2<Real> const &a );

#if !defined(NO_TMPL_FRIENDS)
  friend std::ostream &operator<< NULL_TMPL_ARGS
  ( std::ostream &, complex2<Real> const & );
#endif

private:
  //
  std::complex<Real> _row1;
  //
  std::complex<Real> _row2;
};


// void constructor
template <class Real>
complex2<Real>::
complex2()
    :
    _row1(),
    _row2()
{
}


// copy constructor
template <class Real>
complex2<Real>::
complex2( complex2<Real> const &a )
    :
    _row1( a._row1 ),
    _row2( a._row2 )
{
}


// destructor
template <class Real>
complex2<Real>::
~complex2()
{
}


// assignment operator
template <class Real>
complex2<Real> &
complex2<Real>::
operator=( complex2<Real> const &a )
{
  if ( this != &a )
  {
    _row1 = a._row1;
    _row2 = a._row2;
  }
  return *this;
}


template <class Real>
void
complex2<Real>::
clear()
{
  _row1 = std::complex<Real>(0.0);
  _row2 = std::complex<Real>(0.0);
}


template <class Real>
void
complex2<Real>::
mul( std::complex<Real> const &r, complex2<Real> const &a )
{
  // *this = r * a  (scalar multiplication)
  _row1 = r * a._row1;
  _row2 = r * a._row2;
}


template <class Real>
void
complex2<Real>::
mul( std::complex<Real> const &r )
{
  // *this *= r  (scalar multiplication)
  _row1 *= r;
  _row2 *= r;
}


template <class Real>
void
complex2<Real>::
add( complex2<Real> const &a, complex2<Real> const &b )
{
  // *this = a + b
  _row1 = a._row1 + b._row1;
  _row2 = a._row2 + b._row2;
}


template <class Real>
void
complex2<Real>::
add( complex2<Real> const &a )
{
  // *this += a
  _row1 += a._row1;
  _row2 += a._row2;
}


template <class Real>
void
complex2<Real>::
sub( complex2<Real> const &a, complex2<Real> const &b )
{
  // *this = a - b
  _row1 = a._row1 - b._row1;
  _row2 = a._row2 - b._row2;
}


template <class Real>
void
complex2<Real>::
sub( complex2<Real> const &a )
{
  // *this -= a
  _row1 -= a._row1;
  _row2 -= a._row2;
}


template <class Real>
void
complex2<Real>::
mul_add( complex2<Real> const &a,
         std::complex<Real> const &r,
         complex2<Real> const &b )
{
  // *this = a + r * b
  _row1 = a._row1 + r * b._row1;
  _row2 = a._row2 + r * b._row2;
}


template <class Real>
void
complex2<Real>::
mul_add( std::complex<Real> const &r, complex2<Real> const &a )
{
  // *this += r * a
  _row1 += r * a._row1;
  _row2 += r * a._row2;
}

#if !defined(NO_TMPL_FRIENDS)
template <class Real>
inline
std::ostream &
operator<<( std::ostream &o, complex2<Real> const &a )
{
  o << x._row1 << x._row2;
  return o;
}
#endif

} // namespace math

#endif // math_Complex2_INCLUDED
