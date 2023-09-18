/* GANG Software
 * LAB/bubbletonlab/ui/Controls.H
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

#ifndef bubbletonlab_ui_Controls_INCLUDED
#define bubbletonlab_ui_Controls_INCLUDED

#include "parser/KeyParser.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/String.H"
#include "widget/ui/Float.H"

namespace bubbletonlab {
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

  virtual void normalshift( double ) = 0;
  virtual void load_surface() = 0;

  // callbacks
  virtual void normalshift_cb();
  virtual void normalshift_button0_cb()
    { normalshift_w()->set( 1.0f ); }
  virtual void normalshift_button1_cb()
    { normalshift_w()->set( 0.0f ); }
  virtual void normalshift_button2_cb()
    { normalshift_w()->set( -1.0f ); }

  static char const *label()
    { return "Compute"; }

private:

  // widgets
  virtual widget::ui::String *center_w() = 0;
  virtual widget::ui::String *size_w() = 0;
  virtual widget::ui::Float *normalshift_w() = 0;

  virtual widget::ui::String const *center_w() const = 0;
  virtual widget::ui::String const *size_w() const = 0;
  virtual widget::ui::Float const *normalshift_w() const = 0;

  Controls( Controls const & );
  Controls &operator=( Controls const & );

};

} // namespace ui
} // namespace bubbletonlab

#endif // bubbletonlab_ui_Controls_INCLUDED
