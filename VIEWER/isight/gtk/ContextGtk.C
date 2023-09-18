/* GANG Software
 * VIEWER/isight/gtk/ContextGtk.C
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

#include "ContextGtk.H"

namespace isight {
namespace gtk {

ContextGtk::
ContextGtk( ::isight::context::ContextSetBase *base )
    :
    ::gtk::widget1::GLWindow(),
    ::isight::context::Context(base),
    _idler(this, &isight::context::Context::idle_cb)
{
}

ContextGtk::
~ContextGtk()
{
  _idler.enable(false);
}

int
ContextGtk::
button_press_event_cb( GdkEventButton *event )
{
  int x = (int)event->x;
  int y = (int)event->y;
  int b = event->button- 1;
  return mouse_press_event(b, x, y );
}

int
ContextGtk::
button_release_event_cb( GdkEventButton *event )
{
  int x = (int)event->x;
  int y = (int)event->y;
  int b = event->button - 1;
  return mouse_release_event( b, x, y );
}

int
ContextGtk::
motion_notify_event_cb( GdkEventMotion *event )
{
  int x, y;

  bool state;

  if (event->is_hint)
  {
    GdkModifierType state_;
    gdk_window_get_pointer(event->window, &x, &y, &state_);
    state = (bool) state_;
  }
  else
  {
    x = (int)event->x;
    y = (int)event->y;
    state = event->state;
  }

  // state=0: mouse motion (no button held down)
  // state=1: mouse drag (button held down)

  if ( state )
  {
    return mouse_drag_event( x, y );
  }
  else
  {
    return 0;
  }
}

int
ContextGtk::
configure_event_cb( GdkEventConfigure *event )
{
  context_size_event_cb( event->width, event->height );

  // call baseclass version
  return ::gtk::widget1::GLWindow::configure_event_cb(event);
}

int
ContextGtk::
key_press_event_cb( GdkEventKey *e )
{
  return window_key_press_event( e->keyval, e->state );
}

} // namespace gtk
} // namespace isight
