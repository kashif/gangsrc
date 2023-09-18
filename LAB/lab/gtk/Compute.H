/* GANG Software
 * LAB/lab/gtk/Compute.H
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

#ifndef lab_gtk_Compute_INCLUDED
#define lab_gtk_Compute_INCLUDED

#include "app/app/Dialog.H"
#include "lab/ui/Compute.H"
#include "Compute_.H"

namespace lab {
namespace gtk {

class Compute
  :
    virtual public ui::Compute,
    protected gtk::Compute_,
    public ::app::app::Dialog
{

public:
  // constructor
  Compute( char const *title );

  // destructor
  virtual ~Compute();

protected:

  virtual void grab_focus();

private:

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { Compute_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual widget::ui::Float *progressbar_w()
    { return _progressbar_w; }
  virtual widget::ui::Float const *progressbar_w() const
    { return _progressbar_w; }
  virtual widget::ui::String *time0_w()
    { return _time0_w; }
  virtual widget::ui::String const *time0_w() const
    { return _time0_w; }
  virtual widget::ui::String *time1_w()
    { return _time1_w; }
  virtual widget::ui::String const *time1_w() const
    { return _time1_w; }
  virtual widget::ui::String *name_w()
    { return _name_w; }
  virtual widget::ui::String const *name_w() const
    { return _name_w; }

  // callbacks
  virtual void stop_cb()
    { ui::Compute::stop_cb(); }
  virtual void go_cb()
    { ui::Compute::go_cb(); }

  // disabled copy constructor
  Compute( Compute const & );

  // disabled assignment operator
  Compute &operator=( Compute const & );

};

} // namespace gtk
} // namespace lab

#endif // lab_gtk_Compute_INCLUDED
