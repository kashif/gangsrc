/* GANG Software
 * LAB/cmclab/ui/Controls.H
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

#ifndef cmclab_ui_Controls_INCLUDED
#define cmclab_ui_Controls_INCLUDED

#include <complex>
#include "parser/KeyParser.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Float.H"
#include "widget/ui/String.H"
#include "widget/ui/Boolean.H"
#include "widget/ui/Choice.H"

namespace cmclab {
namespace ui {

class Controls
  :
    public widget::ui::Dialog
{

public:

  // constructor
  Controls();

  // destructor
  virtual ~Controls();

  typedef double Real;
  typedef std::complex<Real> Complex;

  void set_lambda_S3();
  void set_lambda_R3();
  void set_lambda_H3();
  void inc_lambda_R3(float dx);
  void inc_lambda_R3_slow()
    { inc_lambda_R3(0.005f); }
  void inc_lambda_R3_med()
    { inc_lambda_R3(0.02f); }
  void inc_lambda_R3_fast()
    { inc_lambda_R3(0.08f); }
  void dec_lambda_R3_slow()
    { inc_lambda_R3(-0.005f); }
  void dec_lambda_R3_med()
    { inc_lambda_R3(-0.02f); }
  void dec_lambda_R3_fast()
    { inc_lambda_R3(-0.08f); }

  void toggle_normalshift();

protected:

  void set( parser::KeyParser const & );
  void get( parser::KeyParser & ) const;


  virtual void set_lambda_S3( double, double ) = 0;
  virtual void set_lambda_R3( double ) = 0;
  virtual void set_lambda_H3( std::complex<double> const & ) = 0;
  virtual void set_normalshift( double ) = 0;
  virtual void set_mean_curvature( double ) = 0;
  virtual void load_surface() = 0;
//  virtual void stop_motion() = 0;

  // callbacks
  virtual void parameter_notebook_cb();
  virtual void reset_S3_cb();
  virtual void lambda0_S3_cb();
  virtual void lambda_button00_cb();
  virtual void lambda_button01_cb();
  virtual void lambda_button02_cb();
  virtual void lambda_button03_cb();
  virtual void lambda1_S3_cb();
  virtual void lambda_button10_cb();
  virtual void lambda_button11_cb();
  virtual void lambda_button12_cb();
  virtual void lambda_button13_cb();
  virtual void reset_R3_cb();
  virtual void lambda_R3_cb();
  virtual void lambda_button0_cb();
  virtual void lambda_button1_cb();
  virtual void lambda_button2_cb();
  virtual void lambda_button3_cb();
  virtual void normalshift_cb();
  virtual void normalshift_button0_cb();
  virtual void normalshift_button1_cb();
  virtual void normalshift_button2_cb();
  virtual void mean_curvature_cb();
  virtual void reset_H3_cb();
  virtual void lambda0_H3_cb();
  virtual void lambda1_H3_cb();

  static char const *label()
    { return "Compute"; }

private:

  // widgets
  virtual widget::ui::Choice *main_book_w() = 0;
  virtual widget::ui::String *potential_variable_w() = 0;
  virtual widget::ui::String *potential_w() = 0;
  virtual widget::ui::String *zstart_w() = 0;
  virtual widget::ui::String *xstart_w() = 0;
  virtual widget::ui::Choice *parameter_notebook_w() = 0;
  virtual widget::ui::Float *lambda0_S3_w() = 0;
  virtual widget::ui::Float *lambda1_S3_w() = 0;
  virtual widget::ui::Float *lambda_R3_w() = 0;
  virtual widget::ui::Float *normalshift_w() = 0;
  virtual widget::ui::Float *mean_curvature_w() = 0;
  virtual widget::ui::Float *lambda0_H3_w() = 0;
  virtual widget::ui::Float *lambda1_H3_w() = 0;
  virtual widget::ui::String *polynomial_length_w() = 0;
  virtual widget::ui::String *initial_integrator_count_w() = 0;
  virtual widget::ui::String *integrator_count_w() = 0;
  virtual widget::ui::Choice *iwasawa_method_w() = 0;
  virtual widget::ui::String *basis_length_w() = 0;
  virtual widget::ui::Boolean *birkhoff_w() = 0;
  virtual widget::ui::Boolean *one_column_w() = 0;

  virtual widget::ui::Choice const *main_book_w() const = 0;
  virtual widget::ui::String const *potential_variable_w() const = 0;
  virtual widget::ui::String const *potential_w() const = 0;
  virtual widget::ui::String const *zstart_w() const = 0;
  virtual widget::ui::String const *xstart_w() const = 0;
  virtual widget::ui::Choice const *parameter_notebook_w() const = 0;
  virtual widget::ui::Float const *lambda0_S3_w() const = 0;
  virtual widget::ui::Float const *lambda1_S3_w() const = 0;
  virtual widget::ui::Float const *lambda_R3_w() const = 0;
  virtual widget::ui::Float const *normalshift_w() const = 0;
  virtual widget::ui::Float const *mean_curvature_w() const = 0;
  virtual widget::ui::Float const *lambda0_H3_w() const = 0;
  virtual widget::ui::Float const *lambda1_H3_w() const = 0;
  virtual widget::ui::String const *polynomial_length_w() const = 0;
  virtual widget::ui::String const *initial_integrator_count_w() const = 0;
  virtual widget::ui::String const *integrator_count_w() const = 0;
  virtual widget::ui::Choice const *iwasawa_method_w() const = 0;
  virtual widget::ui::String const *basis_length_w() const = 0;
  virtual widget::ui::Boolean const *birkhoff_w() const = 0;
  virtual widget::ui::Boolean const *one_column_w() const = 0;

  Controls( Controls const & );
  Controls &operator=( Controls const & );

};

} // namespace ui
} // namespace cmclab

#endif // cmclab_ui_Controls_INCLUDED
