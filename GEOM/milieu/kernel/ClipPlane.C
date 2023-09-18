/* GANG Software
 * GEOM/milieu/kernel/ClipPlane.C
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
#include "math/WriteUtil.H"
#include "ClipPlane.H"

namespace milieu {
namespace kernel {

ClipPlane::
ClipPlane()
    :
    _enable(false),
    _moving(false),
    _show(false),
    _attached(false),
    _identity()
{
  _identity.identity(4U);
  reset();
}

ClipPlane::
ClipPlane( ClipPlane const &a )
{
  copy(a);
}

ClipPlane::
~ClipPlane()
{
}

ClipPlane &
ClipPlane::
operator=( ClipPlane const &a )
{
  copy(a);
  return *this;
}

void
ClipPlane::
reset()
{
  _enable = false;
  _moving = false;
  _show = false;
  _attached = false;
}

void
ClipPlane::
copy( ClipPlane const &a )
{
  if ( this == &a ) { return; }
  _enable = a._enable;
}

void
ClipPlane::
dump( io::Ostream &o ) const
{
  char const *tab = "\t\t\t";
  o << tab << "<clipplane>\n";
  o << tab << "\t<enable>" << _enable << "</enable>\n";
  write_transform( o, position(), "\t\t\t\t" );
  o << tab << "</clipplane>\n";
}

} // namespace kernel
} // namespace milieu
