/* GANG Software
 * LAB/loop/LULapack.C
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

#if !defined(LAPACK_DISABLED)

#include <algorithm>
#include "math/Math.H"
#include "Common.H"
#include "LULapack.H"

extern "C"
{
  typedef char charF;
  typedef int integerF;
  typedef float realF;
  typedef std::complex<float> complexF;
  typedef double real2F;
  typedef std::complex<double>  complex2F;


  // ZGETRF - compute an LU factorization of a general M-by-N matrix A
  // using partial pivoting with row interchanges

  void zgetrf_(
    integerF *M,
    integerF *N,
    complex2F *A,
    integerF *LDA,
    integerF *IPIV,
    integerF *INFO );

  // ZGESV - compute the solution to a std::complex system of linear equations
  // AX = B

  void zgesv_(
    integerF *N,
    integerF *NRHS,
    complex2F *A,
    integerF *LDA,
    integerF *IPIV,
    complex2F *B,
    integerF *LDB,
    integerF *INFO );
}

namespace loop {

int
LULapack::
factor(
  base::ArrayP<std::complex<double> > &a )
{

  // set up the parameters
  integerF M = _rows;
  integerF N = _cols;
  complex2F *A = &a[0];
  integerF LDA = std::max(1U,_rows);
  integerF *IPIV = new integerF[std::min(_rows, _cols)];
  integerF INFO = 0;

  // perform LU factorization
  zgetrf_( &M, &N, A, &LDA, IPIV, &INFO );

  delete [] IPIV;

  return INFO;
}

int
LULapack::
solve(
  base::ArrayP<std::complex<double> > &a,
  base::ArrayP<std::complex<double> > &b, uint b_cols )
{

  LOOP_DIE_IF( _rows != _cols );
  uint n = _rows;

  // set up the parameters
  integerF N = n;
  integerF NRHS = b_cols;
  complex2F *A = &a[0];
  integerF LDA = std::max(1U,n);
  integerF *IPIV = new integerF[std::min(_rows, _cols)];
  complex2F *B = &b[0];
  integerF LDB = std::max(1U,n);
  integerF INFO = 0;

  // perform LU factorization
  zgesv_( &N, &NRHS, A, &LDA, IPIV, B, &LDB, &INFO );

  delete [] IPIV;

  return INFO;
}

} // namespace loop

#endif // !defined(LAPACK_DISABLED)
