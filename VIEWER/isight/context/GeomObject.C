/* GANG Software
 * VIEWER/isight/context/GeomObject.C
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

#include "math/Vector3.H"
#include "opengl/OpenGL.H"
#include "GeomObject.H"

namespace isight {
namespace context {

GeomObject::
GeomObject( 
  geom::SurfaceGL const *g,
  motion::Place const &position,
  motion::Center const &center,
  motion::ProjectionMode mode )
    :
    motion::Mobile( position, center, mode ),
    _showing(true),
    _moving(true),
    _fast(true),
    _geomobject(g)
{
}

GeomObject::
~GeomObject()
{
}

void
GeomObject::
set_movemode(
  bool fast )
{
  _geomobject->changed();
  _fast = fast;
}

void
GeomObject::
draw() const
{
  // sanity checks
  DIE_IF( _place.position.dim() != _matrix_dim );
  DIE_IF( _geomobject == (geom::SurfaceGL *)0 );

#if 0
  // DUMP
  std::cerr << (void *)this << "\n";
  std::cerr << "position: " << _place.position << "\n";
#endif

  // NOTE: should GeometryMode==CONFORMAL use OpenGL transforms?
  if ( _fast )
  {
    // fast draw using OpenGL to transform surface
    glMatrixMode(GL_MODELVIEW);
    opengl::glLoadMatrix( _place.position );

    _geomobject->draw();
  }
  else
  {
    // draw using custom transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _geomobject->draw(
      _place.position,
      geom::SurfaceGL::ProjectionMode(_projection_mode) );
  }
}

} // namespace context
} // namespace isight
