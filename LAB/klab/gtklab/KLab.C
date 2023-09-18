/* GANG Software
 * LAB/klab/gtklab/KLab.C
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

#include "KLab.H"

namespace klab {
namespace gtklab {

KLab::
KLab()
    :
    ::klab::kernel::Lab(),
    ::klab::gtk::Ui(lab_name()),
    isight::IsightBaseGtk()
{
  // set the "replace" button to true
  replace_geomobject(true);
  geomobject_inherit_materials(true);
}

KLab::
~KLab()
{
}

void
KLab::
hide_all()
{
  ::klab::ui::Ui::show_all(false);
  isight::IsightBaseGtk::hide_all();
}

void
KLab::
enable_tooltips(bool state)
{
  ::klab::ui::Ui::enable_tooltips(state);
  isight::IsightBaseGtk::enable_tooltips(state);
}


bool
KLab::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  return
    lab::ui::Ui::command( command, argument, response ) ||
    klab::ui::Ui::command( command, argument, response ) ||
    isight::IsightBaseGtk::command( command, argument, response );
}

} // namespace gtklab
} // namespace klab
