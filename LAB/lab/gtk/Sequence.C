/* GANG Software
 * LAB/lab/gtk/Sequence.C
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

#include "Sequence.H"

namespace lab {
namespace gtk {

Sequence::
Sequence(char const *title)
    :
    ui::Sequence(),
    gtk::Sequence_(),
    ::app::app::Dialog( title, label(), main_widget() )
{
  _counter_varname_w->usize(60U, 0U);
  _time_varname_w->usize(60U, 0U);
  _function_w->usize(60U, 0U);
  _now_w->usize(60U, 0U);
  _filename_w->usize(60U, 0U);

  int const a[2] = { 0, 4 };
  _counter_w->set(a);
  _counter_varname_w->set("n");
  _time_varname_w->set("s");
  _function_w->set("n");
  _filename_w->set("image####.sgi");
}

Sequence::
~Sequence()
{
}

} // namespace gtk
} // namespace lab
