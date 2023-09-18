/* GANG Software
 * LAB/minlab/ui/Controls.H
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

#ifndef minlab_ui_Controls_INCLUDED
#define minlab_ui_Controls_INCLUDED

#include "parser/KeyParser.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Float.H"
#include "widget/ui/Choice.H"
#include "widget/ui/String.H"

namespace minlab {
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

protected:

  void set( parser::KeyParser const & );
  void get( parser::KeyParser & ) const;


  virtual void set_associate( double ) = 0;
  virtual void load_surface() = 0;


  static char const *label()
    { return "Compute"; }

  // callbacks
  virtual void parameter_reset_cb();
  virtual void associate_slider_cb();
  virtual void associate_button0_cb()
    { associate_slider_w()->set( 0.0f ); }
  virtual void associate_button1_cb()
    { associate_slider_w()->set( 0.25f ); }
  virtual void associate_button2_cb()
    { associate_slider_w()->set( 0.5f ); }
  virtual void associate_button3_cb()
    { associate_slider_w()->set( 0.75f ); }

private:

  // widgets
  virtual widget::ui::Choice *main_widget_w() = 0;
  virtual widget::ui::Choice const *main_widget_w() const = 0;
  virtual widget::ui::Choice *notebook_surf_data_w() = 0;
  virtual widget::ui::Choice const *notebook_surf_data_w() const = 0;
  virtual widget::ui::String *zstart_spinor_w() = 0;
  virtual widget::ui::String const *zstart_spinor_w() const = 0;
  virtual widget::ui::String *spinor1_w() = 0;
  virtual widget::ui::String const *spinor1_w() const = 0;
  virtual widget::ui::String *spinor2_w() = 0;
  virtual widget::ui::String const *spinor2_w() const = 0;
  virtual widget::ui::String *spinor0_init_w() = 0;
  virtual widget::ui::String const *spinor0_init_w() const = 0;
  virtual widget::ui::String *spinor1_init_w() = 0;
  virtual widget::ui::String const *spinor1_init_w() const = 0;
  virtual widget::ui::String *spinor2_init_w() = 0;
  virtual widget::ui::String const *spinor2_init_w() const = 0;
  virtual widget::ui::String *zstart_weierstrass_w() = 0;
  virtual widget::ui::String const *zstart_weierstrass_w() const = 0;
  virtual widget::ui::String *weierstrass1_w() = 0;
  virtual widget::ui::String const *weierstrass1_w() const = 0;
  virtual widget::ui::String *weierstrass2_w() = 0;
  virtual widget::ui::String const *weierstrass2_w() const = 0;
  virtual widget::ui::String *weierstrass0_init_w() = 0;
  virtual widget::ui::String const *weierstrass0_init_w() const = 0;
  virtual widget::ui::String *weierstrass1_init_w() = 0;
  virtual widget::ui::String const *weierstrass1_init_w() const = 0;
  virtual widget::ui::String *weierstrass2_init_w() = 0;
  virtual widget::ui::String const *weierstrass2_init_w() const = 0;
  virtual widget::ui::Float *associate_slider_w() = 0;
  virtual widget::ui::Float const *associate_slider_w() const = 0;
  virtual widget::ui::Float *integrator_count_w() = 0;
  virtual widget::ui::Float const *integrator_count_w() const = 0;
  virtual widget::ui::Float *initial_integrator_count_w() = 0;
  virtual widget::ui::Float const *initial_integrator_count_w() const = 0;

  Controls( Controls const & );
  Controls &operator=( Controls const & );

};

} // namespace ui
} // namespace minlab

#endif // minlab_ui_Controls_INCLUDED
