/* GANG Software
 * WIDGET/widget/cmd/Dialog.H
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

#ifndef widget_cmd_Dialog_INCLUDED
#define widget_cmd_Dialog_INCLUDED

#include <stdlib.h>
#include "widget/ui/Dialog.H"
#include "Window.H"

namespace widget {
namespace cmd {

class Dialog
  :
    virtual public widget::uiDialog
//  :
//  virtual public Window
{

public:
  // constructor
  Dialog() {}

  // destructor
  virtual ~Dialog() {}

  virtual void raise_d( bool state = true ) = 0;
  virtual void show_d( bool state = true ) = 0;
  virtual void toggle_raise_show_d() = 0;
  virtual void enable_tooltips_d( bool state = true ) = 0;
  virtual int key_press_event_d( uint key, uint state ) = 0;

  // connection functions
  virtual void show( bool state = true )
    { Widget::show(state); }
  virtual bool showing() const
    { return Widget::showing(); }
  virtual void set_sensitive( bool state = true )
    { Widget::set_sensitive(state); }

protected:

private:

  // disabled copy constructor
  Dialog( Dialog const & );
  // disabled assignment operator
  Dialog &operator=( Dialog const & );

};

} // namespace cmd
} // namespace widget

#endif // widget_cmd_Dialog_INCLUDED
