/* GANG Software
 * VIEWER/isightui/ui/Ui.C
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

#include "isight/kernel/ViewerBase.H"
#include "Ui.H"

namespace isightui {
namespace ui {

Ui::
Ui()
    :
    Geometry(),
    Mouse(),
    WindowSize(),
    Read(),
    Write(),
    GeomObject(),
    Window(),
    Style(),
    WriteConfig()
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
    _geometry()->command( command, argument, response ) ||
    _mouse()->command( command, argument, response ) ||
    _windowsize()->command( command, argument, response ) ||
    _style()->command( command, argument, response ) ||
    _geomobject()->command( command, argument, response ) ||
    _window()->command( command, argument, response ) ||
    _read()->command( command, argument, response ) ||
    _write()->command( command, argument, response ) ||
    _writeconfig()->command( command, argument, response );
}

void
Ui::
show_all(bool state)
{
  _geometry()->show_d(state);
  _mouse()->show_d(state);
  _windowsize()->show_d(state);
  _style()->show_d(state);
  _geomobject()->show_d(state);
  _window()->show_d(state);
  _read()->show_d(state);
  _write()->show_d(state);
  _writeconfig()->show_d(state);
}

void
Ui::
enable_tooltips( bool state )
{
  _geometry()->enable_tooltips_d( state );
  _mouse()->enable_tooltips_d( state );
  _windowsize()->enable_tooltips_d( state );
  _style()->enable_tooltips_d( state );
  _geomobject()->enable_tooltips_d( state );
  _window()->enable_tooltips_d( state );
  _read()->enable_tooltips_d( state );
  _write()->enable_tooltips_d( state );
  _writeconfig()->enable_tooltips_d( state );
}

void
Ui::
synchronize()
{
  Geometry::synchronize();
  Mouse::synchronize();
  windowsize_synchronize();
  style_synchronize();
}

void
Ui::
reset()
{
#if FIX
  window()->enable_draw(false);
#endif

  Geometry::reset_geometry();
  Mouse::mouse_reset();
  WindowSize::windowsize_reset();

#if FIX
  window()->enable_draw(true);
#endif
}

#if 0
void
Ui::
light_move_reset()
{ light_move_reset(); }

void
Ui::
clipplane_move_reset()
{ clipplane_move_reset(); }
#endif

void
Ui::
controls_file( ::widget::ui::KeyBase &p )
{
  // CTRL-o = Open iSight File
  p.insert(
    "Open iSight File...", GDK_o, MOD_CTRL,
    this,
    &::isightui::ui::Ui::read_toggle_raise_show );

  // CTRL-s = Save iSight File
  p.insert(
    "Save iSight File...", GDK_s, MOD_CTRL,
    this,
    &::isightui::ui::Ui::write_toggle_raise_show );
}

void
Ui::
controls( ::widget::ui::KeyBase &p )
{
  // CTRL-w = WindowSize Widget
  p.insert(
    "Window Size...", GDK_w, MOD_CTRL,
    this,
    &isightui::ui::Ui::windowsize_toggle_raise_show );

  // CTRL-m = Mouse Widget
  p.insert(
    "Mouse...",       GDK_m, MOD_CTRL,
    this,
    &::isightui::ui::Ui::mouse_toggle_raise_show );

  // CTRL-g = Geometry Widget
  p.insert(
    "Geometry...",    GDK_g, MOD_CTRL,
    this,
    &::isightui::ui::Ui::geometry_toggle_raise_show );

  // CTRL-u = Select Object Widget
  p.insert(
    "Select Object...",      GDK_u, MOD_CTRL,
    this,
    &::isightui::ui::Ui::geomobject_toggle_raise_show );

  // CTRL-i = Select Window Widget
  p.insert(
    "Select Window...",      GDK_i, MOD_CTRL,
    this,
    &::isightui::ui::Ui::window_toggle_raise_show );

  // CTRL-p = WriteConfig Widget
  p.insert(
    "Write Config...", GDK_p, MOD_CTRL,
    this,
    &::isightui::ui::Ui::writeconfig_toggle_raise_show );

  // ALT-y = Style Widget
  p.insert(
    "Style...",       GDK_y, MOD_ALT,
    this,
    &::isightui::ui::Ui::style_toggle_raise_show );
}

void
Ui::
controls_win( ::widget::ui::KeyBase &p )
{
  // w = Toggle FullScreen
  p.insert(
    "Toggle fullscreen", GDK_w, MOD_NONE,
    _windowsize(),
    &::isightui::ui::WindowSize::windowsize_toggle_fullscreen );

  // a = Toggle Axes
  p.insert(
    "Toggle axes", GDK_a, MOD_NONE,
    _style(),
    &::isightui::ui::Style::toggle_axes );

  // p = Toggle Sphere
  p.insert(
    "Toggle sphere", GDK_p, MOD_NONE,
    _style(),
    &::isightui::ui::Style::toggle_sphere );

  // y = Next Style
  p.insert(
    "style next", GDK_y, MOD_NONE,
    _style(),
    &::isightui::ui::Style::style_next );

  // Y = Previous Style
  p.insert(
    "style prev", GDK_Y, MOD_SHIFT,
    _style(),
    &::isightui::ui::Style::style_prev );

  // c = Reset Position
  p.insert(
    "reset position", GDK_c, MOD_NONE,
    _window(),
    &::isightui::ui::Window::reset_position );

  // s = Stop Motion
  p.insert(
    "stop motion", GDK_s, MOD_NONE,
    _window(),
    &::isightui::ui::Window::stop_motion );

  // CTRL-ALT-r = Mouse Mode Rotation
  p.insert(
    "Mouse rotation", GDK_r, MOD_CTRL_ALT,
    _geometry(),
    &::isightui::ui::Geometry::mouse_rotation );
  // CTRL-ALT-t = Mouse Mode Translation
  p.insert(
    "Mouse translation", GDK_t, MOD_CTRL_ALT,
    _geometry(),
    &::isightui::ui::Geometry::mouse_translation );
  // CTRL-ALT-i = Mouse Mode Inversion
  p.insert(
    "Mouse inversion", GDK_i, MOD_CTRL_ALT,
    _geometry(),
    &::isightui::ui::Geometry::mouse_inversion );
  // CTRL-ALT-S = Mouse Mode Scale
  p.insert(
    "Mouse scale", GDK_s, MOD_CTRL_ALT,
    _geometry(),
    &::isightui::ui::Geometry::mouse_scale );
}

} // namespace ui
} // namespace isightui
