/* GANG Software
 * GEOM/geom/interface/SurfaceGL.C
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

#include "geom/surfacegl/Surface.H"
#include "SurfaceGL.H"

namespace geom {

SurfaceGL::
SurfaceGL()
    :
    Surface(false),
    _( new surfacegl::Surface )
{
  Surface::_ = _;
}

SurfaceGL::
SurfaceGL( SurfaceGL const &x )
    :
    Surface(false),
    _( new surfacegl::Surface(*x._) )
{
  Surface::_ = _;
}

SurfaceGL::
~SurfaceGL()
{
  // delete is done by base class
}

SurfaceGL &
SurfaceGL::
operator=( SurfaceGL const &x )
{
  if ( this == &x ) { return *this; }
  _->operator=(*x._);
  return *this;
}

void
SurfaceGL::
draw() const
{
  _->draw();
}

void
SurfaceGL::
draw(
  Transform const &transform,
  ProjectionMode mode ) const
{
  _->draw(transform, geom::ProjectionMode(mode) );
}

void
SurfaceGL::
changed() const
{
  _->changed();
}

} // namespace geom
