/* GANG Software
 * GEOM/geomui/interface/GeomUiCmd.C
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

#include "geomui/cmd/Ui.H"
#include "GeomUiCmd.H"

namespace geomui {

class _GeomUiCmd
  :
    public geomui::cmd::Ui
{
public:
  _GeomUiCmd( GeomUiCmd *parent) : _parent(parent) {}
protected:
  virtual geom::Surface *geomlist()
    { return _parent->surface(); }
  virtual geom::Surface const *geomlist() const
    { return _parent->surface(); }
  virtual void refresh_all()
    { return _parent->refresh(); }
private:
  GeomUiCmd *_parent;
  friend class GeomUiCmd;
};

GeomUiCmd::
GeomUiCmd()
    :
    _(new _GeomUiCmd(this))
{
}

GeomUiCmd::
~GeomUiCmd()
{
  delete _;
}

void
GeomUiCmd::
_hide_all()
{
  _->show_all(false);
}

void
GeomUiCmd::
_enable_tooltips(bool state)
{
  _->enable_tooltips(state);
}

bool
GeomUiCmd::
_command( base::String const &command, base::String const &argment, base::String &response )
{
  return _->command( command, argment, response );
}

void
GeomUiCmd::
synchronize()
{
  _->synchronize();
}

void
GeomUiCmd::
build_toggle_raise_show()
{
  static_cast< geomui::ui::Build *>(_)->toggle_raise_show_d();
}

void
GeomUiCmd::
customcolor_toggle_raise_show()
{
  static_cast< geomui::ui::CustomColor *>(_)->toggle_raise_show_d();
}

void
GeomUiCmd::
materialset_toggle_raise_show()
{
  static_cast< geomui::ui::MaterialSet *>(_)->toggle_raise_show_d();
}

void
GeomUiCmd::
meshclip_toggle_raise_show()
{
  static_cast< geomui::ui::MeshClip *>(_)->toggle_raise_show_d();
}

void
GeomUiCmd::
statistics_toggle_raise_show()
{
  static_cast< geomui::ui::Statistics *>(_)->toggle_raise_show_d();
}

void
GeomUiCmd::
statistics_synchronize()
{
  _->statistics_synchronize();
}

void
GeomUiCmd::
build_reset()
{
  _->build_reset();
}

void
GeomUiCmd::
reflect_plane_reset()
{
  _->reflect_plane_reset();
}

void
GeomUiCmd::
reflect_plane( base::ArrayX<float,4U> const &x )
{
  _->reflect_plane( x );
}

void
GeomUiCmd::
reflect_coord_plane0()
{
  _->reflect_coord_plane0();
}

void
GeomUiCmd::
reflect_coord_plane1()
{
  _->reflect_coord_plane1();
}

void
GeomUiCmd::
reflect_coord_plane2()
{
  _->reflect_coord_plane2();
}

void
GeomUiCmd::
meshclip_reset()
{
  _->meshclip_reset();
}

void
GeomUiCmd::
meshclip_i( base::ArrayX<uint,2U> const &x )
{
  _->meshclip_i( x );
}

void
GeomUiCmd::
meshclip_j( base::ArrayX<uint,2U> const &x )
{
  _->meshclip_j( x );
}

void
GeomUiCmd::
meshclip_roll_i( float const &x )
{
  _->meshclip_roll_i( x );
}

void
GeomUiCmd::
meshclip_roll_j( float const &x )
{
  _->meshclip_roll_j( x );
}

void
GeomUiCmd::
customcolor_reset()
{
  _->customcolor_reset();
}

void
GeomUiCmd::
customcolor_select( uint id )
{
  _->customcolor_select( id );
}

void
GeomUiCmd::
customcolor_original( base::Color4 const &c )
{
  _->customcolor_original( c );
}

void
GeomUiCmd::
customcolor_by_normal( base::Color4 const &c )
{
  _->customcolor_by_normal( c );
}

void
GeomUiCmd::
customcolor_by_gaussian_curvature( base::Color4 const &c, float scale )
{
  _->customcolor_by_gaussian_curvature( c, scale );
}

void
GeomUiCmd::
customcolor_by_mean_curvature( base::Color4 const &c, float scale )
{
  _->customcolor_by_mean_curvature( c, scale );
}

void
GeomUiCmd::
customcolor_by_area( base::Color4 const &c, float scale )
{
  _->customcolor_by_area( c, scale );
}

void
GeomUiCmd::
customcolor_by_direction( base::Color4 const &c )
{
  _->customcolor_by_direction( c );
}

void
GeomUiCmd::
customcolor_by_distance( base::Color4 const &c, float scale )
{
  _->customcolor_by_distance( c, scale );
}

void
GeomUiCmd::
customcolor_randomly( base::Color4 const &c )
{
  _->customcolor_randomly( c );
}

void
GeomUiCmd::
customcolor_checked( base::Color4 const &c1, base::Color4 const &c2 )
{
  _->customcolor_checked( c1, c2 );
}

void
GeomUiCmd::
customcolor_fade( base::ArrayX<float,2U> const &a )
{
  _->customcolor_fade( a );
}

void
GeomUiCmd::
customcolor_prev()
{
  _->customcolor_prev();
}

void
GeomUiCmd::
customcolor_next()
{
  _->customcolor_next();
}

void
GeomUiCmd::
material_synchronize()
{
  _->material_synchronize();
}

void
GeomUiCmd::
material_reset()
{
  _->material_reset();
}

void
GeomUiCmd::
material_reset( uint id )
{
  _->material_reset( id );
}

void
GeomUiCmd::
material_enable( uint id, bool x )
{
  _->material_enable( id, x );
}

void
GeomUiCmd::
material_shademodel( uint id, bool x )
{
  _->material_shademodel( id, x );
}

void
GeomUiCmd::
material_model( uint id, uint x )
{
  _->material_model( id, x );
}

void
GeomUiCmd::
material_element_size( uint id, float x )
{
  _->material_element_size( id, x );
}

void
GeomUiCmd::
material_gap( uint id, base::ArrayX<float,2U> const &x )
{
  _->material_gap( id, x );
}

void
GeomUiCmd::
material_color( uint id, base::Color4 const &x )
{
  _->material_color( id, x );
}

void
GeomUiCmd::
material_ambient( uint id, base::Color3 const &x )
{
  _->material_ambient( id, x );
}

void
GeomUiCmd::
material_diffuse( uint id, base::Color4 const &x )
{
  _->material_diffuse( id, x );
}

void
GeomUiCmd::
material_specular( uint id, base::Color3 const &x )
{
  _->material_specular( id, x );
}

void
GeomUiCmd::
material_emissive( uint id, base::Color3 const &x )
{
  _->material_emissive( id, x );
}

void
GeomUiCmd::
material_shininess( uint id, float x )
{
  _->material_shininess( id, x );
}

void
GeomUiCmd::
material_side( uint id, base::ArrayX<uint,2U> const &x )
{
  _->material_side( id, x );
}

void
GeomUiCmd::
material_nudge( uint id, base::ArrayX<float,2U> const &x )
{
  _->material_nudge( id, x );
}

void
GeomUiCmd::
material_lit( uint id, bool x )
{
  _->material_lit( id, x );
}

void
GeomUiCmd::
material_transparent( uint id, bool x )
{
  _->material_transparent( id, x );
}

void
GeomUiCmd::
material_custom_color( uint id, bool x )
{
  _->material_custom_color( id, x );
}

void
GeomUiCmd::
material_shininess(uint x)
{
  _->material_shininess(x);
}

void
GeomUiCmd::
material_shininess_next()
{
  _->material_shininess_next();
}

void
GeomUiCmd::
material_shininess_prev()
{
  _->material_shininess_prev();
}

void
GeomUiCmd::
material_toggle_geomobject( uint n )
{
  _->material_toggle_geomobject( n );
}

void
GeomUiCmd::
material_toggle_faces()
{
  _->material_toggle_faces();
}

void
GeomUiCmd::
material_toggle_edges()
{
  _->material_toggle_edges();
}

void
GeomUiCmd::
material_toggle_vertices()
{
  _->material_toggle_vertices();
}

void
GeomUiCmd::
material_toggle_boundary()
{
  _->material_toggle_boundary();
}

void
GeomUiCmd::
material_toggle_silhouette()
{
  _->material_toggle_silhouette();
}

void
GeomUiCmd::
material_toggle_bbox()
{
  _->material_toggle_bbox();
}

void
GeomUiCmd::
material_toggle_shademodel( uint n )
{
  _->material_toggle_shademodel( n );
}

void
GeomUiCmd::
material_toggle_shademodel()
{
  _->material_toggle_shademodel();
}

void
GeomUiCmd::
material_toggle_transparent( uint n )
{
  _->material_toggle_transparent( n );
}

void
GeomUiCmd::
material_toggle_transparent()
{
  _->material_toggle_transparent();
}

void
GeomUiCmd::
material_toggle_mirror( uint n )
{
  _->material_toggle_mirror( n );
}

void
GeomUiCmd::
material_toggle_mirror()
{
  _->material_toggle_mirror();
}

void
GeomUiCmd::
controls( widget::ui::KeyBase &x )
{
  _->controls(x);
}

void
GeomUiCmd::
controls_win( widget::ui::KeyBase &x )
{
  _->controls_win(x);
}

} // namespace geomui
