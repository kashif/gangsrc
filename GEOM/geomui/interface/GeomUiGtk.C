/* GANG Software
 * GEOM/geomui/interface/GeomUiGtk.C
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

#include "geomui/gtk/Ui.H"
#include "GeomUiGtk.H"

namespace geomui {

class _GeomUiGtk
  :
    public geomui::gtk::Ui
{
public:
  _GeomUiGtk( char const *label, GeomUiGtk *parent) :
      geomui::gtk::Ui(label), _parent(parent) {}
protected:
  virtual int key_press_event_d( uint key, uint state )
    { return _parent->key_press_event_d( key, state ); }
  virtual geom::Surface *geomlist()
    { return _parent->surface(); }
  virtual geom::Surface const *geomlist() const
    { return _parent->surface(); }
  virtual void refresh_all()
    { return _parent->refresh(); }
private:
  GeomUiGtk *_parent;
  friend class GeomUiGtk;
};

GeomUiGtk::
GeomUiGtk( char const *label )
    :
    _(new _GeomUiGtk(label, this))
{
}

GeomUiGtk::
~GeomUiGtk()
{
  delete _;
}

void
GeomUiGtk::
_hide_all()
{
  _->show_all(false);
}

void
GeomUiGtk::
_enable_tooltips(bool state)
{
  _->geomui::ui::Ui::enable_tooltips(state);
}

bool
GeomUiGtk::
_command( base::String const &command, base::String const &argment, base::String &response )
{
  return _->command( command, argment, response );
}

void
GeomUiGtk::
synchronize()
{
  _->synchronize();
}

void
GeomUiGtk::
build_toggle_raise_show()
{
  static_cast< geomui::ui::Build *>(_)->toggle_raise_show_d();
}

void
GeomUiGtk::
customcolor_toggle_raise_show()
{
  static_cast< geomui::ui::CustomColor *>(_)->toggle_raise_show_d();
}

void
GeomUiGtk::
materialset_toggle_raise_show()
{
  static_cast< geomui::ui::MaterialSet *>(_)->toggle_raise_show_d();
}

void
GeomUiGtk::
meshclip_toggle_raise_show()
{
  static_cast< geomui::ui::MeshClip *>(_)->toggle_raise_show_d();
}

void
GeomUiGtk::
statistics_toggle_raise_show()
{
  static_cast< geomui::ui::Statistics *>(_)->toggle_raise_show_d();
}

void
GeomUiGtk::
statistics_synchronize()
{
  _->statistics_synchronize();
}

void
GeomUiGtk::
build_reset()
{
  _->build_reset();
}

void
GeomUiGtk::
reflect_plane_reset()
{
  _->reflect_plane_reset();
}

void
GeomUiGtk::
reflect_plane( base::ArrayX<float,4U> const &x )
{
  _->reflect_plane( x );
}

void
GeomUiGtk::
reflect_coord_plane0()
{
  _->reflect_coord_plane0();
}

void
GeomUiGtk::
reflect_coord_plane1()
{
  _->reflect_coord_plane1();
}

void
GeomUiGtk::
reflect_coord_plane2()
{
  _->reflect_coord_plane2();
}

void
GeomUiGtk::
meshclip_reset()
{
  _->meshclip_reset();
}

void
GeomUiGtk::
meshclip_i( base::ArrayX<uint,2U> const &x )
{
  _->meshclip_i( x );
}

void
GeomUiGtk::
meshclip_j( base::ArrayX<uint,2U> const &x )
{
  _->meshclip_j( x );
}

void
GeomUiGtk::
meshclip_roll_i( float const &x )
{
  _->meshclip_roll_i( x );
}

void
GeomUiGtk::
meshclip_roll_j( float const &x )
{
  _->meshclip_roll_j( x );
}

void
GeomUiGtk::
customcolor_reset()
{
  _->customcolor_reset();
}

void
GeomUiGtk::
customcolor_select( uint id )
{
  _->customcolor_select( id );
}

void
GeomUiGtk::
customcolor_original( base::Color4 const &c )
{
  _->customcolor_original( c );
}

void
GeomUiGtk::
customcolor_by_normal( base::Color4 const &c )
{
  _->customcolor_by_normal( c );
}

void
GeomUiGtk::
customcolor_by_gaussian_curvature( base::Color4 const &c, float scale )
{
  _->customcolor_by_gaussian_curvature( c, scale );
}

void
GeomUiGtk::
customcolor_by_mean_curvature( base::Color4 const &c, float scale )
{
  _->customcolor_by_mean_curvature( c, scale );
}

void
GeomUiGtk::
customcolor_by_area( base::Color4 const &c, float scale )
{
  _->customcolor_by_area( c, scale );
}

void
GeomUiGtk::
customcolor_by_direction( base::Color4 const &c )
{
  _->customcolor_by_direction( c );
}

void
GeomUiGtk::
customcolor_by_distance( base::Color4 const &c, float scale )
{
  _->customcolor_by_distance( c, scale );
}

void
GeomUiGtk::
customcolor_randomly( base::Color4 const &c )
{
  _->customcolor_randomly( c );
}

void
GeomUiGtk::
customcolor_checked( base::Color4 const &c1, base::Color4 const &c2 )
{
  _->customcolor_checked( c1, c2 );
}

void
GeomUiGtk::
customcolor_fade( base::ArrayX<float,2U> const &a )
{
  _->customcolor_fade( a );
}

void
GeomUiGtk::
customcolor_prev()
{
  _->customcolor_prev();
}

void
GeomUiGtk::
customcolor_next()
{
  _->customcolor_next();
}

void
GeomUiGtk::
material_synchronize()
{
  _->material_synchronize();
}

void
GeomUiGtk::
material_reset()
{
  _->material_reset();
}

void
GeomUiGtk::
material_reset( uint id )
{
  _->material_reset( id );
}

void
GeomUiGtk::
material_enable( uint id, bool x )
{
  _->material_enable( id, x );
}

void
GeomUiGtk::
material_shademodel( uint id, bool x )
{
  _->material_shademodel( id, x );
}

void
GeomUiGtk::
material_model( uint id, uint x )
{
  _->material_model( id, x );
}

void
GeomUiGtk::
material_element_size( uint id, float x )
{
  _->material_element_size( id, x );
}

void
GeomUiGtk::
material_gap( uint id, base::ArrayX<float,2U> const &x )
{
  _->material_gap( id, x );
}

void
GeomUiGtk::
material_color( uint id, base::Color4 const &x )
{
  _->material_color( id, x );
}

void
GeomUiGtk::
material_ambient( uint id, base::Color3 const &x )
{
  _->material_ambient( id, x );
}

void
GeomUiGtk::
material_diffuse( uint id, base::Color4 const &x )
{
  _->material_diffuse( id, x );
}

void
GeomUiGtk::
material_specular( uint id, base::Color3 const &x )
{
  _->material_specular( id, x );
}

void
GeomUiGtk::
material_emissive( uint id, base::Color3 const &x )
{
  _->material_emissive( id, x );
}

void
GeomUiGtk::
material_shininess( uint id, float x )
{
  _->material_shininess( id, x );
}

void
GeomUiGtk::
material_side( uint id, base::ArrayX<uint,2U> const &x )
{
  _->material_side( id, x );
}

void
GeomUiGtk::
material_nudge( uint id, base::ArrayX<float,2U> const &x )
{
  _->material_nudge( id, x );
}

void
GeomUiGtk::
material_lit( uint id, bool x )
{
  _->material_lit( id, x );
}

void
GeomUiGtk::
material_transparent( uint id, bool x )
{
  _->material_transparent( id, x );
}

void
GeomUiGtk::
material_custom_color( uint id, bool x )
{
  _->material_custom_color( id, x );
}

void
GeomUiGtk::
material_shininess(uint x)
{
  _->material_shininess(x);
}

void
GeomUiGtk::
material_shininess_next()
{
  _->material_shininess_next();
}

void
GeomUiGtk::
material_shininess_prev()
{
  _->material_shininess_prev();
}

void
GeomUiGtk::
material_toggle_geomobject( uint n )
{
  _->material_toggle_geomobject( n );
}

void
GeomUiGtk::
material_toggle_faces()
{
  _->material_toggle_faces();
}

void
GeomUiGtk::
material_toggle_edges()
{
  _->material_toggle_edges();
}

void
GeomUiGtk::
material_toggle_vertices()
{
  _->material_toggle_vertices();
}

void
GeomUiGtk::
material_toggle_boundary()
{
  _->material_toggle_boundary();
}

void
GeomUiGtk::
material_toggle_silhouette()
{
  _->material_toggle_silhouette();
}

void
GeomUiGtk::
material_toggle_bbox()
{
  _->material_toggle_bbox();
}

void
GeomUiGtk::
material_toggle_shademodel( uint n )
{
  _->material_toggle_shademodel( n );
}

void
GeomUiGtk::
material_toggle_shademodel()
{
  _->material_toggle_shademodel();
}

void
GeomUiGtk::
material_toggle_transparent( uint n )
{
  _->material_toggle_transparent( n );
}

void
GeomUiGtk::
material_toggle_transparent()
{
  _->material_toggle_transparent();
}

void
GeomUiGtk::
material_toggle_mirror( uint n )
{
  _->material_toggle_mirror( n );
}

void
GeomUiGtk::
material_toggle_mirror()
{
  _->material_toggle_mirror();
}

void
GeomUiGtk::
controls( widget::ui::KeyBase &x )
{
  _->controls(x);
}

void
GeomUiGtk::
controls_win( widget::ui::KeyBase &x )
{
  _->controls_win(x);
}

} // namespace geomui
