/* GANG Software
 * GEOM/geomui/ui/Build.H
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

#ifndef geomui_ui_Build_INCLUDED
#define geomui_ui_Build_INCLUDED

#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/FloatSet.H"
#include "geom/interface/Surface.H"

namespace geomui {
namespace ui {

class Build
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:
  typedef geom::Real Real;

  // constructor
  Build();

  // destructor
  virtual ~Build();

  // interface
  virtual void build_reset()
    { build_reset_cb(); }
  virtual void reflect_plane_reset()
    { reflect_plane_reset(); }
  virtual void reflect_plane(
    base::ArrayX<float,4U> const &x)
    { reflect_plane_position_w()->set(x.data()); }
  virtual void reflect_coord_plane0()
    { reflect_coord_plane0_cb(); }
  virtual void reflect_coord_plane1()
    { reflect_coord_plane1_cb(); }
  virtual void reflect_coord_plane2()
    { reflect_coord_plane2_cb(); }
  virtual void build_synchronize() {}

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  void reflect_coord_plane( uint n );

  // callbacks
  virtual void build_reset_cb();
  virtual void reflect_plane_reset_cb();
  virtual void reflect_plane_apply_cb();
  virtual void reflect_coord_plane0_cb();
  virtual void reflect_coord_plane1_cb();
  virtual void reflect_coord_plane2_cb();

  char const *label() const
    { return "Construct"; }

private:

  // pure virtuals
  virtual geom::Surface *geomlist() = 0;
  virtual geom::Surface const *geomlist() const = 0;
  virtual void refresh_all() = 0;

  void reflect( math::VectorX<Real,4U> const &a );
  virtual void statistics_synchronize() = 0;

  // widgets
  virtual widget::ui::FloatSet *reflect_plane_position_w() = 0;

  // disabled constructor
  Build( Build const & );
  // disabled assignment operator
  Build &operator=( Build const & );

};

} // namespace ui
} // namespace geomui

#endif // geomui_ui_Build_INCLUDED
