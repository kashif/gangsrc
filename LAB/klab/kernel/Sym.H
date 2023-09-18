/* GANG Software
 * LAB/klab/kernel/Sym.H
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

#ifndef klab_kernel_Sym_INCLUDED
#define klab_kernel_Sym_INCLUDED

#include "base/System.H"
#include "base/Use.h"
#include "math/Vector3.H"
#include "math/VectorX.H"
#include "loop/Loop4.H"
#include "math/Math.H"
#include "base/Stl.H"
#include "loop/Common.H"
#include "Sym.H"

namespace klab {
namespace kernel {

using namespace ::loop;

/*
  Computes the surface position by the Sym-Bobenko formula.

    Parameters:
    X (output)
    F (input)
    lambda (input)
    polylen (input)

    The sym formula is:

      f = ( (I lambda) dF/d(lambda) F^(-1)

    and F, F^(-1), and dF/dt are evaluated at some real-valued lambda
*/

class Sym
{

public:

  // void constructor
  Sym();

  // destructor
  virtual ~Sym() {}

  // Sym-Bobenko formula: computes the surface normal and metric.
  void
  compute(
    math::Vector3<Real> &f,
    Loop4 const &F,
    std::complex<Real> const &lambda );

private:
#if 0
  math::complex4<Real> e3;
#endif

  // disabled copy constructor
  Sym( Sym const & );

  // disabled assignment operator
  Sym &operator=( Sym const & );
};

} // namespace kernel
} // namespace klab

#endif // klab_kernel_Sym_INCLUDED
