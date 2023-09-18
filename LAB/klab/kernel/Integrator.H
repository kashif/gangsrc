/* GANG Software
 * LAB/klab/kernel/Integrator.H
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

#ifndef klab_kernel_Integrator_INCLUDED
#define klab_kernel_Integrator_INCLUDED

#include <math.h>
#include "base/vector.H"
#include "base/System.H"
#include "base/Array.H"
#include "math/Math.H"
#include "math/Complex2.H"
#include "lab/kernel/Lab.H"
#include "loop/Common.H"
#include "loop/Loop4.H"
#include "loop/EvalLoop.H"

using namespace ::loop;

namespace klab {
namespace kernel {

typedef Loop4 Potential;

/*
  KLab integrator.
*/

class
Integrator
{
public:

  // constructor
  Integrator( EvalLoop *, uint polylen );

  // destructor
  ~Integrator();

  // integrate from z to z+dz in 'step_count' steps
  void integrate(
    Real &x,
    Potential &xi,
    Loop4 &g,
    Real const &dx,
    uint step_count );

protected:

private:

  /* perform one step of the integration of the ODE dX/dz = X A
     order-4 Runge-Kutta
     modifies g
  */
  void integrate_(
    Real const &x,
    Potential &xi,
    Loop4 &g,
    Real const &dx );

  // length of Fourier series (highest lambda power)
  uint _polylen;

  // the potential
  EvalLoop *_potential;

  RangeMatrix _range;

  //
  inline void mul(
    Loop4 &R,
    Loop4 const &,
    Potential const &xi );

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

  // disabled copy constructor
  Integrator( Integrator const & );
  // disabled assignment operator
  Integrator &operator=( Integrator const & );
};

} // namespace kernel
} // namespace klab

#endif // klab_kernel_Integrator_INCLUDED
