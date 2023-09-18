/* GANG Software
 * GEOM/geomui/ui/Ui.H
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

#ifndef geomui_ui_Ui_INCLUDED
#define geomui_ui_Ui_INCLUDED

#include "widget/ui/KeyBase.H"
#include "Build.H"
#include "CustomColor.H"
#include "MaterialSet.H"
#include "MeshClip.H"
#include "Statistics.H"

namespace geomui {
namespace ui {

class Ui
  :
    virtual protected Build,
    virtual protected MaterialSet,
    virtual protected CustomColor,
    virtual protected MeshClip,
    virtual protected Statistics
{

public:
  Ui();

  virtual ~Ui();

  void show_all(bool state);
  void enable_tooltips( bool state );
  void synchronize();
  void reset();

#if 0
  virtual void customcolor_reset()
    { CustomColor::customcolor_reset(); }
  virtual void customcolor_select( uint id )
    { CustomColor::customcolor_select(id); }
  virtual void customcolor_original(
    base::Color4 const &c )
    { CustomColor::customcolor_original(c); }
  virtual void customcolor_by_normal(
    base::Color4 const &c )
    { CustomColor::customcolor_by_normal(c); }
  virtual void customcolor_by_gaussian_curvature(
    base::Color4 const &c, float scale )
    { CustomColor::customcolor_by_gaussian_curvature(c, scale); }
  virtual void customcolor_by_mean_curvature(
    base::Color4 const &c, float scale )
    { CustomColor::customcolor_by_mean_curvature(c, scale); }
  virtual void customcolor_by_area(
    base::Color4 const &c, float scale )
    { CustomColor::customcolor_by_area(c, scale); }
  virtual void customcolor_by_direction(
    base::Color4 const &c )
    { CustomColor::customcolor_by_direction(c); }
  virtual void customcolor_by_distance(
    base::Color4 const &c, float scale )
    { CustomColor::customcolor_by_distance(c, scale); }
  virtual void customcolor_randomly(
    base::Color4 const &c )
    { CustomColor::customcolor_randomly(c); }
  virtual void customcolor_checked(
    base::Color4 const &c1, base::Color4 const &c2 )
    { CustomColor::customcolor_checked(c1, c2); }
  virtual void customcolor_fade(
    base::ArrayX<float,2U> const &c )
    { CustomColor::customcolor_fade(c); }
  virtual void customcolor_prev()
    { CustomColor::customcolor_prev(); }
  virtual void customcolor_next()
    { CustomColor::customcolor_next(); }

  // build
  virtual void build_reset()
    { Build::build_reset(); }
  virtual void reflect_plane_reset()
    { Build::reflect_plane_reset(); }
  virtual void reflect_plane( base::ArrayX<float,4U> const &x )
    { Build::reflect_plane(x); }
  virtual void reflect_coord_plane0()
    { Build::reflect_coord_plane0(); }
  virtual void reflect_coord_plane1()
    { Build::reflect_coord_plane1(); }
  virtual void reflect_coord_plane2()
    { Build::reflect_coord_plane2(); }

  // meshclip
  virtual void meshclip_reset()
    { MeshClip::meshclip_reset(); }
  virtual void meshclip_i( base::ArrayX<uint,2U> const &x )
    { MeshClip::meshclip_i(x); }
  virtual void meshclip_j( base::ArrayX<uint,2U> const &x )
    { MeshClip::meshclip_j(x); }
  virtual void meshclip_roll_i( float const &x )
    { MeshClip::meshclip_roll_i(x); }
  virtual void meshclip_roll_j( float const &x )
    { MeshClip::meshclip_roll_j(x); }

  // materials
  virtual void material_reset()
    { MaterialSet::material_reset(); }
  virtual void material_reset( uint id )
    { MaterialSet::material_reset(id); }
  virtual void material_enable( uint id, bool x )
    { MaterialSet::material_enable(id, x); }
  virtual void material_shademodel( uint id, bool x )
    { MaterialSet::material_shademodel(id, x); }
  virtual void material_model( uint id, uint x )
    { MaterialSet::material_model(id, x); }
  virtual void material_element_size( uint id, float x )
    { MaterialSet::material_element_size(id, x); }
  virtual void material_gap( uint id, base::ArrayX<float,2U> const &x )
    { MaterialSet::material_gap(id, x); }
  virtual void material_color( uint id, base::Color4 const &x )
    { MaterialSet::material_color(id, x); }
  virtual void material_ambient( uint id, base::Color3 const &x )
    { MaterialSet::material_ambient(id, x); }
  virtual void material_diffuse( uint id, base::Color4 const &x )
    { MaterialSet::material_diffuse(id, x); }
  virtual void material_specular( uint id, base::Color3 const &x )
    { MaterialSet::material_specular(id, x); }
  virtual void material_emissive( uint id, base::Color3 const &x )
    { MaterialSet::material_emissive(id, x); }
  virtual void material_shininess( uint id, float x )
    { MaterialSet::material_shininess(id, x); }
  virtual void material_side( uint id, base::ArrayX<uint,2U> const &x )
    { MaterialSet::material_side(id, x); }
  virtual void material_nudge( uint id, base::ArrayX<float,2U> const &x )
    { MaterialSet::material_nudge(id, x); }
  virtual void material_lit( uint id, bool x )
    { MaterialSet::material_lit(id, x); }
  virtual void material_transparent( uint id, bool x )
    { MaterialSet::material_transparent(id, x); }
  virtual void material_custom_color( uint id, bool x )
    { MaterialSet::material_custom_color(id, x); }

  virtual void material_shininess(uint x)
    { MaterialSet::material_shininess(x); }
  virtual void material_shininess_next()
    { MaterialSet::material_shininess_next(); }
  virtual void material_shininess_prev()
    { MaterialSet::material_shininess_prev(); }

  virtual void material_toggle_geomobject( uint n )
    { MaterialSet::material_toggle_geomobject(n); }
  virtual void material_toggle_faces()
    { MaterialSet::material_toggle_faces(); }
  virtual void material_toggle_edges()
    { MaterialSet::material_toggle_edges(); }
  virtual void material_toggle_vertices()
    { MaterialSet::material_toggle_vertices(); }
  virtual void material_toggle_boundary()
    { MaterialSet::material_toggle_boundary(); }
  virtual void material_toggle_silhouette()
    { MaterialSet::material_toggle_silhouette(); }
  virtual void material_toggle_bbox()
    { MaterialSet::material_toggle_bbox(); }

  virtual void material_toggle_shademodel( uint n )
    { MaterialSet::material_toggle_shademodel(n); }
  virtual void material_toggle_shademodel()
    { MaterialSet::material_toggle_shademodel(); }

  virtual void material_toggle_transparent( uint n )
    { MaterialSet::material_toggle_transparent(n); }
  virtual void material_toggle_transparent()
    { MaterialSet::material_toggle_transparent(); }

  virtual void material_toggle_mirror( uint n )
    { MaterialSet::material_toggle_mirror(n); }
  virtual void material_toggle_mirror()
    { MaterialSet::material_toggle_mirror(); }
#endif

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

  virtual void material_synchronize()
    { MaterialSet::material_synchronize(); }
  virtual void customcolor_synchronize()
    { CustomColor::customcolor_synchronize(); }
  virtual void statistics_synchronize()
    { Statistics::statistics_synchronize(); }

protected:

  void controls( ::widget::ui::KeyBase &p );
  void controls_win( ::widget::ui::KeyBase &p );

private:

  void build_toggle_raise_show()
    { _build()->toggle_raise_show_d(); }
  void materialset_toggle_raise_show()
    { _materialset()->toggle_raise_show_d(); }
  void customcolor_toggle_raise_show()
    { _customcolor()->toggle_raise_show_d(); }
  void meshclip_toggle_raise_show()
    { _meshclip()->toggle_raise_show_d(); }
  void statistics_toggle_raise_show()
    { _statistics()->toggle_raise_show_d(); }

  Build *_build() { return this; }
  MaterialSet *_materialset() { return this; }
  CustomColor *_customcolor() { return this; }
  MeshClip *_meshclip() { return this; }
  Statistics *_statistics() { return this; }

  // disabled copy constructor
  Ui( Ui const & );

  // disabled assignment operator
  Ui &operator=( Ui const & );
};

} // namespace ui
} // namespace geomui

#endif // geomui_ui_Ui_INCLUDED
