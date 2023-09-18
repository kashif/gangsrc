/* GANG Software
 * LAB/loop/QR.C
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

#include "math/Blas.H"
#include "QR.H"

namespace loop {

QR::
QR( uint m, uint n )
{
  // sanity checks
  LOOP_DIE_IF( m == 0 );
  LOOP_DIE_IF( n == 0 );
  LOOP_DIE_IF( m < n );
  LOOP_DIE_IF( m >= 0x7fffffff );
  LOOP_DIE_IF( n >= 0x7fffffff );

  // m == rows
  // n == columns
  _m = m;
  _n = n;

  _incA = 1;  // if A is indexed down the columns
  // _incA = _n;  // if A is indexed across the rows

  // allocations are done in contructor for efficiency:
  // then orthogonal_complement() can be called repeatedly
  // without repeated memory allocation

  // P holds the Householder vectors
  _PP.allocate(n);
  uint k;
  for ( k = 0; k < _n; k++ )
  {
    _PP[k].allocate(_m-k);
  }

  // s holds the scale factors
  _s.allocate(m);
}

QR::
~QR()
{
  // deallocate P and s
  uint k;
  for ( k = 0; k < _n; k++ )
  {
    _PP[k].deallocate();
  }

  _PP.deallocate();
  _s.deallocate();
}

int
QR::
projection(
  base::ArrayP<Complex> &A,
  base::ArrayP<Complex> &B,
  uint Bcols )
{
  uint i;
  for ( i = 0; i < Bcols; i++ )
  {
    int r = project(A, B.data() + i*_m);
    if (r != 0) { return r; }
  }
  return 0;
}

int
QR::
factor(
  base::ArrayP<Complex> &A )
{
  int r = 0;

  uint k;

  // householder transformation is I - _s[i] * _PP[i] * transpose[_PP[i]]

  for ( k = 0; k < _n; k++ )
  {
    // kth step in QR decompostion
    uint i, j;

    // compute norm of the column to be zeroed
    Complex  normv2;
    innerProduct( normv2, _m-k, A.data()+ind(k,k), _incA,
                  A.data()+ind(k,k), _incA );
    double normv( normv2.real() );
    if ( math::effectively_zero(normv) ) { r = 1; goto end; }

    // compute Householder base::vector 'P' and scale 's'
    copy( _m-k, A.data()+ind(k,k), 1, _PP[k].data(), 1 );

    Complex e1 = sqrt(normv);
  
    // NOTE: doing the following in two steps prevents crash
    Complex *v1_pointer = A.data() + ind(k,k);
    Complex &v1 = *v1_pointer;

    if ( !math::effectively_zero(v1) )
    {
      e1 *= std::sqrt( v1 / std::conj(v1) );
    }
    _PP[k][0] -= e1;
    double s = normv + std::norm(e1) - 2.0 * std::real( v1 * std::conj(e1) );

    if ( ! math::effectively_zero(s) )
    {
      // multiply A by the Householder transformation
      _s[k] = 2.0 / s;
      for ( j = 0; j < _n-k-1; j++ )
      {
        applyHouseholder( A.data()+ind(k,k+j+1), _PP[k].data(), _s[k], _m-k );
      }
    }
    else
    {
      _s[k] = 0.0;
    }

    // zero the current column
    A[ind(k,k)] = e1;
    for ( i = 1; i < _m-k; i++ )
    {
      A[ind(k+i,k)] = 0.0;
    }
  }
  end:
  return r;
}

int
QR::
project(
  base::ArrayP<Complex> const &A,
  Complex *B )
{
  int r = 0;

  // compute the Projection of B to span(A)
  // X = _PP[0] ... _PP[n-1] . Ix . _PP[n-1] . ... _PP[0] . B

  //  copy( _m, B.data(), 1, _XX.data(), 1 );

  // pass 1
  uint k;
  for ( k = 0; k < _n; k++ )
  {
    applyHouseholder( B+k, _PP[k].data(), _s[k], _m-k );
  }

  // Projection
  for ( k = 0; k < _m-_n; k++ )
  {
    B[_n+k] = 0.0;
  }

  // pass 2
  k = _n-1;
  for (;;)
  {
    applyHouseholder( B+k, _PP[k].data(), _s[k], _m-k );
    if ( k == 0 ) { break; }
    k--;
  }

  return r;
}

void
QR::
copy(
  uint n,
  Complex  const *x,
  uint incx,
  Complex  *y,
  uint incy )
{
  math::blas<double>::zcopy( n, x, incx, y, incy );
}

void
QR::
innerProduct(
  Complex  &r,
  uint n,
  Complex  const *x,
  uint incx,
  Complex  const *y,
  uint incy )
{
  r = math::blas<double>::zdotc( n, y, incx, x, incy );
}

void
QR::
applyHouseholder(
  Complex  *x,
  Complex  const *v,
  double const &s,
  uint n )
{
  // apply Householder transformation (v,s) to x
  // x = x + (-s * <v,x>) v

  Complex r2;
  innerProduct(r2, n, x, 1, v, 1);
  r2 *= -s;
  math::blas<double>::zaxpy( n, r2, v, 1, x, _incA );
}

uint
QR::
ind( uint i, uint j )
{
  // indexed down the columns
  return i + j*_m;

  // indexed across the rows
  // return i*_n + j;
}

} // namespace loop
