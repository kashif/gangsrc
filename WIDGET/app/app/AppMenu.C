/* GANG Software
 * WIDGET/app/app/AppMenu.C
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
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkmenuitem.h>
#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#endif

#include "base/System.H"
#include "AppMenu.H"

namespace app {
namespace app {

AppMenu::
AppMenu(
  char const *app_name )
    :
    ::gtk::widget0::Dialog()
{
  // window sizing policies: allow_shrink, allow_grow, auto_shrink
  set_policy( false, true, true );

  hide();

  ::gtk::widget0::Window::set_title(app_name);

  _vbox_w = new ::gtk::widget0::VBox( false, 0 );
  _vbox_w->show(true);
  add( _vbox_w );

//  show();
}

AppMenu::
~AppMenu()
{
  delete _vbox_w;
//  delete _accelgroup;
}

void
AppMenu::
insert_menu(
  ::gtk::widget1::Menu &menu )
{
  add_accel_group( menu.accelerator() );

  // put menu into vbox
  _vbox_w->add( &menu, true, true, 0 );

  menu.show(true);

#if 0
  if ( g_slist_find(_accelgroup->w()->attach_objects,
                    GTK_OBJECT(GTK_WINDOW(_window_w->w()))) != (GSList *)0 )
  {
    gtk_window_add_accel_group(
      GTK_WINDOW(_window_w->w()), _accelgroup->w() );
  }
#endif

#if 0
  _accelgroup->add(_window_w);
#endif

#if 0
  gtk_accel_group_attach(_accelgroup->w(), GTK_OBJECT(_window_w->w()));
#endif
}

void
AppMenu::
raise_show()
{
  ::gtk::widget0::Window::show(true);
  ::gtk::widget0::Window::raise();
}

} // namespace app
} // namespace app
