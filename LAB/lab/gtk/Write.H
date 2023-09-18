/* GANG Software
 * LAB/lab/gtk/Write.H
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

#ifndef lab_gtk_Write_INCLUDED
#define lab_gtk_Write_INCLUDED

#include "app/app/Dialog.H"
#include "lab/ui/Write.H"
#include "Write_.H"

namespace lab {
namespace gtk {

class Write
  :
    virtual public ui::Write,
    protected gtk::Write_,
    public ::app::app::Dialog
{

public:
  // constructor
  Write(char const *title);

  // destructor
  virtual ~Write();

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
    { Write_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual widget::ui::File *write_w()
    { return _write_w; }

  // callbacks
  virtual void write_cb()
    { ui::Write::write_cb(); }

  // disabled copy constructor
  Write( Write const & );

  // disabled assignment operator
  Write &operator=( Write const & );

};

} // namespace gtk
} // namespace lab

#endif // lab_gtk_Write_INCLUDED
