/* GANG Software
 * WIDGET/gtk/widget1/ButtonBar.C
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

#include "ButtonBar.H"

namespace gtk {
namespace widget1 {

ButtonBar::
ButtonBar(
  uint value,
  char const *text[],
  uint rows,
  uint cols )
    :
    gtk::widget0::Widget( gtk_button_bar_new( rows, cols ) )
{
  // set before connecting the signal to prevent a callback
  gtk_button_bar_set_labels( GTK_BUTTON_BAR(_w), text );
  gtk_button_bar_set( GTK_BUTTON_BAR(_w), value);
}

} // namespace gtk
} // namespace widget1
