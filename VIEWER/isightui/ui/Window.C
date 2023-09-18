/* GANG Software
 * VIEWER/isightui/ui/Window.C
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

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1174
#endif
#include <gtk/gtkclist.h>
#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#endif

#include "base/System.H"
#include "isight/kernel/ViewerBase.H"
#include "Window.H"

namespace isightui {
namespace ui {

Window::
Window()
{
}

Window::
~Window()
{
}

#if 0
void
Window::
new_window_nb( base::String const &label )
{
  // insert new row
  select_window_w()->append_blocked(label.c_str());
  set_sensitive();
}

void
Window::
select_window_nb( uint id )
{
  DIE_IF( id >= item_count() );
  select_window_w()->set_blocked(id);
  set_sensitive();
}

void
Window::
delete_window_nb( uint id )
{
  DIE_IF( id >= item_count() );
  select_window_w()->remove(id);
  set_sensitive();
}

void
Window::
show_window_nb( uint id, bool state )
{
  if ( id == select_window_w()->get() )
  {
    show_window_w()->set(state);
  }
}
#endif


void
Window::
synchronize()
{
  uint id = select_window_w()->get();
  if ( id == NONE ) { return; }
  DIE_IF( id >= item_count() );

  show_window_w()->set( viewer()->window_showing_(id) );
}

void
Window::
set_sensitive()
{
  bool selected = select_window_w()->selected();
  bool morethanone = item_count() > 1;
  show_window_w()->set_sensitive( selected );
  delete_window_w()->set_sensitive( selected && morethanone );
}

void
Window::
new_window()
{
  viewer()->new_window_();

  // insert new row
  select_window_w()->append_blocked( viewer()->window_title().c_str() );

  // select the last window in list
  DIE_IF( item_count() == 0 );
  uint id = item_count() - 1;
  select_window_w()->set(id);

  synchronize();
  set_sensitive();
}

void
Window::
new_window_cb()
{
  viewer()->new_window_();

  // insert new row
  select_window_w()->append_blocked( viewer()->window_title().c_str() );

  // select the last window in list
  DIE_IF( item_count() == 0 );
  uint id = item_count() - 1;
  select_window_w()->set(id);

  // show the window
  viewer()->show_window_( id, true );

  synchronize();
  set_sensitive();
}

void
Window::
select_window_cb()
{
  uint id = select_window_w()->get();
  if ( id == NONE ) { return; }
  DIE_IF( id >= item_count() );

  viewer()->select_window_( id );

  synchronize();
  set_sensitive();
}

void
Window::
show_window_cb()
{
  uint id = select_window_w()->get();
  DIE_IF( id >= item_count() );
  if ( id == NONE ) { return; }

  bool state = show_window_w()->get();
  viewer()->show_window_( id, state );

  synchronize();
  set_sensitive();
}

void
Window::
delete_window_cb()
{
  uint id = select_window_w()->get();
  if ( id == NONE ) { return; }
  viewer()->delete_window_( id );

  DIE_IF( id >= item_count() );
  select_window_w()->remove(id);

  // select window id (or id-1)
  if( item_count() == 0 ) { return; }

  if (id >= item_count() ) { id--; }
  select_window(id);
}

void
Window::
reset_position()
{ viewer()->context()->geomobject_reset_position(); }

void
Window::
stop_motion()
{ viewer()->context()->stop_motion(); }

bool
Window::
command(
  base::String const &command, 
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "newContext" )
  {
    new_window();
    r = true;
  }
  if ( command == "selectContext" )
  {
    select_window( read_uint(argument) );
    r = true;
  }
  if ( command == "showContext" )
  {
    base::String id, x;
    split1( id, x, argument );
    show_window( read_uint(id), read_bool(x) );
    r = true;
  }
  if ( command == "deleteContext" )
  {
    delete_window( read_uint(argument) );
    r = true;
  }
  return r;
}

} // namespace ui
} // namespace isightui
