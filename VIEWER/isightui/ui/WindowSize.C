/* GANG Software
 * VIEWER/isightui/ui/WindowSize.C
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

#include "base/ArrayX.H"
#include "isight/kernel/ViewerBase.H"
#include "WindowSize.H"

namespace isightui {
namespace ui {

WindowSize::uint2 WindowSize::_size[6] =
{
  { 500, 500 },
  { 640, 480 },
  { 800, 800 },
  { 1024, 786 },
  { 1200, 1200 },
  { 1280, 960 }
};

WindowSize::
WindowSize()
    :
    widget::ui::Dialog(),
    _fullscreen(false)
{
}

WindowSize::
~WindowSize()
{
}

void
WindowSize::
windowsize_reset()
{
  resize(0);
}

void
WindowSize::
windowsize_synchronize()
{
  // set the window_size_w widget to window()'s size
  int a[2];
  a[0] = viewer()->context()->width();
  a[1] = viewer()->context()->height();
  window_size_w()->set_blocked( a );
}

void
WindowSize::
window_size_cb()
{
  int a[2];
  window_size_w()->get( a );
  restore( a[0], a[1] );
}

void
WindowSize::
resize(uint id)
{
  // resize window to _size[id]
  restore( _size[id].x, _size[id].y );
}

void
WindowSize::
windowsize_fullscreen( bool state )
{
  if ( state == _fullscreen ) { return; }

  // ignore if not showing
  if ( ! viewer()->context()->showing() ) { return; }

  _fullscreen = state;

  if (state)
  {
    viewer()->context()->save_window_size_and_position();

    // resize and reposition the window
    uint x = viewer()->global_screen_width();
    uint y = viewer()->global_screen_height();
    viewer()->context()->resize( x, y );
    viewer()->context()->reposition( 0U, 0U );
    viewer()->context()->raise();

    // update the window size widget
    update( x, y );
  }
  else
  {
    viewer()->context()->restore_window_size_and_position();
  }
}

void
WindowSize::
restore( uint x, uint y )
{
  // ignore if not showing
  if ( ! viewer()->context()->showing() ) { return; }

  if (x <= 0) { x = 1; }
  if (x > 32000) { x = 32000; }
  if (y <= 0) { y = 1; }
  if (y > 32000) { y = 32000; }

  // turn off fullscreen, return window to cached position, and
  // set window's size to (x, y)
  if ( _fullscreen )
  {
    viewer()->context()->restore_window_size_and_position();
    _fullscreen = false;
  }
  viewer()->context()->resize( x, y );
  update( x, y );
}

void
WindowSize::
update( uint x, uint y)
{
  // set the _window_size_w widget to window()'s size
  int a[2];
  a[0] = x;
  a[1] = y;
  window_size_w()->set_blocked( a );
}


bool
WindowSize::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "windowsizeReset" )
  {
    windowsize_reset();
    r = true;
  }
  if ( command == "windowsizeSet" )
  {
    base::vector<uint> x;
    read_list( x, 2, argument );
    base::ArrayX<uint,2U> y(&x[0]);
    windowsize_set(y);
    r = true;
  }
  if ( command == "windowsizeFullScreen" )
  {
    windowsize_fullscreen( read_bool(argument) );
    r = true;
  }
  if ( command == "windowsizeToggleFullScreen" )
  {
    windowsize_toggle_fullscreen();
    r = true;
  }

  return r;
}

} // namespace ui
} // namespace isightui
