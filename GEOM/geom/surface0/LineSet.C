/* GANG Software
 * GEOM/geom/surface0/LineSet.C
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

#include "base/System.H"
#include "LineSet.H"

namespace geom {
namespace surface0 {

LineSet::
LineSet()
    :
    _line()
{
}

LineSet::
LineSet( LineSet const &a )
    :
    _line(a._line)
{
}

LineSet::
~LineSet()
{
}

LineSet &
LineSet::
operator=( LineSet const &a )
{
  if ( this == &a ) { return *this; }

  _line = a._line;

  return *this;
}

} // namespace surface0
} // namespace geom
