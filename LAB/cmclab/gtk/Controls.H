/* GANG Software
 * LAB/cmclab/gtk/Controls.H
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

#ifndef cmclab_gtk_Controls_INCLUDED
#define cmclab_gtk_Controls_INCLUDED

#include "app/app/Dialog.H"
#include "cmclab/ui/Controls.H"
#include "Controls_.H"

namespace cmclab {
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
  virtual widget::ui::Choice *main_book_w()
    { return _main_book_w; }
  virtual widget::ui::String *potential_variable_w()
    { return _potential_variable_w; }
  virtual widget::ui::String *potential_w()
    { return _potential_w; }
  virtual widget::ui::String *zstart_w()
    { return _zstart_w; }
  virtual widget::ui::String *xstart_w()
    { return _xstart_w; }
  virtual widget::ui::Choice *parameter_notebook_w()
    { return _parameter_notebook_w; }
  virtual widget::ui::Widget *reset_S3_w()
    { return _reset_S3_w; }
  virtual widget::ui::Float *lambda0_S3_w()
    { return _lambda0_S3_w; }
  virtual widget::ui::Widget *lambda_button00_w()
    { return _lambda_button00_w; }
  virtual widget::ui::Widget *lambda_button01_w()
    { return _lambda_button01_w; }
  virtual widget::ui::Widget *lambda_button02_w()
    { return _lambda_button02_w; }
  virtual widget::ui::Widget *lambda_button03_w()
    { return _lambda_button03_w; }
  virtual widget::ui::Float *lambda1_S3_w()
    { return _lambda1_S3_w; }
  virtual widget::ui::Widget *lambda_button10_w()
    { return _lambda_button10_w; }
  virtual widget::ui::Widget *lambda_button11_w()
    { return _lambda_button11_w; }
  virtual widget::ui::Widget *lambda_button12_w()
    { return _lambda_button12_w; }
  virtual widget::ui::Widget *lambda_button13_w()
    { return _lambda_button13_w; }
  virtual widget::ui::Widget *reset_R3_w()
    { return _reset_R3_w; }
  virtual widget::ui::Float *lambda_R3_w()
    { return _lambda_R3_w; }
  virtual widget::ui::Widget *lambda_button0_w()
    { return _lambda_button0_w; }
  virtual widget::ui::Widget *lambda_button1_w()
    { return _lambda_button1_w; }
  virtual widget::ui::Widget *lambda_button2_w()
    { return _lambda_button2_w; }
  virtual widget::ui::Widget *lambda_button3_w()
    { return _lambda_button3_w; }
  virtual widget::ui::Float *normalshift_w()
    { return _normalshift_w; }
  virtual widget::ui::Widget *normalshift_button0_w()
    { return _normalshift_button0_w; }
  virtual widget::ui::Widget *normalshift_button1_w()
    { return _normalshift_button1_w; }
  virtual widget::ui::Widget *normalshift_button2_w()
    { return _normalshift_button2_w; }
  virtual widget::ui::Float *mean_curvature_w()
    { return _mean_curvature_w; }
  virtual widget::ui::Widget *reset_H3_w()
    { return _reset_H3_w; }
  virtual widget::ui::Float *lambda0_H3_w()
    { return _lambda0_H3_w; }
  virtual widget::ui::Float *lambda1_H3_w()
    { return _lambda1_S3_w; }
  virtual widget::ui::String *polynomial_length_w()
    { return _polynomial_length_w; }
  virtual widget::ui::String *initial_integrator_count_w()
    { return _initial_integrator_count_w; }
  virtual widget::ui::String *integrator_count_w()
    { return _integrator_count_w; }
  virtual widget::ui::Choice *iwasawa_method_w()
    { return _iwasawa_method_w; }
  virtual widget::ui::String *basis_length_w()
    { return _basis_length_w; }
  virtual widget::ui::Boolean *birkhoff_w()
    { return _birkhoff_w; }
  virtual widget::ui::Boolean *one_column_w()
    { return _one_column_w; }

  virtual widget::ui::Choice const *main_book_w() const
    { return _main_book_w; }
  virtual widget::ui::String const *potential_variable_w() const
    { return _potential_variable_w; }
  virtual widget::ui::String const *potential_w() const
    { return _potential_w; }
  virtual widget::ui::String const *zstart_w() const
    { return _zstart_w; }
  virtual widget::ui::String const *xstart_w() const
    { return _xstart_w; }
  virtual widget::ui::Choice const *parameter_notebook_w() const
    { return _parameter_notebook_w; }
  virtual widget::ui::Widget const *reset_S3_w() const
    { return _reset_S3_w; }
  virtual widget::ui::Float const *lambda0_S3_w() const
    { return _lambda0_S3_w; }
  virtual widget::ui::Widget const *lambda_button00_w() const
    { return _lambda_button00_w; }
  virtual widget::ui::Widget const *lambda_button01_w() const
    { return _lambda_button01_w; }
  virtual widget::ui::Widget const *lambda_button02_w() const
    { return _lambda_button02_w; }
  virtual widget::ui::Widget const *lambda_button03_w() const
    { return _lambda_button03_w; }
  virtual widget::ui::Float const *lambda1_S3_w() const
    { return _lambda1_S3_w; }
  virtual widget::ui::Widget const *lambda_button10_w() const
    { return _lambda_button10_w; }
  virtual widget::ui::Widget const *lambda_button11_w() const
    { return _lambda_button11_w; }
  virtual widget::ui::Widget const *lambda_button12_w() const
    { return _lambda_button12_w; }
  virtual widget::ui::Widget const *lambda_button13_w() const
    { return _lambda_button13_w; }
  virtual widget::ui::Widget const *reset_R3_w() const
    { return _reset_R3_w; }
  virtual widget::ui::Float const *lambda_R3_w() const
    { return _lambda_R3_w; }
  virtual widget::ui::Widget const *lambda_button0_w() const
    { return _lambda_button0_w; }
  virtual widget::ui::Widget const *lambda_button1_w() const
    { return _lambda_button1_w; }
  virtual widget::ui::Widget const *lambda_button2_w() const
    { return _lambda_button2_w; }
  virtual widget::ui::Widget const *lambda_button3_w() const
    { return _lambda_button3_w; }
  virtual widget::ui::Float const *normalshift_w() const
    { return _normalshift_w; }
  virtual widget::ui::Widget const *normalshift_button0_w() const
    { return _normalshift_button0_w; }
  virtual widget::ui::Widget const *normalshift_button1_w() const
    { return _normalshift_button1_w; }
  virtual widget::ui::Widget const *normalshift_button2_w() const
    { return _normalshift_button2_w; }
  virtual widget::ui::Float const *mean_curvature_w() const
    { return _mean_curvature_w; }
  virtual widget::ui::Widget const *reset_H3_w() const
    { return _reset_H3_w; }
  virtual widget::ui::Float const *lambda0_H3_w() const
    { return _lambda0_H3_w; }
  virtual widget::ui::Float const *lambda1_H3_w() const
    { return _lambda1_H3_w; }
  virtual widget::ui::String const *polynomial_length_w() const
    { return _polynomial_length_w; }
  virtual widget::ui::String const *initial_integrator_count_w() const
    { return _initial_integrator_count_w; }
  virtual widget::ui::String const *integrator_count_w() const
    { return _integrator_count_w; }
  virtual widget::ui::Choice const *iwasawa_method_w() const
    { return _iwasawa_method_w; }
  virtual widget::ui::String const *basis_length_w() const
    { return _basis_length_w; }
  virtual widget::ui::Boolean const *birkhoff_w() const
    { return _birkhoff_w; }
  virtual widget::ui::Boolean const *one_column_w() const
    { return _one_column_w; }

  // callbacks
  virtual void parameter_notebook_cb()
    { ui::Controls::parameter_notebook_cb(); }
  virtual void reset_S3_cb()
    { ui::Controls::reset_S3_cb(); }
  virtual void lambda0_S3_cb()
    { ui::Controls::lambda0_S3_cb(); }
  virtual void lambda_button00_cb()
    { ui::Controls::lambda_button00_cb(); }
  virtual void lambda_button01_cb()
    { ui::Controls::lambda_button01_cb(); }
  virtual void lambda_button02_cb()
    { ui::Controls::lambda_button02_cb(); }
  virtual void lambda_button03_cb()
    { ui::Controls::lambda_button03_cb(); }
  virtual void lambda1_S3_cb()
    { ui::Controls::lambda1_S3_cb(); }
  virtual void lambda_button10_cb()
    { ui::Controls::lambda_button10_cb(); }
  virtual void lambda_button11_cb()
    { ui::Controls::lambda_button11_cb(); }
  virtual void lambda_button12_cb()
    { ui::Controls::lambda_button12_cb(); }
  virtual void lambda_button13_cb()
    { ui::Controls::lambda_button13_cb(); }
  virtual void reset_R3_cb()
    { ui::Controls::reset_R3_cb(); }
  virtual void lambda_R3_cb()
    { ui::Controls::lambda_R3_cb(); }
  virtual void lambda_button0_cb()
    { ui::Controls::lambda_button0_cb(); }
  virtual void lambda_button1_cb()
    { ui::Controls::lambda_button1_cb(); }
  virtual void lambda_button2_cb()
    { ui::Controls::lambda_button2_cb(); }
  virtual void lambda_button3_cb()
    { ui::Controls::lambda_button3_cb(); }
  virtual void normalshift_cb()
    { ui::Controls::normalshift_cb(); }
  virtual void normalshift_button0_cb()
    { ui::Controls::normalshift_button0_cb(); }
  virtual void normalshift_button1_cb()
    { ui::Controls::normalshift_button1_cb(); }
  virtual void normalshift_button2_cb()
    { ui::Controls::normalshift_button2_cb(); }
  virtual void mean_curvature_cb()
    { ui::Controls::mean_curvature_cb(); }
  virtual void reset_H3_cb()
    { ui::Controls::reset_H3_cb(); }
  virtual void lambda0_H3_cb()
    { ui::Controls::lambda0_H3_cb(); }
  virtual void lambda1_H3_cb()
    { ui::Controls::lambda1_H3_cb(); }

  // disabled copy constructor
  Controls( Controls const & );

  // disabled assignment operator
  Controls &operator=( Controls const & );

};

} // namespace gtk
} // namespace cmclab

#endif // cmclab_gtk_Controls_INCLUDED
