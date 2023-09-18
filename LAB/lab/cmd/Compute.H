/* GANG Software
 * LAB/lab/cmd/Compute.H
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

#ifndef lab_cmd_Compute_INCLUDED
#define lab_cmd_Compute_INCLUDED

#include "widget/cmd/Float.H"
#include "widget/cmd/String.H"
#include "lab/ui/Compute.H"

namespace lab {
namespace cmd {

class Compute
  :
    virtual public ui::Compute
{

public:
  // constructor
  Compute();

  // destructor
  virtual ~Compute();

protected:

private:

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

  virtual widget::ui::Float *progressbar_w()
    { return &_progressbar_w; }
  virtual widget::ui::Float const *progressbar_w() const
    { return &_progressbar_w; }
  virtual widget::ui::String *time0_w()
    { return &_time0_w; }
  virtual widget::ui::String const *time0_w() const
    { return &_time0_w; }
  virtual widget::ui::String *time1_w()
    { return &_time1_w; }
  virtual widget::ui::String const *time1_w() const
    { return &_time1_w; }
  virtual widget::ui::String *name_w()
    { return &_name_w; }
  virtual widget::ui::String const *name_w() const
    { return &_name_w; }

  // callbacks
  virtual void stop_cb()
    { ui::Compute::stop_cb(); }
  virtual void go_cb()
    { ui::Compute::go_cb(); }

  widget::cmd::Float _progressbar_w;
  widget::cmd::String _time0_w;
  widget::cmd::String _time1_w;
  widget::cmd::String _name_w;

  // disabled copy constructor
  Compute( Compute const & );

  // disabled assignment operator
  Compute &operator=( Compute const & );

};

} // namespace cmd
} // namespace lab

#endif // lab_cmd_Compute_INCLUDED
