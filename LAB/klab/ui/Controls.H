/* GANG Software
 * LAB/klab/ui/Controls.H
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

#ifndef klab_ui_Controls_INCLUDED
#define klab_ui_Controls_INCLUDED

#include "parser/KeyParser.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/String.H"
#include "widget/ui/Float.H"
#include "widget/ui/Choice.H"


namespace klab {
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

protected:

  void set( parser::KeyParser const & );
  void get( parser::KeyParser & ) const;

  // callbacks
  virtual void reset_lambda_cb();
  virtual void lambda_cb();

  static char const *label()
    { return "Compute"; }

private:

  // pure virtuals
  virtual void lambda( double ) = 0;
  virtual void load_surface() = 0;

  // widgets
  virtual widget::ui::Choice *main_book_w() = 0;
  virtual widget::ui::String *potential_x_w() = 0;
  virtual widget::ui::String *potential_y_w() = 0;
  virtual widget::ui::String *zstart_w() = 0;
  virtual widget::ui::String *initial_x_w() = 0;
  virtual widget::ui::String *initial_y_w() = 0;
  virtual widget::ui::Float *lambda_w() = 0;
  virtual widget::ui::String *polynomial_length_w() = 0;
  virtual widget::ui::String *initial_integrator_count_w() = 0;
  virtual widget::ui::String *integrator_count_w() = 0;

  virtual widget::ui::Choice const *main_book_w() const = 0;
  virtual widget::ui::String const *potential_x_w() const = 0;
  virtual widget::ui::String const *potential_y_w() const = 0;
  virtual widget::ui::String const *zstart_w() const = 0;
  virtual widget::ui::String const *initial_x_w() const = 0;
  virtual widget::ui::String const *initial_y_w() const = 0;
  virtual widget::ui::Float const *lambda_w() const = 0;
  virtual widget::ui::String const *polynomial_length_w() const = 0;
  virtual widget::ui::String const *initial_integrator_count_w() const = 0;
  virtual widget::ui::String const *integrator_count_w() const = 0;

  Controls( Controls const & );
  Controls &operator=( Controls const & );

};

} // namespace ui
} // namespace klab

#endif // klab_ui_Controls_INCLUDED
