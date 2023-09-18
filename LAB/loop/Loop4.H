/* GANG Software
 * LAB/loop/Loop4.H
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

#ifndef loop_Loop4_INCLUDED
#define loop_Loop4_INCLUDED

#include <iostream>
#include "math/Complex4.H"
#include "Loop2.H"
#include "Common.H"

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1375 // destructor not virtual
#endif

namespace loop {

class Loop4
{

public:
  // constructor
  inline Loop4(uint len);

  // copy constructor
  inline Loop4(Loop4 const &);

  // destructor
  inline ~Loop4();

  // assignment operator
  inline Loop4 &operator=(Loop4 const &);

  /// *this = 0
  inline void clear();

  // *this = identity matrix
  inline void identity();

  Loop2 &col1() { return _col1; }
  Loop2 &col2() { return _col2; };
  Loop2 const &col1() const  { return _col1; };
  Loop2 const &col2() const  { return _col2; };

  inline Loop2 &operator[](uint i)
    {
      if (i==0) { return _col1; }
      else if (i==1) { return _col2; }
      throw 1;
    }
  inline Loop2 const &operator[](uint i) const
    {
      if (i==0) { return _col1; }
      else if (i==1) { return _col2; }
      throw 1;
    }

  inline void allocate( uint polylen )
    {
      _polylen = polylen;
      _col1.allocate(_polylen);
      _col2.allocate(_polylen);
    }

  inline uint polylen() const { return _polylen; }

  inline void chop();

  // *this = -a
  inline void neg( Loop4 const &a );

  // *this = -*this
  inline void neg();

  // *this = a + b
  inline void add(
    Loop4 const &a,
    Loop4 const &b );

  // *this += a
  inline void add(
    Loop4 const &a );

  // *this = a - b
  inline void sub(
    Loop4 const &,
    Loop4 const &p );

  // *this -= a
  inline void sub( Loop4 const &a );

  // *this = r * a  (scalar multiplication: Complex r)
  inline void mul(
    Complex const &r,
    Loop4 const &a );

  // *this *= r  (scalar multiplication: Complex r)
  inline void mul( Complex const &r );

  // *this = r * a  (scalar multiplication: Real r)
  inline void mul( Real const &r, Loop4 const &a );

  // *this *= r  (scalar multiplication: Real r)
  inline void mul( Real const &r );

  // *this = a * b (loop scalar multiplication)
  inline void mul( Loop1 const &a, Loop4 const &b );

  // *this *= a (loop scalar multiplication)
  inline void mul( Loop1 const &a );

  // *this = a * b (loop multiplication)
  void mul(
    Loop4 const &a,
    Loop4 const &b );

  // *this = a * b
  // special multiplication optimized according to the range of *b
  void mul(
    Loop4 const &a,
    Loop4 const &b,
    RangeMatrix const &range );

  // *this = a + r * b
  inline void mul_add(
    Loop4 const &a, Complex const &r,
    Loop4 const &b );

  // *this += r * a
  inline void mul_add(
    Complex const &r,
    Loop4 const &a );

  // *this = transpose(a)
  inline void transpose( Loop4 const &a );

  // *this = transpose(*this)
  inline void transpose();

  // *this = conj(transpose(a))
  inline void transpose_conjugate( Loop4 const &a );

  // *this = conj(transpose(*this))
  inline void transpose_conjugate();

  // *this = transpose(cofactor(a))
  // {{a,b},{c,d}} -> {{d,-b},{-c,a}}
  // is the inverse if det==1
  inline void classical_adjoint( Loop4 const &a );

  // *this = transpose(cofactor(*this))
  // {{a,b},{c,d}} -> {{d,-b},{-c,a}}
  // is the inverse if det==1
  inline void classical_adjoint();

  // evaluation
  // r = eval( *this, lambda )
  inline void eval(
    math::complex4<Real> &r, Complex const &lambda ) const;

  //
  inline void eval(
    math::complex4<Real> &r,
    math::complex4<Real> &dr,
    Complex const &lambda ) const;

  // d = det(*this)
  inline void det( Loop1 &d ) const;

  //
  void exp(
    Loop4 const &A, uint count );

  // *this = exp(a)
  // series expansion to a^n
  // a must be trace-free
  // much more accurate than exp()
  void exp_trace_free(
    Loop4 const &a,
    uint iterations,
    uint polylen );

  // print
  friend std::ostream &
  operator<<( std::ostream &, Loop4 const & );

  // full-precision print
  void print( std::ostream & ) const;

  // print in Mathematica array format
  void printM( std::ostream & ) const;

  // print coefficients in C array format
  void printC( std::ostream & ) const;

  // copy b into a, allowing different sizes
  static void resize_copy(
    Loop4 &a,
    Loop4 const &b );

  // set all coefficients of t^i (i<0) to 0
  inline void make_positive();
  // set all coefficients of t^i (i>0) to 0
  inline void make_negative();

protected:
  Loop2 _col1;
  Loop2 _col2;

  // len is the highest lambda power of element 1,1
  uint _polylen;

private:
  //
  inline static void _classical_adjoint(
    Loop4 &r,
    Loop4 const &a );

};

Loop4::
Loop4(uint polylen)
    :
    _col1(polylen),
    _col2(polylen),
    _polylen(polylen)
{
}

Loop4::
Loop4( Loop4 const &a )
    :
    _col1(a._col1),
    _col2(a._col2),
    _polylen(a._polylen)
{
}

Loop4::
~Loop4()
{
}

Loop4 &
Loop4::
operator=( Loop4 const &a )
{
  _col1 = a._col1;
  _col2 = a._col2;
  return *this;
}

void
Loop4::
add( Loop4 const &x, Loop4 const &y )
{
  _col1.add( x._col1, y._col1 );
  _col2.add( x._col2, y._col2 );
}

void
Loop4::
add( Loop4 const &x )
{
  _col1.add( x._col1 );
  _col2.add( x._col2 );
}

void
Loop4::
sub( Loop4 const &x, Loop4 const &y )
{
  _col1.sub( x._col1, y._col1 );
  _col2.sub( x._col2, y._col2 );
}

void
Loop4::
sub( Loop4 const &a )
{
  _col1.sub( a._col1 );
  _col2.sub( a._col2 );
}

void
Loop4::
mul( Complex const &r, Loop4 const &a )
{
  _col1.mul( r, a._col1 );
  _col2.mul( r, a._col2 );
}

void
Loop4::
mul( Complex const &r )
{
  _col1.mul( r );
  _col2.mul( r );
}

void
Loop4::
mul( Real const &r, Loop4 const &a )
{
  // *this = r * a
  _col1.mul( r, a._col1 );
  _col2.mul( r, a._col2 );
}


void
Loop4::
mul( Real const &r )
{
  // *this *= r
  _col1.mul( r );
  _col2.mul( r );
}

void
Loop4::
mul( Loop1 const &a, Loop4 const &b )
{
  // *this = a * b
  _col1.row1().mul( a, b._col1.row1() );
  _col1.row2().mul( a, b._col1.row2() );
  _col2.row1().mul( a, b._col2.row1() );
  _col2.row2().mul( a, b._col2.row2() );
}


void
Loop4::
mul( Loop1 const &a )
{
  // *this *= a
  _col1.row1().mul( a );
  _col1.row2().mul( a );
  _col2.row1().mul( a );
  _col2.row2().mul( a );
}

void
Loop4::
mul_add( Loop4 const &a, Complex const &r,
         Loop4 const &b )
{
  // *this = a + r * b
  _col1.mul_add( a._col1, r, b._col1 );
  _col2.mul_add( a._col2, r, b._col2 );
}


void
Loop4::
mul_add( Complex const &r, Loop4 const &a )
{
  // *this += r * b
  _col1.mul_add( r, a._col1 );
  _col2.mul_add( r, a._col2 );
}

void
Loop4::
clear()
{
  _col1.clear();
  _col2.clear();
}

void
Loop4::
identity()
{
  clear();
  _col1.row1()[0] = 1.0;
  _col2.row2()[0] = 1.0;
}

void
Loop4::
eval( math::complex4<Real> &r, Complex const &lambda ) const
{
  _col1.eval( r.col1(), lambda );
  _col2.eval( r.col2(), lambda );
}

void
Loop4::
eval(
  math::complex4<Real> &r,
  math::complex4<Real> &dr,
  Complex const &lambda ) const
{
  _col1.eval( r.col1(), dr.col1(), lambda );
  _col2.eval( r.col2(), dr.col2(), lambda );
}

void
Loop4::
chop()
{
  _col1.chop();
  _col2.chop();
}


void
Loop4::
neg( Loop4 const &a )
{
  _col1.neg( a._col1 );
  _col2.neg( a._col2 );
}

void
Loop4::
neg()
{
  _col1.neg();
  _col2.neg();
}

void
Loop4::
make_positive()
{
  _col1.make_positive();
  _col2.make_positive();
}

void
Loop4::
make_negative()
{
  _col1.make_negative();
  _col2.make_negative();
}

void
Loop4::
transpose()
{
  transpose(*this);
}

void
Loop4::
transpose( Loop4 const &a )
{
#if 0

  if ( this == &a )
  {
    // NOTE: inefficient: only one element of tmp is used
    //   not sure how to allocate Loop1
    Loop4 *tmp = new Loop4(_polylen);
    tmp->_col1.row2() = _col1.row2();
    this->_col1.row2() = _col2.row1();
    this->_col2.row1() = tmp->_col1.row2();
    delete tmp;
  }
  else
  {
    _col1.row1() = a._col1.row1();
    _col1.row2() = a._col2.row1();
    _col2.row1() = a._col1.row2();
    _col2.row2() = a._col2.row2();
  }

#endif

#if 1
  if ( this == &a )
  {
    // NOTE: more efficient to swap pointers
    Loop1 *tmp = new Loop1( _polylen );
    *tmp = _col1.row2();
    _col1.row2() = _col2.row1();
    _col2.row1() = *tmp;
    delete tmp;
  }
  else
  {
    _col1.row1() = a._col1.row1();
    _col1.row2() = a._col2.row1();
    _col2.row1() = a._col1.row2();
    _col2.row2() = a._col2.row2();
  }
#endif
}

void
Loop4::
transpose_conjugate()
{
  transpose_conjugate(*this);
}

void
Loop4::
transpose_conjugate( Loop4 const &a )
{
  if ( this == &a )
  {
    Loop4 tmp(_polylen);
    tmp._col1.row1().conj( a._col1.row1() );
    tmp._col1.row2().conj( a._col2.row1() );
    tmp._col2.row1().conj( a._col1.row2() );
    tmp._col2.row2().conj( a._col2.row2() );
    *this = tmp;
  }
  else
  {
    _col1.row1().conj( a._col1.row1() );
    _col1.row2().conj( a._col2.row1() );
    _col2.row1().conj( a._col1.row2() );
    _col2.row2().conj( a._col2.row2() );
  }
}

void
Loop4::
classical_adjoint()
{
  classical_adjoint(*this);
}


void
Loop4::
classical_adjoint( Loop4 const &a )
{
  if ( &a == this )
  {
    Loop4 tmp(_polylen);
    _classical_adjoint( tmp, a );
    *this = tmp;
  }
  else
  {
    _classical_adjoint( *this, a );
  }
}

void
Loop4::
_classical_adjoint( Loop4 &r, Loop4 const &a )
{
  // computes the classical adjoint
  // {{a,b},{c,d}} -> {{d,-b},{-c,a}}
  LOOP_DIE_IF( &r == &a );
  r._col1.row1() = a._col2.row2();
  r._col1.row2().neg(a._col1.row2());
  r._col2.row1().neg(a._col2.row1());
  r._col2.row2() = a._col1.row1();
}

void
Loop4::
det( Loop1 &d ) const
{
  // d = det(*this)
  LOOP_DIE_IF( d.polylen() != polylen() );

  Loop1 tmp(_polylen);

  d.mul( _col1.row1(), _col2.row2() );
  tmp.mul( _col2.row1(), _col1.row2() );
  d.sub( tmp );
}

} // namespace loop

#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1375 // destructor not virtual
#endif

#endif // loop_Loop4_INCLUDED
