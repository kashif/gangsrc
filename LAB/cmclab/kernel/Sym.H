/* GANG Software
 * LAB/cmclab/kernel/Sym.H
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

#ifndef cmclab_kernel_Sym_INCLUDED
#define cmclab_kernel_Sym_INCLUDED

#include "base/System.H"
#include "base/Use.h"
#include "math/Vector3.H"
#include "math/VectorX.H"
#include "loop/Loop4.H"
#include "math/Math.H"
#include "base/Stl.H"
#include "loop/Common.H"
#include "Sym.H"

namespace cmclab {
namespace kernel {

using namespace ::loop;

/*
  Sym formulas for R^3, S^3, H^3
*/
class Sym
{

public:

  // void constructor
  Sym();

  // destructor
  virtual ~Sym() {}

  // Sym formula for CMC surface in R^3
  void
  R3(
    math::Vector3<Real> &f,
    Loop4 const &F,
    Real const &mean_curvature,
    Complex const &lambda,
    Real const &normalshift );

  // Sym formula for CMC surface in S^3
  void
  S3(
    math::VectorX<Real,4U> &X,
    Loop4 const &F,
    Complex &lambda1,
    Complex &lambda2 );

  // Sym formula for CMC surface in H^3
  void
  H3(
    math::VectorX<Real,4U> &X,
    Loop4 const &F,
    Complex &lambda1 );

protected:

private:
  math::complex4<Real> e3;

  // disabled copy constructor
  Sym( Sym const & );

  // disabled assignment operator
  Sym &operator=( Sym const & );
};


} // namespace kernel
} // namespace cmclab

#endif // cmclab_kernel_Sym_INCLUDED
