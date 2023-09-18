/* GANG Software
 * LAB/lab/kernel/PlanarDomain.C
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

#include "PlanarDomain.H"

namespace lab {
namespace kernel {

PlanarDomain::
PlanarDomain()
    :
    _count0(0),
    _count1(0)
{
}

PlanarDomain::
PlanarDomain( PlanarDomain const &a )
    :
    _count0( a._count0 ),
    _count1( a._count1 )
{
}

PlanarDomain::
~PlanarDomain()
{
}

PlanarDomain &
PlanarDomain::
operator=( PlanarDomain const &a )
{
  if (this == &a ) { return *this; }
  _count0 = a._count0;
  _count1 = a._count1;
  return *this;
}

} // namespace kernel
} // namespace lab
