/* GANG Software
 * GEOM/milieu/kernel/Camera.C
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
#include "Camera.H"

namespace milieu {
namespace kernel {

milieu::Camera const default_perspective_camera =
{ PERSPECTIVE, 0.25, 5.0e-2, 5.0e+2 };
milieu::Camera const default_orthographic_camera =
{ ORTHOGRAPHIC, 3.0, -5.0e+2, 5.0e+2 };

Camera::Real const Camera::ASPECT_RATIO = 1.0;

Camera::
Camera()
    :
    _camera( default_perspective_camera ),
    _window_width(0U),
    _window_height(0U)
{
//  reset_camera();
}

Camera::
Camera( Camera const &a )
    :
    _camera( default_perspective_camera ),
    _window_width(a._window_width),
    _window_height(a._window_height)
{
}

Camera::
~Camera()
{
}

Camera &
Camera::
operator=( Camera const &a )
{
  if (this == &a) { return *this; }
  _camera = a._camera;
  _window_width = a._window_width;
  _window_height = a._window_height;
  return *this;
}

void
Camera::
reset_camera( CameraMode mode )
{
  if (mode == PERSPECTIVE)
  { set_camera( default_perspective_camera); }
  else if (mode == ORTHOGRAPHIC)
  { set_camera( default_orthographic_camera); }
  else { DIE(); }
}


void
Camera::
set_window_size( uint width, uint height )
{
  _window_width = width;
  _window_height = height;
  set_camera(_camera);
}

void
Camera::
set_camera( milieu::Camera const &cam )
{
  if ( cam.mode == PERSPECTIVE )
  {
    set_perspective_camera( cam );
  }
  else if ( cam.mode == ORTHOGRAPHIC )
  {
    set_orthographic_camera( cam );
  }
  else
  {
    DIE();
  }
}

void
Camera::
set_orthographic_camera(
  milieu::Camera const &cam )
{
  /*
    set orthographic camera from the following data:
    a[0] = zoom
    a[1] = z-near
    a[2] = z-far
  */

  _camera = cam;

  if (_window_width == 0U || _window_height == 0U) { return; }

  float y = cam.zoom;
  float x = y * ASPECT_RATIO;

  base::ArrayX<Real,6U> b;
  b[0] = -x;
  b[1] = x;
  b[2] = -y;
  b[3] = y;
  b[4] = cam.znear;
  b[5] = cam.zfar;

  float r = float(_window_width)/float(_window_height);

  if ( _window_width >= _window_height )
  {
    // wide window
    b[0] *= r;
    b[1] *= r;
  }
  else
  {
    // narrow window
    b[2] /= r;
    b[3] /= r;
  }

  double const epsilon = 1.0e-8;

  if(
    math::abs(b[0]) < epsilon ||
    math::abs(b[1]) < epsilon ||
    math::abs(b[2]) < epsilon ||
    math::abs(b[3]) < epsilon ||
    math::abs(b[4]) < epsilon ||
    math::abs(b[5]) < epsilon ||
    math::abs(b[0]-b[1]) < epsilon ||
    math::abs(b[2]-b[3]) < epsilon ||
    math::abs(b[4]-b[5]) < epsilon )
  { return; }

  _orthographic_camera_gl = b;
}

void
Camera::
set_perspective_camera(
  milieu::Camera const &cam )
{
  /*
    set perspective camera from the following data:
    a[0] = y field-of-view
    a[1] = z-near
    a[2] = z-far

    NOTE: if user changes field-of-view, want image to stay the
    same size. This may require modifying the camera's position
  */

  _camera = cam;

  if (_window_width == 0U || _window_height == 0U) { return; }

  float y = tan( 0.5*math::pi*cam.fov );
  float x = y * ASPECT_RATIO;

  base::ArrayX<Real,6U> b;
  b[0] = -x;
  b[1] = x;
  b[2] = -y;
  b[3] = y;
  b[4] = cam.znear;
  b[5] = cam.zfar;

  // if ( y == 0.0 ) { y = 1.0; }
  b[0] *= cam.znear;
  b[1] *= cam.znear;
  b[2] *= cam.znear;
  b[3] *= cam.znear;

  float r = float(_window_width)/float(_window_height);

  if ( _window_width >= _window_height )
  {
    // wide window
    b[0] *= r;
    b[1] *= r;
  }
  else
  {
    // narrow window
    b[2] /= r;
    b[3] /= r;
  }
  double const epsilon = 1.0e-8;

  if(
    math::abs(b[0]) < epsilon ||
    math::abs(b[1]) < epsilon ||
    math::abs(b[2]) < epsilon ||
    math::abs(b[3]) < epsilon ||
    math::abs(b[4]) < epsilon ||
    math::abs(b[5]) < epsilon ||
    math::abs(b[0]-b[1]) < epsilon ||
    math::abs(b[2]-b[3]) < epsilon ||
    math::abs(b[4]-b[5]) < epsilon )
  { return; }

  _perspective_camera_gl = b;
}

#if 0
void
Camera::
_orthographic_transform(
  base::ArrayX<float,6U> const &b )
{
  if( math::effectively_zero( b[1]-b[0] ) ||
      math::effectively_zero( b[3]-b[2] ) ||
      math::effectively_zero( b[5]-b[4] ) )
  {
    WARN("invalid camera data");
    return;
  }

  // sets the orthographic transformation matrix like glOrtho()
  _transform.zero();

  _transform[0][0] = 2.0f/(b[1]-b[0]);
  _transform[0][3] = 2.0f*(b[1]+b[0])/(b[1]-b[0]);
  _transform[1][1] = 2.0f/(b[3]-b[2]);
  _transform[1][3] = 2.0f*(b[3]+b[2])/(b[3]-b[2]);
  _transform[2][2] = -2.0f/(b[5]-b[4]);
  _transform[2][3] = (b[5]+b[4])/(b[5]-b[4]);
  _transform[3][3] = 1.0f;

  DIE_IF(_transform.isnan());
}

void
Camera::
_perspective_transform(
  base::ArrayX<float,6U> const &b )
{
  // sets the perspective transformation matrix like glFrustum()

  if( math::effectively_zero( b[1]-b[0] ) ||
      math::effectively_zero( b[3]-b[2] ) ||
      math::effectively_zero( b[5]-b[4] ) )
  {
    WARN("invalid camera data");
    return;
  }

  _transform.zero();

  _transform[0][0] = 2.0f*b[4]/(b[1]-b[0]);
  _transform[0][2] = (b[1]+b[0])/(b[1]-b[0]);
  _transform[1][1] = 2.0f*b[4]/(b[3]-b[2]);
  _transform[1][2] = (b[3]+b[2])/(b[3]-b[2]);
  _transform[2][2] = -(b[5]+b[4])/(b[5]-b[4]);
  _transform[2][3] = -2.0*b[5]*b[4]/(b[5]-b[4]);
  _transform[3][2] = -1.0f;

  DIE_IF(_transform.isnan());
}
#endif

void
Camera::
dump( io::Ostream &o ) const
{
  char const *tab = "\t\t";

  o << tab <<  "<camera>\n";
  if (_camera.mode == PERSPECTIVE)
  {
    o << tab << "\t<perspective>"
      << _camera.fov << " "
      << _camera.znear << " "
      << _camera.zfar << "</perspective>\n";
  }
  else if ( _camera.mode == ORTHOGRAPHIC )
  {
    o << tab << "\t<orthographic>"
      << _camera.zoom << " "
      << _camera.znear << " "
      << _camera.zfar << "</orthographic>\n";
  }
  else
  {
    DIE();
  }
  o << tab  << "\t<window_size>"
    << _window_width << " " << _window_height << "</window_size>\n";
  o << tab <<  "</camera>\n";
}

} // namespace kernel
} // namespace milieu
