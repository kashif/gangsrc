/* GANG Software
 * LAB/loop/Loop4.C
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

#include "Loop4.H"

namespace loop {

void
Loop4::
mul(
  Loop4 const &a,
  Loop4 const &b )
{
  // *this = a * b

  Loop1 u0(_polylen), u1(_polylen), u2(_polylen), u3(_polylen);
  Loop1 v0(_polylen), v1(_polylen), v2(_polylen), v3(_polylen);

  u0.mul( a._col1.row1(), b._col1.row1() );
  u1.mul( a._col2.row1(), b._col1.row2() );

  v0.mul( a._col1.row1(), b._col2.row1() );
  v1.mul( a._col2.row1(), b._col2.row2() );

  v2.mul( a._col1.row2(), b._col1.row1() );
  v3.mul( a._col2.row2(), b._col1.row2() );

  u2.mul( a._col1.row2(), b._col2.row1() );
  u3.mul( a._col2.row2(), b._col2.row2() );

  _col1.row1().add( u0, u1 );
  _col2.row1().add( v0, v1 );
  _col1.row2().add( v2, v3 );
  _col2.row2().add( u2, u3 );
}


void
Loop4::
mul(
  Loop4 const &a,
  Loop4 const &b,
  RangeMatrix const &range )
{
  // *this = a * b
  // special multiplication optimized according to the range of *b

  // unrolled version
  clear();

  Loop1 const &A11 = a[0][0];
  Loop1 const &A12 = a[1][0];
  Loop1 const &A21 = a[0][1];
  Loop1 const &A22 = a[1][1];

  Loop1 const &B11 = b[0][0];
  Loop1 const &B12 = b[1][0];
  Loop1 const &B21 = b[0][1];
  Loop1 const &B22 = b[1][1];

  Loop1 &X11 = (*this)[0][0];
  Loop1 &X12 = (*this)[1][0];
  Loop1 &X21 = (*this)[0][1];
  Loop1 &X22 = (*this)[1][1];

  uint i;
  // B11
  for ( i = 0; i < range[0][0].count; i++ )
  {
    int s = range[0][0].start + int(i);
    X11.mul_add( B11.data()[_polylen+s], A11, s );
    X21.mul_add( B11.data()[_polylen+s], A21, s );
  }
  // B21
  for ( i = 0; i < range[1][0].count; i++ )
  {
    int s = range[1][0].start + int(i);
    X11.mul_add( B21.data()[_polylen+s], A12, s );
    X21.mul_add( B21.data()[_polylen+s], A22, s );
  }
  // B12
  for ( i = 0; i < range[0][1].count; i++ )
  {
    int s = range[0][1].start + int(i);
    X12.mul_add( B12.data()[_polylen+s], A11, s );
    X22.mul_add( B12.data()[_polylen+s], A21, s );
  }
  // B22
  for ( i = 0; i < range[1][1].count; i++ )
  {
    int s = range[1][1].start + int(i);
    X12.mul_add( B22.data()[_polylen+s], A12, s );
    X22.mul_add( B22.data()[_polylen+s], A22, s );
  }

#if 0
  // loop version
  clear();

  uint i;
  for ( i= 0; i < 2; i++ )
  {
    uint j;
    for ( j = 0; j < 2; j++ )
    {
      uint k;
      for ( k = 0; k < range[i][j].count; k++ )
      {
        int s = range[i][j].start + int(k);
        uint l;
        for ( l = 0; l < 2; l++ )
        {
          (*this)[j][l].mul_add( b[j][i].data()[_polylen+s], a[i][l], s );
        }
      }
    }
  }
#endif
}


void
Loop4::
exp_trace_free(
  Loop4 const &a_,
  uint iteration,
  uint polylen )
{
  /*
   Computes *this = exp(a)

   a is assumed to be trace-free
   this method for computing exp is much more accurate than exp() above

   input:
     a_: a trace-free loop in a lie algebra
     iteration: number of terms taken in power series
     polylen: Fourier series length used internally
   output: sets *this to exp(a_)

   algorithm:
   exp(A) = cosh(d) I + 1/sqrt(d) sinh(d) A,
   where d = sqrt(-det(A)) (so A^2=-det(A)I )

   avoids sqrt() and inversion by the power series:

   cosh(sqrt(x)) = 1 + x/2! + x^2/4! + ...
   1/sqrt(x) sinh(sqrt(x)) = 1 + x/3! + x^2/5! + ...

   NOTE: in the special case that  polylen == _polylen, this could be made more
     efficient by not copying
  */

  // sanity checks
  LOOP_DIE_IF( this == &a_ );
  LOOP_DIE_IF( a_._polylen != _polylen );

  // allocate a bigger loop
  Loop4 *a = new Loop4(polylen);

  // copy a_ into a bigger space (resize-copy)
  resize_copy( *a, a_ );

  // d = -det(a)
  Loop1 *d = new Loop1(polylen);
  a->det(*d);
  d->neg();

  // allocate temporaries
  Loop1 *P = new Loop1(polylen);
  // Set P := Id
  P->data()[polylen/2] = 1.0;

  // allocate temporaries
  Loop1 *S1 = new Loop1(polylen);
  Loop1 *S2 = new Loop1(polylen);

  uint i;
  for ( i = 0; i < iteration; i+= 2 )
  {
    S1->mul_add( 1.0/math::factorial(i), *P );
    S2->mul_add( 1.0/math::factorial(i+1), *P );
    P->mul( *d );
  }

  // compute e = exp(a)
  Loop1 *tmp = new Loop1(polylen);
  Loop4 *e = new Loop4(polylen);

  // Compute e11
  e->_col1.row1() = *S1;
  tmp->mul( *S2, a->_col1.row1() );
  e->_col1.row1().add( *tmp );

  // Compute e12
  e->_col2.row1().mul( *S2, a->_col2.row1() );

  // Compute e21
  e->_col1.row2().mul( *S2, a->_col1.row2() );

  // Compute e22
  e->_col2.row2() = *S1;
  tmp->mul( *S2, a->_col2.row2() );
  e->_col2.row2().add( *tmp );

  // resize-copy e into *this
  resize_copy( *this, *e );

  // deallocate temporaries
  delete e;
  delete tmp;
  delete S2;
  delete S1;
  delete P;
  delete d;
  delete a;
}


void
Loop4::
exp(
  Loop4 const &A,
  uint count )
{
  // computes exp(A) by integrating (*this)' = (*this) A
  // count is number of steps in integration from 0 to 1

  this->identity();

  Loop4 K1(_polylen);
  Loop4 K2(_polylen);
  Loop4 K3(_polylen);
  Loop4 K4(_polylen);

  Complex const &x1 = 0.0;
  Complex const &x2 = 1.0;
  Complex dx = (x2 - x1)/Complex(count);

  uint i;
  for ( i = 0; i < count; i++ )
  {
//    Complex x = x1 + Complex(i) * dx;
    Complex dx2 = dx * 0.5;
//    Complex xh = x + dx2;

    K1 = *this;
    K1.mul( K1, A );

    K2 = K1;
    K2.mul(dx2);
    K2.add(*this);
    K2.mul( K2, A );

    K3 = K2;
    K3.mul(dx2);
    K3.add(*this);
    K3.mul( K3, A );

    K4 = K3;

    K3.add( K2 );

    K4.mul(dx);
    K4.add(*this);
    K4.mul( K4, A );

    K3.mul(2.0);
    K3.add( K1 );
    K3.add( K4 );
    K3.mul( dx/6.0 );
    this->add( K3 );
  }
}

void
Loop4::
resize_copy( Loop4 &a, Loop4 const &b )
{
  // copies b into a, allowing for different sizes
  uint i;
  LOOP_DIE_IF( a._polylen % 2 != 0 );
  LOOP_DIE_IF( b._polylen % 2 != 0 );

  if ( a._polylen > b._polylen )
  {
    a.clear();

    // copy smaller into bigger
    uint t = a._polylen/2 - b._polylen/2;

    for ( i = 0; i < b._polylen+1; i++ )
    {
      a._col1.row1().data()[i+t] = b._col1.row1().data()[i];
      a._col2.row2().data()[i+t] = b._col2.row2().data()[i];
    }
    for ( i = 0; i < b._polylen; i++ )
    {
      a._col1.row2().data()[i+t] = b._col1.row2().data()[i];
      a._col2.row1().data()[i+t] = b._col2.row1().data()[i];
    }
  }
  else
  {
    uint t = b._polylen/2 - a._polylen/2;

    for ( i = 0; i < a._polylen+1; i++ )
    {
      a._col1.row1().data()[i] = b._col1.row1().data()[i+t];
      a._col2.row2().data()[i] = b._col2.row2().data()[i+t];
    }
    for ( i = 0; i < a._polylen; i++ )
    {
      a._col1.row2().data()[i] = b._col1.row2().data()[i+t];
      a._col2.row1().data()[i] = b._col2.row1().data()[i+t];
    }
  }
}

void
Loop4::
print( std::ostream &o ) const
{
  _col1.row1().print( o );
  _col2.row1().print( o );
  _col1.row2().print( o );
  _col2.row2().print( o );
}

void
Loop4::
printM( std::ostream &o ) const
{
  o << "{{\n";
  _col1.row1().printM( o );
  o << ",\n";
  _col2.row1().printM( o );
  o << "},{\n";
  _col1.row2().printM( o );
  o << ",\n";
  _col2.row2().printM( o );
  o << "}}\n";
}

void
Loop4::
printC( std::ostream &o ) const
{
  o << "{{\n";
  _col1.row1().printC( o );
  o << ",\n";
  _col2.row1().printC( o );
  o << "},{\n";
  _col1.row2().printC( o );
  o << ",\n";
  _col2.row2().printC( o );
  o << "}}\n";
}

std::ostream &
operator<<( std::ostream &o, Loop4 const &a )
{
  o << a._col1.row1();
  o << a._col2.row1();
  o << a._col1.row2();
  o << a._col2.row2();
  return o;
}

} // namespace loop
