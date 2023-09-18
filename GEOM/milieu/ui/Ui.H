/* GANG Software
 * GEOM/milieu/ui/Ui.H
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

#ifndef milieu_ui_Ui_INCLUDED
#define milieu_ui_Ui_INCLUDED

#include "math/Matrix.H"
#include "widget/ui/KeyBase.H"
#include "milieu/opengl/Milieu.H"
#include "Background.H"
#include "BgRead.H"
#include "Blend.H"
#include "Camera.H"
#include "ClipPlane.H"
#include "GlobalLight.H"
#include "Light.H"

namespace milieu {
namespace ui {

class Ui
  :
    virtual protected BgRead,
    virtual protected Background,
    virtual protected Blend,
    virtual protected Camera,
    virtual protected ClipPlane,
    virtual protected GlobalLight,
    virtual protected Light
{

public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  Ui();

  // destructor
  virtual ~Ui();

  void show_all(bool state);
  void enable_tooltips( bool state );
  void synchronize();
  void reset();

#if 0
  // background
  virtual void background_reset()
    { Background::background_reset(); }
  virtual void background_color( uint n )
    { Background::background_color(n); }
  virtual void background_color( base::Color3 const &c)
    { Background::background_color(c); }
#endif

//  virtual void background_image( base::String const &filename ) = 0;

#if 0
  virtual void background_image( base::String const &filename )
    { Background::background_image(filename); }
  virtual void background_clear_image()
    { Background::background_clear_image(); }
#endif

#if 0
  virtual void background_prev()
    { Background::background_prev(); }
  virtual void background_next()
    { Background::background_next(); }

  // blend
  virtual void blend_reset()
    { Blend::blend_reset(); }
  virtual void antialias_point( bool x )
    { Blend::antialias_point(x); }
  virtual void antialias_line( bool x )
    { Blend::antialias_line(x); }
  virtual void blend_enable( bool x )
    { Blend::blend_enable(x); }
  virtual void blend_src_function( uint x )
    { Blend::blend_src_function(x); }
  virtual void blend_dest_function( uint x )
    { Blend::blend_dest_function(x); }
  virtual void fog_enable( bool x )
    { Blend::fog_enable(x); }
  virtual void fog_mode( uint x )
    { Blend::fog_mode(x); }
  virtual void fog_parameter( base::ArrayX<float,3U> const &x )
    { Blend::fog_parameter(x); }
  virtual void fog_color( base::Color3 const &x )
    { Blend::fog_color(x); }
  virtual void depth_enable( bool x )
    { Blend::depth_enable(x); }
  virtual void depth_function( uint x )
    { Blend::depth_function(x); }
  virtual void depth_mask( bool x )
    { Blend::depth_mask(x); }
#if 0
  virtual void hint_point_smooth( bool x )
    { Blend::hint_point_smooth(x); }
  virtual void hint_line_smooth( uint x )
    { Blend::hint_line_smooth(x); }
  virtual void hint_polygon_smooth( uint x )
    { Blend::hint_polygon_smooth(x); }
  virtual void hint_fog( uint x )
    { Blend::hint_fog(x); }
  virtual void hint_perspective_correction( uint x )
    { Blend::hint_perspective_correction(x); }
#endif

  // camera
  virtual void camera_reset()
    { Camera::camera_reset(); }
  virtual void camera_perspective_reset()
    { Camera::camera_perspective_reset(); }
  virtual void camera_orthographic_reset()
    { Camera::camera_orthographic_reset(); }
  virtual void camera_orthographic( base::ArrayX<float,4U> const &x )
    { Camera::camera_orthographic(x); }
  virtual void camera_perspective( base::ArrayX<float,4U> const &x )
    { Camera::camera_perspective(x); }

  // clipplane
  virtual void clipplane_reset()
    { ClipPlane::clipplane_reset(); }
  virtual void clipplane_reset( uint id )
    { ClipPlane::clipplane_reset(); }
  virtual void clipplane_enable( uint id, bool x )
    { ClipPlane::clipplane_enable(id, x); }
  virtual void clipplane_moving( uint id, bool x )
    { ClipPlane::clipplane_moving(id, x); }
  virtual void clipplane_attached( uint id, bool x )
    { ClipPlane::clipplane_attached(id, x); }
  virtual void clipplane_position( bool id,
                                   Transform const &x )
    { ClipPlane::clipplane_position(id, x); }

  // light
  virtual void light_select(uint id)
    { Light::light_select(id); }
  virtual void light_reset()
    { Light::light_reset(); }
  virtual void light_reset( uint id )
    { Light::light_reset(id); }
  virtual void light_enable( uint id, bool x )
    { Light::light_enable(id, x); }
  virtual void light_moving( uint id, bool x )
    { Light::light_moving(id, x); }
  virtual void light_attached( uint id, bool x )
    { Light::light_attached(id, x); }
  virtual void light_position( bool(id),
                               Transform const &x )
    { Light::light_position(id, x); }
  virtual void light_ambient( uint id, base::Color3 const &x )
    { Light::light_ambient(id, x); }
  virtual void light_diffuse( uint id, base::Color3 const &x )
    { Light::light_diffuse(id, x); }
  virtual void light_specular( uint id, base::Color3 const &x )
    { Light::light_specular(id, x); }
  virtual void light_spot( uint id, base::ArrayX<float,5U> const &x )
    { Light::light_spot(id, x); }
  virtual void light_attenuation( uint id,
                                  base::ArrayX<float,3U> const &x )
    { Light::light_attenuation(id, x); }
  virtual void light_prev()
    { Light::light_prev(); }
  virtual void light_next()
    { Light::light_next(); }

  // global light
  virtual void globallight_reset()
    { GlobalLight::globallight_reset(); }
  virtual void globallight_enable( bool x )
    { GlobalLight::globallight_enable(x); }
  virtual void globallight_ambient( base::Color3 const &x )
    { GlobalLight::globallight_ambient(x); }
  virtual void globallight_viewpoint( bool x )
    { GlobalLight::globallight_viewpoint(x); }
  virtual void globallight_sidedness( bool x )
    { GlobalLight::globallight_sidedness(x); }
  virtual void globallight_toggle()
    { GlobalLight::globallight_toggle(); }
  virtual void globallight_synchronize()
    { GlobalLight::globallight_synchronize(); }
#endif

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

#if 0
  virtual void geomobject_move_enable( bool ) = 0;
  virtual void light_moving_off();
  virtual void clipplane_moving_off();
#endif

  void controls( ::widget::ui::KeyBase &p );
  void controls_win( ::widget::ui::KeyBase &p );

private:
  void camera_toggle_raise_show()
    { _camera()->toggle_raise_show_d(); }
  void globallight_toggle_raise_show()
    { _globallight()->toggle_raise_show_d(); }
  void light_toggle_raise_show()
    { _light()->toggle_raise_show_d(); }
  void background_toggle_raise_show()
    { _light()->toggle_raise_show_d(); }
  void bgread_toggle_raise_show()
    { _bgread()->toggle_raise_show_d(); }
  void blend_toggle_raise_show()
    { _blend()->toggle_raise_show_d(); }
  void clipplane_toggle_raise_show()
    { _clipplane()->toggle_raise_show_d(); }




  virtual milieu::opengl::Milieu *milieu() = 0;
  virtual milieu::opengl::Milieu const *milieu() const = 0;
  virtual milieu::opengl::Background *background()
    { return milieu(); }
  virtual milieu::opengl::Background const *background() const
    { return milieu(); }
  virtual milieu::opengl::Blend *blend()
    { return milieu(); }
  virtual milieu::opengl::Blend const *blend() const
    { return milieu(); }
  virtual milieu::opengl::Camera *camera()
    { return milieu(); }
  virtual milieu::opengl::Camera const *camera() const
    { return milieu(); }
  virtual milieu::opengl::ClipPlaneSet *clipplaneset()
    { return milieu(); }
  virtual milieu::opengl::ClipPlaneSet const *clipplaneset() const
    { return milieu(); }
  virtual milieu::opengl::GlobalLight *globallight()
    { return milieu(); }
  virtual milieu::opengl::GlobalLight const *globallight() const
    { return milieu(); }
  virtual milieu::opengl::LightSet *lightset()
    { return milieu(); }
  virtual milieu::opengl::LightSet const *lightset() const
    { return milieu(); }

  

  Background *_background() { return this; }
  BgRead *_bgread() { return this; }
  Blend *_blend() { return this; }
  Camera *_camera() { return this; }
  ClipPlane *_clipplane() { return this; }
  GlobalLight *_globallight() { return this; }
  Light *_light() { return this; }

  // disabled copy constructor
  Ui( Ui const & );
  // disabled assignment operator
  Ui &operator=( Ui const & );

};

} // namespace ui
} // namespace milieu

#endif // milieu_ui_Ui_INCLUDED
