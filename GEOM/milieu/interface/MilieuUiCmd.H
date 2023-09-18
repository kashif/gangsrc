/* GANG Software
 * GEOM/milieu/interface/MilieuUiCmd.H
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

#ifndef milieu_MilieuUiCmd_INCLUDED
#define milieu_MilieuUiCmd_INCLUDED

#include "MilieuUi.H"

namespace milieu {

class _MilieuUiCmd;

class MilieuUiCmd
  :
    virtual public MilieuUi
{

public:
  // constructor
  MilieuUiCmd();

  // destructor
  virtual ~MilieuUiCmd();

  void _hide_all();
  void _enable_tooltips(bool state);

  bool _command( base::String const &command, base::String const &argment,
                base::String &response );

  void background_toggle_raise_show();
  void blend_toggle_raise_show();
  void camera_toggle_raise_show();
  void clipplane_toggle_raise_show();
  void globallight_toggle_raise_show();
  void light_toggle_raise_show();
  void readbackground_toggle_raise_show();

  // background
  void background_reset();
  void background_color( uint );
  void background_color( base::Color3 const &c);
  void background_prev();
  void background_next();
//  void background_image( base::String const &filename );

  // blend
  void blend_reset();
  void antialias_point( bool x );
  void antialias_line( bool x );
  void blend_enable( bool x );
  void blend_src_function( uint x );
  void blend_dest_function( uint x );
  void fog_enable( bool x );
  void fog_mode( uint x );
  void fog_parameter( base::ArrayX<float,3U> const &x );
  void fog_color( base::Color3 const &x );
  void depth_enable( bool x );
  void depth_function( uint x );
  void depth_mask( bool x );
#if 0
  void hint_point_smooth( bool x );
  void hint_line_smooth( uint x );
  void hint_polygon_smooth( uint x );
  void hint_fog( uint x );
  void hint_perspective_correction( uint x );
#endif

  // get the camera
  virtual milieu::Camera const &get_camera() const;
  // set the camera
  virtual void set_camera( milieu::Camera const &cam );
  // reset the camera
  virtual void reset_camera( milieu::CameraMode = milieu::PERSPECTIVE );

  // clipplane
  void clipplane_reset();
  void clipplane_reset( uint id );
  void clipplane_enable( uint id, bool x );
  void clipplane_moving( uint id, bool x );
  void clipplane_attached( uint id, bool x );
  void clipplane_position( bool id, geom::Transform const &t );
  // light
  void light_select(uint id);
  void light_reset();
  void light_reset( uint id );
  void light_enable( uint id, bool x );
  void light_moving( uint id, bool x );
  void light_attached( uint id, bool x );
  void light_position( bool(id), geom::Transform const &t );
  void light_ambient( uint id, base::Color3 const &y );
  void light_diffuse( uint id, base::Color3 const &y );
  void light_specular( uint id, base::Color3 const &y );
  void light_spot( uint id, base::ArrayX<float,5U> const &x );
  void light_attenuation( uint id,
                                  base::ArrayX<float,3U> const &x );
  void light_prev();
  void light_next();

  // global light
  void globallight_reset();
  void globallight_enable( bool x );
  void globallight_ambient( base::Color3 const &x );
  void globallight_viewpoint( bool x );
  void globallight_sidedness( bool x );
  void globallight_toggle();
  void globallight_synchronize();

  // synchronize the widgets with the current milieu
  void synchronize();

protected:

  virtual void controls( widget::ui::KeyBase &);
  virtual void controls_win( widget::ui::KeyBase &);

private:
  _MilieuUiCmd *_;

  // disabled copy constructor
  MilieuUiCmd( MilieuUiCmd const & );
  // disabled assignment operator
  MilieuUiCmd &operator=( MilieuUiCmd const & );

  friend class _MilieuUiCmd;
};

} // namespace milieu

#endif // milieu_MilieuUiCmd_INCLUDED
