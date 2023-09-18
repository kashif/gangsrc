/* GANG Software
 * LAB/cmclab/kernel/Sym.C
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

#include <complex>
#include "loop/Common.H"
#include "Sym.H"

namespace cmclab {
namespace kernel {

Sym::
Sym()
{
  e3.col1().row1() = Complex( 0.0, -1.0 );
  e3.col1().row2() = Complex( 0.0 );
  e3.col2().row1() = Complex( 0.0 );
  e3.col2().row2() = Complex( 0.0, 1.0 );
}

void
Sym::
R3(
  math::Vector3<Real> &X,
  Loop4 const &F,
  Real const &mean_curvature,
  Complex const &lambda,
  Real const &normalshift )
{
  /*
    Sym formula for CMC surface in R^3

    Sym[F] = -1/H( 2 F' F^(-1) + n F e3 F^(-2) )
      where n = 0, 1/2, 1 for CMC, K, parallelCMC
  */

  // Sym formula
  math::complex4<Real> F1, dF1;

  // evaluate F1 := F(t) and dF1 := (dF/dt)(t)
  F.eval( F1, dF1, lambda );
  dF1.mul( 2.0 * Complex(0.0, 1.0) * lambda );

  math::complex4<Real> f;

  if ( normalshift == Real(1.0) )
  {
    f = dF1;
  }
  else
  {
    math::complex4<Real> tmp;

    // tmp := F1 * e3
    tmp.mul( F1, e3 );

    // shift off of the normal    f := dF1 + normalshift * F1 * e3
    f.mul_add( dF1, 0.5*(1.0 - normalshift), tmp );
  }

  math::complex4<Real> invF1;

  // compute the inverse of F1     invF1 := F1^(-1)
  invF1.inv( F1 );

  // multiply by the inverse       f := f * invF1
  f.mul( f, invF1 );

  // multiply by the mean curvature   f := -1/H f
  f.mul( -1.0 / mean_curvature );

  // make f trace-free
  Complex trace_av = 0.5 * ( f.col1().row1() + f.col2().row2() );
  f.col1().row1() -= trace_av;
  f.col2().row2() -= trace_av;

  // map to R^3
  X.x = -std::imag( f.col2().row1() );
  X.y = -std::real( f.col2().row1() );
  X.z = -std::imag( f.col1().row1() );

  if ( math::isnan(X.x) || math::isnan(X.y) || math::isnan(X.z) )
  {
    throw ( base::Exception( "nan in Sym formula" ) );
  }
}

void
Sym::
S3(
  math::VectorX<Real,4U> &X,
  Loop4 const &F,
  Complex &lambda1,
  Complex &lambda2 )
{
  /*
    Sym formula for CMC surface in S^3

    F1 * L * F2^(-1), where
      F1 = F(lambda1)
      F2 = F(lambda2)
      L = diag( sqrt(lambda2/lambda1), sqrt(lambda1/lambda2) )
  */

  // evaluate F at lambda1
  math::complex4<Real> F1;
  F.eval( F1, lambda1 );

  // evaluate F2 at lambda2
  math::complex4<Real> F2;
  F.eval( F2, lambda2 );

#if 0
  Complex g = std::sqrt(lambda2/lambda1);
  math::complex4<Real> L;
  L.col1().row1() = g;
  L.col2().row1() = 0.0;
  L.col1().row2() = 0.0;
  L.col2().row2() = 1.0/g;

  // multiply F1 by L
  F1.mul(F1, L);
#endif

  // invert F2
  F2.inv();

  // compute F1 = F1 L (F2)^{-1}
  F1.mul(F1, F2);

  // normalize: divide by square root of det
  Complex d;
  F1.det( d );
  d = std::sqrt(d);
  if ( math::effectively_zero(d) )
  { throw ( base::Exception( "nan in Sym formula" ) ); }

  F1.mul( 1.0/d );

  X[0] = std::real(F1.col1().row1());
  X[1] = std::imag(F1.col1().row1());
  X[3] = std::real(F1.col1().row2());
  X[2] = std::imag(F1.col1().row2());
}

void
Sym::
H3(
  math::VectorX<Real,4U> &X,
  Loop4 const &F,
  Complex &lambda )
{
  /*
    Sym formula for CMC surface in H^3

    F(lambda) Conj[Trans[F(lambda)]]
  */

  // evaluate F at lambda1
  math::complex4<Real> F1;
  F.eval( F1, lambda );

  // F2 = conjugate_transpose[F1]
  math::complex4<Real> F2;
  F2.col1().row1() = std::conj(F1.col1().row1());
  F2.col2().row1() = std::conj(F1.col1().row2());
  F2.col1().row2() = std::conj(F1.col2().row1());
  F2.col2().row2() = std::conj(F1.col2().row2());

  // multiply F1 by F2
  F1.mul(F1, F2);

  // normalize: divide by square root of det
  Complex d;
  F1.det( d );
  d = std::sqrt(d);
  if ( math::effectively_zero(d) )
  { throw ( base::Exception( "nan in Sym formula" ) ); }

  F1.mul( 1.0/d );

  // take components
  Real r1 = std::real( F1.col1().row1() );
  Real r2 = std::real( F1.col2().row2() );
  Real s1 = std::real( F1.col1().row2() );
  Real s2 = std::imag( F1.col1().row2() );

  X[0] = 0.5 * (r1 - r2);
  X[1] = s1;
  X[2] = s2;
  X[3] = -0.5 * (r1 + r2);
}

} // namespace kernel
} // namespace cmclab
