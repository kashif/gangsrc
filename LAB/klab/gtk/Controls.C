/* GANG Software
 * LAB/klab/gtk/Controls.C
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

#include "Controls.H"

namespace klab {
namespace gtk {

Controls::
Controls( char const *title )
    :
    ui::Controls(),
    Controls_(),
    ::app::app::Dialog( title, label(), main_widget() )
{
  // set sizes
  _initial_x_w->usize(1, 80);
  _initial_y_w->usize(1, 80);
  _potential_x_w->usize(1, 80);
  _potential_y_w->usize(1, 80);
  _zstart_w->usize(60U, 0U);
  _polynomial_length_w->usize(60U, 0U);
  _initial_integrator_count_w->usize(60U, 0U);
  _integrator_count_w->usize(60U, 0U);

  _main_book_w->set_packing( 0, 1, 1, 0, GTK_PACK_START);
  _main_book_w->set_packing( 1, 1, 1, 0, GTK_PACK_START);
}

Controls::
~Controls()
{
}

} // namespace gtk
} // namespace klab
