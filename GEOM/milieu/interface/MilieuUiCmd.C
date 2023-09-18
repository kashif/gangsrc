/* GANG Software
 * GEOM/milieu/interface/MilieuUiCmd.C
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

#include "milieu/cmd/Ui.H"
#include "MilieuUiCmd.H"

namespace milieu {

class _MilieuUiCmd
  :
    public milieu::cmd::Ui
{
public:
  _MilieuUiCmd( MilieuUiCmd *parent) : _parent(parent) {}
protected:
  virtual milieu::opengl::Milieu *milieu()
    { return _parent->milieu(); }
  virtual milieu::opengl::Milieu const *milieu() const
    { return _parent->milieu(); }
  virtual void geomobject_move_enable( bool state ) { WARN(); }
private:
  MilieuUiCmd *_parent;
  friend class MilieuUiCmd;
};

MilieuUiCmd::
MilieuUiCmd()
    :
    _(new _MilieuUiCmd(this))
{
}

MilieuUiCmd::
~MilieuUiCmd()
{
  delete _;
}

void
MilieuUiCmd::
_hide_all()
{
  _->show_all(false);
}

void
MilieuUiCmd::
_enable_tooltips( bool state )
{
  _->enable_tooltips( state );
}

bool
MilieuUiCmd::
_command( base::String const &command, base::String const &argment, base::String &response )
{
  return _->command( command, argment, response );
}

void
MilieuUiCmd::
synchronize()
{
  _->synchronize();
}


void
MilieuUiCmd::
background_toggle_raise_show()
{
  static_cast< ::milieu::ui::Background *>(_)->toggle_raise_show_d();
}

void
MilieuUiCmd::
blend_toggle_raise_show()
{
  static_cast< ::milieu::ui::Blend *>(_)->toggle_raise_show_d();
}

void
MilieuUiCmd::
camera_toggle_raise_show()
{
  static_cast< ::milieu::ui::Camera *>(_)->toggle_raise_show_d();
}

void
MilieuUiCmd::
clipplane_toggle_raise_show()
{
  static_cast< ::milieu::ui::ClipPlane *>(_)->toggle_raise_show_d();
}

void
MilieuUiCmd::
globallight_toggle_raise_show()
{
  static_cast< ::milieu::ui::GlobalLight *>(_)->toggle_raise_show_d();
}

void
MilieuUiCmd::
light_toggle_raise_show()
{
  static_cast< ::milieu::ui::Light *>(_)->toggle_raise_show_d();
}

void
MilieuUiCmd::
readbackground_toggle_raise_show()
{
  static_cast< ::milieu::ui::BgRead *>(_)->toggle_raise_show_d();
}

void
MilieuUiCmd::
background_reset()
{
  _->background_reset();
}

void
MilieuUiCmd::
background_color( uint x )
{
  _->background_color( x );
}

void
MilieuUiCmd::
background_color( base::Color3 const &c)
{
  _->background_color( c);
}

void
MilieuUiCmd::
background_prev()
{
  _->background_prev();
}

void
MilieuUiCmd::
background_next()
{
  _->background_next();
}

void
MilieuUiCmd::
blend_reset()
{
  _->blend_reset();
}

void
MilieuUiCmd::
antialias_point( bool x )
{
  _->antialias_point( x );
}

void
MilieuUiCmd::
antialias_line( bool x )
{
  _->antialias_line( x );
}

void
MilieuUiCmd::
blend_enable( bool x )
{
  _->blend_enable( x );
}

void
MilieuUiCmd::
blend_src_function( uint x )
{
  _->blend_src_function( x );
}

void
MilieuUiCmd::
blend_dest_function( uint x )
{
  _->blend_dest_function( x );
}

void
MilieuUiCmd::
fog_enable( bool x )
{
  _->fog_enable( x );
}

void
MilieuUiCmd::
fog_mode( uint x )
{
  _->fog_mode( x );
}

void
MilieuUiCmd::
fog_parameter( base::ArrayX<float,3U> const &x )
{
  _->fog_parameter( x );
}

void
MilieuUiCmd::
fog_color( base::Color3 const &x )
{
  _->fog_color( x );
}

void
MilieuUiCmd::
depth_enable( bool x )
{
  _->depth_enable( x );
}

void
MilieuUiCmd::
depth_function( uint x )
{
  _->depth_function( x );
}

void
MilieuUiCmd::
depth_mask( bool x )
{
  _->depth_mask( x );
}

milieu::Camera const &
MilieuUiCmd::
get_camera() const
{
  return _->get_camera();
}

void
MilieuUiCmd::
set_camera( milieu::Camera const &cam )
{
  _->set_camera(cam);
}

void
MilieuUiCmd::
reset_camera( milieu::CameraMode mode )
{
  _->reset_camera(mode);
}

void
MilieuUiCmd::
clipplane_reset()
{
  _->clipplane_reset();
}

void
MilieuUiCmd::
clipplane_reset( uint id )
{
  _->clipplane_reset( id );
}

void
MilieuUiCmd::
clipplane_enable( uint id, bool x )
{
  _->clipplane_enable( id, x );
}

void
MilieuUiCmd::
clipplane_moving( uint id, bool x )
{
  _->clipplane_moving( id, x );
}

void
MilieuUiCmd::
clipplane_attached( uint id, bool x )
{
  _->clipplane_attached( id, x );
}

void
MilieuUiCmd::
clipplane_position( bool id, geom::Transform const &t )
{
  _->clipplane_position( id, t );
}

void
MilieuUiCmd::
light_select(uint id)
{
  _->light_select(id);
}

void
MilieuUiCmd::
light_reset()
{
  _->light_reset();
}

void
MilieuUiCmd::
light_reset( uint id )
{
  _->light_reset( id );
}

void
MilieuUiCmd::
light_enable( uint id, bool x )
{
  _->light_enable( id, x );
}

void
MilieuUiCmd::
light_moving( uint id, bool x )
{
  _->light_moving( id, x );
}

void
MilieuUiCmd::
light_attached( uint id, bool x )
{
  _->light_attached( id, x );
}

void
MilieuUiCmd::
light_position( bool id, geom::Transform const &t )
{
  _->light_position( id, t );
}

void
MilieuUiCmd::
light_ambient( uint id, base::Color3 const &y )
{
  _->light_ambient( id, y );
}

void
MilieuUiCmd::
light_diffuse( uint id, base::Color3 const &y )
{
  _->light_diffuse( id, y );
}

void
MilieuUiCmd::
light_specular( uint id, base::Color3 const &y )
{
  _->light_specular( id, y );
}

void
MilieuUiCmd::
light_spot( uint id, base::ArrayX<float,5U> const &x )
{
  _->light_spot( id, x );
}

void
MilieuUiCmd::
light_attenuation( uint id, base::ArrayX<float,3U> const &x )
{
  _->light_attenuation( id, x );
}

void
MilieuUiCmd::
light_prev()
{
  _->light_prev();
}

void
MilieuUiCmd::
light_next()
{
  _->light_next();
}

void
MilieuUiCmd::
globallight_reset()
{
  _->globallight_reset();
}

void
MilieuUiCmd::
globallight_enable( bool x )
{
  _->globallight_enable( x );
}

void
MilieuUiCmd::
globallight_ambient( base::Color3 const &x )
{
  _->globallight_ambient( x );
}

void
MilieuUiCmd::
globallight_viewpoint( bool x )
{
  _->globallight_viewpoint( x );
}

void
MilieuUiCmd::
globallight_sidedness( bool x )
{
  _->globallight_sidedness( x );
}

void
MilieuUiCmd::
globallight_toggle()
{
  _->globallight_toggle();
}

void
MilieuUiCmd::
globallight_synchronize()
{
  _->globallight_synchronize();
}

void
MilieuUiCmd::
controls( widget::ui::KeyBase &x )
{
  _->controls(x);
}

void
MilieuUiCmd::
controls_win( widget::ui::KeyBase &x )
{
  _->controls_win(x);
}

} // namespace milieu
