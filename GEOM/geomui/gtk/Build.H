/* GANG Software
 * GEOM/geomui/gtk/Build.H
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

#ifndef geomui_gtk_Build_INCLUDED
#define geomui_gtk_Build_INCLUDED

#include "app/app/Dialog.H"
#include "geomui/ui/Build.H"
#include "Build_.H"

namespace geomui {
namespace gtk {

class Build
  :
    virtual public ui::Build,
    protected gtk::Build_,
    public ::app::app::Dialog
{

public:
  // constructor
  Build(char const *title);

  // destructor
  virtual ~Build();

protected:

private:

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { Build_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual widget::ui::FloatSet *reflect_plane_position_w()
    { return _reflect_plane_position_w; }

  // callbacks
  virtual void build_reset_cb()
    { ui::Build::build_reset_cb(); }
  virtual void reflect_plane_reset_cb()
    { ui::Build::reflect_plane_reset_cb(); }
  virtual void reflect_plane_apply_cb()
    { ui::Build::reflect_plane_apply_cb(); }
  virtual void reflect_coord_plane0_cb()
    { ui::Build::reflect_coord_plane0_cb(); }
  virtual void reflect_coord_plane1_cb()
    { ui::Build::reflect_coord_plane1_cb(); }
  virtual void reflect_coord_plane2_cb()
    { ui::Build::reflect_coord_plane2_cb(); }

  // disabled copy constructor
  Build( Build const & );

  // disabled assignment operator
  Build &operator=( Build const & );

};

} // namespace gtk
} // namespace geomui

#endif // geomui_gtk_Build_INCLUDED
