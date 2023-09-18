/* GANG Software
 * WIDGET/app/cmd/Message.H
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

#ifndef app_cmd_Message_INCLUDED
#define app_cmd_Message_INCLUDED

#include "widget/cmd/String.H"
#include "app/ui/Message.H"

namespace app {
namespace cmd {

class Message
  :
    virtual public ui::Message
{

public:
  // constructor
  Message();

  // destructor
  virtual ~Message();

  virtual void message( base::String const &text ) const;

protected:

private:
  // widgets
  virtual widget::ui::String *messagebox_w()
    { return &_messagebox_w; }
  virtual widget::ui::String const *messagebox_w() const
    { return &_messagebox_w; }

  widget::cmd::String _messagebox_w;

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

  // disabled copy constructor
  Message( Message const & );
  // disabled assignment operator
  Message &operator=( Message const & );

};

} // namespace cmd
} // namespace app

#endif // app_cmd_Message_INCLUDED
