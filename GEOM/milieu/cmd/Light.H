/* GANG Software
 * GEOM/milieu/cmd/Light.H
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

#ifndef milieu_cmd_Light_INCLUDED
#define milieu_cmd_Light_INCLUDED

#include "widget/cmd/Boolean.H"
#include "widget/cmd/Choice.H"
#include "widget/cmd/FloatSet.H"
#include "milieu/ui/Light.H"

namespace milieu {
namespace cmd {

class Light
  :
    virtual public milieu::ui::Light
{

public:
  // constructor
  Light();

  // destructor
  virtual ~Light();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::Choice *id_w()
    { return &_id_w; }
  virtual widget::ui::Boolean *enable_w()
    { return &_enable_w; }
  virtual widget::ui::Boolean *moving_w()
    { return &_moving_w; }
  virtual widget::ui::Boolean *show_w()
    { return &_show_w; }
  virtual widget::ui::Boolean *attached_w()
    { return &_attached_w; }
  virtual widget::ui::FloatSet *ambient_w()
    { return &_ambient_w; }
  virtual widget::ui::FloatSet *diffuse_w()
    { return &_diffuse_w; }
  virtual widget::ui::FloatSet *specular_w()
    { return &_specular_w; }
  virtual widget::ui::FloatSet *spot_w()
    { return &_spot_w; }
  virtual widget::ui::FloatSet *attenuation_w()
    { return &_attenuation_w; }
  virtual widget::ui::Widget *hidebox_w()
    { return &_hidebox_w; }

  // widgets
  widget::cmd::Choice _id_w;
  widget::cmd::Boolean _enable_w;
  widget::cmd::Boolean _moving_w;
  widget::cmd::Boolean _show_w;
  widget::cmd::Boolean _attached_w;
  widget::cmd::FloatSet _ambient_w;
  widget::cmd::FloatSet _diffuse_w;
  widget::cmd::FloatSet _specular_w;
  widget::cmd::FloatSet _spot_w;
  widget::cmd::FloatSet _attenuation_w;
  widget::cmd::Widget _hidebox_w;

  // disabled copy constructor
  Light( Light const & );
  // disabled assignment operator
  Light &operator=( Light const & );

};

} // namespace cmd
} // namespace milieu

#endif // milieu_cmd_Light_INCLUDED
