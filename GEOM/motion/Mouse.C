/* GANG Software
 * GEOM/motion/Mouse.C
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

#include <unistd.h>
#include <iostream>
#include "base/System.H"
#include "Mouse.H"

namespace motion {

// MOUSE_STOP_TIME: kill inertia if mouse is held down this long (sec)
float const Mouse::MOUSE_STOP_TIME = 0.2f;

Mouse::
Mouse()
    :
    _button(0),
    _button_down(false),
    _drags(0),
    _point0(),
    _point1()
{
}

Mouse::
~Mouse()
{
}

bool
Mouse::
mouse_press_event(
  int button, int u, int v )
{
#if 0
  std::cerr << "press=" << button << " "
            << "drags=" << _drags << " "
            << "button_down=" << _button_down << "\n";
#endif

  // ignore invalid buttons
  if ( button < 0 || button > 2 ) { return 0; }

  // ignore the button press event if a mouse button is already pressed
  if ( _button_down ) { return 0; }

  // start timer
  _timer.start();

  _drags = 0;

  // store info
  _button = button;
  _button_down = true;
  _point1.x = u;
  _point1.y = v;

  enable_inertia(false);

  return 1;
}

bool
Mouse::
mouse_drag_event( int u, int v )
{
#if 0
  std::cerr << "drag=" << _button << " "
            << "drags=" << _drags << " "
            << "button_down=" << _button_down << "\n";
#endif

  if ( ! _button_down ) { return 0; }

  // start timer
  _timer.start();

  Point p(u, v );
  compute_inertia( _button, _point1, p );
  refresh();

  _drags++;
  _point0 = _point1;
  _point1 = p;

  return 1;
}

bool
Mouse::
mouse_release_event(
  int button, int u, int v )
{
#if 0
  std::cerr << "release=" << button << " " << _button << " "
            << "drags=" << _drags << " "
            << "button_down=" << _button_down << "\n";
#endif

  // ignore invalid buttons
  if ( button < 0 || button > 2 ) { return 0; }

  // ignore if no button is down
  if ( ! _button_down ) { return 0; }

  // ignore if the button released is different from the button pressed
  if ( button != _button) { return 0; }

  _button_down = 0;

  float dt = _timer.time();

  if ( dt >= MOUSE_STOP_TIME )
  {
    enable_inertia(false);
    return 1;
  }

  if ( _drags == 0 )
  {
    // no mouse drag events have occured: move by the distance from the
    // previous mouse button press event to this event
    compute_inertia( button, _point1, Point(u,v) );
  }
  else
  {
    // at least one mouse drag events have occurred:
    // move by the second to last interval
    // this is done because the interval from a mouse drag event to a
    // mouse release event is inaccurate (often less than the previous
    // drag intervals). Adjusting by clock doesnt seem to fix it
    compute_inertia( button, _point0, _point1 );
  }
  enable_inertia(true);

  return 1;
}

} // namespace motion
