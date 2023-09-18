/* GANG Software
 * VIEWER/isightui/ui/Geometry.C
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

#include "isight/kernel/ViewerBase.H"
#include "Geometry.H"

namespace isightui {
namespace ui {

Geometry::
Geometry()
    :
    widget::ui::Dialog()
{
#if FIX
  mousemode_w()->set_sensitive(0, true);
  mousemode_w()->set_sensitive(1, false);
  mousemode_w()->set_sensitive(2, false);
  mousemode_w()->set_sensitive(3, false);
  mousemode_w()->set_sensitive(4, false);
#endif
}

Geometry::
~Geometry()
{
}

void
Geometry::
synchronize()
{
  geometry_mode_w()->set_blocked(
    viewer()->context()->geometry_mode() );
  geometry_group_w()->set_blocked(
    viewer()->context()->geometry_group() );
  geometry_dim_w()->set_blocked(
    viewer()->context()->geometry_dim() - DIM_OFFSET );
  mousemode_w()->set_blocked(
    viewer()->context()->mouse_mode() );
}

void
Geometry::
get_geometry(
  motion::GeometryMode &mode,
  motion::GeometryGroup &group,
  uint &dim ) const
{
  mode = (motion::GeometryMode)geometry_mode_w()->get();
  group = (motion::GeometryGroup)geometry_group_w()->get();
  dim = DIM_OFFSET + geometry_dim_w()->get();
}

void
Geometry::
set_geometry(
  motion::GeometryMode mode,
  motion::GeometryGroup group,
  uint dim )
{
  // do nothing if already in this mode
  if (
    (motion::GeometryMode)geometry_mode_w()->get() == mode &&
    (motion::GeometryGroup)geometry_group_w()->get() == group &&
    geometry_dim_w()->get() + DIM_OFFSET == dim )
  { return; }

  geometry_mode_w()->set_blocked( mode );
  geometry_group_w()->set_blocked( group );
  geometry_dim_w()->set_blocked( dim - DIM_OFFSET );
  _set_geometry();
}

void
Geometry::
_set_geometry()
{
  motion::GeometryMode mode =
      motion::GeometryMode( geometry_mode_w()->get() );
  motion::GeometryGroup group =
      motion::GeometryGroup( geometry_group_w()->get() );
  uint dim = geometry_dim_w()->get() + DIM_OFFSET;

  viewer()->geometry_( mode, group, dim );

  if (mode == motion::MOEBIUS )
  {
    mousemode_w()->set_sensitive(0, false);
    mousemode_w()->set_sensitive(1, true);
    mousemode_w()->set_sensitive(2, true);
    mousemode_w()->set_sensitive(3, true);
    mousemode_w()->set_sensitive(4, true);
    mousemode_w()->set(1);
  }
  else if ( dim == 4 )
  {
    mousemode_w()->set_sensitive(0, false);
    mousemode_w()->set_sensitive(1, true);
    mousemode_w()->set_sensitive(2, true);
    mousemode_w()->set_sensitive(3, false);
    mousemode_w()->set_sensitive(4, false);
    mousemode_w()->set(1);
  }
  else
  {
    mousemode_w()->set_sensitive(0, true);
    mousemode_w()->set_sensitive(1, false);
    mousemode_w()->set_sensitive(2, false);
    mousemode_w()->set_sensitive(3, false);
    mousemode_w()->set_sensitive(4, false);
    mousemode_w()->set(0);
  }
}

void
Geometry::
reset_geometry()
{
  geometry_mode_w()->set_blocked( motion::PROJECTIVE );
  geometry_group_w()->set_blocked( motion::PARABOLIC );
  geometry_dim_w()->set_blocked( 3U - DIM_OFFSET );
//  normals_w()->set(true); // with callback

  set_geometry(
    motion::PROJECTIVE, motion::PARABOLIC, 3U );

  mousemode_w()->set(0);

  mousemode_w()->set_sensitive(1, false);
  mousemode_w()->set_sensitive(2, false);
  mousemode_w()->set_sensitive(3, false);
  mousemode_w()->set_sensitive(4, false);
}

void
Geometry::
reset_position_cb()
{
  viewer()->context()->geomobject_reset_position();
}

void
Geometry::
mousemode_cb()
{
  uint n = mousemode_w()->get();
  viewer()->context()->mouse_mode( motion::MouseMode(n) );
}

bool
Geometry::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;
  if ( command == "setGeometry" )
  {
    base::vector<uint> x;
    read_list( x, 3, argument );
    set_geometry(
      motion::GeometryMode(x[0]),
      motion::GeometryGroup(x[1]), x[2] );
    r = true;
  }
  else if ( command == "mouseMode" )
  {
    geometry_mousemode( motion::MouseMode(read_uint(argument)) );
    r = true;
  }
  return r;
}

} // namespace ui
} // namespace isightui
