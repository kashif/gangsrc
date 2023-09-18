/* GANG Software
 * GEOM/milieu/gtk/Light.H
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

#ifndef milieu_gtk_Light_INCLUDED
#define milieu_gtk_Light_INCLUDED

#include "app/app/Dialog.H"
#include "milieu/ui/Light.H"
#include "Light_.H"

namespace milieu {
namespace gtk {

class Light
  :
    virtual public ui::Light,
    protected Light_,
    public ::app::app::Dialog
{

public:
  // constructor
  Light(char const *title);

  // destructor
  virtual ~Light();

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { Light_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

protected:

private:

  // widgets
  virtual widget::ui::Choice *id_w()
    { return _id_w; }
  virtual widget::ui::Boolean *enable_w()
    { return _enable_w; }
  virtual widget::ui::Boolean *moving_w()
    { return _moving_w; }
  virtual widget::ui::Boolean *show_w()
    { return _show_w; }
  virtual widget::ui::Boolean *attached_w()
    { return _attached_w; }
  virtual widget::ui::FloatSet *ambient_w()
    { return _ambient_w; }
  virtual widget::ui::FloatSet *diffuse_w()
    { return _diffuse_w; }
  virtual widget::ui::FloatSet *specular_w()
    { return _specular_w; }
  virtual widget::ui::FloatSet *spot_w()
    { return _spot_w; }
  virtual widget::ui::FloatSet *attenuation_w()
    { return _attenuation_w; }
  virtual widget::ui::Widget *hidebox_w()
    { return _hidebox_w; }

  // callbacks
  virtual void hidebutton_cb()
    { ui::Light::hidebutton_cb(); }
  virtual void id_cb()
    { ui::Light::id_cb(); }
  virtual void enable_cb()
    { ui::Light::enable_cb(); }
  virtual void moving_cb()
    { ui::Light::moving_cb(); }
  virtual void show_cb()
    { ui::Light::show_cb(); }
  virtual void attached_cb()
    { ui::Light::attached_cb(); }
  virtual void reset_cb()
    { ui::Light::reset_cb(); }
  virtual void ambient_cb()
    { ui::Light::ambient_cb(); }
  virtual void diffuse_cb()
    { ui::Light::diffuse_cb(); }
  virtual void specular_cb()
    { ui::Light::specular_cb(); }
  virtual void spot_cb()
    { ui::Light::spot_cb(); }
  virtual void attenuation_cb()
    { ui::Light::attenuation_cb(); }

  // disabled copy constructor
  Light( Light const & );

  // disabled assignment operator
  Light &operator=( Light const & );

};

} // namespace gtk
} // namespace milieu

#endif // milieu_gtk_Light_INCLUDED
