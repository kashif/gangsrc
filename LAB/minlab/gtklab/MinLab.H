/* GANG Software
 * LAB/minlab/gtklab/MinLab.H
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

#ifndef minlab_gtklab_MinLab_INCLUDED
#define minlab_gtklab_MinLab_INCLUDED

#include "minlab/gtk/Ui.H"
#include "minlab/kernel/Lab.H"
#include "isight/interface/IsightBaseGtk.H"
#include "lab/gtklab/Lab.H"

namespace minlab {
namespace gtklab {

class MinLab
  :
    public kernel::Lab,
    public gtk::Ui,
    public isight::IsightBaseGtk
{

public:
  // constructor
  MinLab();

  // destructor
  virtual ~MinLab();

  static char const *app_name()
    { return "minlab"; }

protected:

  virtual bool
  command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

  void toggle_raise_show_controls()
    { static_cast< ::minlab::ui::Controls *>(this)->toggle_raise_show_d(); }

  // show/hide all dialog boxes
  virtual void hide_all();
  // enable/disable help balloons
  virtual void enable_tooltips( bool state );

private:

  virtual void export_object_v( geom::Surface const &surf )
    { isight::IsightBaseGtk::insert_geomobject(surf); }
  virtual void write_surface( geom::Surface const &surf,
                              base::String const &filename )
    { isight::IsightBaseGtk::write( filename ); }

  // disabled copy constructor
  MinLab( MinLab const & );

  // disabled assignment operator
  MinLab &operator=( MinLab const & );
};

} // namespace gtklab
} // namespace minlab

#endif // minlab_gtklab_MinLab_INCLUDED
