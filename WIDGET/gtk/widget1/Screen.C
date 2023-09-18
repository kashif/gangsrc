/* GANG Software
 * WIDGET/gtk/widget1/Screen.C
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

#include "Screen.H"

namespace gtk {
namespace widget1 {

Screen::
Screen()
    :
    gtk::widget0::DrawingArea(),
    _gc(0)
{
}

Screen::
~Screen()
{
}

void
Screen::
draw_point(
  PointInt const &p,
  Color256 const &c)
{
  DIE_IF( GTK_WIDGET(w())->window == 0 );

  if ( _gc == 0 )
  {
    _gc = gdk_gc_new( GTK_WIDGET(w())->window );
    DIE_IF(_gc == 0);
  }

  GdkColor color;
  color.red   = 256 * c.red;
  color.green = 256 * c.green;
  color.blue  = 256 * c.blue;

  color.pixel = (gulong)( (c.red << 16) + (c.green << 8) + c.blue );

  gdk_color_alloc(
    gtk_widget_get_colormap( GTK_WIDGET(w()) ), &color);

  gdk_gc_set_foreground( _gc, &color );

  gdk_draw_point( GTK_WIDGET(w())->window,
                  _gc, p.x, p.y );
}

} // namespace widget1
} // namespace gtk
