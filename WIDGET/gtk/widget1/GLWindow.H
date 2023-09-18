/* GANG Software
 * WIDGET/gtk/widget1/GLWindow.H
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

#ifndef gtk_widget1_GLWindow_INCLUDED
#define gtk_widget1_GLWindow_INCLUDED

#include "gtk/widget0/Window.H"
#include "GLArea.H"

namespace gtk {
namespace widget1 {

class GLWindow
  :
    public gtk::widget0::Window
{

public:

  // void constructor
  GLWindow();

  // destructor
  virtual ~GLWindow();

  void enable_draw(bool state = true);
  void clear_screen();
  void show_screen(bool state);
  void swap_buffers()
    { _screen_w->swap_buffers(); }
private:

  // The OpenGL drawing area inside the window.
  GLArea *_screen_w;

public:

  // call gtk_widget_draw() on the screen
  void refresh()
    { _screen_w->draw(); }

  // set the OpenGL context to this screen
  void make_current()
    { _screen_w->make_current(); }

  // return the width of the window
  uint area_width() const
    { return _screen_w->width(); }

  // return the height of the window
  uint area_height() const
    { return _screen_w->height(); }

  // default window width
  static uint const DEFAULT_WIDTH = 500;

  // default window height
  static uint const DEFAULT_HEIGHT = 500;

protected:

  virtual void draw() = 0;

  // Called _screen_w is first created and when it changes size
  virtual int configure_event_cb( GdkEventConfigure * );

  // Called by gtk when _screen_w needs to be redrawn
  virtual int expose_event_cb( GdkEventExpose * );

  // Called by gtk when the user presses a mouse button.
  virtual int button_press_event_cb( GdkEventButton * ) = 0;

  // Called by gtk when the user presses a mouse button.
  virtual int button_release_event_cb( GdkEventButton * ) = 0;

  // Called by gtk when user moves or drags the mouse over the window
  virtual int motion_notify_event_cb( GdkEventMotion * ) = 0;

  // Called by gtk when a keyboard key is pressed (and the window has focus)
  virtual int key_press_event_cb( GdkEventKey * ) = 0;

  // Called by gtk when a keyboard key is released
  virtual int key_release_event_cb( GdkEventKey * ) = 0;

  // Called by gtk when a keyboard key is released
  virtual int focus_in_event_cb( GdkEventFocus * ) = 0;

  // Called by gtk when a keyboard key is released
  virtual int focus_out_event_cb( GdkEventFocus * ) = 0;

  //
  virtual int delete_event_cb();

  //
  virtual void destroy_cb() {};

private:

  // static callback functions -- wrappers for non-static versions
  static gint configure_event_cb_(
    GtkWidget *, GdkEventConfigure *event, gpointer p )
    { return static_cast<GLWindow *>(p)->configure_event_cb( event ); }

  static gint expose_event_cb_(
    GtkWidget *, GdkEventExpose *event, gpointer p )
    { return static_cast<GLWindow *>(p)->expose_event_cb( event ); }

  static gint button_press_event_cb_(
    GtkWidget *, GdkEventButton *event, gpointer p )
    { return static_cast<GLWindow *>(p)->button_press_event_cb( event ); }

  static gint button_release_event_cb_(
    GtkWidget *, GdkEventButton *event, gpointer p )
    { return static_cast<GLWindow *>(p)->button_release_event_cb( event ); }

  static gint motion_notify_event_cb_(
    GtkWidget *, GdkEventMotion *event, gpointer p )
    { return static_cast<GLWindow *>(p)->motion_notify_event_cb( event ); }

  static gint key_press_event_cb_(
    GtkWidget *, GdkEventKey *event, gpointer p )
    { return static_cast<GLWindow *>(p)->key_press_event_cb( event ); }
  
  static gint key_release_event_cb_(
    GtkWidget *, GdkEventKey *event, gpointer p )
    { return static_cast<GLWindow *>(p)->key_release_event_cb( event ); }

  static gint focus_in_event_cb_(
    GtkWidget *, GdkEventFocus *event, gpointer p )
    { return static_cast<GLWindow *>(p)->focus_in_event_cb( event ); }

  static gint focus_out_event_cb_(
    GtkWidget *, GdkEventFocus *event, gpointer p )
    { return static_cast<GLWindow *>(p)->focus_out_event_cb( event ); }

  static void destroy_cb_(
    GtkWidget *, gpointer p )
    { static_cast<GLWindow *>(p)->destroy_cb(); }

  static gint delete_event_cb_(
    GtkWidget *, GdkEvent *, gpointer p )
    { return static_cast<GLWindow *>(p)->delete_event_cb(); }

  uint _enable_draw;

  // disabled copy constructor
  GLWindow( GLWindow const & );

  // disabled assignment operator
  GLWindow &operator=( GLWindow const & );
};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_GLWindow_INCLUDED
