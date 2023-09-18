/* GANG Software
 * WIDGET/gtk/widget1/GLWindow.C
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

#include <stdlib.h>
#include <GL/gl.h>
#include "base/System.H"
#include "base/Exception.H"
#include "GLWindow.H"

namespace gtk {
namespace widget1 {

GLWindow::
GLWindow()
    :
    ::gtk::widget0::Window( GTK_WINDOW_TOPLEVEL ),
    _enable_draw(0)
{
  // key press events are connected to the window rather than to
  // to _screen. Connecting them to the screen doesn't work

  gtk_widget_set_events(
    GTK_WIDGET(w()),
    gtk_widget_get_events(GTK_WIDGET(w())) |
    GDK_KEY_PRESS_MASK |
    GDK_KEY_RELEASE_MASK |
    GDK_FOCUS_CHANGE_MASK
    );

  gtk_signal_connect(
    GTK_OBJECT(w()), "key_press_event",
    GTK_SIGNAL_FUNC(key_press_event_cb_), this);

  gtk_signal_connect(
    GTK_OBJECT(w()), "key_release_event",
    GTK_SIGNAL_FUNC(key_release_event_cb_), this);

  gtk_signal_connect(
    GTK_OBJECT(w()), "delete_event",
    GTK_SIGNAL_FUNC(delete_event_cb_), this);

  gtk_signal_connect(
    GTK_OBJECT(w()), "focus_in_event",
    GTK_SIGNAL_FUNC(focus_in_event_cb_), this);

  gtk_signal_connect(
    GTK_OBJECT(w()), "focus_out_event",
    GTK_SIGNAL_FUNC(focus_out_event_cb_), this);

  // destroy callback
  gtk_signal_connect(
    GTK_OBJECT(w()), "destroy",
    GTK_SIGNAL_FUNC(destroy_cb_), this);

  // size
  set_default_size( DEFAULT_WIDTH, DEFAULT_HEIGHT );
  //NOTE: calls to width(), height() are wrong (give 200)

  int attributes[] =
  {
    GDK_GL_RGBA,
    GDK_GL_RED_SIZE,   1,
    GDK_GL_GREEN_SIZE, 1,
    GDK_GL_BLUE_SIZE,  1,
//    GDK_GL_ALPHA_SIZE, 1,
    GDK_GL_DEPTH_SIZE, 1,
    GDK_GL_DOUBLEBUFFER,
    GDK_GL_NONE
    };
  // GDK_GL_ALPHA_SIZE makes all color look grainy

  // create new OpenGL screen
  _screen_w = new GLArea( attributes );

  if ( _screen_w->w() == (::GtkWidget *)0 )
  {
    throw base::Exception( "Can't create GtkGLArea widget" );
  }

  // show it
  _screen_w->show();

  // set the size of the screen
//  _screen_w->size( DEFAULT_WIDTH, DEFAULT_HEIGHT );

  // set up events and signals for OpenGL widget
  _screen_w->set_events(
    GDK_EXPOSURE_MASK |
    GDK_BUTTON_PRESS_MASK |
    GDK_BUTTON_RELEASE_MASK |
    GDK_POINTER_MOTION_MASK |
    GDK_POINTER_MOTION_HINT_MASK
    );

  // signals for screen
  gtk_signal_connect(
    GTK_OBJECT(_screen_w->w()), "expose_event",
    GTK_SIGNAL_FUNC(expose_event_cb_), this);

  gtk_signal_connect(
    GTK_OBJECT(_screen_w->w()), "motion_notify_event",
    GTK_SIGNAL_FUNC(motion_notify_event_cb_), this);

  gtk_signal_connect(
    GTK_OBJECT(_screen_w->w()), "button_press_event",
    GTK_SIGNAL_FUNC(button_press_event_cb_), this);

  gtk_signal_connect(
    GTK_OBJECT(_screen_w->w()), "button_release_event",
    GTK_SIGNAL_FUNC(button_release_event_cb_), this);

  gtk_signal_connect(
    GTK_OBJECT(_screen_w->w()), "configure_event",
    GTK_SIGNAL_FUNC(configure_event_cb_), this);

  // put _screen_w into window
  add( _screen_w );

  _screen_w->realize();
}

GLWindow::
~GLWindow()
{
  // NOTE: crashes
  delete _screen_w;
}

#if 0
void
GLWindow::
show( bool state )
{
  if (state && w()->window != 0) {
    // set the position of the window to where it previously was
    // this is necessary because the window manager places it
    // randomly on the desktop
    gint x, y;
    gdk_window_get_deskrelative_origin( w()->window, &x, &y );
    set_uposition( x, y );
  }

  ::gtk::widget0::Window::show(state);

  if ( state )
  {
    // Set usize so that the window can be resized smaller by the user.
    // This call must be after the first Window::show() call.
    _screen_w->usize( 1U, 1U );
  }
}
#endif

int
GLWindow::
configure_event_cb( GdkEventConfigure *event )
{
  // OpenGL calls can be done only if make_current returns true
  int e = _screen_w->make_current();
  if ( !e )
  {
    throw base::Exception( "OpenGL call failed" );
  }

  // OpenGL call: set the viewport size
  glViewport( 0, 0, area_width(), area_height() );

  return 1;
}

int
GLWindow::
expose_event_cb( GdkEventExpose *event )
{
  // draw only last expose
  if (event->count > 0) { return 1; }

  if (_enable_draw != 0) { return 1; }

  // OpenGL calls can be done only if make_current returns true
  int e = _screen_w->make_current();
  if ( !e )
  {
    throw base::Exception( "OpenGL call failed" );
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  draw();

  // swap buffers
  _screen_w->swap_buffers();

  return 1;
}

int
GLWindow::
delete_event_cb()
{
  hide();
  return 1;  // return value of 1 means do not delete the window
}

void
GLWindow::
clear_screen()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _screen_w->swap_buffers();
}

void
GLWindow::
show_screen(bool state)
{
  _screen_w->show(state);
}

void
GLWindow::
enable_draw( bool state )
{
  if (state)
  {
    DIE_IF( _enable_draw == 0 );
    _enable_draw--;
  }
  else
  {
    _enable_draw++;
  }
}

} // namespace gtk
} // namespace widget1
