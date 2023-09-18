/* GANG Software
 * LAB/minlab/ui/Ui.H
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

#ifndef minlab_ui_Ui_INCLUDED
#define minlab_ui_Ui_INCLUDED

#include "base/vector.H"
#include "base/String.H"
#include "base/Exception.H"
#include "lab/ui/Ui.H"
#include "Controls.H"

namespace minlab {
namespace ui {

class Ui
  :
    virtual public ::lab::ui::Ui,
    virtual public Controls
{
public:

  // constructor
  Ui();

  // destructor
  virtual ~Ui();

  void toggle_raise_show_controls()
    { static_cast< ::minlab::ui::Controls *>(this)->toggle_raise_show_d(); }

protected:

  void show_all(bool state);
  void enable_tooltips(bool state);

#if 0
  // Controls virtuals
  virtual void set_associate_v( float x )
    { set_associate( double(x) ); }
  virtual void load_surface_v()
    { export_(); }
#endif

#if 0
  virtual void set_ui_from_data()
    { Controls::set(data()); }
  virtual void set_data_from_ui()
    { Controls::get(data()); }
#endif

private:

  Controls *controls_p() { return this; }

  // disabled copy constructor
  Ui( Ui const & );
  // disabled assignment operator
  Ui &operator=( Ui const & );
};

} // namespace ui
} // namespace minlab

#endif // minlab_ui_Ui_INCLUDED
