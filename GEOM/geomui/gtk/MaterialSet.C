/* GANG Software
 * GEOM/geomui/gtk/MaterialSet.C
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

#include "MaterialSet.H"

namespace geomui {
namespace gtk {

MaterialSet::
MaterialSet(char const *title)
    :
    ui::MaterialSet(),
    gtk::MaterialSet_(),
    ::app::app::Dialog( title, label(), main_widget() )
{

/*
THIS HAS BEEN FIXED (by changing signal name from "toggled" to "toggled0"
in gtk_buttonbar

BUG FIX
insert the line

  new ::gtk::ToggleButtonCb<MaterialSet_>(
    "enable", 0, this, &MaterialSet_::enable_cb );

in MaterialSet_::MaterialSet_()
in MaterialSet_.C
before the construction of any ButtonBarCb
*/

  _color_w->show(false);
  _hidebox_w->show(true);
}

MaterialSet::
~MaterialSet()
{
}


} // namespace gtk
} // namespace geomui
