/* GANG Software
 * VIEWER/isightui/gtk/Geometry.H
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

#ifndef isightui_gtk_Geometry_INCLUDED
#define isightui_gtk_Geometry_INCLUDED

#include "app/app/Dialog.H"
#include "isightui/ui/Geometry.H"
#include "Geometry_.H"

namespace isightui {
namespace gtk {

class Geometry
  :
    virtual public ui::Geometry,
    protected gtk::Geometry_,
    public ::app::app::Dialog
{

public:
  // constructor
  Geometry(char const *title);

  // destructor
  virtual ~Geometry();

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
    { Geometry_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual widget::ui::Choice *geometry_mode_w()
    { return _geometry_mode_w; }
  virtual widget::ui::Choice const *geometry_mode_w() const
    { return _geometry_mode_w; }
  virtual widget::ui::Choice *geometry_group_w()
    { return _geometry_group_w; }
  virtual widget::ui::Choice const *geometry_group_w() const
    { return _geometry_group_w; }
  virtual widget::ui::Choice *geometry_dim_w()
    { return _geometry_dim_w; }
  virtual widget::ui::Choice const *geometry_dim_w() const
    { return _geometry_dim_w; }
  virtual widget::ui::Choice *mousemode_w()
    { return _mousemode_w; }
  virtual widget::ui::Choice const *mousemode_w() const
    { return _mousemode_w; }

  // callbacks
  virtual void reset_position_cb()
    { ui::Geometry::reset_position_cb(); }
  virtual void geometry_reset_cb()
    { ui::Geometry::geometry_reset_cb(); }
  virtual void geometry_mode_cb()
    { ui::Geometry::geometry_mode_cb(); }
  virtual void geometry_group_cb()
    { ui::Geometry::geometry_group_cb(); }
  virtual void geometry_dim_cb()
    { ui::Geometry::geometry_dim_cb(); }
  virtual void mousemode_cb()
    { ui::Geometry::mousemode_cb(); }

  // disabled copy constructor
  Geometry( Geometry const & );

  // disabled assignment operator
  Geometry &operator=( Geometry const & );

};

} // namespace gtk
} // namespace isightui

#endif // isightui_gtk_Geometry_INCLUDED
