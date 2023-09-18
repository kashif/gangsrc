/* GANG Software
 * LAB/loop/QRLapack.C
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

//#include <limits.h>
#include <algorithm>
#include "math/Math.H"
#include "math/Blas.H"
#include "Common.H"
#include "QRLapack.H"

namespace loop {

extern "C"
{
  typedef char charF;
  typedef int integerF;
  typedef float realF;
  typedef double real2F;
  typedef Complex  complex2F;

  // QR decomposition
  void zgeqrf_(
    integerF const *M,
    integerF const *N,
    complex2F *A,
    integerF const *LDA,
    complex2F *TAU,
    complex2F *WORK,
    integerF const *LWORK,
    integerF *INFO
    );

  // convert reflectors to a matrix from zgeqrf
  void zunmqr_(
    charF const *SIDE,
    charF const *TRANS,
    integerF const *M,
    integerF const *N,
    integerF const *K,
    complex2F const *A,
    integerF const *LDA,
    complex2F const *TAU,
    complex2F *C,
    integerF const *LDC,
    complex2F *WORK,
    integerF const *LWORK,
    integerF *INFO );
}

// constructor
QRLapack::
QRLapack( uint rows, uint cols )
{
  // sanity checks
  LOOP_DIE_IF( rows == 0 );
  LOOP_DIE_IF( cols == 0 );
  LOOP_DIE_IF( rows < cols );
  LOOP_DIE_IF( rows >= 0x7fffffff );
  LOOP_DIE_IF( cols >= 0x7fffffff );

  _rows = rows;
  _cols = cols;

  // allocate TAU
  TAU.allocate( std::min(_rows, _cols) );
  WORK.allocate( _cols );
}

void
QRLapack::
factor(
  base::ArrayP<Complex> &A )
  throw (int)
{
  /*
    Computes the Projection of B to the linear space spanned by A
    Puts the result into B
    modifies A (see zgeqrf manpage on how)
    Uses QR decomposition

    A is a rows-by-cols matrix
    B is a rows-by-1 matrix

    NOTE: allocations can be optimized
  */

  // compute QR decomposition of A = QR
  // A is modified to contain Q and R encoded

  integerF M = (integerF)_rows;
  integerF N = (integerF)_cols;
  integerF LDA = (integerF)_rows;
  integerF LWORK = (integerF)_cols;
  integerF INFO = 0;

  zgeqrf_( &M, &N, A.data(), &LDA, TAU.data(), WORK.data(), &LWORK, &INFO );

  if ( INFO != 0 ) { throw INFO; }
}

void
QRLapack::
projection(
  base::ArrayP<Complex> const &A,
  base::ArrayP<Complex> &B,
  uint Bcols )
  throw (int)
{
  // left-multiply the conjugate-transpose of Q onto B

  // WORK allocation check
  if (Bcols > _cols)
  {
    WORK.allocate(Bcols);
  }

  charF SIDE = 'L';  // apply Q on the left
  charF TRANS = 'C';  // conjugate transpose
  integerF M = (integerF)_rows;
  integerF N = (integerF)Bcols;
  integerF K = (integerF)std::min(_rows, _cols);
  integerF LDA = (integerF)_rows;
  integerF LDC = (integerF)_rows;
  integerF LWORK = (integerF)Bcols;
  integerF INFO = 0;

  zunmqr_( &SIDE, &TRANS, &M, &N, &K, A.data(), &LDA, TAU.data(),
           B.data(), &LDC, WORK.data(), &LWORK, &INFO );

  if ( INFO != 0 ) { throw INFO; }

  // set the last _cols-_rows entries of B to zero
  uint i;
  for ( i = 0; i < Bcols; i++ )
  {
    uint j;
    for ( j = _cols; j < _rows; j++ )
    {
      B[i*_rows + j] = 0.0;
    }
  }

  // Project B to the _cols-dimensional subspace
  TRANS = 'N'; // no transpose

  zunmqr_( &SIDE, &TRANS, &M, &N, &K, A.data(), &LDA, TAU.data(),
           B.data(), &LDC, WORK.data(), &LWORK, &INFO );

  if ( INFO != 0 ) { throw INFO; }
}

} // namespace loop
