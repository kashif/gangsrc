/* GANG Software
 * GEOM/milieu/opengl/LightSet.C
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
#include "LightSet.H"

namespace milieu {
namespace opengl {

LightSet::
LightSet()
    :
    kernel::LightSetBase(),
    _()
{
  uint i;
  for ( i = 0; i < count(); i++ )
  {
    _[i] = new Light1( i, this );
    _reset(i);
  }
}

LightSet::
~LightSet()
{
  uint i;
  for ( i = 0; i < count(); i++ )
  {
    delete _[i];
  }
}

void
LightSet::
moving( uint id, bool state )
{
  LightSetBase::moving(id, state);
  _milieu_moving_notify(state);
}

void
LightSet::
reset()
{
  uint i;
  for ( i = 0; i < count(); i++ )
  {
    _reset(i);
  }
}

void
LightSet::
reset( uint n )
{
  _[n]->reset();
  _reset(n);
  refresh();
}

void
LightSet::
_reset(uint n)
{
  if (n <=2 )
  {
    _[n]->kernel::Light::enable( true );
    _[n]->kernel::Light::diffuse( base::Color3( 0.5f, 0.5f, 0.5f ) );
    motion::Transform t;
    t.allocate(4U);
    t.identity();
    t[3U][n] = 8.0;
    (*this)[n].translation(t);
    (*this)[n].position(t);
  }
}

void
LightSet::
move( motion::TransformX const &x )
{
  // disable motion with dim is not 3
  if ( x.dim() != 4U) { return; }

  uint i;
  for ( i = 0; i < count(); i++ )
  {
    if ( (*this)[i].moving()) { (*this)[i].move(x); }
  }
}

void
LightSet::
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
