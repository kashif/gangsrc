/* GANG Software
 * GEOM/milieu/ui/Camera.H
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

#ifndef milieu_ui_Camera_INCLUDED
#define milieu_ui_Camera_INCLUDED

#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Choice.H"
#include "widget/ui/FloatSet.H"
#include "geom/interface/Common.H"
#include "milieu/kernel/Camera.H"

namespace milieu {

namespace opengl { class Camera; }

namespace ui {

class Camera
  : 
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  Camera();

  // destructor
  virtual ~Camera();

  // interface
  // get the camera
  virtual milieu::Camera const &get_camera() const;
  // set the camera
  virtual void set_camera( milieu::Camera const &cam );
  // reset the camera
  virtual void reset_camera( milieu::CameraMode = milieu::PERSPECTIVE );


  virtual void camera_synchronize();

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void camera_choice_cb();
  virtual void camera_perspective_reset_cb();
  virtual void camera_perspective_cb();
  virtual void camera_orthographic_reset_cb();
  virtual void camera_orthographic_cb();

  char const *label()
    { return "Camera"; }

private:

  // pure virtuals
  virtual ::milieu::opengl::Camera *camera() = 0;
  virtual ::milieu::opengl::Camera const *camera() const = 0;

  // widgets
  virtual widget::ui::Choice *camera_choice_w() = 0;
  virtual widget::ui::FloatSet *camera_perspective_w() = 0;
  virtual widget::ui::FloatSet *camera_orthographic_w() = 0;

  milieu::Camera _perspective_camera;
  milieu::Camera _orthographic_camera;

  Camera( Camera const & );
  Camera &operator=( Camera const & );

};

} // namespace ui
} // namespace milieu

#endif // milieu_ui_Camera_INCLUDED
