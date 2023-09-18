/* GANG Software
 * LAB/cmclab/kernel/Integrator.H
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

#ifndef cmclab_kernel_Integrator_INCLUDED
#define cmclab_kernel_Integrator_INCLUDED

#include <math.h>
#include <complex>
#include "base/vector.H"
#include "base/System.H"
#include "math/Math.H"
#include "math/Complex2.H"
#include "loop/Common.H"
#include "loop/Loop4.H"
#include "loop/EvalLoop.H"
#include "lab/kernel/Curve.H"
#include "lab/kernel/Lab.H"

using namespace ::loop;
namespace cmclab {
namespace kernel {

typedef Loop4 Potential;

/*
  CMC integrator.
*/

class
Integrator
{
public:

  // constructor
  Integrator( EvalLoop *, uint polylen );

  // destructor
  ~Integrator();

  // integrate from z to z+dz in step_count steps
  void integrate(
    Complex &z,
    Potential &xi,
    Loop4 &X,
    Complex const &dz,
    uint step_count );

  // integrate along curve
  void integrate(
    Loop4 &X,
    lab::kernel::Curve const &curve );

protected:

  /*
    performs one step of the integration of the ODE dX/dz = X A
    order-4 Runge-Kutta
    modifies X
  */
  void integrate_(
    Complex &z,
    Potential &xi,
    Loop4 &X,
    Complex const &dz );

  //
  void mul(
    Loop4 &,
    Loop4 const &,
    Potential &xi );

  /*
    F defines the differential equation dX = F( z, X )
    the raw (naive, unormalized) F is defined by F(x, xi) = X.xi
    matrix multiplication
  */
  inline void F(
    Loop4 &dX,
    Loop4 const &X,
    Potential &xi
    );

  //
  uint _polylen;
  //
  EvalLoop *_potential;
  RangeMatrix _range;

  //
  Loop4 *K1;
  //
  Loop4 *K2;
  //
  Loop4 *K3;
  //
  Loop4 *K4;
  //
  Loop4 *Ktmp;

private:
  //
  Integrator( Integrator const & );
  //
  Integrator &operator=( Integrator const & );
};

} // namespace kernel
} // namespace cmclab

#endif // cmclab_kernel_Integrator_INCLUDED
