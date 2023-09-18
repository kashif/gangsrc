/* GANG Software
 * LAB/lab/gtklab/Lab.H
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

#ifndef lab_gtklab_Lab_INCLUDED
#define lab_gtklab_Lab_INCLUDED

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "app/app/App.H"
#include "gtk/widget1/Input.H"
#include "widget/ui/Command.H"
#include "widget/ui/KeyHandler.H"
#include "lab/ui/Ui.H"

namespace lab {
namespace gtklab {

template <class LAB>
class Lab
  :
    public LAB,
    public ::app::app::App,
    protected widget::ui::Command,
    protected ::gtk::widget1::Input<widget::ui::Command>
{

public:

  // constructor
  Lab();

  // destructor
  virtual ~Lab();

  // allow input from stdin
  void command_mode( bool state = true );

protected:

private:
  // show/hide all dialog boxes
  virtual void hide_all()
    { LAB::hide_all(); }
  // enable/disable help balloons
  virtual void enable_tooltips( bool state )
    { LAB::enable_tooltips(state); }
  // -> app::ui::Message connector function
  virtual void message( base::String const &text ) const
    { ::app::gtk::Message::message(text); }

  // app::ui::Commands -> widget::ui::Command connector functions
  virtual void execute_command( base::String const &text )
    { widget::ui::Command::execute_command(text); }

  // widget::ui::Command -> app::ui::Commands connector functions
  virtual void command_respond( base::String const &text, bool raw )
    { app::ui::Commands::command_respond(text, raw); }

  // widget::ui::Command -> connector functions
  virtual bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

  virtual void sync()
    { app::app::App::sync(); }

  virtual void exit()
    { stop_computation(); stop_motion(); gtk_main_quit(); }

  // key handler from dialog boxes
  virtual int key_press_event_d( uint key, uint state );
  // key handler from geometry window
  virtual int window_key_press_event( uint key, uint state );

  void make_menus();
  void make_key_shortcuts();

  ::widget::ui::KeyHandler _main_keyhandler;
  ::widget::ui::KeyHandler _window_keyhandler;

  ::gtk::widget1::Menu _file_menu;
  ::gtk::widget1::Menu _lab_menu;
  ::gtk::widget1::Menu _controls_menu;
  ::gtk::widget1::Menu _geom_menu;
  ::gtk::widget1::Menu _milieu_menu;
  ::gtk::widget1::Menu _viewer_menu;

  // disabled copy constructor
  Lab( Lab const &);

  // disabled assignment operator
  Lab &operator=( Lab const & );

};

template <class LAB>
Lab<LAB>::
Lab()
    :
    LAB(),
    app::app::App(
      app_name(),
      lab_name(),
      about_info(),
      xpm(),
      env_help_url() ),
    ::gtk::widget1::Input<widget::ui::Command>
      (static_cast<widget::ui::Command *>(this),
       &::widget::ui::Command::execute_command ),
    _main_keyhandler(),
    _file_menu( "File             " ),
    _lab_menu     ( "Lab             "),
    _controls_menu("Controls    "),
    _geom_menu( "Geometry" ),
    _milieu_menu( "Window" ),
    _viewer_menu( "Viewer" )
{
  set_lab_lib_env_path( env_lib_path() );

  make_menus();
  make_key_shortcuts();

  ::app::app::AppMenu::raise_show();
}

template <class LAB>
Lab<LAB>::
~Lab()
{
}

template <class LAB>
void
Lab<LAB>::
make_menus()
{
  // file menu
  lab::ui::Ui::controls_file(_file_menu);
  _file_menu.insert_separator();
  isightui::ViewerUiGtk::controls_file(_file_menu);
  _file_menu.insert_separator();
  app::app::App::controls_file(_file_menu);
  insert_menu(_file_menu);

  // controls menu
  app::app::App::controls(_controls_menu);
  insert_menu(_controls_menu);

  // lab menu
  lab::ui::Ui::controls(_lab_menu);
  insert_menu(_lab_menu);

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

template <class LAB>
void
Lab<LAB>::
make_key_shortcuts()
{
  // main_keyhandler
  ::lab::ui::Ui::controls_file(_main_keyhandler);
  isightui::ViewerUiGtk::controls_file(_main_keyhandler);
  app::app::App::controls_file(_main_keyhandler);
  app::app::App::controls(_main_keyhandler);
  ::lab::ui::Ui::controls(_main_keyhandler);
  app::app::App::controls(_main_keyhandler);
  ::geomui::GeomUiGtk::controls(_main_keyhandler);
  ::milieu::MilieuUiGtk::controls(_main_keyhandler);
  ::isightui::ViewerUiGtk::controls(_main_keyhandler);

  // window_keyhandler
  ::geomui::GeomUiGtk::controls_win( _window_keyhandler );
  ::milieu::MilieuUiGtk::controls_win( _window_keyhandler );
  ::isightui::ViewerUiGtk::controls_win( _window_keyhandler );
}

template <class LAB>
int
Lab<LAB>::
key_press_event_d( uint key, uint modifier )
{
  // handle key press events coming from dialog boxes and main menu

  // generic handler
  return _main_keyhandler.go( key, modifier );
}

template <class LAB>
int
Lab<LAB>::
window_key_press_event( uint key, uint modifier )
{
  // handle key press events coming from window

  return
    // lab-specific window handlers
    _window_keyhandler.go( key, modifier ) ||

    // generic handler
    _main_keyhandler.go( key, modifier );
}

template <class LAB>
bool
Lab<LAB>::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  return
    LAB::command(command, argument, response) ||
    static_cast< ::app::ui::Ui *>(this)->command(command, argument, response);
}

template <class LAB>
void
Lab<LAB>::
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

} // namespace gtklab
} // namespace lab

#endif // lab_gtklab_Lab_INCLUDED
