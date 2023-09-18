/* GANG Software
 * GEOM/geomui/ui/Ui.C
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

#include "base/Regex.H"
#include "Ui.H"

namespace geomui {
namespace ui {

Ui::
Ui()
  :
    Build(),
    MaterialSet(),
    CustomColor(),
    MeshClip(),
    Statistics()
{
}

Ui::
~Ui()
{
}

bool
Ui::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  return
    _build()->command( command, argument, response ) ||
    _customcolor()->command( command, argument, response ) ||
    _materialset()->command( command, argument, response ) ||
    _meshclip()->command( command, argument, response ) ||
    _statistics()->command( command, argument, response );
}

void
Ui::
show_all(bool state)
{
  _build()->show_d(state);
  _customcolor()->show_d(state);
  _materialset()->show_d(state);
  _meshclip()->show_d(state);
  _statistics()->show_d(state);
}

void
Ui::
enable_tooltips( bool state )
{
  _build()->enable_tooltips_d(state);
  _customcolor()->enable_tooltips_d(state);
  _materialset()->enable_tooltips_d(state);
  _meshclip()->enable_tooltips_d(state);
  _statistics()->enable_tooltips_d(state);
}

void
Ui::
reset()
{
  Build::build_reset();
  CustomColor::customcolor_reset();
  MaterialSet::material_reset();
  MeshClip::meshclip_reset();
  Statistics::statistics_reset();
}

void
Ui::
synchronize()
{
  Build::build_synchronize();
  CustomColor::customcolor_synchronize();
  MaterialSet::material_synchronize();
  MeshClip::meshclip_synchronize();
  Statistics::statistics_synchronize();
}

void
Ui::
controls( ::widget::ui::KeyBase &p )
{
  // CTRL-b = Build Widget
  p.insert(
    "Construct...",   GDK_b, MOD_CTRL,
    this,
    &::geomui::ui::Ui::build_toggle_raise_show );

  // CTRL-t = Statistics Widget
  p.insert(
    "Statistics...",  GDK_t, MOD_CTRL,
    this,
    &::geomui::ui::Ui::statistics_toggle_raise_show );

  // ALT-h = Mesh Clip Widget
  p.insert(
    "Mesh Clip...",   GDK_h, MOD_ALT,
    this,
    &::geomui::ui::Ui::meshclip_toggle_raise_show );

  // ALT-m = Materials Widget
  p.insert(
    "Materials...",   GDK_m, MOD_ALT,
    this,
    &::geomui::ui::Ui::materialset_toggle_raise_show );

  // ALT-k = Custom Color Widget
  p.insert(
    "Custom Color...",  GDK_k, MOD_ALT,
    this,
    &::geomui::ui::Ui::customcolor_toggle_raise_show );
}

void
Ui::
controls_win( ::widget::ui::KeyBase &p )
{
  // f = Toggle Faces
  p.insert(
    "Toggle faces", GDK_f, MOD_NONE,
    _materialset(),
    &::geomui::ui::MaterialSet::material_toggle_faces );

  // e = Toggle Edges
  p.insert(
    "Toggle edges", GDK_e, MOD_NONE,
    _materialset(),
    &::geomui::ui::MaterialSet::material_toggle_edges );

  // v = Toggle Vertices
  p.insert(
    "Toggle vertices", GDK_v, MOD_NONE,
    _materialset(),
    &::geomui::ui::MaterialSet::material_toggle_vertices );

  // u = Toggle Boundary
  p.insert(
    "Toggle boundary", GDK_u, MOD_NONE,
    _materialset(),
    &::geomui::ui::MaterialSet::material_toggle_boundary );

  // x = Toggle Bounding Box
  p.insert(
    "Toggle bbox", GDK_x, MOD_NONE,
    _materialset(),
    &::geomui::ui::MaterialSet::material_toggle_bbox );

  // o = Toggle Silhouette
  p.insert(
    "Toggle sihouette", GDK_o, MOD_NONE,
    _materialset(),
    &::geomui::ui::MaterialSet::material_toggle_silhouette );

  // j = Toggle Smooth
  p.insert(
    "Toggle shademodel", GDK_j, MOD_NONE,
    _materialset(),
    &::geomui::ui::MaterialSet::material_toggle_shademodel );

  // t = Toggle Transparent
  p.insert(
    "Toggle transparent", GDK_t, MOD_NONE,
    _materialset(),
    &::geomui::ui::MaterialSet::material_toggle_transparent );

  // m = Cycle Two-way Mirror
  p.insert(
    "Toggle mirror", GDK_m, MOD_NONE,
    _materialset(),
    &::geomui::ui::MaterialSet::material_toggle_mirror );

  // k = Next Custom Color
  p.insert(
    "color next", GDK_k, MOD_NONE,
    _customcolor(),
    &::geomui::ui::CustomColor::customcolor_next );

  // K = Previous Custom Color
  p.insert(
    "color prev", GDK_K, MOD_SHIFT,
    _customcolor(),
    &::geomui::ui::CustomColor::customcolor_prev );

  // h = Cycle Shininess
  p.insert(
    "Cycle shininess", GDK_h, MOD_NONE,
    _materialset(),
    &::geomui::ui::MaterialSet::material_shininess_next );

  // H = Cycle Shininess
  p.insert(
    "Cycle shininess", GDK_H, MOD_SHIFT,
    _materialset(),
    &::geomui::ui::MaterialSet::material_shininess_prev );
}

} // namespace ui
} // namespace geomui
