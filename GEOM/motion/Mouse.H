/* GANG Software
 * GEOM/motion/Mouse.H
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

#ifndef motion_Mouse_INCLUDED
#define motion_Mouse_INCLUDED

#include "base/Timer.H"

namespace motion {

class Mouse
{

public:
  // constructor
  Mouse();

  // destructor
  virtual ~Mouse();

  bool mouse_press_event( int button, int x, int y );
  bool mouse_release_event( int button, int x, int y );
  bool mouse_drag_event( int x, int y );

protected:

  // current mouse coordinates
  struct Point
  {
    Point() : x(0), y(0) {};
    Point( int u, int v ) : x(u), y(v) {};
    int x; int y;
  };

  virtual void compute_inertia(
    uint button, Point const &p0, Point const &p1 ) = 0;

  virtual void enable_inertia(bool state) = 0;

  virtual void refresh() = 0;

private:

  base::Timer _timer;

  // _button: the current button
  int _button;

  // _button_down is true when a mouse button is down
  bool _button_down;

  // _drags counts the number of mouse drag events that have occured
  int _drags;

  // begin and end points of mouse drag
  Point _point0, _point1;

  static float const MOUSE_STOP_TIME;

  // disabled copy constructor
  Mouse( Mouse const & );

  // disabled assignment operator
  Mouse &operator=( Mouse const & );

};

} // namespace motion

#endif // motion_Mouse_INCLUDED
