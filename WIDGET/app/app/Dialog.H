/* GANG Software
 * WIDGET/app/app/Dialog.H
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

#ifndef app_app_Dialog_INCLUDED
#define app_app_Dialog_INCLUDED

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1174
#endif
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkwindow.h>
#include <gtk/gtkframe.h>
#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#endif

#include "gtk/widget0/Dialog.H"
#include "gtk/widget0/VBox.H"
#include "gtk/widget0/HBox.H"
#include "gtk/widget0/Frame.H"
#include "gtk/widget0/AccelGroup.H"
#include "gtk/widget0/ButtonCb.H"
#include "gtk/widget0/EventBox.H"
#include "gtk/widget0/AccelGroup.H"
#include "gtk/widget0/Tooltips.H"
#include "gtk/widget1/Pixmap.H"

namespace app {
namespace app {

/*
   Gtk dialog box.
*/
class Dialog
{

public:

  // constructor
  Dialog(
    char const *title,
    char const *frame_label,
    ::gtk::widget0::Widget *contents = (gtk::widget0::Widget *)0,
    char **xpm = (char **)0);

  // destructor
  virtual ~Dialog();

  // NOTE: non-virtual override
  void add( gtk::widget0::Widget *contents )
    {
      //contents->show();
      _frame->add(contents); }

  void raise( bool state = true )
    { _window.raise(state); }
  void show( bool state = true )
    { _window.show(state); }
  void toggle_raise_show()
    { _window.toggle_raise_show(); }
  void raise_show()
    { _window.raise_show(); }

protected:

  void realize()
    { _window.realize(); }
  gtk::widget0::Window *window()
    { return &_window; }

  virtual int key_press_event( uint key, uint state ) = 0;

private:

  guint key_press_event_cb( GdkEventKey *e );
  static gint key_press_event_cb_(
    GtkWidget *, GdkEventKey *event, gpointer p)
    { return static_cast<Dialog *>(p)->key_press_event_cb( event ); }

  gtk::widget0::AccelGroup *_accelgroup_w;
  gtk::widget0::VBox *_vbox;
  gtk::widget0::HBox *_hbox;
  gtk::widget0::Frame *_frame;
  gtk::widget0::EventBox *_eventbox;
  gtk::widget1::Pixmap *_pixmap;

  void close_cb();
  static gint close_cb_( GtkWidget *, GdkEventButton *, gpointer p );

  gint delete_event_cb();

  static gint delete_event_cb_(
    GtkWidget *widget,
    GdkEvent  *event,
    gpointer   data );

  ::gtk::widget0::Window _window;

  // disabled copy constructor
  Dialog( Dialog const & );

  // disabled assignment operator
  Dialog &operator=( Dialog const & );

};

} // namespace app
} // namespace app

#endif // app_app_Dialog_INCLUDED
