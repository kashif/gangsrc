/* GANG Software
 * GEOM/milieu/ui/Camera.C
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

#include "math/Math.H"
#include "milieu/opengl/Camera.H"
#include "Camera.H"

namespace milieu {
namespace ui {

Camera::
Camera()
    :
    _perspective_camera( milieu::kernel::default_perspective_camera ),
    _orthographic_camera( milieu::kernel::default_orthographic_camera )
{
}

Camera::
~Camera()
{
}

void
Camera::
set_camera( milieu::Camera const &cam )
{
  if (cam.mode == milieu::PERSPECTIVE)
  {
    _perspective_camera = cam;
  }
  else if (cam.mode == milieu::ORTHOGRAPHIC)
  {
    _orthographic_camera = cam;
  }
  else
  {
    DIE();
  }
  camera()->set_camera(cam);
  camera_synchronize();
}

milieu::Camera const &
Camera::
get_camera() const
{
  return camera()->get_camera();
}

void
Camera::
reset_camera( CameraMode mode )
{
  if (mode == milieu::PERSPECTIVE)
  {
    camera()->set_camera(_perspective_camera);
  }
  else if (mode == milieu::ORTHOGRAPHIC)
  {
    camera()->set_camera(_orthographic_camera);
  }
  camera_synchronize();
}

void
Camera::
camera_synchronize()
{
  milieu::Camera const &cam = camera()->get_camera();

  uint n = 0;
  if (cam.mode == PERSPECTIVE)
  { n = 0; }
  else if (cam.mode == ORTHOGRAPHIC)
  { n = 1; }
  else
  { DIE(); }

  camera_choice_w()->set_blocked( n );
  if (n == 0)
  {
    base::ArrayX<float,3U> a;
    a[0] = cam.fov;
    a[1] = cam.znear;
    a[2] = cam.zfar;
    camera_perspective_w()->set_blocked(a.data());
  }
  else
  {
    base::ArrayX<float,3U> a;
    a[0] = cam.zoom;
    a[1] = cam.znear;
    a[2] = cam.zfar;
    camera_orthographic_w()->set_blocked(a.data());
  }
}

void
Camera::
camera_perspective_cb()
{
  base::ArrayX<float,3U> a;
  camera_perspective_w()->get( a.data() );
  milieu::Camera cam;
  cam.mode = milieu::PERSPECTIVE;
  cam.fov = a[0];
  cam.znear = a[1];
  cam.zfar = a[2];
  camera()->set_camera( cam );
}

void
Camera::
camera_orthographic_cb()
{
  base::ArrayX<float,3U> a;
  camera_orthographic_w()->get( a.data() );
  milieu::Camera cam;
  cam.mode = milieu::ORTHOGRAPHIC;
  cam.zoom = a[0];
  cam.znear = a[1];
  cam.zfar = a[2];
  camera()->set_camera( cam );
}

void
Camera::
camera_perspective_reset_cb()
{
  camera()->reset_camera(PERSPECTIVE);
  camera_synchronize();
}

void
Camera::
camera_orthographic_reset_cb()
{
  camera()->reset_camera(ORTHOGRAPHIC);
  camera_synchronize();
}

void
Camera::
camera_choice_cb()
{
  uint n = camera_choice_w()->get();

  // this callback function is called whenever the user switches
  // the camera notebook widget
  if ( n == 0 )
  {
    // perspective camera
    camera_perspective_cb();
  }
  else if ( n == 1 )
  {
    // orthographic camera
    camera_orthographic_cb();
  }
}

bool
Camera::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "cameraReset" )
  {
    reset_camera();
  }
  else if( command == "orthographicCamera" )
  {
    base::vector<float> v;
    read_list( v, 3, argument );
    milieu::Camera cam;
    cam.zoom = v[0];
    cam.znear = v[1];
    cam.zfar = v[2];
    set_camera(cam);
    r = true;
  }
  else if( command == "perspectiveCamera" )
  {
    base::vector<float> v;
    read_list( v, 3, argument );
    milieu::Camera cam;
    cam.fov = v[0];
    cam.znear = v[1];
    cam.zfar = v[2];
    set_camera(cam);
    r = true;
  }

  return r;
}

} // namespace ui
} // namespace milieu
