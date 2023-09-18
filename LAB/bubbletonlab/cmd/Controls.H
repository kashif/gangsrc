/* GANG Software
 * LAB/bubbletonlab/cmd/Controls.H
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

#ifndef bubbletonlab_cmd_Controls_INCLUDED
#define bubbletonlab_cmd_Controls_INCLUDED

#include "widget/cmd/Float.H"
#include "widget/cmd/String.H"
#include "bubbletonlab/ui/Controls.H"

namespace bubbletonlab {
namespace cmd {

class Controls
  :
    virtual public ui::Controls
{

public:
  // constructor
  Controls();

  // destructor
  virtual ~Controls();

protected:

private:

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

  // widgets
  virtual widget::ui::String *center_w()
    { return &_center_w; }
  virtual widget::ui::String *size_w()
    { return &_size_w; }
  virtual widget::ui::Float *normalshift_w()
    { return &_normalshift_w; }

  virtual widget::ui::String const *center_w() const
    { return &_center_w; }
  virtual widget::ui::String const *size_w() const
    { return &_size_w; }
  virtual widget::ui::Float const *normalshift_w() const
    { return &_normalshift_w; }

  // callbacks
  virtual void normalshift_cb()
    { ui::Controls::normalshift_cb(); }
  virtual void normalshift_button0_cb()
    { ui::Controls::normalshift_button0_cb(); }
  virtual void normalshift_button1_cb()
    { ui::Controls::normalshift_button1_cb(); }
  virtual void normalshift_button2_cb()
    { ui::Controls::normalshift_button2_cb(); }

  widget::cmd::String _center_w;
  widget::cmd::String _size_w;
  widget::cmd::Float _normalshift_w;

  // disabled copy constructor
  Controls( Controls const & );

  // disabled assignment operator
  Controls &operator=( Controls const & );

};

} // namespace cmd
} // namespace bubbletonlab

#endif // bubbletonlab_cmd_Controls_INCLUDED
