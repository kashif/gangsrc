/* GANG Software
 * GEOM/geomui/cmd/Ui.H
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

#ifndef geomui_cmd_Ui_INCLUDED
#define geomui_cmd_Ui_INCLUDED

#include "geomui/ui/Ui.H"
#include "Build.H"
#include "MaterialSet.H"
#include "CustomColor.H"
#include "MeshClip.H"
#include "Statistics.H"

namespace geomui {
namespace cmd {

class Ui
  :
    public ui::Ui,
    public Build,
    public MaterialSet,
    public CustomColor,
    public MeshClip,
    public Statistics
{

public:
  // constructor
  Ui();

  // destructor
  virtual ~Ui();

  virtual void statistics_synchronize()
    { Statistics::statistics_synchronize(); }

  virtual void material_custom_color(uint id, bool x)
    { material_custom_color(id, x); }

protected:

private:

  // disabled copy constructor
  Ui( Ui const & );
  // disabled assignment operator
  Ui &operator=( Ui const & );

};

} // namespace cmd
} // namespace geomui

#endif // geomui_cmd_Ui_INCLUDED
