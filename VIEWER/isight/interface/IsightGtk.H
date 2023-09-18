/* GANG Software
 * VIEWER/isight/interface/IsightGtk.H
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

#ifndef isight_IsightGtk_INCLUDED
#define isight_IsightGtk_INCLUDED

#include "app/app/App.H"
#include "widget/ui/Command.H"
#include "widget/ui/KeyHandler.H"
#include "gtk/widget1/Input.H"
#include "IsightBaseGtk.H"

namespace isight {

class IsightGtk
  :
    public app::app::App,
    public IsightBaseGtk,
    protected widget::ui::Command,
    protected ::gtk::widget1::Input<widget::ui::Command>
{

public:

  // constructor
  IsightGtk();

  // destructor
  virtual ~IsightGtk();

  // name of executable
  virtual char const *app_name()
    { return "isight"; }

  // allow input from stdin
  void command_mode( bool state = true );

protected:

private:

#if 0
  // hide all dialog boxes
  virtual void hide_all();

  // enable/disable help balloons
  virtual void enable_tooltips( bool state );
  // toggle help balloons
  void toggle_tooltips()
    { enable_tooltips( !_tooltip_state ); }
#endif

  // -> app::ui::Message connector function
  virtual void message( base::String const &text ) const
    { ::app::gtk::Message::message(text); }

  // app::ui::Commands -> widget::ui::Command connector functions
  virtual void execute_command( base::String const &text )
    { static_cast< widget::ui::Command *>(this)->execute_command(text); }

  // widget::ui::Command -> app::ui::Commands connector functions
  virtual void command_respond( base::String const &text, bool raw )
    { ::app::ui::Commands::command_respond(text, raw); }

  // widget::ui::Command -> connector functions
  virtual bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

  virtual void exit()
    { gtk_main_quit(); }
  void hide_all()
    { IsightBase::hide_all(); }
  void enable_tooltips( bool state )
    { IsightBase::enable_tooltips(state); }


  // key handler from dialog boxes
  virtual int key_press_event_d( uint key, uint state );
  // key handler from geometry window
  virtual int window_key_press_event( uint key, uint state );

  void make_menus();
  void make_key_shortcuts();

  ::widget::ui::KeyHandler _main_keyhandler;
  ::widget::ui::KeyHandler _window_keyhandler;

  ::gtk::widget1::Menu _file_menu;
  ::gtk::widget1::Menu _controls_menu;
  ::gtk::widget1::Menu _geom_menu;
  ::gtk::widget1::Menu _milieu_menu;
  ::gtk::widget1::Menu _viewer_menu;

  // disabled copy constructor
  IsightGtk( IsightGtk const & );

  // disabled assignment operator
  IsightGtk &operator=( IsightGtk const & );
};

} // namespace isight

#endif // isight_IsightGtk_INCLUDED
