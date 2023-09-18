/* GANG Software
 * GEOM/milieu/ui/Light.H
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

#ifndef milieu_ui_Light_INCLUDED
#define milieu_ui_Light_INCLUDED

#include "base/Color3.H"
#include "base/Color4.H"
#include "math/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Choice.H"
#include "widget/ui/Boolean.H"
#include "widget/ui/FloatSet.H"
#include "milieu/opengl/LightSet.H"

namespace milieu {

namespace opengl { class LightSet; }

namespace ui {

class Light
  :
    public widget::ui::Dialog,
    public math::ReadUtil
{

public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  Light();

  // destructor
  virtual ~Light();

  // interface
  virtual void light_reset();
  virtual void light_reset( uint id );
  virtual void light_select( uint id )
    { id_w()->set(id); }
  virtual void light_enable( uint id, bool a );
  virtual void light_moving( uint id, bool a );
  virtual void light_show( uint id, bool a );
  virtual void light_attached( uint id, bool a );
  virtual void light_position( bool id, Transform const &a );
  virtual void light_ambient( uint id, base::Color3 const &a );
  virtual void light_diffuse( uint id, base::Color3 const &a );
  virtual void light_specular( uint id, base::Color3 const &a );
  virtual void light_spot( uint id, base::ArrayX<float,5U> const &a );
  virtual void light_attenuation( uint id, base::ArrayX<float,3U> const &a );
  virtual void light_prev();
  virtual void light_next();
  virtual void light_synchronize()
    { set_ui_from_data( lightset() ); }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void id_cb()
    { light_synchronize(); }
  virtual void enable_cb()
    { _enable( id_w()->get(), enable_w()->get() ); }
  virtual void moving_cb()
    { lightset()->moving( id_w()->get(), moving_w()->get() ); }
  virtual void show_cb()
    { _show( id_w()->get(), show_w()->get() ); }
  virtual void attached_cb()
    { _attached( id_w()->get(), attached_w()->get() ); }
  virtual void reset_cb()
    { light_reset( id_w()->get() ); }
  virtual void ambient_cb();
  virtual void diffuse_cb();
  virtual void specular_cb();
  virtual void spot_cb();
  virtual void attenuation_cb();
  virtual void hidebutton_cb();

  bool _showflag;

  char const *label()
    { return "Light"; }

private:

  // pure virtuals
  virtual ::milieu::opengl::LightSet *lightset() = 0;
  virtual ::milieu::opengl::LightSet const *lightset() const = 0;
//  virtual void geomobject_move_enable(bool state) = 0;
//  virtual void clipplane_moving_off() = 0;

  // widgets
  virtual widget::ui::Choice *id_w() = 0;
  virtual widget::ui::Boolean *enable_w() = 0;
  virtual widget::ui::Boolean *moving_w() = 0;
  virtual widget::ui::Boolean *show_w() = 0;
  virtual widget::ui::Boolean *attached_w() = 0;
  virtual widget::ui::FloatSet *ambient_w() = 0;
  virtual widget::ui::FloatSet *diffuse_w() = 0;
  virtual widget::ui::FloatSet *specular_w() = 0;
  virtual widget::ui::FloatSet *spot_w() = 0;
  virtual widget::ui::FloatSet *attenuation_w() = 0;
  virtual widget::ui::Widget *hidebox_w() = 0;

  // implementation
  void _select( uint id );
  void _reset( uint id );
  void _enable( uint id, bool a )
    { lightset()->enable( id, a ); }
//  void _moving( uint id, bool a );
  void _show( uint id, bool a )
    { lightset()->show( id, a ); }
  void _attached( uint id, bool a )
    { lightset()->attached( id, a ); }
  void _ambient( uint id, base::Color3 const &a )
    { lightset()->ambient( id, a ); }
  void _diffuse( uint id, base::Color3 const &a )
    { lightset()->diffuse( id, a ); }
  void _specular( uint id, base::Color3 const &a )
    { lightset()->specular( id, a ); }
  void _spot( uint id, base::ArrayX<float,5U> const &a )
    { lightset()->spot( id, a ); }
  void _attenuation( uint id, base::ArrayX<float,3U> const &a )
    { lightset()->attenuation( id, a ); }

  // utility
  void set_ui_from_data( opengl::LightSet *lightset );

  uint _light_counter;

  // disabled copy constructor
  Light( Light const & );
  // disabled assignment operator
  Light &operator=( Light const & );
};

} // namespace ui
} // namespace milieu

#endif // milieu_ui_Light_INCLUDED
