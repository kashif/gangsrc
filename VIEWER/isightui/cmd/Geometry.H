/* GANG Software
 * VIEWER/isightui/cmd/Geometry.H
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

#ifndef isightui_cmd_Geometry_INCLUDED
#define isightui_cmd_Geometry_INCLUDED

#include "widget/cmd/Choice.H"
#include "isightui/ui/Geometry.H"

namespace isightui {
namespace cmd {

class Geometry
  :
    virtual public isightui::ui::Geometry
{

public:
  // constructor
  Geometry();

  // destructor
  virtual ~Geometry();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::Choice *geometry_mode_w()
    { return &_geometry_mode_w; }
  virtual widget::ui::Choice const *geometry_mode_w() const
    { return &_geometry_mode_w; }
  virtual widget::ui::Choice *geometry_group_w()
    { return &_geometry_group_w; }
  virtual widget::ui::Choice const *geometry_group_w() const
    { return &_geometry_group_w; }
  virtual widget::ui::Choice *geometry_dim_w()
    { return &_geometry_dim_w; }
  virtual widget::ui::Choice const *geometry_dim_w() const
    { return &_geometry_dim_w; }
  virtual widget::ui::Choice *mousemode_w()
    { return &_mousemode_w; }
  virtual widget::ui::Choice const *mousemode_w() const
    { return &_mousemode_w; }

  // widgets
  widget::cmd::Choice _geometry_mode_w;
  widget::cmd::Choice _geometry_group_w;
  widget::cmd::Choice _geometry_dim_w;
  widget::cmd::Choice _mousemode_w;

  // disabled copy constructor
  Geometry( Geometry const & );
  // disabled assignment operator
  Geometry &operator=( Geometry const & );

};

} // namespace cmd
} // namespace isightui

#endif // isightui_cmd_Geometry_INCLUDED
