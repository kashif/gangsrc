/* GANG Software
 * LAB/loop/Loop1.H
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

#ifndef loop_Loop1_INCLUDED
#define loop_Loop1_INCLUDED

#include <algorithm>
#include <iostream>
#include <complex>
#include "base/System.H"
#include "base/Array.H"
#include "math/Math.H"
#include "math/Blas.H"
#include "Common.H"

namespace loop {

/*
  Class Loop1 represents an complex laurent series.
*/

class Loop1
{
public:

  // void constructor
  inline Loop1(uint polylen);

  // copy constructor
  inline Loop1( Loop1 const & );

  // destructor
  virtual ~Loop1() { _data.deallocate(); }

  // assignment operator
  inline Loop1 &operator=( Loop1 const & );

  uint size() const
    { return _data.size(); }

  uint polylen() const
    { return _polylen; }

  // *this = 0
  inline void clear();

  // data access
  base::Array<Complex> &data() { return _data; }
  //
  base::Array<Complex> const &data() const { return _data; }

  inline Complex &operator[]( int n );
  inline Complex const &operator[]( int n ) const;

  inline void allocate( uint polylen );

  inline void chop();

  // *this = conj(a)  ( Sum[a_k t^k] -> Sum[conj(a_k) t^(-k)]
  void conj( Loop1 const &a );

  // *this = conj(*this)
  inline void conj();

  inline void make_real() { DIE(); }

  // *this = -a
  inline void neg( Loop1 const &a );

  // *this = -*this
  inline void neg();

  // *this = a + b
  inline void add( Loop1 const &a, Loop1 const &b );

  // *this += a
  inline void add( Loop1 const &a );

  // *this = a - b
  inline void sub( Loop1 const &a, Loop1 const &b );

  // *this -= a
  inline void sub( Loop1 const &a );

  // *this = r * a  (Complex r, Loop1 a)
  inline void mul( Complex const &r, Loop1 const &a );

  // *this *= r  (Complex r)
  inline void mul( Complex const &r );

  // *this = r * a  (real r, Loop1 a)
  inline void mul( Real const &r, Loop1 const & );

  // *this *= r  (real r)
  inline void mul( Real const &r );

  // *this *= a  (Loop1 a)
  inline void mul( Loop1 const &a );

  // *this = a * b  (Loop1 a, Loop1 b)
  void mul( Loop1 const &a, Loop1 const &b );

  // *this = a * b, optimized according to the range of b
  void mul( Loop1 const &a, Loop1 const &b,
    int n1, int n2 );

  // *this = r * a  (where a is shifted by shift)
  void mul( Complex const &r, Loop1 const &a, int shift );

  // *this += r * a  (where a is shifted by shift)
  void mul_add( Complex const &r, Loop1 const &a, int shift );


  // *this = a + r * b
  inline void mul_add( Loop1 const &a, Complex const &r,
                       Loop1 const &b );

  // *this += r * a
  inline void mul_add( Complex const &r, Loop1 const &a );

  // set all coefficients of t^i (i<0) to 0
  inline void make_positive();

  // set all coefficients of t^i (i>0) to 0
  inline void make_negative();

  // *this = inverse(a) (a must be postive)
  inline void inv_pos( Loop1 const &a );

  // *this = inverse(*this) (*this must be postive)
  inline void inv_pos();

  // *this = sqrt(a) (*this must be postive)
  inline void sqrt_pos( Loop1 const &a );

  // *this = sqrt(*this) (*this must be postive)
  inline void sqrt_pos();

  void eval(
    Complex &r, Complex const &lambda ) const;

  /*
    evaluates (*this) and d(*this)/dt at lambda=exp(it)
    deriv is with respect to t, not lambda

    p = X.len-1
    X.len is not Loop len, but the raw length

    X = X[0] lambda^-p + X[1] lambda^(-p+2) + ...
      + X[i] lambda^(2i-p) + ... + X[p] lambda^p
  */


  void eval(
    Complex &r,
    Complex &dr,
    Complex const &lambda ) const;

  //
  inline Real norm();

  // r = a . conj(b)
  friend inline void inner_product(
    Complex &r, Loop1 const &a, Loop1 const &b );

  // r = shift(a,sa) . conj( shift(b.sb) )
  // used by Iwasawa decomposition (Cholesky)
  friend void inner_product_shift(
    Complex &, Loop1 const &, int sa, Loop1 const &, int sb );

  // print
  friend std::ostream &operator<<( std::ostream &, Loop1 const & );

  // full-precision print
  void print( std::ostream & ) const;

  // print in Mathematica array format
  void printM( std::ostream & ) const;

  //
  void printC( std::ostream & ) const;

protected:

private:

  uint _polylen;
  base::Array<Complex> _data;

  // x = inv(a) (*this must be postive)
  static void inv_pos_static( Loop1 &x, Loop1 const &a );

  // x = sqrt(a) (*this must be postive)
  static void sqrt_pos_static( Loop1 &x, Loop1 const &a );
  //
};


// void constructor
Loop1::
Loop1(uint polylen)
    :
    _data()
{
  _polylen = polylen;
  _data.allocate( 2*_polylen + 1);
}


// copy constructor
Loop1::
Loop1( Loop1 const &a )
    :
    _polylen( a._polylen ),
    _data( a._data )
{
}

// assignement operator
Loop1 &
Loop1::
operator=( Loop1 const &a )
{
  LOOP_DIE_IF( _polylen != a._polylen );

  if ( this != &a )
  {
    _polylen = a._polylen;
    math::blas<Real>::zcopy(
      _data.length(), a._data.data(), 1, _data.data(), 1 );
  }
  return *this;
}

void
Loop1::
clear()
{
  math::zero( _data.data(), 2*_polylen + 1 );
#if 0
  uint i;
  Complex zero( 0.0, 0.0 );
  uint n = _data.length();
  for ( i = 0; i < n; i++ )
  {
    _data[i] = zero;
  }
#endif
}

Complex &
Loop1::
operator[]( int n )
{
  LOOP_DIE_IF( n > (int)_polylen );
  LOOP_DIE_IF( n < -(int)_polylen );
  return data()[n + (int)_polylen];
}

Complex const &
Loop1::
operator[]( int n ) const
{
  LOOP_DIE_IF( n > (int)_polylen );
  LOOP_DIE_IF( n < -(int)_polylen );
  return data()[n + (int)_polylen];
}


void
Loop1::
add( Loop1 const &a, Loop1 const &b )
{
  // *this = a + b
  // NOTE: inefficient
  LOOP_DIE_IF( _polylen != a._polylen );
  LOOP_DIE_IF( _polylen != b._polylen );
  LOOP_DIE_IF(this == &a);
  LOOP_DIE_IF(this == &b);

  // copy a into *this
  math::blas<Real>::zcopy( _data.length(), a._data.data(), 1,
                           _data.data(), 1 );
  // add b to *this
  math::blas<Real>::zaxpy( _data.length(), Complex(1.0,0.0),
                     b._data.data(), 1, _data.data(), 1 );
}


void
Loop1::
add( Loop1 const &a )
{
  // c += a
  LOOP_DIE_IF( _polylen != a._polylen );

  math::blas<Real>::zaxpy( _data.length(), Complex(1.0,0.0),
                     a._data.data(), 1, _data.data(), 1 );
}


void
Loop1::
sub( Loop1 const &a, Loop1 const &b )
{
  // *this = a - b
  // NOTE: inefficient
  LOOP_DIE_IF( _polylen != a._polylen );
  LOOP_DIE_IF( _polylen != b._polylen );
  LOOP_DIE_IF(this == &a);
  LOOP_DIE_IF(this == &b);

  // copy a into *this
  math::blas<Real>::zcopy( _data.length(), a._data.data(), 1,
                           _data.data(), 1 );
  // subtract b from *this
  math::blas<Real>::zaxpy( _data.length(), Complex(-1.0,0.0),
                           b._data.data(), 1, _data.data(), 1 );
}


void
Loop1::
sub( Loop1 const &a )
{
  // c += a
  LOOP_DIE_IF( _polylen != a._polylen );

  math::blas<Real>::zaxpy( _data.length(), Complex(-1.0,0.0),
                     a._data.data(), 1, _data.data(), 1 );
}

void
Loop1::
mul( Complex const &r, Loop1 const &a )
{
  // *this = r * a  (scalar multiplication: Complex r)
  LOOP_DIE_IF( _polylen != a._polylen );

  if ( this != &a )
  {
    math::copy( _data.data(), a._data.data(), 2*_polylen + 1 );
  }

  if (r == 0.0)
  {
    clear();
  }
  else if (r == 1.0)
  {
    // do nothing
  }
  else if (r == -1.0)
  {
    neg();
  }
  else
  {
    math::blas<Real>::zscal( 2*_polylen + 1, r, _data.data(), 1 );
  }
}

void
Loop1::
mul( Complex const &r )
{
  // *this *= r  (scalar multiplication: Complex r)
  mul( r, *this );
}

void
Loop1::
mul( Real const &r, Loop1 const &a )
{
  // *this = r * a  (scalar multiplication: Complex r)
  LOOP_DIE_IF( _polylen != a._polylen );

  if ( this != &a )
  {
    math::copy( _data.data(), a._data.data(), 2*_polylen + 1 );
  }

  if (r == 0.0)
  {
    clear();
  }
  else if (r == 1.0)
  {
    // do nothing
  }
  else if (r == -1.0)
  {
    neg();
  }
  else
  {
    math::blas<Real>::zdscal( 2*_polylen + 1, r, _data.data(), 1 );
  }
}

void
Loop1::
mul( Real const &r )
{
  // *this *= r  (scalar multiplication: Complex r)
  mul( r, *this );
}

void
Loop1::
mul( Loop1 const &a )
{
  // create a temporary
  Loop1 tmp(_polylen);
  // multiply
  tmp.mul( *this, a );
  // copy the temporary
  *this = tmp;
}

void
Loop1::
mul_add( Loop1 const &a, Complex const &r, Loop1 const &b )
{
  // *this = a + r * b

  LOOP_DIE_IF( this == &b );
  LOOP_DIE_IF( &a == &b );
  LOOP_DIE_IF( _polylen != a._polylen );
  LOOP_DIE_IF( _polylen != b._polylen );

  if ( this != &a )
  {
    // copy a to *this
    math::blas<Real>::zcopy( _data.length(), a._data.data(), 1,
                             _data.data(), 1 );
  }

  // add r * b to *this
  math::blas<Real>::zaxpy( _data.length(), r, b._data.data(), 1,
                           _data.data(), 1 );
}


void
Loop1::
mul_add( Complex const &r, Loop1 const &a )
{
  // this += t * a
  LOOP_DIE_IF( this == &a );

  LOOP_DIE_IF( _polylen != a._polylen );

  math::blas<Real>::zaxpy( a._data.length(), r, a._data.data(), 1,
                           _data.data(), 1 );
}

void
Loop1::
neg( Loop1 const &a )
{
  LOOP_DIE_IF( this == &a );
  LOOP_DIE_IF( _polylen != a._polylen );

  operator=(a);
  neg();

#if 0
  // another method
  math::blas<Real>::zaxpby(
    _data.length(),
    Complex(-1.0), a._data.data(), 1,
    Complex(0.0), _data.data(), 1 );
#endif
}


void
Loop1::
neg()
{
  math::blas<Real>::zdscal( _data.length(), Real(-1.0), _data.data(), 1 );
}

void
Loop1::
make_positive()
{
  uint i;
  for ( i = 0; i < _polylen; i++ )
  {
    _data[i] = 0.0;
  }
}

void
Loop1::
make_negative()
{
  uint i;
  for ( i = _polylen+1; i <= 2*_polylen; i++ )
  {
    _data[i] = 0.0;
  }
}

void
Loop1::
inv_pos( Loop1 const &a )
{
  if ( this != &a )
  {
    inv_pos_static( *this, a );
  }
  else
  {
    Loop1 x( _polylen );
    inv_pos_static( x, a );
    *this = x;
  }
}


void
Loop1::
inv_pos()
{
  inv_pos(*this);
}


void
Loop1::
sqrt_pos( Loop1 const &a )
{
  if ( this != &a )
  {
    sqrt_pos_static( *this, a );
  }
  else
  {
    Loop1 x( _polylen );
    sqrt_pos_static( x, a );
    *this = x;
  }
}


void
Loop1::
sqrt_pos()
{
  sqrt_pos(*this);
}


void
Loop1::
conj()
{
  // *this = conj(*this)
  conj( *this );
}

Real
Loop1::
norm()
{
  Complex y;
  inner_product( y, *this, *this );
  return y.real();
}


void
inner_product( Complex &r, Loop1 const &a, Loop1 const &b )
{
  // evaluates a . conj(b)

  LOOP_DIE_IF(a._polylen != b._polylen);

  r = math::blas<Real>::zdotc( a._data.length(),
                         b._data.data(), 1,
                         a._data.data(), 1 );
  // (note order switch)
}


void
Loop1::
chop()
{
  uint i;
  uint len = data().length();
  for ( i = 0; i < len; i++ )
  {
    data()[i] = math::chop( data()[i] );
  }
}

void
Loop1::
allocate( uint polylen )
{
  _polylen = polylen;
  _data.allocate( 2*_polylen + 1 );
}

} // namespace loop

#endif // loop_Loop1_INCLUDED
