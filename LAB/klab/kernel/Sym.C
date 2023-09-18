/* GANG Software
 * LAB/klab/kernel/Sym.C
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
#include "Sym.H"
#include "loop/Common.H"

namespace klab {
namespace kernel {

Sym::
Sym()
{
#if 0
  e3.col1().row1() = Complex( 1.0 );
  e3.col1().row2() = Complex( 0.0 );
  e3.col2().row1() = Complex( 0.0 );
  e3.col2().row2() = Complex( -1.0 );
#endif
}

void
Sym::
compute(
  math::Vector3<Real> &X,
  Loop4 const &F,
  std::complex<Real> const &lambda )
{
  /* The Sym formula for K-surfaces

     input: F, a unitary frame in SU(2)
     output: Compute f := dF/dt F^(-1) evaluated at t, where lambda = exp(t)
       Set X = the image of f under the map su(2)->R^3.

     NOTE: moving through the associate family could be sped up by
       pre-computing the loop X, so that only an evaluation of X at lambda
       is required.
     NOTE: could renormalize X to put it into su(2), to correct numerical skew
       in the Birkhoff factorization.
  */

  // F1, dF1, F1_inv and f are constant matrices, not loops

  // Evaluate F1 := F(t) and dF1 := (dF/dt)(t).
  // eval_deriv() takes lambda as input, but actually computes the
  //   derivative with respect to t, where lambda = exp(t).

#if 0
  std::cerr << "F=\n";
  F.printM(std::cerr);
  std::cerr << "F=\n\n";
#endif

  // compute F(lambda) and dF(lambda)
  math::complex4<Real> F1, dF1;
  F.eval( F1, dF1, lambda );

  // compute Finv(lambda)
  math::complex4<Real> F1inv;
  F1inv.inv( F1 );

  // compute f = dF(lambda) Finv(lambda)
  math::complex4<Real> f;
  f.mul(dF1, F1inv);

  // make f trace-free
  std::complex<Real> trace = 0.5 * (f.col1().row1() + f.col2().row2());
  f.col1().row1() -= trace;
  f.col2().row2() -= trace;

  // Set X to the image of f under the isomorphism su(2) -> R^3
  X.x = f.col1().row1().imag();
  X.y = f.col2().row1().real();
  X.z = f.col2().row1().imag();

  // check for error
  if ( math::isnan(X.x) || math::isnan(X.y) || math::isnan(X.z) )
  {
    throw base::Exception( "nan in Sym formula" );
  }
}

} // namespace kernel
} // namespace klab
