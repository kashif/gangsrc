/* GANG Software
 * WIDGET/gtk/widget1/ScreenWindow.H
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

#ifndef gtk_widget1_ScreenWindow_INCLUDED
#define gtk_widget1_ScreenWindow_INCLUDED

#include "gtk/widget0/Window.H"
#include "Screen.H"

namespace gtk {
namespace widget1 {

class ScreenWindow
  :
    public gtk::widget0::Window
{

public:

  typedef Screen::PointInt PointInt;
  typedef Screen::Color256 Color256;

  // constructor
  ScreenWindow();

  // destructor
  virtual ~ScreenWindow();

  // default window width
  static uint const DEFAULT_WIDTH = 500;

  // default window height
  static uint const DEFAULT_HEIGHT = 500;

  void draw_point( PointInt const &p, Color256 const &c)
    { _screen_w->draw_point( p, c ); }

protected:

  virtual void display_cb() = 0;

private:

  static gint expose_event_cb_(
    GtkWidget *, GdkEventExpose *event, gpointer p )
    { return static_cast<ScreenWindow *>(p)->expose_event_cb(event); }
  gint expose_event_cb(GdkEventExpose *event)
    { display_cb(); return 0; }

  // The drawing area inside the window.
  Screen *_screen_w;

  // disabled copy constructor
  ScreenWindow( ScreenWindow const & );
  // disabled assignment operator
  ScreenWindow &operator=( ScreenWindow const & );

};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_ScreenWindow_INCLUDED
