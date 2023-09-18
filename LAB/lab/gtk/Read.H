/* GANG Software
 * LAB/lab/gtk/Read.H
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

#ifndef lab_gtk_Read_INCLUDED
#define lab_gtk_Read_INCLUDED

#include "app/app/Dialog.H"
#include "lab/ui/Read.H"
#include "Read_.H"

namespace lab {
namespace gtk {

class Read
  :
    virtual public ui::Read,
    protected gtk::Read_,
    public ::app::app::Dialog
{

public:
  // constructor
  Read(char const *title);

  // destructor
  virtual ~Read();

  void set_read_env_path(  char const *lib_env_path )
    { _read_w->set_lib_env_path( lib_env_path ); }
protected:

private:

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }
  virtual void enable_tooltips_d( bool state = true )
    { Read_::enable_tooltips(state); }

  // widgets
  virtual widget::ui::ReadFile *read_w()
    { return _read_w; }

  // callbacks
  virtual void read_cb()
    { ui::Read::read_cb(); }

  // disabled copy constructor
  Read( Read const & );

  // disabled assignment operator
  Read &operator=( Read const & );

};

} // namespace gtk
} // namespace lab

#endif // lab_gtk_Read_INCLUDED
