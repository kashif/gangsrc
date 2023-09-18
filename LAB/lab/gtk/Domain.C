/* GANG Software
 * LAB/lab/gtk/Domain.C
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

#include "Domain.H"

namespace lab {
namespace gtk {

Domain::
Domain(char const *title)
    :
    ui::Domain(),
    gtk::Domain_(),
    ::app::app::Dialog( title, label(), main_widget() )
{
  // set the packing on the triangulation page to expand
  _domain_choice_w->set_packing( 2, 1, 1, 0, GTK_PACK_START);

  // set the packing on the curve page to expand
  _domain_choice_w->set_packing( 3, 1, 1, 0, GTK_PACK_START);
}

Domain::
~Domain()
{
}

} // namespace gtk
} // namespace lab
