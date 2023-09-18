/* GANG Software
 * GEOM/geomui/interface/GeomUiCmd.H
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

#ifndef geomui_GeomUiCmd_INCLUDED
#define geomui_GeomUiCmd_INCLUDED

#include "GeomUi.H"

namespace geomui {

class _GeomUiCmd;

class GeomUiCmd
  :
    virtual public GeomUi
{

public:
  // constructor
  GeomUiCmd();

  // destructor
  virtual ~GeomUiCmd();

  void _hide_all();
  void _enable_tooltips(bool state);

  bool _command( base::String const &command,
                        base::String const &argment,
                        base::String &response );

  void build_toggle_raise_show();
  void customcolor_toggle_raise_show();
  void materialset_toggle_raise_show();
  void meshclip_toggle_raise_show();
  void statistics_toggle_raise_show();

  // build
  void build_reset();
  void reflect_plane_reset();
  void reflect_plane( base::ArrayX<float,4U> const &x );
  void reflect_coord_plane0();
  void reflect_coord_plane1();
  void reflect_coord_plane2();

  // meshclip
  void meshclip_reset();
  void meshclip_i( base::ArrayX<uint,2U> const &x );
  void meshclip_j( base::ArrayX<uint,2U> const &x );
  void meshclip_roll_i( float const &x );
  void meshclip_roll_j( float const &x );

  // customcolor
  void customcolor_reset();
  void customcolor_select( uint id );
  void customcolor_original(
    base::Color4 const &c );
  void customcolor_by_normal(
    base::Color4 const &c );
  void customcolor_by_gaussian_curvature(
    base::Color4 const &c, float scale );
  void customcolor_by_mean_curvature(
    base::Color4 const &c, float scale );
  void customcolor_by_area(
    base::Color4 const &c, float scale );
  void customcolor_by_direction(
    base::Color4 const &c );
  void customcolor_by_distance(
    base::Color4 const &c, float scale );
  void customcolor_randomly(
    base::Color4 const &c );
  void customcolor_checked(
    base::Color4 const &c1, base::Color4 const &c2 );
  void customcolor_fade(
    base::ArrayX<float,2U> const &a );
  void customcolor_prev();
  void customcolor_next();

  // materials
  void material_reset();
  void material_reset( uint id );
  void material_enable( uint id, bool x );
  void material_shademodel( uint id, bool x );
  void material_model( uint id, uint x );
  void material_element_size( uint id, float x );
  void material_gap( uint id, base::ArrayX<float,2U> const &x );
  void material_color( uint id, base::Color4 const &x );
  void material_ambient( uint id, base::Color3 const &x );
  void material_diffuse( uint id, base::Color4 const &x );
  void material_specular( uint id, base::Color3 const &x );
  void material_emissive( uint id, base::Color3 const &x );
  void material_shininess( uint id, float x );
  void material_side( uint id, base::ArrayX<uint,2U> const &x );
  void material_nudge( uint id, base::ArrayX<float,2U> const &x );
  void material_lit( uint id, bool x );
  void material_transparent( uint id, bool x );
  void material_custom_color( uint id, bool x );
  void material_shininess(uint);
  void material_shininess_next();
  void material_shininess_prev();
  void material_toggle_geomobject( uint n );
  void material_toggle_faces();
  void material_toggle_edges();
  void material_toggle_vertices();
  void material_toggle_boundary();
  void material_toggle_silhouette();
  void material_toggle_bbox();
  void material_toggle_shademodel( uint n );
  void material_toggle_shademodel();
  void material_toggle_transparent( uint n );
  void material_toggle_transparent();
  void material_toggle_mirror( uint n );
  void material_toggle_mirror();


  // synchronize the widgets with the current Surface
  void synchronize();
  void statistics_synchronize();
  void material_synchronize();

protected:

  virtual void controls( widget::ui::KeyBase &);
  virtual void controls_win( widget::ui::KeyBase &);

private:

  _GeomUiCmd *_;

  // disabled copy constructor
  GeomUiCmd( GeomUiCmd const & );
  // disabled assignment operator
  GeomUiCmd &operator=( GeomUiCmd const & );

  friend class _GeomUiCmd;
};

} // namespace geomui

#endif // geomui_GeomUiCmd_INCLUDED
