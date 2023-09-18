/* GANG Software
 * LAB/loop/Loop2.H
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

#ifndef loop_Loop2_INCLUDED
#define loop_Loop2_INCLUDED

#include <iostream>
#include <complex>
#include "math/Math.H"
#include "base/ArrayP.H"
#include "math/Complex2.H"
#include "Common.H"
#include "Loop1.H"

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1375 // destructor not virtual
#endif

namespace loop {

/*
   Class Loop4Twisted represents a column of a 2x2 matrix of std::complex
   laurent series.
 */

class Loop2
{

public:
  // constructor
  inline Loop2( uint n );

  // copy constructor
  inline Loop2( Loop2 const & );

  // destructor
  inline ~Loop2();

  // assignement operator
  inline Loop2 &
  operator=( Loop2 const &a );

  // *this = 0
  inline void clear();

  // *this = a
  inline void copy( Loop2 const &a );

  inline uint polylen() const { return _polylen; }

  // data access
  Loop1 &row1() { return _row1; }
  Loop1 &row2() { return _row2; };
  Loop1 const &row1() const { return _row1; };
  Loop1 const &row2() const { return _row2; };

  Loop1 &operator[](uint i)
    {
      if (i==0) { return _row1; }
      else if (i==1) { return _row2; }
      throw 1;
    }
  Loop1 const &operator[](uint i) const
    {
      if (i==0) { return _row1; }
      else if (i==1) { return _row2; }
      throw 1;
    }

  inline void allocate( uint polylen )
    {
      _polylen = polylen;
      _row1.allocate(_polylen);
      _row2.allocate(_polylen);
    }

  // set small numbers to 0
  inline void chop();

  // *this = -a
  inline void neg( Loop2 const &a );

  // *this = -*this
  inline void neg();

  // *this = a + b
  inline void add(
    Loop2 const &a,
    Loop2 const &b );

  // *this += a
  inline void add(
    Loop2 const &a );

  // *this = a - b
  inline void sub(
    Loop2 const &a,
    Loop2 const &b );

  // *this -= a
  inline void sub(
    Loop2 const &a );

  // *this = r * a
  inline void mul( Complex const &r, Loop2 const &a );

  // *this = r * a
  inline void mul( Real const &r, Loop2 const &a );

  // *this *= r
  inline void mul( Complex const &r );

  // *this *= r
  inline void mul( Real const &r );

  // *this = a + r * b
  inline void mul_add(
    Loop2 const &a,
    Complex const &r,
    Loop2 const &b );

  // *this += r * a
  inline void mul_add(
    Complex const &r,
    Loop2 const &a );

  // r = (*this) . conj(*this)
  inline void norm( Real & ) const;

  // *this /= sqrt(norm(*this))
  inline int normalize();

  // set all coefficients of t^i (i<0) to 0
  inline void make_positive();

  // set all coefficients of t^i (i>0) to 0
  inline void make_negative();

  // r = eval( *this, lamba )
  inline void eval(
    math::complex2<Real> &, Complex const &t ) const;
  //
  inline void eval(
    math::complex2<Real> &r,
    math::complex2<Real> &dr,
    Complex const &t ) const;

  // print
  inline friend std::ostream &
  operator<<( std::ostream &, Loop2 const & );

  // full-precision print
  inline void print( std::ostream & ) const;

  // print in Mathematica array format
  inline void printM( std::ostream & ) const;

  // print in C format
  inline void printC( std::ostream & ) const;

protected:
  //
  Loop1 _row1;
  //
  Loop1 _row2;

  uint _polylen;
private:

};

// r = a . conj(b)
inline void inner_product(
  Complex &r,
  Loop2 const &a,
  Loop2 const &b );

inline void inner_product_shift(
  Complex &,
  Loop2 const &u,
  uint shift_u,
  Loop2 const &v,
  uint shift_v );


Loop2::
Loop2(uint n)
    :
    _row1(n),
    _row2(n)
{
}

Loop2::
Loop2( Loop2 const &a )
    :
    _row1(a._row1),
    _row2(a._row2)
{
}

Loop2::
~Loop2()
{
}

Loop2 &
Loop2::
operator=( Loop2 const &a )
{
  _row1 = a._row1;
  _row2 = a._row2;
  return *this;
}

void
Loop2::
clear()
{
  _row1.clear();
  _row2.clear();
}

void
Loop2::
mul( Complex const &r, Loop2 const &a )
{
  _row1.mul( r, a._row1 );
  _row2.mul( r, a._row2 );
}

void
Loop2::
mul( Complex const &r )
{
  _row1.mul(r);
  _row2.mul(r);
}

void
Loop2::
mul( Real const &r, Loop2 const &a )
{
  _row1.mul( r, a._row1 );
  _row2.mul( r, a._row2 );
}

void
Loop2::
mul( Real const &r )
{
  _row1.mul(r);
  _row2.mul(r);
}


void
Loop2::
norm( Real &r ) const
{
  Complex a;
  inner_product( a, *this, *this );
  LOOP_DIE_IF( a.real() < 0.0 );
  LOOP_DIE_IF( fabs(a.imag()) > 1.0e-6 );
  r = a.real();
}

int
Loop2::
normalize()
{
  Real r;
  norm( r );
  if (math::effectively_zero(r))
  {
    return 1;
  }
  mul( 1.0/sqrt(r) );
  return 0;
}


void
inner_product(
  Complex &r,
  Loop2 const &a,
  Loop2 const &b )
{
  Complex r1, r2;
  inner_product( r1, a.row1(), b.row1() );
  inner_product( r2, a.row2(), b.row2() );
  r = r1 + r2;
}


void inner_product_shift(
  Complex &r,
  Loop2 const &u,
  uint shift_u,
  Loop2 const &v,
  uint shift_v )
{
  Complex r1, r2;
  inner_product_shift( r1, u.row1(), shift_u, v.row1(), shift_v );
  inner_product_shift( r2, u.row2(), shift_u, v.row2(), shift_v );
  r = r1 + r2;
}


void
Loop2::
add( Loop2 const &u, Loop2 const &v )
{
  _row1.add( u._row1, v._row1 );
  _row2.add( u._row2, v._row2 );
}


void
Loop2::
add( Loop2 const &u )
{
  _row1.add( u._row1 );
  _row2.add( u._row2 );
}


void
Loop2::
sub( Loop2 const &u, Loop2 const &v )
{
  _row1.sub( u._row1, v._row1 );
  _row2.sub( u._row2, v._row2 );
}


void
Loop2::
sub( Loop2 const &u )
{
  _row1.sub( u._row1 );
  _row2.sub( u._row2 );
}


void
Loop2::
mul_add( Loop2 const &x, Complex const &a,
         Loop2 const &y)
{
  // r = x + r * y
  _row1.mul_add( x._row1, a, y._row1 );
  _row2.mul_add( x._row2, a, y._row2 );
}


void
Loop2::
mul_add( Complex const &r, Loop2 const &a)
{
  // *this += r * a
  _row1.mul_add( r, a._row1 );
  _row2.mul_add( r, a._row2 );
}


void
Loop2::
chop()
{
  _row1.chop();
  _row2.chop();
}


void
Loop2::
neg( Loop2 const &a )
{
  _row2.neg( a._row1 );
  _row2.neg( a._row2 );
}


void
Loop2::
neg()
{
  _row1.neg();
  _row2.neg();
}

void
Loop2::
make_positive()
{
  _row1.make_positive();
  _row2.make_positive();
}

void
Loop2::
make_negative()
{
  _row1.make_negative();
  _row2.make_negative();
}

void
Loop2::
eval( math::complex2<Real> &r, Complex const &lambda ) const
{
  _row1.eval( r.row1(), lambda );
  _row2.eval( r.row2(), lambda );
}


void
Loop2::
eval(
  math::complex2<Real> &r,
  math::complex2<Real> &dr,
  Complex const &lambda ) const
{
  _row1.eval( r.row1(), dr.row1(), lambda );
  _row2.eval( r.row2(), dr.row2(), lambda );
}

void
Loop2::
print( std::ostream &o ) const
{
  _row1.print( o );
  _row2.print( o );
}

void
Loop2::
printM( std::ostream &o ) const
{
  o << "{";
  _row1.printM( o );
  o << ",\n";
  _row2.printM( o );
  o << "}";
}

void
Loop2::
printC( std::ostream &o ) const
{
  o << "{";
  _row1.printC( o );
  o << ", ";
  _row2.printC( o );
  o << "}";
}

inline
std::ostream &
operator<<(
  std::ostream &o,
  Loop2 const &r )
{
  o << r._row1;
  o << r._row2;
  return o;
}

} // namespace loop

#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1375 // destructor not virtual
#endif

#endif // loop_Loop2_INCLUDED
