/* GANG Software
 * LAB/surflab/cmd/Controls.H
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

#ifndef surflab_cmd_Controls_INCLUDED
#define surflab_cmd_Controls_INCLUDED

#include "widget/cmd/String.H"
#include "widget/cmd/Choice.H"
#include "surflab/ui/Controls.H"

namespace surflab {
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
  virtual widget::ui::Choice *geometry_w()
    { return &_geometry_w; }
  virtual widget::ui::Choice const *geometry_w() const
    { return &_geometry_w; }
  virtual widget::ui::Choice *dimension_w()
    { return &_dimension_w; }
  virtual widget::ui::Choice const *dimension_w() const
    { return &_dimension_w; }
  virtual widget::ui::String *var1_w()
    { return &_var1_w; }
  virtual widget::ui::String const *var1_w() const
    { return &_var1_w; }
  virtual widget::ui::String *var2_w()
    { return &_var2_w; }
  virtual widget::ui::String const *var2_w() const
    { return &_var2_w; }
  virtual widget::ui::String *function_w(uint n)
    { return &_function_w[n]; }
  virtual widget::ui::String const *function_w(uint n) const
    { return &_function_w[n]; }
  virtual widget::ui::Widget *function_box_w(uint n)
    { return &_function_box_w[n]; }
  virtual widget::ui::Widget const *function_box_w(uint n) const
    { return &_function_box_w[n]; }

  // callbacks
  virtual void geometry_cb()
    { ui::Controls::geometry_cb(); }
  virtual void dimension_cb()
    { ui::Controls::dimension_cb(); }


  widget::cmd::Choice _geometry_w;
  widget::cmd::Choice _dimension_w;
  widget::cmd::String _var1_w;
  widget::cmd::String _var2_w;

  static uint const COUNT = 5;
  mutable widget::cmd::String _function_w[COUNT];
  widget::cmd::Widget _function_box_w[COUNT];

  // disabled copy constructor
  Controls( Controls const & );
  // disabled assignment operator
  Controls &operator=( Controls const & );

};

} // namespace cmd
} // namespace surflab

#endif // surflab_cmd_Controls_INCLUDED
