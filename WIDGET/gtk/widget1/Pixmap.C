/* GANG Software
 * WIDGET/gtk/widget1/Pixmap.C
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

#include "Pixmap.H"

namespace gtk {
namespace widget1 {

Pixmap::
Pixmap(
  char const * const *xpm,
  gtk::widget0::Window *window )
    :
    gtk::widget0::Misc( (GtkWidget *)0 )
{
  GdkBitmap *mask;
  GtkStyle *style = window->get_style();

  GdkPixmap *pixmap = gdk_pixmap_create_from_xpm_d(
    window->w()->window,
    &mask,
    &style->bg[GTK_STATE_NORMAL],
    (gchar **)xpm
    );

  _w = GTK_OBJECT(gtk_pixmap_new( pixmap, mask ));
  // NOTE: memory leak
}

} // namespace gtk
} // namespace widget1
