/* GANG Software
 * WIDGET/gtk/widget0/Window.C
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

#include <iostream>
#include "base/System.H"
#include "Window.H"

namespace gtk {
namespace widget0 {

void
Window::
_show()
{
#if !defined(__sgi)
  if ( type() == GTK_WINDOW_TOPLEVEL && w()->window )
  {
    gint x, y;
    gdk_window_get_deskrelative_origin( w()->window, &x, &y );
    set_uposition( x, y );
  }
#endif
  Widget::show();
}

} // namespace gtk
} // namespace widget0
