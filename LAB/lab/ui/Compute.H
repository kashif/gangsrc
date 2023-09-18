/* GANG Software
 * LAB/lab/ui/Compute.H
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

#ifndef lab_ui_Compute_INCLUDED
#define lab_ui_Compute_INCLUDED

#include "base/String.H"
#include "parser/KeyParser.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Float.H"
#include "widget/ui/String.H"

namespace lab {
namespace ui {

class Compute
  :
    public widget::ui::Dialog
{

public:
  // constructor
  Compute();

  // destructor
  virtual ~Compute();

  void compute();
  void stop_computation();

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  virtual void set_status( uint count, uint total );
  virtual void set_status(
    base::String user_time,
    base::String system_time,
    base::String elapsed_time );
  virtual void clear_status();

  void reset();

#if 0
  void set_name( char const *text )
    { name_w()->set(text); }
#endif
  void set_time( char const *t0, char const *t1 );

protected:

  char const *label()
    { return "Compute"; }

  // callbacks
  virtual void go_cb()
    { compute(); }

  virtual void stop_cb()
    { stop_computation(); }

  void set( parser::KeyParser const & );
  void get( parser::KeyParser & ) const;

private:

  // pure virtuals
//  virtual base::String const &name() const = 0;
  virtual void _compute_and_export() = 0;
  virtual void _stop_computation() = 0;
  virtual void grab_focus() {}
  virtual void sync() {}

  // widgets
  virtual widget::ui::Float *progressbar_w() = 0;
  virtual widget::ui::Float const *progressbar_w() const = 0;
  virtual widget::ui::String *time0_w() = 0;
  virtual widget::ui::String const *time0_w() const = 0;
  virtual widget::ui::String *time1_w() = 0;
  virtual widget::ui::String const *time1_w() const = 0;
  virtual widget::ui::String *name_w() = 0;
  virtual widget::ui::String const *name_w() const = 0;

  Compute( Compute const & );
  Compute &operator=( Compute const & );
};

} // namespace ui
} // namespace lab

#endif // lab_ui_Compute_INCLUDED
