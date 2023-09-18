/* GANG Software
 * GEOM/milieu/opengl/ClipPlane.C
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

#include "opengl/OpenGL.H"
#include "ClipPlane.H"

namespace milieu {
namespace opengl {

// the xy coordinate plane
double const ClipPlane::
standard_clipplane[4] = {0.0f, 0.0f, 1.0f, 0.0f};

ClipPlane::
ClipPlane( uint id )
    :
    ::milieu::kernel::ClipPlane(),
    Mobile(3U, motion::CENTRAL),
    _id(id)
{
}

ClipPlane::
~ClipPlane()
{
}

void
ClipPlane::
reset()
{
  // reset position
  motion::Place place;
  place.position.identity(4U);
  place.rotation.identity(4U);
  place.translation.identity(4U);
  motion::Center center;
  center.set(0.0);
  set( place, center, motion::CENTRAL );

  // baseclass version
  kernel::ClipPlane::reset();
}

void
ClipPlane::
enable( bool state )
{
  ::milieu::kernel::ClipPlane::enable(state);
#ifndef __linux__
  ::opengl::glenable( GLenum(GL_CLIP_PLANE0 + _id), state );
#endif
#if 0
  clipplane_enable( _id, state );
#endif
  refresh();
}

void
ClipPlane::
moving( bool state )
{
  ::milieu::kernel::ClipPlane::moving(state);
#if 0
  clipplane_moving( _id, state );
#endif
  refresh();
}

void
ClipPlane::
show( bool state )
{
  ::milieu::kernel::ClipPlane::show(state);
  refresh();
}

void
ClipPlane::
attached( bool state )
{
  ::milieu::kernel::ClipPlane::moving(state);
#if 0
  clipplane_attached( _id, state );
#endif
  refresh();
}

void
ClipPlane::
draw() const
{
#ifndef __linux__
  ::opengl::glenable( GLenum(GL_CLIP_PLANE0 + _id), enable() );
#endif
  draw_position();
}

void
ClipPlane::
draw_position() const
{
  // position the clipplane
  if ( enable() )
  {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    ::opengl::glLoadMatrix( _place.position );
#ifndef __linux__
    glClipPlane( GL_CLIP_PLANE0 + _id, standard_clipplane );
#endif
    glPopMatrix();
  }

  // show the clipplane
  if ( show() )
  {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    ::opengl::glLoadMatrix( _place.position );

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glBegin(GL_POLYGON);
    glVertex3d( -1.0, -1.0, 0.0 );
    glVertex3d( 1.0, -1.0, 0.0 );
    glVertex3d( 1.0, 1.0, 0.0 );
    glVertex3d( -1.0, 1.0, 0.0 );
    glEnd();
    glPopAttrib();

    glPopMatrix();
  }
}

} // namespace opengl
} // namespace milieu
