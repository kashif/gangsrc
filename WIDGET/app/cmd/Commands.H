/* GANG Software
 * WIDGET/app/cmd/Commands.H
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

#ifndef app_cmd_Commands_INCLUDED
#define app_cmd_Commands_INCLUDED

#include "widget/cmd/String.H"
#include "app/ui/Commands.H"

namespace app {
namespace cmd {

class Commands
  :
    virtual public ui::Commands
{

public:
  // constructor
  Commands();

  // destructor
  virtual ~Commands();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::String *text_w()
    { return &_text_w; }
  virtual widget::ui::String const *text_w() const
    { return &_text_w; }

  // widgets
  widget::cmd::String _text_w;

  // disabled copy constructor
  Commands( Commands const & );
  // disabled assignment operator
  Commands &operator=( Commands const & );

};

} // namespace cmd
} // namespace app

#endif // app_cmd_Commands_INCLUDED
