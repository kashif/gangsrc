/* GANG Software
 * LAB/lab/gtk/Sequence.H
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

#ifndef lab_gtk_Sequence_INCLUDED
#define lab_gtk_Sequence_INCLUDED

#include "app/app/Dialog.H"
#include "lab/ui/Sequence.H"
#include "Sequence_.H"

namespace lab {
namespace gtk {

class Sequence
  :
    virtual public ui::Sequence,
    protected gtk::Sequence_,
    public ::app::app::Dialog
{

public:
  // constructor
  Sequence(char const *title);

  // destructor
  virtual ~Sequence();

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
    { Sequence_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual widget::ui::Widget *go_w()
    { return _go_w; }
  virtual widget::ui::Widget *go_write_w()
    { return _go_write_w; }
  virtual widget::ui::Widget *stop_w()
    { return _stop_w; }
  virtual widget::ui::Widget *reset_w()
    { return _reset_w; }
  virtual widget::ui::String *now_w()
    { return _now_w; }
  virtual widget::ui::IntSet *counter_w()
    { return _counter_w; }
  virtual widget::ui::String *counter_varname_w()
    { return _counter_varname_w; }
  virtual widget::ui::String *time_varname_w()
    { return _time_varname_w; }
  virtual widget::ui::String *function_w()
    { return _function_w; }
  virtual widget::ui::String *filename_w()
    { return _filename_w; }

  // callbacks
  virtual void go_cb()
    { ui::Sequence::go_cb(); }
  virtual void go_write_cb()
    { ui::Sequence::go_write_cb(); }
  virtual void stop_cb()
    { ui::Sequence::stop_cb(); }
  virtual void reset_cb()
    { ui::Sequence::reset_cb(); }


  // disabled copy constructor
  Sequence( Sequence const & );

  // disabled assignment operator
  Sequence &operator=( Sequence const & );

};

} // namespace gtk
} // namespace lab

#endif // lab_gtk_Sequence_INCLUDED
