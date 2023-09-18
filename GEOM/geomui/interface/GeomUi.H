/* GANG Software
 * GEOM/geomui/interface/GeomUi.H
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

#ifndef geomui_GeomUi_INCLUDED
#define geomui_GeomUi_INCLUDED

#include "base/String.H"
#include "base/ArrayX.H"
#include "base/Color3.H"
#include "base/Color4.H"
#include "widget/ui/KeyBase.H"

namespace geom { class Surface; }

namespace geomui {

class GeomUi
{

public:

  virtual void _hide_all() = 0;
  virtual void _enable_tooltips(bool state) = 0;

  virtual bool _command( base::String const &command,
                        base::String const &argment,
                        base::String &response ) = 0;

  virtual void build_toggle_raise_show() = 0;
  virtual void customcolor_toggle_raise_show() = 0;
  virtual void materialset_toggle_raise_show() = 0;
  virtual void meshclip_toggle_raise_show() = 0;
  virtual void statistics_toggle_raise_show() = 0;

  // build
  virtual void build_reset() = 0;
  virtual void reflect_plane_reset() = 0;
  virtual void reflect_plane( base::ArrayX<float,4U> const &x ) = 0;
  virtual void reflect_coord_plane0() = 0;
  virtual void reflect_coord_plane1() = 0;
  virtual void reflect_coord_plane2() = 0;

  // meshclip
  virtual void meshclip_reset() = 0;
  virtual void meshclip_i( base::ArrayX<uint,2U> const &x ) = 0;
  virtual void meshclip_j( base::ArrayX<uint,2U> const &x ) = 0;
  virtual void meshclip_roll_i( float const &x ) = 0;
  virtual void meshclip_roll_j( float const &x ) = 0;

  // customcolor
  virtual void customcolor_reset() = 0;
  virtual void customcolor_select( uint id ) = 0;
  virtual void customcolor_original(
    base::Color4 const &c ) = 0;
  virtual void customcolor_by_normal(
    base::Color4 const &c ) = 0;
  virtual void customcolor_by_gaussian_curvature(
    base::Color4 const &c, float scale ) = 0;
  virtual void customcolor_by_mean_curvature(
    base::Color4 const &c, float scale ) = 0;
  virtual void customcolor_by_area(
    base::Color4 const &c, float scale ) = 0;
  virtual void customcolor_by_direction(
    base::Color4 const &c ) = 0;
  virtual void customcolor_by_distance(
    base::Color4 const &c, float scale ) = 0;
  virtual void customcolor_randomly(
    base::Color4 const &c ) = 0;
  virtual void customcolor_checked(
    base::Color4 const &c1, base::Color4 const &c2 ) = 0;
  virtual void customcolor_fade(
    base::ArrayX<float,2U> const &a ) = 0;
  virtual void customcolor_prev() = 0;
  virtual void customcolor_next() = 0;

  // materials
  virtual void material_reset() = 0;
  virtual void material_reset( uint id ) = 0;
  virtual void material_enable( uint id, bool x ) = 0;
  virtual void material_shademodel( uint id, bool x ) = 0;
  virtual void material_model( uint id, uint x ) = 0;
  virtual void material_element_size( uint id, float x ) = 0;
  virtual void material_gap( uint id, base::ArrayX<float,2U> const &x ) = 0;
  virtual void material_color( uint id, base::Color4 const &x ) = 0;
  virtual void material_ambient( uint id, base::Color3 const &x ) = 0;
  virtual void material_diffuse( uint id, base::Color4 const &x ) = 0;
  virtual void material_specular( uint id, base::Color3 const &x ) = 0;
  virtual void material_emissive( uint id, base::Color3 const &x ) = 0;
  virtual void material_shininess( uint id, float x ) = 0;
  virtual void material_side( uint id, base::ArrayX<uint,2U> const &x ) = 0;
  virtual void material_nudge( uint id, base::ArrayX<float,2U> const &x ) = 0;
  virtual void material_lit( uint id, bool x ) = 0;
  virtual void material_transparent( uint id, bool x ) = 0;
  virtual void material_custom_color( uint id, bool x ) = 0;
  virtual void material_shininess(uint) = 0;
  virtual void material_shininess_next() = 0;
  virtual void material_shininess_prev() = 0;
  virtual void material_toggle_geomobject( uint n ) = 0;
  virtual void material_toggle_faces() = 0;
  virtual void material_toggle_edges() = 0;
  virtual void material_toggle_vertices() = 0;
  virtual void material_toggle_boundary() = 0;
  virtual void material_toggle_silhouette() = 0;
  virtual void material_toggle_bbox() = 0;
  virtual void material_toggle_shademodel( uint n ) = 0;
  virtual void material_toggle_shademodel() = 0;
  virtual void material_toggle_transparent( uint n ) = 0;
  virtual void material_toggle_transparent() = 0;
  virtual void material_toggle_mirror( uint n ) = 0;
  virtual void material_toggle_mirror() = 0;

  // synchronize the widgets with the current Surface
  virtual void synchronize() = 0;
  // statistics
  virtual void statistics_synchronize() = 0;
  // materials
  virtual void material_synchronize() = 0;

protected:
  
  virtual geom::Surface *surface() = 0;
  virtual geom::Surface const *surface() const = 0;
  virtual void refresh() = 0;

private:

};

} // namespace geomui

#endif // geomui_GeomUi_INCLUDED
