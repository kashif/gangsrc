/* GANG Software
 * LAB/cmclab/gtklab/CMCLab.C
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

#include "CMCLab.H"

namespace cmclab {
namespace gtklab {

CMCLab::
CMCLab()
    :
    ::cmclab::kernel::Lab(),
    ::cmclab::gtk::Ui(lab_name()),
    isight::IsightBaseGtk()
{
  // set the "replace" button to true
  replace_geomobject(true);
  geomobject_inherit_materials(true);
}

CMCLab::
~CMCLab()
{
}

void
CMCLab::
hide_all()
{
  ::cmclab::ui::Ui::show_all(false);
  isight::IsightBaseGtk::hide_all();
}

void
CMCLab::
enable_tooltips(bool state)
{
  ::cmclab::ui::Ui::enable_tooltips(state);
  isight::IsightBaseGtk::enable_tooltips(state);
}

void
CMCLab::
set_lambda_R3( Real lambda )
{
  // call baseclass version
  kernel::Lab::set_lambda_R3(lambda);
#if 0  
  // set the geometry of the viewer
  set_geometry( motion::PROJECTIVE, motion::PARABOLIC, 3U );
#endif
}

void
CMCLab::
set_lambda_S3( Real lambda0, Real lambda1 )
{
  // call baseclass version
  kernel::Lab::set_lambda_S3(lambda0, lambda1);
#if 0
  // set the geometry of the viewer
  set_geometry( motion::CONFORMAL, motion::ELLIPTIC, 3U );
#endif
}

void
CMCLab::
set_lambda_H3( Complex const &lambda )
{
  // call baseclass version
  kernel::Lab::set_lambda_H3(lambda);
#if 0  
  // set the geometry of the viewer
  set_geometry( motion::CONFORMAL, motion::HYPERBOLIC, 3U );
#endif
}

bool
CMCLab::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  return
    lab::ui::Ui::command( command, argument, response ) ||
    cmclab::ui::Ui::command( command, argument, response ) ||
    isight::IsightBaseGtk::command( command, argument, response );
}

} // namespace gtklab
} // namespace cmclab
