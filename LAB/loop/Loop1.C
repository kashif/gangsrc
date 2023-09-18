/* GANG Software
 * LAB/loop/Loop1.C
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

#include "Loop1.H"
#include "Common.H"

namespace loop {

void
Loop1::
mul( Complex const &r, Loop1 const &a, int shift )
{
  // sanity checks
  DIE_IF( a._polylen != _polylen );
  DIE_IF( this == &a );

  // *this = (r t^shift) * a
  if ( r == 0.0 )
  {
    math::zero(_data.data(), 2*_polylen + 1 );
    return;
  }

  if (shift >= 0)
  {
    math::copy( _data.data() + shift, a._data.data(), 2*_polylen + 1 - shift );
    math::zero( _data.data(), shift );
    math::blas<Real>::zscal( 2*_polylen + 1 - shift, r, _data.data() + shift, 1 );
  }
  else
  {
    math::copy( _data.data(), a._data.data() - shift, 2*_polylen + 1 + shift );
    math::zero( _data.data() + 2*_polylen + 1 + shift, -shift );
    math::blas<Real>::zscal( 2*_polylen + 1 + shift, r, _data.data(), 1 );
  }
}

void
Loop1::
mul( Loop1 const &a, Loop1 const &b )
{
  // x = a * b

  // sanity checks
  DIE_IF( a._polylen != _polylen );
  DIE_IF( b._polylen != _polylen );
  DIE_IF( this == &a );
  DIE_IF( this == &b );

  uint k;
  uint N;

  N = _polylen;
  for ( k = 0; k < N; k++ )
  {
    LOOP_DIE_IF(k >= this->data().length());
    LOOP_DIE_IF(2*N-k >= this->data().length());
    LOOP_DIE_IF(a.data().length() < N+k+1);
    LOOP_DIE_IF(a.data().length() < N-k+N+k+1);
    LOOP_DIE_IF(2*N + 1 < N+k+1 );

    this->data()[k] = math::blas<Real>::zdotu(
      N+k+1, a.data().data(), 1, b.data().data(), -1 );
    this->data()[2*N-k] = math::blas<Real>::zdotu(
      N+k+1, a.data().data() + N-k, 1, b.data().data() + N-k, -1 );
  }
  LOOP_DIE_IF(a.data().length() < 2*N+1);

  this->data()[N] = math::blas<Real>::zdotu(
    2*N+1, a.data().data(), 1, b.data().data(), -1 );
}

void Loop1::
mul(
  Loop1 const &a,
  Loop1 const &b,
  int n1,
  int n2 )
{
  // *this = a * b
  // coefficients of b run from n1 to n2
  
  // sanity checks
  DIE_IF( a._polylen != _polylen );
  DIE_IF( b._polylen != _polylen );
  DIE_IF( this == &a );
  DIE_IF( this == &b );
  DIE_IF( n1 > n2 );

  if (n1 == 0 && n2 == 0)
  {
    mul( b[0], a );
  }
  else if (n1 == -1 && n2 == -1)
  {
    mul( b[-1], a, -1 );
  }
  else if (n1 == 1 && n2 == 1)
  {
    mul( b[1], a, 1 );
  }
  else if (n1 == 0 && n2 == 1)
  {
    mul( b[1], a, 1 );
    mul_add( b[0], a );
  }
  else if (n1 == -1 && n2 == 0)
  {
    mul( b[-1], a, -1 );
    mul_add( b[0], a );
  }
  else
  {
  clear();

  int i;
  int p = _polylen;
  for ( i = -p; i < 0; i++ )
  {
    int n = std::min(n2, i+p);

    this->_data[p + i] =
      math::blas<Real>::zdotu( n - n1 + 1, a.data().data() + p + i - n, -1, b.data().data() + p + n1, 1 );
  }
  for ( i = 0; i <= p; i++ )
  {
    int n = std::max(n1, i-p);

    this->_data[p + i] =
      math::blas<Real>::zdotu( n2 - n + 1, a.data().data() + p + i - n2, -1, b.data().data() + p + n, 1 );
  }
  }
}

void
Loop1::
inv_pos_static( Loop1 &x, Loop1 const &a )
{
  // *this = 1/a (a must be positive)

  /*
    invert a loop
    must be postive and even
    x[0] = 1/a[0]
    x[1] = (-1/a[0])(a[1]x[0])
    x[2] = (-1/a[0])(a[2]x[0]+a[1]x[1])
    x[3] = (-1/a[0])(a[3]x[0]+a[2]x[1]+a[1]x[2])
    ...
  */

  LOOP_DIE_IF( &x == &a );

  LOOP_DIE_IF( math::effectively_zero(a[0]) );
  x.clear();

  Complex d = 1.0/a[0];
  x[0] = d;

  uint n = x.polylen();
  uint i;
  for ( i = 1; i <= n; i++ )
  {
    uint j;
    Complex s = 0.0;
    for( j = 0; j < i; j++)
    {
      s += a[i-j] * x[j];
    }
    x[i] = -d * s;
  }
}

void
Loop1::
sqrt_pos_static( Loop1 &x, Loop1 const &a )
{
  // NOTE: this is for even loops
  // must be modified for generic loops
  abort();


  LOOP_DIE_IF( &x == &a );
  LOOP_DIE_IF( a._data.length() % 2 != 1 );

  int n = (a._data.length() - 1)/2;
  x._data[n] = std::sqrt(a._data[n]);

  Complex d = 0.5/x._data[n];

  Complex s;
  int i, j;
  for ( i = 1; i < n; i++ )
  {
    s = 0.0;
    int v = ( i % 2 == 0 ? (i-2)/2 : (i-1)/2 );
    for( j = 1; j <= v; j++)
    {
      s += x._data[n+j] * x._data[n+i-j];
    }
    s *= 2.0;
    if (i%2 == 0)
    {
      s += math::sqr(x._data[n+i/2]);
    }
    x._data[n+i] = (a._data[n+i] - s) * d;
  }
}

void
Loop1::
conj( Loop1 const &a )
{
  // *this = conj(a)
  // ok if 'this' is 'a'

  LOOP_DIE_IF( _data.length() != a._data.length() );

  Complex t1, t2;

  uint i;
  uint n = (a._data.length()-(a._data.length() % 2))/2;
  for ( i = 0; i < n; i++ )
  {
    // swap and conjugate
    t1 = a._data[i];
    t2 = a._data[a._data.length()-i-1];
    _data[i] = std::conj(t2);
    _data[a._data.length()-i-1] = std::conj(t1);
  }
  if ( a._data.length() % 2 == 1 )
  {
    _data[(a._data.length()-1)/2] = std::conj(a._data[(a._data.length()-1)/2]);
  }
}

void
Loop1::
eval(
  Complex &r,
  Complex const &lambda ) const
{
  /*
    Evaluates *this at lambda; puts result in r

    algorithm:
    for loop a[n]t^n + ... + a[-n]t^(-n),
    computes
    u = t^(-n) ( (((a[n]t+a[n-1]) t + a[n-2] ) t + a[n-3])t+ ... )
  */

  uint n = polylen();

  Complex u = operator[](n);

  if (lambda == 1.0)
  {
    // optimized for case lambda==1
    int i;
    for (i = int(n)-1; i >= -int(n); i--)
    {
      u += _data[_polylen+i];
    }
    r = u;
  }
  else
  {
    int i;
    for (i = int(n)-1; i >= -int(n); i--)
    {
      u = u * lambda + _data[_polylen+i];
    }
    r = u * std::pow(lambda, -Real(n) );
  }
}

void
Loop1::
eval(
  Complex &r,
  Complex &dr,
  Complex const &lambda ) const
{
  /*
    Evaluates *this at lambda; puts result in r
    Evaluates derivative of *this (with respect to the loop parameter)
      at lambda; puts result in dr

    algorithm:
    for loop a[n]t^n + ... + a[-n]t^(-n),
    computes
    u = t^(-n) ( (((a[n]t+a[n-1]) t + a[n-2] ) t + a[n-3])t+ ... )
    du = t^(-n) ( ((( n a[n]t+ (n-1)a[n-1]) t + (n-2)a[n-2] ) t +
      (n-3)a[n-3])t+ ... )
  */

  uint n = polylen();

  Complex u = operator[](n);
  Complex du = Real(n) * operator[](n);

  if (lambda == 1.0)
  {
    // optimized for case lambda==1
    int i;
    for (i = int(n)-1; i >= -int(n); i--)
    {
      u += _data[_polylen+i];
      du += Real(i) * _data[_polylen+i];
    }
    r = u;
    dr = du;
  }
  else
  {
    int i;
    for (i = int(n)-1; i >= -int(n); i--)
    {
      u = u * lambda + _data[_polylen+i];
      du = du * lambda + Real(i) * _data[_polylen+i];
    }
    r = u * std::pow(lambda, -Real(n) );
    dr = du * std::pow(lambda, -Real(n)-1.0 );
  }
}

void
inner_product_shift(
  Complex &r,
  Loop1 const &a, int a_shift,
  Loop1 const &b, int b_shift )
{
  // evaluates a . conj(b)

  // a._[shift_a] b._[b_shift] + a._[shift_a+1] b._[b_shift+1] + ... +

  LOOP_DIE_IF( abs(int(a._data.length()) - int(b._data.length())) % 2
           != abs(int(a_shift) - int(b_shift)) % 2 );

  int g = a_shift - b_shift;

  int d = -int(a._data.length()) + int(b._data.length()) + g;
  int a_x, b_x;
  if ( d < 0 )
  {
    a_x = -d/2;
    b_x = 0;
  }
  else
  {
    a_x = 0;
    b_x = d/2;
  }

  int count;
  if ( int(a._data.length())-1 + g <= int(b._data.length())-1 )
  {
    count = a._data.length() - a_x;
  }
  else
  {
    count = b._data.length() - b_x;
  }

  if (count > 0 )
  {
    // note order reversal
    r = math::blas<Real>::zdotc(
      count,
      b._data.data() + b_x, 1,
      a._data.data() + a_x, 1);
  }
  else
  {
    r = 0.0;
  }
}

void
Loop1::
print( std::ostream &o ) const
{
  uint i;
  for( i = 0; i < _data.length(); i++ )
  {
    base::println( o, _data[i]);
  }
  o << std::endl;
}

void
Loop1::
printM( std::ostream &o ) const
{
  int p = polylen();

  uint i;
  for( i = 0; i < size(); i++ )
  {
    o << "(";
    base::printM( o, _data[i]);
    o << ")*t^(" << -p+int(i) << ")";
    if ( i != _data.length()-1 ) { o << "+"; }
    o << "\n";
  }
}

void
Loop1::
printC( std::ostream &o ) const
{
  int p = polylen();

  uint i;
  for( i = 0; i < _data.length(); i++ )
  {
    o << "(";
    base::print( o, _data[i]);
    o << ")*t^(" << -p+int(i) << ")";
    if ( i != _data.length()-1 ) { o << "+"; }
    o << "\n";
  }
}

std::ostream &
operator<<( std::ostream &o, Loop1 const &a )
{
  uint i;
  for( i = 0; i < a._data.length(); i++ )
  {
    o << a._data[i] << " ";
  }
  o << std::endl;
  return o;
}

void
Loop1::
mul_add( Complex const &r, Loop1 const &a, int shift )
{
  if (r == 0.0) { return; }

  if (shift == 0)
  {
    mul_add( r, a );
  }
  else if (shift > 0)
  {
    int count = int(2*_polylen+1) - shift;
    DIE_IF( count < 0 );
    math::blas<Real>::zaxpy(
      count, r, a._data.data(), 1, _data.data() + shift, 1 );
  }
  else
  {
    int count = int(2*_polylen+1) + shift;
    DIE_IF( count < 0 );
    math::blas<Real>::zaxpy(
      count, r, a._data.data() - shift, 1, _data.data(), 1 );
  }
}

} // namespace loop
