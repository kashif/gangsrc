/* GANG Software
 * GEOM/geom/surfacegl/Drawer.C
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

#include <GL/gl.h>
#include "base/System.H"
#include "base/Regex.H"
#include "math/Matrix4.H"
#include "opengl/OpenGL.H"
#include "Drawer.H"

namespace geom {
namespace surfacegl {

Drawer::
Drawer()
    :
    _use_transform (false),
    _enable_display_list(true),
    _current_context( (GLXContext)0 )
{
}

Drawer::
~Drawer()
{
}

void
Drawer::
draw( surface0::GeomObject const *g ) const
{
  _geomobject = g;

  if ( _materials->draw(MaterialSet::SILHOUETTE) )
  { _geomobject->changed(true); }

  _use_transform = false;

  // NOTE: should do glDeleteLists()
  // NOTE: change of context may possible have same pointer,
  //   so that display list is called when it should be created
  if ( _enable_display_list )
  {
    uint n = (GLuint)(_geomobject->id());

    GLXContext const context = glXGetCurrentContext();

    if ( _geomobject->is_changed() || context != _current_context )
    {
//      std::cerr << "creating list: surface=" << n << "\n";
      glNewList( n, GL_COMPILE_AND_EXECUTE );
      _draw();
      glEndList();
      _geomobject->changed(false);
      _current_context = context;
    }
    else
    {
//      std::cerr << "using list: surface=" << n << "\n";
      glCallList( n );
    }
  }
  else
  {
    _draw();
    _geomobject->changed(true);
  }

  _geomobject = (surface0::GeomObject *)0;
}

void
Drawer::
draw(
  surface0::GeomObject const *g,
  geom::Transform const &transform,
  geom::ProjectionMode mode ) const
{
  _geomobject = g;

  if ( _materials->draw(MaterialSet::SILHOUETTE) )
  { _geomobject->changed(true); }

  _use_transform = true;
  _transform = transform;

  _projection_mode = mode;

  // always redraw
  _draw();

  _geomobject = (surface0::GeomObject *)0;
}

} // namespace surfacegl
} // namespace geom
