/* GANG Software
 * LAB/lab/gtk/Compute.C
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

#include "Compute.H"

namespace lab {
namespace gtk {

Compute::
Compute(char const *title)
    :
    ui::Compute(),
    gtk::Compute_(),
    ::app::app::Dialog( title, label(), main_widget() )
{
  // set the widths of the time widgets
  _time0_w->set_usize(60, 0);
  _time1_w->set_usize(60, 0);

  // configure the progress bar
  _progressbar_w->format_string( "%v" );
  _progressbar_w->show_text( true );
}

Compute::
~Compute()
{
}

void
Compute::
grab_focus()
{
  // NOTE: this doesn't work
  _go_w->grab_focus();
}

} // namespace gtk
} // namespace lab
