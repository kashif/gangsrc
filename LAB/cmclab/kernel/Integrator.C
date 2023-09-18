/* GANG Software
 * LAB/cmclab/kernel/Integrator.C
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

#include "loop/Common.H"
#include "Integrator.H"

namespace cmclab {
namespace kernel {

Integrator::
Integrator(
  EvalLoop *potential,
  uint polylen )
{
  _potential = potential;
  _range = _potential->range();
  _polylen = polylen;
  K1 = new Loop4( _polylen );
  K2 = new Loop4( _polylen );
  K3 = new Loop4( _polylen );
  K4 = new Loop4( _polylen );
  Ktmp = new Loop4( _polylen );
}

Integrator::
~Integrator()
{
  delete K1;
  delete K2;
  delete K3;
  delete K4;
  delete Ktmp;
}

void
Integrator::
integrate(
  Complex &z,
  Potential &xi,
  Loop4 &X,
  Complex const &dz,
  uint step_count )
{
  DIE_IF( step_count == 0 );

  if ( ! math::effectively_zero( dz ) )
  {
    Complex dz_ = dz / Real(step_count);
    Complex z_;

    uint i;
    for ( i = 0; i < step_count; i++ )
    {
      z_ = z + Real(i) * dz_;
      // perform one integration step
      integrate_( z_, xi, X, dz_ );
    }
  }

  // update z
  z += dz;
}

void
Integrator::
integrate_(
  Complex &z,
  Potential &xi,
  Loop4 &X,
  Complex const &dz )
{
  DIE_IF( math::isnan(X.col1().row1().data()[0]) );

  Real const half = 0.5;
  Real const s3 = Real(1.0)/Real(3.0);
  Real const s6 = Real(1.0)/Real(6.0);

  // K1 = dz * F( z, X );
  // K2 = dz * F( z + 0.5 * dz, X + 0.5 * K1 );
  // K3 = dz * F( z + 0.5 * dz, X + 0.5 * K2 );
  // K4 = dz * F( z + dz, X + K3 );
  // X[n+1] = X[n] + (1/6)(K1 + 2 K2 + 2 K3 + K4)  + O(dz^5)

  //---------------------------------
  // step 1: compute K1
  // use original value for xi
  mul( *K1, X, xi );

  // K1 = dz * K1
  K1->mul(dz);

  //---------------------------------
  // step 2: compute K2

  // Ktmp = X + 0.5*K1
  Ktmp->mul_add( X, half, *K1 );

  _potential->evaluate( xi, z+half*dz );

  // K2 = Ktmp * xi
  F( *K2, *Ktmp, xi );

  // K2 = dz * K2
  K2->mul( dz );

  //---------------------------------
  // step 3: compute K3

  // Ktmp = X + 0.5*K1
  Ktmp->mul_add( X, half, *K2 );

  // K3 = Ktmp * xi
  // use previous value for xi
  F( *K3, *Ktmp, xi );

  // K3 = dz * K3
  K3->mul( dz );

  //---------------------------------
  // step 4: compute K4
  Ktmp->add( X, *K3 );

  _potential->evaluate( xi, z+dz );

  // K4 = Ktmp * xi
  F( *K4, *Ktmp, xi );

  // K4 = dz * K4
  K4->mul( dz );

  //---------------------------------
  // final step: compute new X

  // Ktmp = 1/6 K1 + 1/3 K2 + 1/3 K3 + 1/6 K4
  X.mul_add( s6, *K1 );
  X.mul_add( s3, *K2 );
  X.mul_add( s3, *K3 );
  X.mul_add( s6, *K4 );

  if ( math::isnan(X.col1().row1().data()[0]) )
  {
    throw base::Exception( "nan in integration" );
  }
}

void
Integrator::
F(
  Loop4 &dX,
  Loop4 const &X,
  Potential &xi )
{
  mul( dX, X, xi );
}

void
Integrator::
mul(
  Loop4 &R,
  Loop4 const &X,
  Potential &xi )
{
  // R = X . xi
  R.mul(X, xi, _range );
}

void
Integrator::
integrate(
  Loop4 &X,
  lab::kernel::Curve const &curve )
{
  Complex z2;

  uint step_count = curve.count();
  DIE_IF(step_count < 2);

  Complex z1 = curve.z(0);

  // compute potential at z1
  Potential xi(_polylen);

  _potential->evaluate( xi, z1 );

  uint i;
  for ( i = 1; i < step_count; i++ ) // starts at 1
  {
    z2 = curve.z(i);
    // perform one integration step
    integrate_( z1, xi, X, z2-z1 );
    z1 = z2;
  }
}

} // namespace kernel
} // namespace cmclab
