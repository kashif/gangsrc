/* GANG Software
 * LAB/loop/Birkhoff.C
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

#include "Common.H"
#include "Birkhoff.H"

namespace loop {

Birkhoff::
Birkhoff(
  uint polylen,
  bool upper_triangular_correction )
    :
    _polylen(polylen),
    _upper_triangular_correction(upper_triangular_correction),
    _T( new Loop4(_polylen) ),
    _R( (Loop4 *)0 ),
    _LU( new LULapack(2*(polylen+1), 2*(polylen+1) ) )
{
  uint m = 2*(_polylen+1);
  _Ax.allocate( m*m );
  _Bx.allocate( 2*m );
  if (_upper_triangular_correction)
  {
    _R = new Loop4(_polylen);
  }
}

Birkhoff::
~Birkhoff()
{
  delete _T;
  delete _LU;
  if (_upper_triangular_correction)
  {
    delete _R;
  }
}

void
Birkhoff::
factor_minus_plus(
  Loop4 &X_minus,
  Loop4 const &X )
{
  /*
    Performs Birkhoff factorization X = X_minus * X_plus as a germ at 0,
    normalized so X_minus(infinity)=I. Returns X_minus.

    Algorithm: solving two separate p-by-p linear systems.
    Perform one (2p)x(2p) LU-decompositions and two back-substitutions.

    The matrix A is

      a11[0] ... a11[-n] a12[0] ... a12[-n]
      ...
      a11[n] ... a11[0]  a12[n] ... a12[0]
      a21[0] ... a21[-n] a22[0] ... a22[-n]
      ...
      a21[n] ... a21[0]  a22[n] ... a22[0]
   */

  // sanity checks
  LOOP_DIE_IF( &X == &X_minus );
  LOOP_DIE_IF( X.polylen() != _polylen );

  setup_A( X );

  setup_B();

  // linear solve
  int r = _LU->solve( _Ax, _Bx, 2 );
  if ( r != 0 )
  {
    throw base::Exception( "error in Birkoff factorization" );
  }

  // copy result into *T
  setup_T();

  Loop4 *Result = &X_minus;

  if (_upper_triangular_correction)
  {
    Result = _R;
  }

  // X_minus = X.T
  {
  Range r;
  r.start = 0;
  r.count = _polylen+1;
  RangeMatrix _rangematrix;
  _rangematrix[0][0] = r;
  _rangematrix[0][1] = r;
  _rangematrix[1][0] = r;
  _rangematrix[1][1] = r;
  
  Result->mul(X, *_T, _rangematrix);
  }
  // set all coefficients of t^i (i>0) to 0
  Result->make_negative();

  // upper triangular correction
  // modify X_minus so X_plus(0) is upper triangular with positive diagonal
  if (_upper_triangular_correction)
  {
    upper_triangular_correction( X_minus, *Result );
  }

//  X_minus.chop();
}

void
Birkhoff::
setup_A( Loop4 const &X )
{
  uint p = _polylen + 1;

  // set up A
  uint i;
  for ( i = 0; i < 2; i++ )
  {
    uint j;
    for (j = 0; j < 2; j++ )
    {
      base::Array<Complex> const &X1 = X[j][i].data();
      uint s;
      for (s = 0; s < p; s++ )
      {
        math::blas<Real>::zcopy(
          p, X1.data() + (int(_polylen)-s), 1, _Ax.data() +
          (i*p+j*2*p*p+2*p*s), 1 );
      }
    }
  }
}

void
Birkhoff::
setup_B()
{
  uint const m = 2*(_polylen+1);

  // set up B
  math::zero( _Bx.data(), 2*m );
  _Bx[0] = 1.0;
  _Bx[3*m/2] = 1.0;
}

void
Birkhoff::
setup_T() const
{
  _T->clear();

  uint i;
  for ( i = 0; i < 2; i++ )
  {
    uint j;
    for ( j = 0; j < 2; j++ )
    {
      math::blas<Real>::zcopy(
        _polylen+1, _Bx.data() + (i+2*j)*(_polylen+1), 1, &(*_T)[j][i][0], 1 );
    }
  }
}

void
Birkhoff::
upper_triangular_correction(
  Loop4 &X, Loop4 const &R )
{
  // evaluate T at 0
  math::complex4<Real> A;

  Complex &A11 = A.col1().row1();
  Complex &A12 = A.col2().row1();
  Complex &A21 = A.col1().row2();
  Complex &A22 = A.col2().row2();

  A11 = (*_T)[0][0][0];
  A12 = (*_T)[1][0][0];
  A21 = (*_T)[0][1][0];
  A22 = (*_T)[1][1][0];

  A.inv();

  // perform QR decomposition on A via Gram-Schmidt

  // normalize first column
  Complex r = std::sqrt(A11*std::conj(A11) + A21*std::conj(A21));
  A11 /= r;
  A21 /= r;

  // align second column
  r = A12*std::conj(A11) + A22*std::conj(A21);
  A12 -= r * A11;
  A22 -= r * A21;

  // normalize second column
  r = std::sqrt(A12*std::conj(A12) + A22*std::conj(A22));
  A12 /= r;
  A22 /= r;

  X[0][0].mul(A11, R[0][0]);
  X[0][0].mul_add( A21, R[1][0]);

  X[1][0].mul(A12, R[0][0]);
  X[1][0].mul_add( A22, R[1][0]);

  X[0][1].mul(A11, R[0][1]);
  X[0][1].mul_add( A21, R[1][1]);

  X[1][1].mul(A12, R[0][1]);
  X[1][1].mul_add( A22, R[1][1]);
}

void
Birkhoff::
factor_plus_minus(
  Loop4 &X_plus,
  Loop4 const &X )
{
  /*
    Performs Birkhoff factorization X = X_plus X_minus as a germ at 0,
    normalized so X_minus(infinity)=I. Returns X_plus.

    Algorithm:
    1. Let Y = transpose(X)
    2. Perform Birkhoff factorization on Y: Y = (Y-)*(Y+) via
       factor_minus_plus(). This gives us Y-.
       Hence X = transpose(Y+) * transpose(Y-)
    3. Let X+ = X * inverse(transpose(Y-))
       Hence X = X+ * transpose(Y-).
    X+ is returned in X_plus.

    NOTE: re speed improvements:
    1. computing the factorization via factor_minus_plus() with transposes
      and inverses is slower than a direct computation
    2. transpose and inverse computations can be sped up by exchanging
      pointers rather than copying.
    3. the temporary loops Y, Z should be allocated in the constructor
  */

  // Allocate the temporary loop Y.
  Loop4 Y(_polylen);

  // set Y := transpose(X)
  Y.transpose(X);

  // Allocate the temporary loop Z.
  Loop4 Z(_polylen);

#if 0
  std::cerr << "Y=\n";
  Y.printM(std::cerr);
#endif

  // perform minus_plus Birkoff factorization on Y, returning the minus part
  // in Z, i.e.
  // compute Z := negative part of the Y=(Y-)*(Y+) Birkhoff factorization.
  factor_minus_plus( Z, Y );

#if 0
  std::cerr << "Z1=\n";
  Z.printM(std::cerr);
#endif

  // set Z := transpose(Z)
  Z.transpose();

  // Compute the inverse of Z. Put the result into Z.
  // Note: this works because the classical_adjoint is the inverse in the
  // case that det(Z) = 1
  Z.classical_adjoint();

  // Compute X_plus := X * Z.
  X_plus.mul( X, Z );

//  X_plus.chop();
}

} // namespace loop
