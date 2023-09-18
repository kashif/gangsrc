/* GANG Software
 * GEOM/milieu/opengl/Camera.C
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
#include "base/System.H"
#include "Camera.H"

namespace milieu {
namespace opengl {

Camera::
Camera()
{
}

Camera::
Camera( Camera const & )
{
}

Camera::
~Camera()
{
}

Camera &
Camera::
operator=( Camera const & )
{
  return *this;
}

void
Camera::
set_camera( milieu::Camera const &cam )
{
  kernel::Camera::set_camera(cam);
  draw();
  refresh();
}

void
Camera::
reset_camera( CameraMode mode )
{
  kernel::Camera::reset_camera(mode);
  draw();
  refresh();
}

void
Camera::
set_window_size( uint width, uint height )
{
  ::milieu::kernel::Camera::set_window_size( width, height );
  draw();
  refresh();
}

void
Camera::
draw() const
{
  // set the camera
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if ( mode() == PERSPECTIVE )
  {
    base::ArrayX<double,6U> const &b = perspective_camera_gl();
    glFrustum(b[0],b[1],b[2],b[3],b[4],b[5]);
  }
  else if ( mode() == ORTHOGRAPHIC )
  {
    base::ArrayX<double,6U> const &b = orthographic_camera_gl();
    glOrtho(b[0],b[1],b[2],b[3],b[4],b[5]);
  }
  else
  {
    DIE();
  }
}

} // namespace opengl
} // namespace milieu
