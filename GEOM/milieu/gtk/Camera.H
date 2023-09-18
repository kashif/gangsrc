/* GANG Software
 * GEOM/milieu/gtk/Camera.H
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

#ifndef milieu_gtk_Camera_INCLUDED
#define milieu_gtk_Camera_INCLUDED

#include "app/app/Dialog.H"
#include "milieu/ui/Camera.H"
#include "Camera_.H"

namespace milieu {
namespace gtk {

class Camera
  :
    virtual public ui::Camera,
    protected gtk::Camera_,
    public ::app::app::Dialog
{

public:
  // constructor
  Camera(char const *title);

  // destructor
  virtual ~Camera();

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { Camera_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

protected:

private:

  // widgets
  virtual widget::ui::Choice *camera_choice_w()
    { return _camera_choice_w; }
  virtual widget::ui::FloatSet *camera_perspective_w()
    { return _camera_perspective_w; }
  virtual widget::ui::FloatSet *camera_orthographic_w()
    { return _camera_orthographic_w; }

  // callbacks
  virtual void camera_choice_cb()
    { ui::Camera::camera_choice_cb(); }
  virtual void camera_perspective_reset_cb()
    { ui::Camera::camera_perspective_reset_cb(); }
  virtual void camera_perspective_cb()
    { ui::Camera::camera_perspective_cb(); }
  virtual void camera_orthographic_reset_cb()
    { ui::Camera::camera_orthographic_reset_cb(); }
  virtual void camera_orthographic_cb()
    { ui::Camera::camera_orthographic_cb(); }

  // disabled copy constructor
  Camera( Camera const & );

  // disabled assignment operator
  Camera &operator=( Camera const & );

};

} // namespace gtk
} // namespace milieu

#endif // milieu_gtk_Camera_INCLUDED
