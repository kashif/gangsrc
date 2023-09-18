/* GANG Software
 * WIDGET/gtk/widget1/FileSelection.C
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

#include "base/Regex.H"
#include "gtk/widgetc/gtk_filesel2.h"
#include "FileSelection.H"

namespace gtk {
namespace widget1 {

FileSelection::
FileSelection()
    :
    gtk::widget0::VBox( gtk_file_selection2_new() ),
    _button(0)
#if 0
    ,
    raise_show_callback(this, &gtk::widget0::FileSelection::raise_show_cb),
    toggle_raise_show_callback(
      this, &gtk::widget0::FileSelection::toggle_raise_show_cb)
#endif
{
  uint const DIR_LIST_WIDTH   = 140;
  uint const DIR_LIST_HEIGHT  = 180;
  uint const FILE_LIST_WIDTH  = 140;
  uint const FILE_LIST_HEIGHT = 180;

  // file read dialog
  GtkFileSelection2 *x = GTK_FILE_SELECTION2( w() );
  //gtk_window_position(GTK_WINDOW(x), GTK_WIN_POS_MOUSE);

  // compactify the file dialog box
  gtk_box_set_spacing(GTK_BOX(x->main_vbox), 0);
  gtk_container_set_border_width( GTK_CONTAINER(x->main_vbox), 0);
  gtk_widget_set_usize(
    GTK_WIDGET(x->dir_list), DIR_LIST_WIDTH, DIR_LIST_HEIGHT);
  gtk_widget_set_usize(
    GTK_WIDGET(x->file_list), FILE_LIST_WIDTH, FILE_LIST_HEIGHT);

#if 0
  // delete event (window closed by window manager)
  gtk_signal_connect(
    GTK_OBJECT( _w ),
    "delete_event",
    GTK_SIGNAL_FUNC(delete_event_cb_),
    (gpointer)this );
#endif

  // ok button callback
  gtk_signal_connect(
    GTK_OBJECT( x->ok_button ),
    "clicked",
    GTK_SIGNAL_FUNC(ok_cb_),
    (gpointer)this );

  // cancel button callback
  gtk_signal_connect(
    GTK_OBJECT( x->cancel_button ),
    "clicked",
    GTK_SIGNAL_FUNC(cancel_cb_),
    (gpointer)this );
}

void FileSelection::ok_cb()
{
//  char const *s = get();
//  if ( s == (char const *)0) { return; }
  _button = 1;
  callback();
}
void FileSelection::cancel_cb()
{
  _button = 0;
  callback();
}

#if 0
FileSelection::
~FileSelection()
{
  // destroy the dialogbox before writing because it looks better
  gtk_widget_destroy( GTK_WIDGET(_w) );
}
#endif

#if 0
void
FileSelection::
show(bool state)
{
  gtk::widget0::Widget::show(state);
  if (!state)
  {
    // force gtk to hide the window immediately
    while (g_main_iteration(FALSE));
  }
}
#endif

#if 0
gint FileSelection::delete_event_cb()
{
  show(false);
  return true; // don't delete window
}
#endif

#if 0
void
FileSelection::
raise_show_cb()
{
  raise_show();
}

void
FileSelection::
toggle_raise_show_cb()
{
  toggle_raise_show();
}
#endif

#if 0
gint FileSelection::delete_event_cb_(GtkWidget *, GdkEvent *, gpointer p )
{ return static_cast<FileSelection *>(p)->delete_event_cb(); }
#endif

} // namespace widget1
} // namespace gtk
