/* GANG Software
 * VIEWER/isight/interface/IsightGtk.C
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

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "isight.xpm"
#include "IsightGtk.H"

namespace isight {

static char const *about_info =
"Created by Nick Schmitt";

IsightGtk::
IsightGtk()
    :
    app::app::App(
      app_name(),
      "iSight", // NOTE
      about_info,
      isight_xpm,
      "ISIGHT_DOC" ),
    IsightBaseGtk(),
    ::gtk::widget1::Input<widget::ui::Command>
      (static_cast<widget::ui::Command *>(this),
       &::widget::ui::Command::execute_command ),
    _main_keyhandler(),
    _window_keyhandler(),
    _file_menu( "File             " ),
    _controls_menu("Controls    "),
    _geom_menu( "Geometry" ),
    _milieu_menu( "Window" ),
    _viewer_menu( "Viewer" )
{
  make_menus();
  make_key_shortcuts();
//  new_window();

  // show AppMenu
  ::app::app::AppMenu::show(true);
}

void
IsightGtk::
make_menus()
{
  // file menu
  ::isightui::ViewerUiGtk::controls_file(_file_menu);
  _file_menu.insert_separator();
  app::app::App::controls_file(_file_menu);
  insert_menu(_file_menu);

  // controls menu
  app::app::App::controls(_controls_menu);
  insert_menu(_controls_menu);

  // geom menu
  ::geomui::GeomUiGtk::controls(_geom_menu);
  insert_menu(_geom_menu);

  // milieu menu
  ::milieu::MilieuUiGtk::controls(_milieu_menu);
  insert_menu(_milieu_menu);

  // viewer menu
  ::isightui::ViewerUiGtk::controls(_viewer_menu);
  insert_menu(_viewer_menu);
}

void
IsightGtk::
make_key_shortcuts()
{
  // main_keyhandler
  ::app::app::App::controls( _main_keyhandler );
  ::app::app::App::controls_file( _main_keyhandler );
  ::geomui::GeomUiGtk::controls( _main_keyhandler );
  ::milieu::MilieuUiGtk::controls( _main_keyhandler );
  ::isightui::ViewerUiGtk::controls( _main_keyhandler );
  ::isightui::ViewerUiGtk::controls_file( _window_keyhandler );

  // window_keyhandler
  ::geomui::GeomUiGtk::controls_win( _window_keyhandler );
  ::milieu::MilieuUiGtk::controls_win( _window_keyhandler );
  ::isightui::ViewerUiGtk::controls_win( _window_keyhandler );
}

IsightGtk::
~IsightGtk()
{
}

int
IsightGtk::
key_press_event_d( uint key, uint modifier )
{
  // handle key press events coming from dialog boxes and main menu

  // generic handler
  return _main_keyhandler.go( key, modifier );
}

int
IsightGtk::
window_key_press_event( uint key, uint modifier )
{
  // handle key press events coming from window

  return
    // window-specific handler
    _window_keyhandler.go( key, modifier ) ||

    // generic handler
    _main_keyhandler.go( key, modifier );
}

void
IsightGtk::
command_mode( bool state )
{
  if (state)
  {
    // set stdin to be non-blocking
    ::fcntl( 0, F_SETFL, O_NONBLOCK );
  }
  else
  {
    ::fcntl( 0, F_SETFL, 0 );
  }
  static_cast< ::gtk::widget1::Input<widget::ui::Command> *>(this)->set(state);
}

bool
IsightGtk::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  return
    ::app::ui::Ui::command(command, argument, response) ||
    IsightBase::command(command, argument, response);
}

} // namespace isight
