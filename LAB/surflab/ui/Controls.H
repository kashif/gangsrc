/* GANG Software
 * LAB/surflab/ui/Controls.H
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

#ifndef surflab_ui_Controls_INCLUDED
#define surflab_ui_Controls_INCLUDED

#include "base/ReadUtil.H"
#include "parser/KeyParser.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/String.H"
#include "widget/ui/Choice.H"

namespace surflab {
namespace ui {

class Lab;

class Controls
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  Controls();

  // destructor
  virtual ~Controls();

  void geometry(uint x)
    { geometry_w()->set(x); }
  void dimension(uint x)
    { dimension_w()->set(x); }
  void variable( base::String const &x, base::String const &y )
    { var1_w()->set(x.c_str()); var2_w()->set(y.c_str()); }
  void function( uint id, base::String const &f )
    { function_w(id)->set(f.c_str()); }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  void set( parser::KeyParser const & );
  void get( parser::KeyParser & ) const;

  // virtual callbacks
  virtual void geometry_cb();
  virtual void dimension_cb();

  static char const *label()
    { return "Compute"; }

private:

  // widgets
  virtual widget::ui::Choice *geometry_w() = 0;
  virtual widget::ui::Choice const *geometry_w() const = 0;
  virtual widget::ui::Choice *dimension_w() = 0;
  virtual widget::ui::Choice const *dimension_w() const= 0;
  virtual widget::ui::String *var1_w() = 0;
  virtual widget::ui::String const *var1_w() const = 0;
  virtual widget::ui::String *var2_w() = 0;
  virtual widget::ui::String const *var2_w() const = 0;
  virtual widget::ui::String *function_w(uint n) = 0;
  virtual widget::ui::String const *function_w(uint n) const = 0;
  virtual widget::ui::Widget *function_box_w(uint n) = 0;
  virtual widget::ui::Widget const *function_box_w(uint n) const = 0;

  void _show();

  static uint const COUNT = 5;

  Controls( Controls const & );
  Controls &operator=( Controls const & );

};

} // namespace ui
} // namespace surflab

#endif // surflab_ui_Controls_INCLUDED
