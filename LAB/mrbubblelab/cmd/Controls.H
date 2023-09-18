/* GANG Software
 * LAB/mrbubblelab/cmd/Controls.H
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

#ifndef mrbubblelab_cmd_Controls_INCLUDED
#define mrbubblelab_cmd_Controls_INCLUDED

#include "widget/cmd/String.H"
#include "widget/cmd/Float.H"
#include "mrbubblelab/ui/Controls.H"

namespace mrbubblelab {
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
  virtual widget::ui::String *coefficient_w()
    { return &_coefficient_w; }
  virtual widget::ui::String *exponent_w()
    { return &_exponent_w; }
  virtual widget::ui::String *u0_w()
    { return &_u0_w; }
  virtual widget::ui::String *uprime0_w()
    { return &_uprime0_w; }
  virtual widget::ui::Float *normalshift_w()
    { return &_normalshift_w; }
  virtual widget::ui::String *initial_integrator_count_w()
    { return &_initial_integrator_count_w; }
  virtual widget::ui::String *integrator_count_w()
    { return &_integrator_count_w; }

  virtual widget::ui::String const *coefficient_w() const
    { return &_coefficient_w; }
  virtual widget::ui::String const *exponent_w() const
    { return &_exponent_w; }
  virtual widget::ui::String const *u0_w() const
    { return &_u0_w; }
  virtual widget::ui::String const *uprime0_w() const
    { return &_uprime0_w; }
  virtual widget::ui::Float const *normalshift_w() const
    { return &_normalshift_w; }
  virtual widget::ui::String const *initial_integrator_count_w() const
    { return &_initial_integrator_count_w; }
  virtual widget::ui::String const *integrator_count_w() const
    { return &_integrator_count_w; }

  // callbacks
  virtual void normalshift_cb()
    { ui::Controls::normalshift_cb(); }
  virtual void normalshift_button0_cb()
    { ui::Controls::normalshift_button0_cb(); }
  virtual void normalshift_button1_cb()
    { ui::Controls::normalshift_button1_cb(); }
  virtual void normalshift_button2_cb()
    { ui::Controls::normalshift_button2_cb(); }

  widget::cmd::String _coefficient_w;
  widget::cmd::String _exponent_w;
  widget::cmd::String _u0_w;
  widget::cmd::String _uprime0_w;
  widget::cmd::Float _normalshift_w;
  widget::cmd::String _initial_integrator_count_w;
  widget::cmd::String _integrator_count_w;

  // disabled copy constructor
  Controls( Controls const & );

  // disabled assignment operator
  Controls &operator=( Controls const & );

};

} // namespace cmd
} // namespace mrbubblelab

#endif // mrbubblelab_cmd_Controls_INCLUDED
