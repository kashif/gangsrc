/* GANG Software
 * VIEWER/isight/context/Context.C
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

#include <gdk/gdkkeysyms.h>
#include <iomanip>
#include "base/Regex.H"
#include "imagegl/ScreenLoad.H"
#include "Context.H"

namespace isight {
namespace context {

Context::
Context( ContextSetBase *base )
    :
    Background(base),
    opengl::Fade(),
    _size_x(0),
    _size_y(0),
    _position_x(0),
    _position_y(0)
{
}

Context::
~Context()
{
}

void
Context::
geometry( motion::GeometryMode mode,
          motion::GeometryGroup group,
          uint dim )
{
  stop_motion();
  geom_motion()->geometry( mode, group, dim);
  geomobject_reset_position();

  // turn sphere on for hyperbolic geometry, off otherwise
  sphere(group == motion::HYPERBOLIC);
}

void
Context::
destroy_cb()
{
  enable_idle(false);
}

void
Context::
context_size_event_cb( uint x, uint y )
{
  Camera::set_window_size( x, y );
  Camera::draw();
  base()->viewer_ui()->windowsize_synchronize_notify();
}

void
Context::
draw()
{
  // draw the background image
  ::imagegl::ScreenLoad::draw();

  // draw axes, sphere, stars
  draw_background();

  if (motion_mode() == GEOMOBJECT)
  {
    if (geom_motion()->moving())
    {
      // move the geomobjects
      GeomObjectSet::move( *geom_motion()->inertia() );
    }
  }
  else if (motion_mode() == MILIEU)
  {
    if (milieu_motion()->moving())
    {
      // move the lights and clipplanes
      Milieu::move( *milieu_motion()->inertia() );
    }
  }

  // draw the milieu
  Milieu::draw();
  // draw the geomobjects
  GeomObjectSet::draw();
}

} // namespace context
} // namespace isight
