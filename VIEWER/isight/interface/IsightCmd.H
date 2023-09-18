/* GANG Software
 * VIEWER/isight/interface/IsightCmd.H
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

#ifndef isight_IsightCmd_INCLUDED
#define isight_IsightCmd_INCLUDED

#include "app/cmd/Ui.H"
#include "app/ui/Ui.H"
#include "widget/ui/Command.H"
#include "widget/ui/KeyHandler.H"
#include "IsightBaseCmd.H"

namespace isight {

class IsightCmd
  :
    public IsightBaseCmd,
    public app::cmd::Ui,
    public app::ui::Ui,
    protected widget::ui::Command
{

public:

  // constructor
  IsightCmd();

  // destructor
  virtual ~IsightCmd();

  // name of executable
  virtual char const *app_name()
    { return "isight"; }

protected:

private:

  // show/hide all dialog boxes
  virtual void show_all( bool state ) {}
  // hide all dialog boxes
  void hide_all() {}

  // enable/disable help balloons
  virtual void enable_all_tooltips( bool state ) {}
  // toggle help balloons
  void toggle_all_tooltips() {}

  // -> app::ui::Message connector function
  virtual void message( base::String const &text ) const
    { ::app::cmd::Message::message(text); }

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

  virtual void exit()
    { ::exit(0); }

  // key handler from dialog boxes
  virtual int key_press_event_d( uint key, uint state )
    { return 0; }
  // key handler from geometry window
  virtual int window_key_press_event( uint key, uint state )
    { return 0; }

protected:

private:

  // disabled copy constructor
  IsightCmd( IsightCmd const & );

  // disabled assignment operator
  IsightCmd &operator=( IsightCmd const & );
};

} // namespace isight

#endif // isight_IsightCmd_INCLUDED
