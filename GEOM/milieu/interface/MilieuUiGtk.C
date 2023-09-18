/* GANG Software
 * GEOM/milieu/interface/MilieuUiGtk.C
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

#include "milieu/gtk/Ui.H"
#include "MilieuUiGtk.H"

namespace milieu {

class _MilieuUiGtk
  :
    public milieu::gtk::Ui
{
public:
  _MilieuUiGtk( char const *label, MilieuUiGtk *parent) :
      milieu::gtk::Ui(label), _parent(parent) {}
protected:
  virtual int key_press_event_d( uint key, uint state )
    { return _parent->key_press_event_d( key, state ); }
  virtual milieu::opengl::Milieu *milieu()
    { return _parent->milieu(); }
  virtual milieu::opengl::Milieu const *milieu() const
    { return _parent->milieu(); }
//  virtual void geomobject_move_enable( bool state ) { WARN(); }
  virtual void milieu_moving_notify( bool state )
    { _parent->milieu_moving_notify(state); }
private:
  MilieuUiGtk *_parent;
  friend class MilieuUiGtk;
};

MilieuUiGtk::
MilieuUiGtk( char const *label )
    :
    _(new _MilieuUiGtk(label, this))
{
}

MilieuUiGtk::
~MilieuUiGtk()
{
  delete _;
}

void
MilieuUiGtk::
_hide_all()
{
  _->show_all(false);
}

void
MilieuUiGtk::
_enable_tooltips( bool state )
{
  _->milieu::ui::Ui::enable_tooltips( state );
}

bool
MilieuUiGtk::
_command( base::String const &command, base::String const &argment, base::String &response )
{
  return _->command( command, argment, response );
}

void
MilieuUiGtk::
synchronize()
{
  _->synchronize();
}

void
MilieuUiGtk::
background_toggle_raise_show()
{
  static_cast< ::milieu::ui::Background *>(_)->toggle_raise_show_d();
}

void
MilieuUiGtk::
blend_toggle_raise_show()
{
  static_cast< ::milieu::ui::Blend *>(_)->toggle_raise_show_d();
}

void
MilieuUiGtk::
camera_toggle_raise_show()
{
  static_cast< ::milieu::ui::Camera *>(_)->toggle_raise_show_d();
}

void
MilieuUiGtk::
clipplane_toggle_raise_show()
{
  static_cast< ::milieu::ui::ClipPlane *>(_)->toggle_raise_show_d();
}

void
MilieuUiGtk::
globallight_toggle_raise_show()
{
  static_cast< ::milieu::ui::GlobalLight *>(_)->toggle_raise_show_d();
}

void
MilieuUiGtk::
light_toggle_raise_show()
{
  static_cast< ::milieu::ui::Light *>(_)->toggle_raise_show_d();
}

void
MilieuUiGtk::
readbackground_toggle_raise_show()
{
  static_cast< ::milieu::ui::BgRead *>(_)->toggle_raise_show_d();
}

void
MilieuUiGtk::
background_reset()
{
  _->background_reset();
}

void
MilieuUiGtk::
background_color( uint x )
{
  _->background_color( x );
}

void
MilieuUiGtk::
background_color( base::Color3 const &c)
{
  _->background_color( c);
}

void
MilieuUiGtk::
background_prev()
{
  _->background_prev();
}

void
MilieuUiGtk::
background_next()
{
  _->background_next();
}

void
MilieuUiGtk::
blend_reset()
{
  _->blend_reset();
}

void
MilieuUiGtk::
antialias_point( bool x )
{
  _->antialias_point( x );
}

void
MilieuUiGtk::
antialias_line( bool x )
{
  _->antialias_line( x );
}

void
MilieuUiGtk::
blend_enable( bool x )
{
  _->blend_enable( x );
}

void
MilieuUiGtk::
blend_src_function( uint x )
{
  _->blend_src_function( x );
}

void
MilieuUiGtk::
blend_dest_function( uint x )
{
  _->blend_dest_function( x );
}

void
MilieuUiGtk::
fog_enable( bool x )
{
  _->fog_enable( x );
}

void
MilieuUiGtk::
fog_mode( uint x )
{
  _->fog_mode( x );
}

void
MilieuUiGtk::
fog_parameter( base::ArrayX<float,3U> const &x )
{
  _->fog_parameter( x );
}

void
MilieuUiGtk::
fog_color( base::Color3 const &x )
{
  _->fog_color( x );
}

void
MilieuUiGtk::
depth_enable( bool x )
{
  _->depth_enable( x );
}

void
MilieuUiGtk::
depth_function( uint x )
{
  _->depth_function( x );
}

void
MilieuUiGtk::
depth_mask( bool x )
{
  _->depth_mask( x );
}

milieu::Camera const &
MilieuUiGtk::
get_camera() const
{
  return _->get_camera();
}

void
MilieuUiGtk::
set_camera( milieu::Camera const &cam )
{
  _->set_camera(cam);
}

void
MilieuUiGtk::
reset_camera( milieu::CameraMode mode )
{
  _->reset_camera(mode);
}

void
MilieuUiGtk::
clipplane_reset()
{
  _->clipplane_reset();
}

void
MilieuUiGtk::
clipplane_reset( uint id )
{
  _->clipplane_reset( id );
}

void
MilieuUiGtk::
clipplane_enable( uint id, bool x )
{
  _->clipplane_enable( id, x );
}

void
MilieuUiGtk::
clipplane_moving( uint id, bool x )
{
  _->clipplane_moving( id, x );
}

void
MilieuUiGtk::
clipplane_attached( uint id, bool x )
{
  _->clipplane_attached( id, x );
}

void
MilieuUiGtk::
clipplane_position( bool id, geom::Transform const &t )
{
  _->clipplane_position( id, t );
}

void
MilieuUiGtk::
light_select(uint id)
{
  _->light_select(id);
}

void
MilieuUiGtk::
light_reset()
{
  _->light_reset();
}

void
MilieuUiGtk::
light_reset( uint id )
{
  _->light_reset( id );
}

void
MilieuUiGtk::
light_enable( uint id, bool x )
{
  _->light_enable( id, x );
}

void
MilieuUiGtk::
light_moving( uint id, bool x )
{
  _->light_moving( id, x );
}

void
MilieuUiGtk::
light_attached( uint id, bool x )
{
  _->light_attached( id, x );
}

void
MilieuUiGtk::
light_position( bool id, geom::Transform const &t )
{
  _->light_position( id, t );
}

void
MilieuUiGtk::
light_ambient( uint id, base::Color3 const &y )
{
  _->light_ambient( id, y );
}

void
MilieuUiGtk::
light_diffuse( uint id, base::Color3 const &y )
{
  _->light_diffuse( id, y );
}

void
MilieuUiGtk::
light_specular( uint id, base::Color3 const &y )
{
  _->light_specular( id, y );
}

void
MilieuUiGtk::
light_spot( uint id, base::ArrayX<float,5U> const &x )
{
  _->light_spot( id, x );
}

void
MilieuUiGtk::
light_attenuation( uint id, base::ArrayX<float,3U> const &x )
{
  _->light_attenuation( id, x );
}

void
MilieuUiGtk::
light_prev()
{
  _->light_prev();
}

void
MilieuUiGtk::
light_next()
{
  _->light_next();
}

void
MilieuUiGtk::
globallight_reset()
{
  _->globallight_reset();
}

void
MilieuUiGtk::
globallight_enable( bool x )
{
  _->globallight_enable( x );
}

void
MilieuUiGtk::
globallight_ambient( base::Color3 const &x )
{
  _->globallight_ambient( x );
}

void
MilieuUiGtk::
globallight_viewpoint( bool x )
{
  _->globallight_viewpoint( x );
}

void
MilieuUiGtk::
globallight_sidedness( bool x )
{
  _->globallight_sidedness( x );
}

void
MilieuUiGtk::
globallight_toggle()
{
  _->globallight_toggle();
}

void
MilieuUiGtk::
globallight_synchronize()
{
  _->globallight_synchronize();
}


void
MilieuUiGtk::
controls( widget::ui::KeyBase &x )
{
  _->controls(x);
}

void
MilieuUiGtk::
controls_win( widget::ui::KeyBase &x )
{
  _->controls_win(x);
}

} // namespace milieu
