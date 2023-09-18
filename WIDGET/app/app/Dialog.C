/* GANG Software
 * WIDGET/app/app/Dialog.C
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
#include <gtk/gtk.h>
#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#endif
#include <ctype.h>
#include "base/String.H"
#include "base/System.H"
#include "panel.xpm"
#include "Dialog.H"

namespace app {
namespace app {

Dialog::
Dialog(
  char const *title,
  char const *label,
  gtk::widget0::Widget *contents,
  char **xpm )
    :
    _accelgroup_w( new ::gtk::widget0::AccelGroup ),
    _window( GTK_WINDOW_TOPLEVEL )
{
  DIE_IF( title == (char *)0 );
  DIE_IF( label == (char *)0 );

  base::String s;

  if (title != (char *)0)
  {
    s = title;
  }
  else
  {
    DIE();
  }
  if (title != (char *)0 && label != 0)
  {
    s += " | ";
  }
  if ( label != (char *)0 )
  {
    s += label;
  }
  _window.set_title( s.c_str() );

  gtk_widget_set_events(
    GTK_WIDGET(_window.w()),
    gtk_widget_get_events(GTK_WIDGET(_window.w())) |
    GDK_KEY_PRESS_MASK );

  gtk_signal_connect(
    GTK_OBJECT(_window.w()), "key_press_event",
    GTK_SIGNAL_FUNC(key_press_event_cb_), this);

  gtk_signal_connect(
    GTK_OBJECT(_window.w()), "delete_event",
    GTK_SIGNAL_FUNC(delete_event_cb_), this);

  // vbox
  _vbox = new gtk::widget0::VBox( false, 0 );
  _vbox->show();
  _window.add(_vbox);

  _hbox = new gtk::widget0::HBox( false, 0 );
  _hbox->show();
  _vbox->add( _hbox, false, false, 0);

  _window.realize();

  _eventbox = new gtk::widget0::EventBox();
  gtk_signal_connect(
    GTK_OBJECT(_eventbox->w()), "button_press_event",
    GTK_SIGNAL_FUNC(close_cb_), this );
  _hbox->add_end( _eventbox, false, false, 0);
  _eventbox->show();
  _eventbox->realize();

  // logo
  char **x = ( xpm ? xpm : panel_xpm );
  _pixmap = new ::gtk::widget1::Pixmap( x, &_window );
  _pixmap->show();
  _eventbox->add( _pixmap);

  // _frame
  _frame = new gtk::widget0::Frame( label );
  _frame->show();
  _vbox->add( _frame, true, true, 0 );

  if (contents != (::gtk::widget0::Widget *)0)
  {
//    contents->show();
    _frame->add(contents);
  }

  gdk_window_set_cursor(
    _eventbox->w()->window, gdk_cursor_new(GDK_DOT));

  // window sizing policies: allow_shrink, allow_grow, auto_shrink
  _window.set_policy( false, true, true );
}

Dialog::
~Dialog()
{
  delete _frame;
  delete _pixmap;
  delete _eventbox;
  delete _hbox;
  delete _vbox;
  delete _accelgroup_w;
}

gint
Dialog::
delete_event_cb()
{
  show(false);
  return 1;
}

gint
Dialog::
delete_event_cb_(
  GtkWidget *widget,
  GdkEvent  *event,
  gpointer   data )
{
  return ((Dialog *)data)->delete_event_cb();
}

void
Dialog::
close_cb()
{
  _window.show(false);
}

gint
Dialog::
close_cb_( GtkWidget *, GdkEventButton *, gpointer p )
{
  static_cast<Dialog *>(p)->close_cb();
  return 1;
}

guint
Dialog::
key_press_event_cb( GdkEventKey *e )
{
  return key_press_event( e->keyval, GdkModifierType(e->state) );
}

} // namespace app
} // namespace app
