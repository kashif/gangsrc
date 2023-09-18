/* GANG Software
 * GEOM/milieu/opengl/Milieu.C
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

#include "Milieu.H"

namespace milieu {
namespace opengl {

Milieu::
Milieu()
    :
    kernel::MilieuBase(),
    opengl::Background(),
    opengl::Blend(),
    opengl::ClipPlaneSet(),
    opengl::Camera(),
    opengl::GlobalLight(),
    opengl::LightSet()
{
}

Milieu::
~Milieu()
{
}

void
Milieu::
move( motion::TransformX const &x )
{
  ClipPlaneSet::move(x);
  LightSet::move(x);
}

void
Milieu::
draw() const
{
  Background::draw();
  Blend::draw();
  Camera::draw();
  ClipPlaneSet::draw();
  GlobalLight::draw();
  LightSet::draw();
}

void
Milieu::
_milieu_moving_notify(bool state)
{
  // check whether any light or clipplane is moving
  bool r = false;
  for ( uint i = 0; i < LightSet::count(); i++ )
  {
    r |= LightSet::moving(i);
  }
  for ( uint i = 0; i < ClipPlaneSet::count(); i++ )
  {
    r |= ClipPlaneSet::moving(i);
  }

  milieu_moving_notify(r);
}

} // namespace opengl
} // namespace milieu
