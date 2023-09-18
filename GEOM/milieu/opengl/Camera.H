/* GANG Software
 * GEOM/milieu/opengl/Camera.H
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

#ifndef milieu_opengl_Camera_INCLUDED
#define milieu_opengl_Camera_INCLUDED

#include "milieu/kernel/Camera.H"

namespace milieu {
namespace opengl {

class Camera
  :
    virtual public ::milieu::kernel::Camera
{

public:
  // constructor
  Camera();

  // copy constructor
  Camera( Camera const & );

  // destructor
  virtual ~Camera();

  // assignment operator
  Camera &operator=( Camera const & );

  void draw() const;

  virtual void set_camera( milieu::Camera const &cam );
  virtual void reset_camera(CameraMode mode = PERSPECTIVE);
  virtual void set_window_size( uint width, uint height );

protected:

  virtual void refresh() = 0;

private:
};

} // namespace opengl
} // namespace milieu

#endif // milieu_opengl_Camera_INCLUDED
