/* GANG Software
 * GEOM/geomui/gtk/MeshClip.H
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

#ifndef geomui_gtk_MeshClip_INCLUDED
#define geomui_gtk_MeshClip_INCLUDED

#include "app/app/Dialog.H"
#include "geomui/ui/MeshClip.H"
#include "MeshClip_.H"

namespace geomui {
namespace gtk {

class MeshClip
  :
    virtual public ui::MeshClip,
    protected gtk::MeshClip_,
    public ::app::app::Dialog
{

public:
  // constructor
  MeshClip(char const *title);

  // destructor
  virtual ~MeshClip();

protected:

private:

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }
  virtual void enable_tooltips_d( bool state = true )
    { MeshClip_::enable_tooltips(state); }

  // widgets
  virtual widget::ui::Widget *meshclip_reset_w()
    { return _meshclip_reset_w; }
  virtual widget::ui::IntSet *meshclip_i_w()
    { return _meshclip_i_w; }
  virtual widget::ui::IntSet *meshclip_j_w()
    { return _meshclip_j_w; }
  virtual widget::ui::Float *mesh_roll_i_w()
    { return _mesh_roll_i_w; }
  virtual widget::ui::Float *mesh_roll_j_w()
    { return _mesh_roll_j_w; }

  // callbacks
  virtual void meshclip_cb()
    { ui::MeshClip::meshclip_cb(); }
  virtual void mesh_roll_cb()
    { ui::MeshClip::mesh_roll_cb(); }
  virtual void meshclip_reset_cb()
    { ui::MeshClip::meshclip_reset_cb(); }

  // disabled copy constructor
  MeshClip( MeshClip const & );

  // disabled assignment operator
  MeshClip &operator=( MeshClip const & );

};

} // namespace gtk
} // namespace geomui

#endif // geomui_gtk_MeshClip_INCLUDED
