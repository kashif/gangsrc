/* GANG Software
 * GEOM/geomui/cmd/MeshClip.H
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

#ifndef geomui_cmd_MeshClip_INCLUDED
#define geomui_cmd_MeshClip_INCLUDED

#include "widget/cmd/Widget.H"
#include "widget/cmd/Float.H"
#include "widget/cmd/IntSet.H"
#include "geomui/ui/MeshClip.H"

namespace geomui {
namespace cmd {

class MeshClip
  :
    virtual public geomui::ui::MeshClip
{

public:
  // constructor
  MeshClip();

  // destructor
  virtual ~MeshClip();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::Widget *meshclip_reset_w()
    { return &_meshclip_reset_w; }
  virtual widget::ui::IntSet *meshclip_i_w()
    { return &_meshclip_i_w; }
  virtual widget::ui::IntSet *meshclip_j_w()
    { return &_meshclip_j_w; }
  virtual widget::ui::Float *mesh_roll_i_w()
    { return &_mesh_roll_i_w; }
  virtual widget::ui::Float *mesh_roll_j_w()
    { return &_mesh_roll_j_w; }

  // widgets
  widget::cmd::Widget _meshclip_reset_w;
  widget::cmd::IntSet _meshclip_i_w;
  widget::cmd::IntSet _meshclip_j_w;
  widget::cmd::Float _mesh_roll_i_w;
  widget::cmd::Float _mesh_roll_j_w;

  // disabled copy constructor
  MeshClip( MeshClip const & );
  // disabled assignment operator
  MeshClip &operator=( MeshClip const & );

};

} // namespace cmd
} // namespace geomui

#endif // geomui_cmd_MeshClip_INCLUDED
