/* GANG Software
 * WIDGET/app/gtk/Commands.H
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

#ifndef app_gtk_Commands_INCLUDED
#define app_gtk_Commands_INCLUDED

#include "app/app/Dialog.H"
#include "app/ui/Commands.H"
#include "Commands_.H"

namespace app {
namespace gtk {

class Commands
  :
    virtual public ui::Commands,
    protected Commands_,
    public ::app::app::Dialog
{

public:
  // constructor
  Commands(char const *title);

  // destructor
  virtual ~Commands();

protected:

private:

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { Commands_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  virtual widget::ui::String *text_w()
    { return _text_w; }
  virtual widget::ui::String const *text_w() const
    { return _text_w; }

  // callbacks
  virtual void execute_cb()
    { ui::Commands::execute_cb(); }

  static char const *label()
    { return "Commands"; }

  // disabled copy constructor
  Commands( Commands const & );
  // disabled assignment operator
  Commands &operator=( Commands const & );

};

} // namespace gtk
} // namespace app

#endif // app_gtk_Commands_INCLUDED
