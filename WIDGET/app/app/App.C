/* GANG Software
 * WIDGET/app/app/App.C
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

#include "App.H"

namespace app {
namespace app {

App::
App(
  char const *app_name,
  char const *window_title,
  char const *about_info,
  char const * const *xpm,
  char const *help_url_env )
    :
    ::app::ui::Ui(),
    ::app::gtk::Ui( window_title, app_name, about_info, xpm),
    Help( help_url_env ),
    AppMenu( window_title ),
    AppWindow( static_cast<AppMenu *>(this) ),
    _tooltip_state(true)

{
}

App::
~App()
{
}

void
App::
sync()
{
  while(gtk_events_pending()) { gtk_main_iteration(); }
}

void
App::
hide_all_cb()
{
  hide_all();
  ::app::ui::Ui::hide_all();
}

void
App::
toggle_tooltips_cb()
{
  _tooltip_state = ! _tooltip_state;
  static_cast< ::app::ui::Ui *>(this)->enable_tooltips( _tooltip_state );
  enable_tooltips( _tooltip_state );
}

void
App::
controls_file( ::widget::ui::KeyBase &p )
{
  // CTRL-h = Help
  p.insert(
    "Netscape Help...",      GDK_h, MOD_CTRL,
    static_cast< ::app::app::Help *>(this),
    &::app::app::Help::help );

  // CTRL-q = Quit
  p.insert(
    "Quit...",                 GDK_q, MOD_CTRL,
    static_cast< ::app::app::App *>(this),
    &::app::app::App::exit );
}

void
App::
controls( ::widget::ui::KeyBase &p )
{
  // CTRL-C = Commands Widget
  p.insert(
    "Command...",    GDK_C, MOD_CTRL_SHIFT,
    static_cast< ::app::app::Dialog *>(
      static_cast< ::app::gtk::Commands *>(this) ),
    &::app::gtk::Commands::toggle_raise_show );

  // CTRL-S = Shortcut Widget
  p.insert(
    "Shortcuts...",    GDK_S, MOD_CTRL_SHIFT,
    static_cast< ::app::app::Dialog *>(
      static_cast< ::app::gtk::Shortcut *>(this) ),
    &::app::gtk::Shortcut::toggle_raise_show );

  // CTRL-; = Main Menu Widget
  p.insert(
    "Menu",       GDK_semicolon, MOD_CTRL,
    static_cast< ::app::app::AppMenu *>(this),
    &::app::app::AppMenu::raise_show );

  // CTRL-X = Close Windows
  p.insert(
    "Close Windows",  GDK_W, MOD_CTRL_SHIFT,
    this,
    &::app::app::App::hide_all_cb );

  // CTRL-T = Toggle Tooltips
  p.insert(
    "Toggle Help Balloons",    GDK_T, MOD_CTRL_SHIFT,
    this,
    &::app::app::App::toggle_tooltips_cb );

  // CTRL-A = About Widget
  p.insert(
    "About...",       GDK_A, MOD_CTRL_SHIFT,
    static_cast< ::app::app::Dialog *>(
      static_cast< ::app::gtk::About *>(this) ),
    &::app::gtk::About::toggle_raise_show );

  // CTRL-M = Messages Widget
  p.insert(
    "Messages...",    GDK_M, MOD_CTRL_SHIFT,
    static_cast< ::app::app::Dialog *>(
      static_cast< ::app::gtk::Message *>(this) ),
    &::app::gtk::Message::toggle_raise_show );
}

} // namespace app
} // namespace app
