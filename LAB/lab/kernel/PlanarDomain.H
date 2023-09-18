/* GANG Software
 * LAB/lab/kernel/PlanarDomain.H
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

#ifndef lab_kernel_PlanarDomain_INCLUDED
#define lab_kernel_PlanarDomain_INCLUDED

#include <complex>
#include "base/System.H"
#include "base/Exception.H"
#include "Common.H"

namespace lab {
namespace kernel {

class PlanarDomain
{

public:
  // constructor
  PlanarDomain();

  // copy constructor
  PlanarDomain( PlanarDomain const & );

  // destructor
  virtual ~PlanarDomain();

  // assignment operator
  PlanarDomain &operator=( PlanarDomain const & );

  uint count0() const
    { return _count0; }

  uint count1() const
    { return _count1; }

  virtual Complex z( uint i, uint j ) const = 0;

protected:

  uint _count0, _count1;

  static uint const COUNT_MIN = 2U;

private:

};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_PlanarDomain_INCLUDED
