/* GANG Software
 * GEOM/geomui/cmd/Build.H
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

#ifndef geomui_cmd_Build_INCLUDED
#define geomui_cmd_Build_INCLUDED

#include "widget/cmd/FloatSet.H"
#include "geomui/ui/Build.H"

namespace geomui {
namespace cmd {

class Build
  :
    virtual public geomui::ui::Build
{

public:
  // constructor
  Build();

  // destructor
  virtual ~Build();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::FloatSet *reflect_plane_position_w()
    { return &_reflect_plane_position_w; }

  // widgets
  widget::cmd::FloatSet _reflect_plane_position_w;

  // disabled copy constructor
  Build( Build const & );
  // disabled assignment operator
  Build &operator=( Build const & );

};

} // namespace cmd
} // namespace geomui

#endif // geomui_cmd_Build_INCLUDED
