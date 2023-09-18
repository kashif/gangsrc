/* GANG Software
 * WIDGET/gtk/widget1/PopNotebook.C
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

#include "PopNotebook.H"

namespace gtk {
namespace widget1 {

#if 0

PopNotebook::
PopNotebook(
  uint value,
  char const *text[],
  uint count )
    :
    gtk::widget0::Widget( gtk_button_bar_new( count ) )
{
  // set before connecting the signal to prevent a callback
  gtk_button_bar_set_labels( GTK_BUTTON_BAR(_w), text );
  gtk_button_bar_set( GTK_BUTTON_BAR(_w), value);
}
#endif

void
PopNotebook::
add( gtk::widget0::Widget *w, char const *tab_label )
{
  // MEMORY LEAK
  add( w, new gtk::widget0::Label(tab_label) );
}

void
PopNotebook::
add( gtk::widget0::Widget *w, gtk::widget0::Label *l )
{
  gtk_popnotebook_add_with_label( GTK_POPNOTEBOOK(_w), w->w(), l->w() );
}

} // namespace gtk
} // namespace widget1
