/* GANG Software
 * GEOM/geomui/ui/Build.C
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

#include "Build.H"

namespace geomui {
namespace ui {

Build::
Build()
    :
    widget::ui::Dialog(),
    base::ReadUtil()
{
}

Build::
~Build()
{
}

void
Build::
build_reset_cb()
{
  reflect_plane_reset_cb();
}

void
Build::
reflect_plane_apply_cb()
{
  math::VectorX<float,4U> a_;
  reflect_plane_position_w()->get( a_.data() );

  // convert float to geomui::Real
  math::VectorX<Real,4U> a;
  a[0] = a_[0];
  a[1] = a_[1];
  a[2] = a_[2];
  a[3] = a_[3];

  reflect( a );

  statistics_synchronize();
  refresh_all();
}

void
Build::
reflect_coord_plane0_cb()
{
  reflect_coord_plane(0);
}

void
Build::
reflect_coord_plane1_cb()
{
  reflect_coord_plane(1);
}

void
Build::
reflect_coord_plane2_cb()
{
  reflect_coord_plane(2);
}


void
Build::
reflect_plane_reset_cb()
{
  geomlist()->remove_to_one();
  statistics_synchronize();
  refresh_all();
}


void
Build::
reflect_coord_plane( uint n )
{
  DIE_IF( n > 3 );

  // set a coordinate plane
  math::VectorX<Real,4U> a;
  a.set(0.0f);
  a[n] = 1.0f;

  reflect( a );
  statistics_synchronize();
  refresh_all();
}

void
Build::
reflect( math::VectorX<Real,4U> const &a )
{
  geomlist()->build_reflect( a );
}

bool
Build::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "buildReset" )
  {
    build_reset();
    r = true;
  }
  else if ( command == "reflectPlaneReset" )
  {
    reflect_plane_reset();
    r = true;
  }
  else if ( command == "reflectPlane" )
  {
    base::vector<float> x;
    read_list( x, 4, argument );
    base::ArrayX<float,4U> y(&x[0]);
    reflect_plane( y );
    r = true;
  }
  else if ( command == "reflectCoordPlane0" )
  {
    reflect_coord_plane0();
    r = true;
  }
  else if ( command == "reflectCoordPlane1" )
  {
    reflect_coord_plane1();
    r = true;
  }
  else if ( command == "reflectCoordPlane2" )
  {
    reflect_coord_plane2();
    r = true;
  }

  return r;
}

} // namespace ui
} // namespace geomui
