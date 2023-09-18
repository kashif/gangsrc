/* GANG Software
 * LAB/bubbletonlab/gtk/Controls.H
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

#ifndef bubbletonlab_gtk_Controls_INCLUDED
#define bubbletonlab_gtk_Controls_INCLUDED

#include "app/app/Dialog.H"
#include "bubbletonlab/ui/Controls.H"
#include "Controls_.H"

namespace bubbletonlab {
namespace gtk {

class Controls
  :
    virtual public ui::Controls,
    protected Controls_,
    public ::app::app::Dialog
{

public:
  // constructor
  Controls(char const *title);

  // destructor
  virtual ~Controls();

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
    { Controls_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual widget::ui::String *center_w()
    { return _center_w; }
  virtual widget::ui::String *size_w()
    { return _size_w; }
  virtual widget::ui::Float *normalshift_w()
    { return _normalshift_w; }
  virtual widget::ui::Widget *normalshift_button0_w()
    { return _normalshift_button0_w; }
  virtual widget::ui::Widget *normalshift_button1_w()
    { return _normalshift_button1_w; }
  virtual widget::ui::Widget *normalshift_button2_w()
    { return _normalshift_button2_w; }

  virtual widget::ui::String const *center_w() const
    { return _center_w; }
  virtual widget::ui::String const *size_w() const
    { return _size_w; }
  virtual widget::ui::Float const *normalshift_w() const
    { return _normalshift_w; }
  virtual widget::ui::Widget const *normalshift_button0_w() const
    { return _normalshift_button0_w; }
  virtual widget::ui::Widget const *normalshift_button1_w() const
    { return _normalshift_button1_w; }
  virtual widget::ui::Widget const *normalshift_button2_w() const
    { return _normalshift_button2_w; }

  // callbacks
  virtual void normalshift_cb()
    { ui::Controls::normalshift_cb(); }
  virtual void normalshift_button0_cb()
    { ui::Controls::normalshift_button0_cb(); }
  virtual void normalshift_button1_cb()
    { ui::Controls::normalshift_button1_cb(); }
  virtual void normalshift_button2_cb()
    { ui::Controls::normalshift_button2_cb(); }

  // disabled copy constructor
  Controls( Controls const & );

  // disabled assignment operator
  Controls &operator=( Controls const & );

};

} // namespace gtk
} // namespace bubbletonlab

#endif // bubbletonlab_gtk_Controls_INCLUDED
