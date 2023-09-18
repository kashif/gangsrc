/* GANG Software
 * LAB/lab/ui/Sequence.H
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

#ifndef lab_ui_Sequence_INCLUDED
#define lab_ui_Sequence_INCLUDED

#include "base/String.H"
#include "parser/KeyParser.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/String.H"
#include "widget/ui/IntSet.H"

namespace lab {
namespace ui {

class Lab;

class Sequence
  :
    public widget::ui::Dialog
{

public:
  // constructor
  Sequence();

  // destructor
  virtual ~Sequence();

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  virtual void update_sequencer( uint );

  void update() {}
  void reset() { reset_cb(); }

protected:

  char const *label()
    { return "Sequence"; }

  // compute a sequence of surfaces without writing image files
  virtual void go_cb();

  // compute a sequence of surfaces and write image files
  virtual void go_write_cb();

  // reset sequencer
  virtual void reset_cb();

  // stop a sequence computation
  virtual void stop_cb()
    { _stop_computation(); }

  void set( parser::KeyParser const & ) {}
  void get( parser::KeyParser & ) const {}

private:

  // pure virtuals
  virtual void compute_sequence(
    base::String const &filename,
    base::String const &counter_var,
    base::String const &time_varname,
    base::String const &function,
    uint start,
    uint count ) = 0;

  virtual void _stop_computation() = 0;


  // widgets
#if 0
  virtual widget::ui::Widget *go_w() = 0;
  virtual widget::ui::Widget *go_write_w() = 0;
  virtual widget::ui::Widget *stop_w() = 0;
  virtual widget::ui::Widget *reset_w() = 0;
#endif
  virtual widget::ui::String *now_w() = 0;
  virtual widget::ui::IntSet *counter_w() = 0;
  virtual widget::ui::String *counter_varname_w() = 0;
  virtual widget::ui::String *time_varname_w() = 0;
  virtual widget::ui::String *function_w() = 0;
  virtual widget::ui::String *filename_w() = 0;

  Sequence( Sequence const & );
  Sequence &operator=( Sequence const & );

};

} // namespace ui
} // namespace lab

#endif // lab_ui_Sequence_INCLUDED
