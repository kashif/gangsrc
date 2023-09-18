/* GANG Software
 * GEOM/geomui/gtk/MeshClip.C
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

#include "MeshClip.H"

namespace geomui {
namespace gtk {

MeshClip::
MeshClip(char const *title)
    :
    ui::MeshClip(),
    gtk::MeshClip_(),
    ::app::app::Dialog( title, label(), main_widget() )
{
  _meshclip_reset_w->set_sensitive(false);
  _meshclip_i_w->set_sensitive(false);
  _meshclip_j_w->set_sensitive(false);
  _mesh_roll_i_w->set_sensitive(false);
  _mesh_roll_j_w->set_sensitive(false);
}

MeshClip::
~MeshClip()
{
}

} // namespace gtk
} // namespace geomui
