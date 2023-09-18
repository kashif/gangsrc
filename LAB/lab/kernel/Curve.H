/* GANG Software
 * LAB/lab/kernel/Curve.H
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

#ifndef lab_kernel_Curve_INCLUDED
#define lab_kernel_Curve_INCLUDED

#include "base/System.H"
#include "base/String.H"
#include "Common.H"

namespace lab {
namespace kernel {

/*
  Abstract base class representing a one-dimensional domain (curve).
 */

class Curve
{

public:

  // destructor
  virtual ~Curve() {}

  //
  virtual Complex z(uint) const = 0;

  //
  virtual uint count() const = 0;

protected:

private:

  // no constructors
#if 0
  Curve();
  Curve( Curve const & );
#endif

  // disabled assignment operator
  Curve &operator=( Curve const & );
};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_Curve_INCLUDED
