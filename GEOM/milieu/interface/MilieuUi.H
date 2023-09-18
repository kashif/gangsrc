/* GANG Software
 * GEOM/milieu/interface/MilieuUi.H
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

#ifndef milieu_MilieuUi_INCLUDED
#define milieu_MilieuUi_INCLUDED

#include "base/ArrayX.H"
#include "base/Color3.H"
#include "widget/ui/KeyBase.H"
#include "geom/interface/Common.H"
#include "milieu/interface/Common.H"

namespace geom { class Surface; }
namespace milieu { namespace opengl { class Milieu; } }

namespace milieu {

class MilieuUi
{

public:

  virtual void _hide_all() = 0;
  virtual void _enable_tooltips(bool state) = 0;

  virtual bool _command( base::String const &command,
                        base::String const &argment,
                        base::String &response ) = 0;

  virtual void background_toggle_raise_show() = 0;
  virtual void blend_toggle_raise_show() = 0;
  virtual void camera_toggle_raise_show() = 0;
  virtual void clipplane_toggle_raise_show() = 0;
  virtual void globallight_toggle_raise_show() = 0;
  virtual void light_toggle_raise_show() = 0;
  virtual void readbackground_toggle_raise_show() = 0;

  // background
  virtual void background_reset() = 0;
  virtual void background_color( uint ) = 0;
  virtual void background_color( base::Color3 const &c) = 0;
  virtual void background_prev() = 0;
  virtual void background_next() = 0;
//  virtual void background_image( base::String const &filename ) = 0;

  // blend
  virtual void blend_reset() = 0;
  virtual void antialias_point( bool x ) = 0;
  virtual void antialias_line( bool x ) = 0;
  virtual void blend_enable( bool x ) = 0;
  virtual void blend_src_function( uint x ) = 0;
  virtual void blend_dest_function( uint x ) = 0;
  virtual void fog_enable( bool x ) = 0;
  virtual void fog_mode( uint x ) = 0;
  virtual void fog_parameter( base::ArrayX<float,3U> const &x ) = 0;
  virtual void fog_color( base::Color3 const &x ) = 0;
  virtual void depth_enable( bool x ) = 0;
  virtual void depth_function( uint x ) = 0;
  virtual void depth_mask( bool x ) = 0;
#if 0
  virtual void hint_point_smooth( bool x ) = 0;
  virtual void hint_line_smooth( uint x ) = 0;
  virtual void hint_polygon_smooth( uint x ) = 0;
  virtual void hint_fog( uint x ) = 0;
  virtual void hint_perspective_correction( uint x ) = 0;
#endif

  // get the camera
  virtual milieu::Camera const &get_camera() const = 0;
  // set the camera
  virtual void set_camera( milieu::Camera const &cam ) = 0;
  // reset the camera
  virtual void reset_camera( milieu::CameraMode = milieu::PERSPECTIVE ) = 0;

  // clipplane
  virtual void clipplane_reset() = 0;
  virtual void clipplane_reset( uint id ) = 0;
  virtual void clipplane_enable( uint id, bool x ) = 0;
  virtual void clipplane_moving( uint id, bool x ) = 0;
  virtual void clipplane_attached( uint id, bool x ) = 0;
  virtual void clipplane_position( bool id, geom::Transform const &t ) = 0;
  // light
  virtual void light_select(uint id) = 0;
  virtual void light_reset() = 0;
  virtual void light_reset( uint id ) = 0;
  virtual void light_enable( uint id, bool x ) = 0;
  virtual void light_moving( uint id, bool x ) = 0;
  virtual void light_attached( uint id, bool x ) = 0;
  virtual void light_position( bool(id), geom::Transform const &t ) = 0;
  virtual void light_ambient( uint id, base::Color3 const &y ) = 0;
  virtual void light_diffuse( uint id, base::Color3 const &y ) = 0;
  virtual void light_specular( uint id, base::Color3 const &y ) = 0;
  virtual void light_spot( uint id, base::ArrayX<float,5U> const &x ) = 0;
  virtual void light_attenuation( uint id,
                                  base::ArrayX<float,3U> const &x ) = 0;
  virtual void light_prev() = 0;
  virtual void light_next() = 0;

  // global light
  virtual void globallight_reset() = 0;
  virtual void globallight_enable( bool x ) = 0;
  virtual void globallight_ambient( base::Color3 const &x ) = 0;
  virtual void globallight_viewpoint( bool x ) = 0;
  virtual void globallight_sidedness( bool x ) = 0;
  virtual void globallight_toggle() = 0;
  virtual void globallight_synchronize() = 0;

  // synchronize the widgets with the current milieu
  virtual void synchronize() = 0;

protected:

  virtual milieu::opengl::Milieu *milieu() = 0;
  virtual milieu::opengl::Milieu const *milieu() const = 0;
};

} // namespace milieu

#endif // milieu_MilieuUi_INCLUDED
