/* GANG Software
 * VIEWER/isight/kernel/Viewer.H
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

#ifndef isight_kernel_Viewer_INCLUDED
#define isight_kernel_Viewer_INCLUDED

#include "io/Istream.H"
#include "motion/Common.H"
#include "Write.H"

namespace isight {
namespace kernel {

class Viewer
  :
    public Write
{

public:
  // constructor
  Viewer();

  // destructor
  virtual ~Viewer();

  // insert a Surface into the viewer
  virtual void insert_geomobject( geom::Surface const & );
  // insert a SurfaceGL into the viewer
  virtual void insert_geomobject( geom::SurfaceGL const & );

  // set the geometry of the viewer
  virtual void
  geometry_(
    motion::GeometryMode mode,
    motion::GeometryGroup group,
    uint dim );

  virtual void select_geomobject_( uint id );
  virtual void show_geomobject_( uint id, bool state );
  virtual void move_geomobject_( uint id, bool state );
  virtual void delete_geomobject_( uint id );

  virtual void new_window_();
  virtual void select_window_( uint id );
  virtual void show_window_( uint id, bool state )
    { context(id)->show(state); }
  virtual void delete_window_( uint id );

protected:
private:

  void _position();

  char const *viewer_name() const
    { return "iSight"; }

  virtual uint global_screen_width() = 0;
  virtual uint global_screen_height() = 0;

  void insert_geomobject( geom::SurfaceGL *g );

  bool _fade;

  // disabled copy constructor
  Viewer( Viewer const & );
  // disabled assignment operator
  Viewer &operator=( Viewer const & );

};

} // namespace kernel
} // namespace isight

#endif // isight_kernel_Viewer_INCLUDED
