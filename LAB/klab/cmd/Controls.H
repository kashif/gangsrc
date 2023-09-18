/* GANG Software
 * LAB/klab/cmd/Controls.H
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

#ifndef klab_cmd_Controls_INCLUDED
#define klab_cmd_Controls_INCLUDED

#include "widget/cmd/Choice.H"
#include "widget/cmd/Float.H"
#include "widget/cmd/String.H"
#include "klab/ui/Controls.H"

namespace klab {
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
  virtual widget::ui::Choice *main_book_w()
    { return &_main_book_w; }
  virtual widget::ui::String *potential_x_w()
    { return &_potential_x_w; }
  virtual widget::ui::String *potential_y_w()
    { return &_potential_y_w; }
  virtual widget::ui::String *zstart_w()
    { return &_zstart_w; }
  virtual widget::ui::String *initial_x_w()
    { return &_initial_x_w; }
  virtual widget::ui::String *initial_y_w()
    { return &_initial_y_w; }
  virtual widget::ui::Float *lambda_w()
    { return &_lambda_w; }
  virtual widget::ui::String *polynomial_length_w()
    { return &_polynomial_length_w; }
  virtual widget::ui::String *initial_integrator_count_w()
    { return &_initial_integrator_count_w; }
  virtual widget::ui::String *integrator_count_w()
    { return &_integrator_count_w; }

  virtual widget::ui::Choice const *main_book_w() const
    { return &_main_book_w; }
  virtual widget::ui::String const *potential_x_w() const
    { return &_potential_x_w; }
  virtual widget::ui::String const *potential_y_w() const
    { return &_potential_y_w; }
  virtual widget::ui::String const *zstart_w() const
    { return &_zstart_w; }
  virtual widget::ui::String const *initial_x_w() const
    { return &_initial_x_w; }
  virtual widget::ui::String const *initial_y_w() const
    { return &_initial_y_w; }
  virtual widget::ui::Float const *lambda_w() const
    { return &_lambda_w; }
  virtual widget::ui::String const *polynomial_length_w() const
    { return &_polynomial_length_w; }
  virtual widget::ui::String const *initial_integrator_count_w() const
    { return &_initial_integrator_count_w; }
  virtual widget::ui::String const *integrator_count_w() const
    { return &_integrator_count_w; }

  // callbacks
  virtual void reset_lambda_cb()
    { ui::Controls::reset_lambda_cb(); }
  virtual void lambda_cb()
    { ui::Controls::lambda_cb(); }

  widget::cmd::Choice _main_book_w;
  widget::cmd::String _potential_x_w;
  widget::cmd::String _potential_y_w;
  widget::cmd::String _zstart_w;
  widget::cmd::String _initial_x_w;
  widget::cmd::String _initial_y_w;
  widget::cmd::Float _lambda_w;
  widget::cmd::String _polynomial_length_w;
  widget::cmd::String _initial_integrator_count_w;
  widget::cmd::String _integrator_count_w;

  // disabled copy constructor
  Controls( Controls const & );

  // disabled assignment operator
  Controls &operator=( Controls const & );

};

} // namespace cmd
} // namespace klab

#endif // klab_cmd_Controls_INCLUDED
