/* GANG Software
 * GEOM/milieu/opengl/ClipPlaneSet.C
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
#include "ClipPlaneSet.H"

namespace milieu {
namespace opengl {

ClipPlaneSet::
ClipPlaneSet()
    :
    kernel::ClipPlaneSetBase(),
    _()
{
  uint i;
  for ( i = 0; i < count(); i++ )
  {
    _[i] = new ClipPlane1( i, this );
  }
}

ClipPlaneSet::
~ClipPlaneSet()
{
  uint i;
  for ( i = 0; i < count(); i++ )
  {
    delete _[i];
  }
}

void
ClipPlaneSet::
moving( uint id, bool state )
{
  ClipPlaneSetBase::moving(id, state);
  _milieu_moving_notify(state);
}

void
ClipPlaneSet::
reset()
{
  uint i;
  for ( i = 0; i < count(); i++ )
  {
    reset(i);
  }
}

void
ClipPlaneSet::
reset( uint n )
{
  _[n]->reset();
  refresh();
}

void
ClipPlaneSet::
move( motion::TransformX const &x )
{
  // disable motion with dim is not 3
  if ( x.dim() != 4U) { return; }

  uint i;
  for ( i = 0; i < count(); i++ )
  {
    if ( (*this)[i].moving() ) { (*this)[i].move(x); }
  }
}

void
ClipPlaneSet::
draw() const
{
  uint i;
  for ( i = 0; i < count(); i++ )
  {
    (*this)[i].draw();
  }
}

} // namespace opengl
} // namespace milieu
