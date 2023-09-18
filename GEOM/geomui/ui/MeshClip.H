/* GANG Software
 * GEOM/geomui/ui/MeshClip.H
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

#ifndef geomui_ui_MeshClip_INCLUDED
#define geomui_ui_MeshClip_INCLUDED

#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Float.H"
#include "widget/ui/IntSet.H"
#include "geom/interface/Surface.H"

namespace geomui {
namespace ui {

class MeshClip
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  MeshClip();

  // destructor
  virtual ~MeshClip();

  // interface
  virtual void meshclip_i( base::ArrayX<uint,2U> const &x );
  virtual void meshclip_j( base::ArrayX<uint,2U> const &x );
  virtual void meshclip_roll_i( float const &x );
  virtual void meshclip_roll_j( float const &x );
  virtual void meshclip_synchronize();
  virtual void meshclip_reset()
    { meshclip_synchronize(); }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void meshclip_cb();
  virtual void mesh_roll_cb();
  virtual void meshclip_reset_cb();

  char const *label()
    { return "Mesh Clip"; }

private:

  // pure virtuals
  virtual geom::Surface *geomlist() = 0;
  virtual geom::Surface const *geomlist() const = 0;
  virtual void refresh_all() = 0;

  // widgets
  virtual widget::ui::Widget *meshclip_reset_w() = 0;
  virtual widget::ui::IntSet *meshclip_i_w() = 0;
  virtual widget::ui::IntSet *meshclip_j_w() = 0;
  virtual widget::ui::Float  *mesh_roll_i_w() = 0;
  virtual widget::ui::Float  *mesh_roll_j_w() = 0;

  bool is_grid() const;

  // disabled copy constructor
  MeshClip( MeshClip const & );
  // disabled assignment operator
  MeshClip &operator=( MeshClip const & );

};

} // namespace ui
} // namespace geomui

#endif // geomui_ui_MeshClip_INCLUDED
