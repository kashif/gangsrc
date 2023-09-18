/* GANG Software
 * VIEWER/isightui/ui/Mouse.C
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
#include "Mouse.H"

namespace isightui {
namespace ui {

Mouse::
Mouse()
    :
    widget::ui::Dialog()
{
}

Mouse::
~Mouse()
{
}

void
Mouse::
mouse_reset()
{
  // unaccelerated mouse
  inertia_enable_w()->set(true);
  inertia_decay_enable_w()->set(false);
  inertia_decay_rate_w()->set_sensitive(false);
  inertia_decay_rate_w()->set( 0.975f );
  viewmode_w()->set(0);

  // speed, acceleration
  float b[2] = { 0.15f, 0.0f };
  mouse_speed_w()->set( b );
}

void
Mouse::
synchronize()
{
  inertia_enable_w()->set_blocked(
    viewer()->context()->inertia_enable() );
  inertia_decay_enable_w()->set_blocked(
    viewer()->context()->inertia_decay() );
  inertia_decay_rate_w()->set_blocked(
    viewer()->context()->inertia_decay_rate() );
  inertia_decay_rate_w()->set_sensitive(
    viewer()->context()->inertia_decay() );
  float a[2];
  a[0] = viewer()->context()->speed();
  a[1] = viewer()->context()->acceleration();
  mouse_speed_w()->set_blocked( a );
  viewmode_w()->set_blocked( viewer()->context()->view_mode() );
}

void
Mouse::
mouse_speed_cb()
{
  float a[2];
  mouse_speed_w()->get( a );
  viewer()->context()->speed( a[0], a[1] );
}

void
Mouse::
inertia_enable_cb()
{
  viewer()->context()->inertia_enable( inertia_enable_w()->get() );
}

void
Mouse::
inertia_decay_enable_cb()
{
  bool b = inertia_decay_enable_w()->get();
  viewer()->context()->inertia_decay( b );
  inertia_decay_rate_w()->set_sensitive( b );
}

void
Mouse::
inertia_decay_rate_cb()
{
  viewer()->context()->inertia_decay_rate( inertia_decay_rate_w()->get() );
}

void
Mouse::
viewmode_cb()
{
  viewer()->context()->view_mode( viewmode_w()->get() );
}

void
Mouse::
reset0_cb()
{
  mouse_reset();
}

void
Mouse::
reset1_cb()
{
  // accelerated mouse
  inertia_enable_w()->set(true);
  inertia_decay_enable_w()->set(true);
  inertia_decay_rate_w()->set( 0.975f );
  inertia_decay_rate_w()->set_sensitive(true);
  viewmode_w()->set(0);

  float b[2] = { 1.0f, 1.0f };
  mouse_speed_w()->set( b );
}

bool
Mouse::
command(
  base::String const &command, 
  base::String const &argument,
  base::String &response )
{
  bool r = false;
  if ( command == "mouseReset" )
  {
    mouse_reset();
    r = true;
  }

  if ( command == "mouseInertiaEnable" )
  {
    mouse_inertia_enable( read_bool(argument) );
    r = true;
  }

  if ( command == "mouseInertiaDecayEnable" )
  {
    mouse_inertia_decay_enable( read_bool(argument) );
    r = true;
  }

  if ( command == "mouseInertiaDecayRate" )
  {
    mouse_inertia_decay_rate( read_real(argument) );
    r = true;
  }

  if ( command == "mouseSpeed" )
  {
    base::vector<float> x;
    read_list( x, 2, argument );
    base::ArrayX<float,2U> y(&x[0]);
    mouse_speed(y);
    r = true;
  }

  if ( command == "mouseViewmode" )
  {
    mouse_viewmode( read_uint(argument) );
    r = true;
  }
  return r;
}

} // namespace ui
} // namespace isightui
