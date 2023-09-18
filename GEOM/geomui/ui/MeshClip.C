/* GANG Software
 * GEOM/geomui/ui/MeshClip.C
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

#include "MeshClip.H"

namespace geomui {
namespace ui {

MeshClip::
MeshClip()
    :
    widget::ui::Dialog(),
    base::ReadUtil()
{
}

MeshClip::
~MeshClip()
{
}

bool
MeshClip::
is_grid() const
{
  return ! geomlist()->empty() &&
    geomlist()->type() == geomlist()->GRID;
  return false;
}

void
MeshClip::
meshclip_synchronize()
{
  int a[2] = { 0, 0 };
  int b[2] = { 0, 0 };

  if ( is_grid() )
  {
    // set_sensitive widgets appropriate for ::geomui::kernel::Grid surfaces
    meshclip_reset_w()->set_sensitive(true);
    meshclip_i_w()->set_sensitive(true);
    meshclip_j_w()->set_sensitive(true);
    mesh_roll_i_w()->set_sensitive(true);
    mesh_roll_j_w()->set_sensitive(true);

    // should not reset clip -- (called when an object is selected)
    uint x = geomlist()->i_count();
    uint y = geomlist()->j_count();
    if ( x > 0 ) { x--; }
    if ( y > 0 ) { y--; }
    a[1] = x; b[1] = y;
    geomlist()->reset_clip();
  }
  else
  {
    // disable widgets inappropriate for ::geomui::kernel::Indexed surfaces
    meshclip_reset_w()->set_sensitive(false);
    meshclip_i_w()->set_sensitive(false);
    meshclip_j_w()->set_sensitive(false);
    mesh_roll_i_w()->set_sensitive(false);
    mesh_roll_j_w()->set_sensitive(false);
  }

  // set bounds
  meshclip_i_w()->set_bounds(0, 0, a[1]);
  meshclip_i_w()->set_bounds(1, 0, a[1]);
  meshclip_j_w()->set_bounds(0, 0, b[1]);
  meshclip_j_w()->set_bounds(1, 0, b[1]);

  meshclip_i_w()->set_blocked( a );
  meshclip_j_w()->set_blocked( b );
  mesh_roll_i_w()->set_blocked( 0 );
  mesh_roll_j_w()->set_blocked( 0 );
}

void
MeshClip::
meshclip_reset_cb()
{
  meshclip_reset();
  refresh_all();
}

void
MeshClip::
meshclip_cb()
{
  if ( ! is_grid() ) { return; }

  uint x = geomlist()->i_count();
  uint y = geomlist()->j_count();
  if ( x > 0 ) { x--; }
  if ( y > 0 ) { y--; }

  int a[2], b[2];
  meshclip_i_w()->get( a );
  meshclip_j_w()->get( b );
  math::sort(a[0], a[1]);
  math::sort(b[0], b[1]);

  mesh_roll_i_w()->set_blocked(
    int(x) == a[1] - a[0] ? 0 : int(float(a[0])/float(x-a[1]+a[0])) );
  mesh_roll_j_w()->set_blocked(
    int(y) == b[1] - b[0] ? 0 : int(float(b[0])/float(y-b[1]+b[0])) );

  geomlist()->set_clip( a[0], a[1]-a[0]+1, b[0], b[1]-b[0]+1 );

  refresh_all();
}

void
MeshClip::
mesh_roll_cb()
{
  if ( ! is_grid() ) { return; }

  int x = geomlist()->i_count();
  int y = geomlist()->j_count();
  if ( x > 0 ) { x--; }
  if ( y > 0 ) { y--; }

  int a[2], b[2];
  meshclip_i_w()->get( a );
  meshclip_j_w()->get( b );

  int ax = int( mesh_roll_i_w()->get() * float(x - math::abs(a[1] - a[0])) );
  int bx = int( mesh_roll_j_w()->get() * float(y - math::abs(b[1] - b[0])) );

  if (a[0] <= a[1])
  {
    a[1] -= a[0]; a[1] += ax;
    a[0] = ax;
  }
  else
  {
    a[0] -= a[1]; a[0] += ax;
    a[1] = ax;
  }
  if (b[0] <= b[1])
  {
    b[1] -= b[0]; b[1] += bx;
    b[0] = bx;
  }
  else
  {
    b[0] -= b[1]; b[0] += bx;
    b[1] = bx;
  }
  meshclip_i_w()->set_blocked( a );
  meshclip_j_w()->set_blocked( b );

  math::sort(a[0], a[1]);
  math::sort(b[0], b[1]);

  geomlist()->set_clip( a[0], a[1]-a[0]+1, b[0], b[1]-b[0]+1 );

  refresh_all();
}

void
MeshClip::
meshclip_i( base::ArrayX<uint,2U> const &x )
{
  if ( ! is_grid() ) { return; }
  int y[2];
  y[0] = x[0];
  y[1] = x[1];
  meshclip_i_w()->set_blocked( y );
  meshclip_cb();
}

void
MeshClip::
meshclip_j( base::ArrayX<uint,2U> const &x )
{
  if ( ! is_grid() ) { return; }
  int y[2];
  y[0] = x[0];
  y[1] = x[1];
  meshclip_j_w()->set_blocked( y );
  meshclip_cb();
}

void
MeshClip::
meshclip_roll_i( float const &x )
{
  if ( ! is_grid() ) { return; }
  if ( x < 0.0 || x > 1.0 ) { return; }
  mesh_roll_i_w()->set_blocked( x );
  meshclip_cb();
}

void
MeshClip::
meshclip_roll_j( float const &x )
{
  if ( ! is_grid() ) { return; }
  if ( x < 0.0 || x > 1.0 ) { return; }
  mesh_roll_j_w()->set_blocked( x );
  meshclip_cb();
}

bool
MeshClip::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "meshclipReset" )
  {
    meshclip_reset();
    r = true;
  }

  if ( command == "meshclipI" )
  {
    base::vector<uint> x;
    read_list( x, 2, argument );
    base::ArrayX<uint,2U> y(&x[0]);
    meshclip_i(y);
    r = true;
  }

  if ( command == "meshclipJ" )
  {
    base::vector<uint> x;
    read_list( x, 2, argument );
    base::ArrayX<uint,2U> y(&x[0]);
    meshclip_j(y);
    r = true;
  }

  if ( command == "meshclipRollI" )
  {
    meshclip_roll_i( read_real(argument) );
    r = true;
  }

  if ( command == "meshclipRollJ" )
  {
    meshclip_roll_j( read_real(argument));
    r = true;
  }

  return r;
}

} // namespace ui
} // namespace geomui
