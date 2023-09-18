/* GANG Software
 * WIDGET/app/app/AppWindow.C
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

#include "AppWindow.H"

namespace app {
namespace app {

AppWindow::
AppWindow( ::gtk::widget0::Dialog *main_window )
    :
    exit_callback(this, &::app::app::AppWindow::exit)
{
  gtk_signal_connect(
    GTK_OBJECT(main_window->w()), "delete_event",
    GTK_SIGNAL_FUNC(delete_event_cb_), this );

  // note: may not work for sgi
  gtk_signal_connect(
    GTK_OBJECT(main_window->w()), "destroy",
    GTK_SIGNAL_FUNC(exit_callback.static_callback_fn),
    &exit_callback );
}

AppWindow::
~AppWindow()
{
}

gint
AppWindow::
delete_event_cb()
{
  // called when this window is closed
  exit();
  return 1;
}

gint
AppWindow::
delete_event_cb_( GtkWidget *, GdkEvent *, gpointer p )
{
  return static_cast<AppWindow *>(p)->delete_event_cb();
}

} // namespace app
} // namespace app
