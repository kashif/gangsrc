/* GANG Software
 * LAB/klab/kernel/Integrator.C
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

namespace klab {
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

// destructor
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
  Real &x,
  Potential &xi,
  Loop4 &g,
  Real const &dx,
  uint step_count )
{
  /*
    z = point in domain
    xi = the potential
    gx, gy = as input, the solution of the ODE at z
      as output, the solution of the ODE at z + dz
    dz = the step in the domain (integration from z to z+dz)
    step_count = the line from z to z+dz is divided into 'step_count' equal
      parts. Integration is done in this many steps.
  */

  DIE_IF( step_count == 0 );

  if ( ! math::effectively_zero( dx ) )
  {
    Real dx_ = dx / Real(step_count);
    Real x_;

    uint i;
    for ( i = 0; i < step_count; i++ )
    {
      x_ = x + Real(i) * dx_;
      // perform one integration step
      integrate_( x_, xi, g, dx_ );
    }
  }

  // update x
  x += dx;
}

void
Integrator::
integrate_(
  Real const &x,
  Potential &xi,
  Loop4 &X,
  Real const &dx )
{
  /*
    Integrator one step

    Input:
    x = real input value
    xi = potential
    g = solutions to ODE at z
    dx = step

    K1 = dx * F( x, X );
    K2 = dx * F( x + 0.5 * dx, X + 0.5 * K1 );
    K3 = dx * F( x + 0.5 * dx, X + 0.5 * K2 );
    K4 = dx * F( x + dx, X + K3 );
    X[n+1] = X[n] + (1/6)(K1 + 2 K2 + 2 K3 + K4)  + O(dx^5)
  */

  // sanity check
  DIE_IF( math::isnan(X.col1().row1().data()[0]) );

  Real const half = 0.5;
  Real const s3 = Real(1.0)/Real(3.0);
  Real const s6 = Real(1.0)/Real(6.0);

  //---------------------------------
  // step 1: compute K1
  mul( *K1, X, xi );

  // K1 = dx * K1
  K1->mul(dx);

  //---------------------------------
  // step 2: compute K2

  // Ktmp = X + 0.5*K1
  Ktmp->mul_add( X, half, *K1 );

  _potential->evaluate( xi, x + half*dx );

  // K2 = Ktmp.xi
  mul( *K2, *Ktmp, xi );

  // K2 = dx * K2
  K2->mul( dx );

  //---------------------------------
  // step 3: compute K3

  // Ktmp = X + 0.5*K1
  Ktmp->mul_add( X, half, *K2 );
  // use previous value for xi
  mul( *K3, *Ktmp, xi );

  // K3 = dx * K3
  K3->mul( dx );

  //---------------------------------
  // step 4: compute K4
  Ktmp->add( X, *K3 );

  _potential->evaluate( xi, x + dx );

  // K4 = Ktmp.xi
  mul( *K4, *Ktmp, xi );

  // K4 = dx * K4
  K4->mul( dx );

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
mul(
  Loop4 &R,
  Loop4 const &X,
  Potential const &xi )
{
  // R = X . xi
  R.mul( X, xi, _range );
}

} // namespace kernel
} // namespace klab
