/* GANG Software
 * GEOM/milieu/kernel/Camera.H
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

#ifndef milieu_kernel_Camera_INCLUDED
#define milieu_kernel_Camera_INCLUDED

#include "base/ArrayX.H"
#include "io/Ostream.H"
#include "geom/interface/Common.H"
#include "milieu/interface/Common.H"

namespace milieu {
namespace kernel {

extern milieu::Camera const default_perspective_camera;
extern milieu::Camera const default_orthographic_camera;

class Camera
{

public:
  typedef geom::Real Real;


  // constructor
  Camera();

  // copy constructor
  Camera( Camera const & );

  // destructor
  virtual ~Camera();

  // assignment operator
  Camera &operator=( Camera const & );

  void dump( io::Ostream & ) const;

  // get the camera
  virtual milieu::Camera const &get_camera() const
    { return _camera; }
  // set the camera
  virtual void set_camera( milieu::Camera const &cam );
  // reset the camera
  virtual void reset_camera(CameraMode mode = PERSPECTIVE);

  virtual void get_window_size( uint &width, uint &height ) const
    { width = _window_width;
    height = _window_height; }
  virtual void set_window_size( uint width, uint height );

  CameraMode mode() const
    { return _camera.mode; } 

protected:

  virtual void set_perspective_camera( milieu::Camera const &cam );
  virtual void set_orthographic_camera( milieu::Camera const &cam );

  virtual base::ArrayX<double,6U> const &perspective_camera_gl() const
    { return _perspective_camera_gl; }
  virtual base::ArrayX<double,6U> const &orthographic_camera_gl() const
    { return _orthographic_camera_gl; }

private:

#if 0
  void _perspective_transform( base::ArrayX<float,6U> const &b );
  void _orthographic_transform( base::ArrayX<float,6U> const &b );
#endif

  milieu::Camera _camera;

  base::ArrayX<Real,6U> _perspective_camera_gl;
  base::ArrayX<Real,6U> _orthographic_camera_gl;

  uint _window_width, _window_height;

  static const Real ASPECT_RATIO;
};

} // namespace kernel
} // namespace milieu

#endif // milieu_kernel_Camera_INCLUDED
