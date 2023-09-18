/* GANG Software
 * GEOM/milieu/ui/Ui.C
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

#include "Ui.H"

namespace milieu {
namespace ui {

Ui::
Ui()
    :
    BgRead(),
    Background(),
    Blend(),
    Camera(),
    ClipPlane(),
    GlobalLight(),
    Light()
{
}

Ui::
~Ui()
{
}

bool
Ui::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  return
    _bgread()->command( command, argument, response ) ||
    _background()->command( command, argument, response ) ||
    _blend()->command( command, argument, response ) ||
    _camera()->command( command, argument, response ) ||
    _clipplane()->command( command, argument, response ) ||
    _globallight()->command( command, argument, response ) ||
    _light()->command( command, argument, response );
}

void
Ui::
reset()
{
  background_reset();
  blend_reset();
  reset_camera();
  clipplane_reset();
  globallight_reset();
  light_reset();
}

void
Ui::
show_all(bool state)
{
  _bgread()->show_d(state);
  _background()->show_d(state);
  _blend()->show_d(state);
  _camera()->show_d(state);
  _clipplane()->show_d(state);
  _globallight()->show_d(state);
  _light()->show_d(state);
}

void
Ui::
enable_tooltips( bool state )
{
  _bgread()->enable_tooltips_d( state );
  _background()->enable_tooltips_d( state );
  _blend()->enable_tooltips_d( state );
  _camera()->enable_tooltips_d( state );
  _clipplane()->enable_tooltips_d( state );
  _globallight()->enable_tooltips_d( state );
  _light()->enable_tooltips_d( state );
}

void
Ui::
synchronize()
{
  background_synchronize();
  blend_synchronize();
  camera_synchronize();
  clipplane_synchronize();
  globallight_synchronize();
  light_synchronize();
}

#if 0
void
Ui::
light_moving_off()
{
  // stop all lights
  uint id;
  for (id = 0; id < 8; id++ )
  {
    light_moving( id, false );
  }
}

void
Ui::
clipplane_moving_off()
{
  // stop all clipplanes
  uint id;
  for (id = 0; id < 6; id++ )
  {
    clipplane_moving( id, false );
  }
}
#endif

void
Ui::
controls( ::widget::ui::KeyBase &p )
{
  // CTRL-c = Camera Widget
  p.insert(
    "Camera...",      GDK_c, MOD_CTRL,
    this,
    &::milieu::ui::Ui::camera_toggle_raise_show );

  // ALT-g = Global Light Widget
  p.insert(
    "Global Light...",  GDK_g, MOD_ALT,
    this,
    &::milieu::ui::Ui::globallight_toggle_raise_show );

  // ALT-l = Light Widget
  p.insert(
    "Lights...",      GDK_l, MOD_ALT,
    this,
    &::milieu::ui::Ui::light_toggle_raise_show );

  // ALT-b = Background Widget
  p.insert(
    "Background...",  GDK_b, MOD_ALT,
    this,
    &::milieu::ui::Ui::background_toggle_raise_show );

  // ALT-d = Blend Widget
  p.insert(
    "Blend...",       GDK_d, MOD_ALT,
    this,
    &::milieu::ui::Ui::blend_toggle_raise_show );

  // ALT-p = Clip Plane Widget
  p.insert(
    "Clip Planes...", GDK_p, MOD_ALT,
    this,
    &::milieu::ui::Ui::clipplane_toggle_raise_show );
}

void
Ui::
controls_win( ::widget::ui::KeyBase &p )
{
  // b = Next Background
  p.insert(
    "background next", GDK_b, MOD_NONE,
    _background(),
    &::milieu::ui::Background::background_next );

  // B = Previous Background
  p.insert(
    "background prev", GDK_B, MOD_SHIFT,
    _background(),
    &::milieu::ui::Background::background_prev );

  // g = Toggle Global Light
  p.insert(
    "Toggle global light", GDK_g, MOD_NONE,
    _globallight(),
    &::milieu::ui::GlobalLight::globallight_toggle );

  // l = Cycle Lights
  p.insert(
    "Cycle lights", GDK_l, MOD_NONE,
    _light(),
    &::milieu::ui::Light::light_next);

  // L = Cycle Lights
  p.insert(
    "Cycle lights", GDK_L, MOD_SHIFT,
    _light(),
    &::milieu::ui::Light::light_prev);
}

} // namespace ui
} // namespace milieu
