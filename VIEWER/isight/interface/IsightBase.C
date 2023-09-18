/* GANG Software
 * VIEWER/isight/interface/IsightBase.C
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

#include "IsightBase.H"

namespace isight {

IsightBase::
IsightBase()
    :
    geomui::GeomUi(),
    milieu::MilieuUi(),
    isightui::ViewerUi()
{
}

IsightBase::
~IsightBase()
{
}

void
IsightBase::
hide_all()
{
  _milieu_ui()->_hide_all();
  _geom_ui()->_hide_all();
  _viewer_ui()->_hide_all();
}

void
IsightBase::
enable_tooltips(bool state)
{
  _milieu_ui()->_enable_tooltips(state);
  _geom_ui()->_enable_tooltips(state);
  _viewer_ui()->_enable_tooltips(state);
}

bool
IsightBase::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  return
    _geom_ui()->_command( command, argument, response ) ||
    _milieu_ui()->_command( command, argument, response ) ||
    _viewer_ui()->_command( command, argument, response );
}

} // namespace isight
