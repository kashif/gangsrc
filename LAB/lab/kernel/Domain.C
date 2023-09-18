/* GANG Software
 * LAB/lab/kernel/Domain.C
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

#include "Exception.H"
#include "Domain.H"

namespace lab {
namespace kernel {

Domain::
Domain( DomainBase *base )
    :
    _stop(false),
    _configuration(),
    _dim(3U),
    _spaceform(),
    _base(base)
{
}

Domain::
~Domain()
{
}

void
Domain::
check_stopped()
{
  if (_stop)
  {
    _stop = false;
    throw Exception(Exception::STOP);
  }
}

} // namespace kernel
} // namespace lab
