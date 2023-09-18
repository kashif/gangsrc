/* GANG Software
 * GEOM/geomui/ui/MaterialSet.H
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

#ifndef geomui_ui_MaterialSet_INCLUDED
#define geomui_ui_MaterialSet_INCLUDED

#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Choice.H"
#include "widget/ui/Boolean.H"
#include "widget/ui/Float.H"
#include "widget/ui/FloatSet.H"
#include "widget/ui/IntSet.H"
#include "geom/interface/Surface.H"

namespace geomui {
namespace ui {

class MaterialSet
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  MaterialSet();

  // destructor
  virtual ~MaterialSet();

  // implementation
  virtual void material_reset();
  virtual void material_reset(uint id);
  virtual void material_enable(uint id, bool a);
  virtual void material_model( uint id, uint a )
    { _model( id, a ); }
  virtual void material_side( uint id, base::ArrayX<uint,2U> const &a );
  virtual void material_element_size( uint id, float a );
  virtual void material_color( uint id, base::Color4 const &a );
  virtual void material_ambient( uint id, base::Color3 const &a );
  virtual void material_diffuse( uint id, base::Color4 const &a );
  virtual void material_specular( uint id, base::Color3 const &a );
  virtual void material_emissive( uint id, base::Color3 const &a );
  virtual void material_shininess( uint id, float a );
  virtual void material_shademodel( uint id, bool a );
  virtual void material_nudge( uint id, base::ArrayX<float,2U> const &a );
  virtual void material_transparent( uint id, bool a );
  virtual void material_custom_color( uint id, bool a );
  virtual void material_gap( uint id, base::ArrayX<float,2U> const &a );
  virtual void material_lit( uint id, bool a );

  virtual void material_shininess(uint);
  virtual void material_shininess_next();
  virtual void material_shininess_prev();

  virtual void material_toggle_geomobject( uint n );
  virtual void material_toggle_faces()
    { material_toggle_geomobject(0); }
  virtual void material_toggle_edges()
    { material_toggle_geomobject(1); }
  virtual void material_toggle_vertices()
    { material_toggle_geomobject(2); }
  virtual void material_toggle_boundary()
    { material_toggle_geomobject( geom::BOUNDARY ); }
  virtual void material_toggle_silhouette()
    { material_toggle_geomobject( geom::SILHOUETTE ); }
  virtual void material_toggle_bbox()
    { material_toggle_geomobject( geom::BBOX ); }

  virtual void material_toggle_shademodel( uint n );
  virtual void material_toggle_shademodel()
    { material_toggle_shademodel(0); }

  virtual void material_toggle_transparent( uint n );
  virtual void material_toggle_transparent()
    { material_toggle_transparent(0); }

  virtual void material_toggle_mirror( uint n );
  virtual void material_toggle_mirror()
    { material_toggle_mirror(0); }

  //
  virtual void material_synchronize()
    { 
      set_ui_from_data( id_w()->get(), *geomlist() );
    }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void reset_cb();
  virtual void id_cb()
    { material_synchronize(); }
  virtual void enable_cb()
    { _enable( id_w()->get(), enable_w()->get() ); }
  virtual void transparent_cb()
    { _transparent( id_w()->get(), transparent_w()->get() ); }
  virtual void shademodel_cb()
    { _transparent( id_w()->get(), shademodel_w()->get() ); }
  virtual void element_size_cb();
  virtual void gap_cb();
  virtual void side_cb();
  virtual void nudge_cb();
  virtual void reset_color_cb();
  virtual void custom_color_cb()
    { _custom_color( id_w()->get(), custom_color_w()->get() ); }
  virtual void lit_cb()
    { _lit( id_w()->get(), lit_w()->get() ); }
  virtual void model_cb()
    { _model( id_w()->get(), model_w()->get() ); }
  virtual void color_cb();
  virtual void ambient_cb();
  virtual void diffuse_cb();
  virtual void specular_cb();
  virtual void emissive_cb();
  virtual void shininess_cb()
    { _shininess( id_w()->get(), shininess_w()->get() ); }

  char const *label() const
    { return "MaterialSet"; }

private:

  // pure virtuals
  virtual geom::Surface *geomlist() = 0;
  virtual geom::Surface const *geomlist() const = 0;
  virtual void refresh_all() = 0;

  // widgets
  virtual widget::ui::Choice   *id_w() = 0;
  virtual widget::ui::Boolean  *enable_w() = 0;
  virtual widget::ui::FloatSet *color_w() = 0;
  virtual widget::ui::FloatSet *ambient_w() = 0;
  virtual widget::ui::FloatSet *diffuse_w() = 0;
  virtual widget::ui::FloatSet *specular_w() = 0;
  virtual widget::ui::FloatSet *emissive_w() = 0;
  virtual widget::ui::Float    *shininess_w() = 0;
  virtual widget::ui::Choice   *model_w() = 0;
  virtual widget::ui::Boolean  *lit_w() = 0;
  virtual widget::ui::Boolean  *transparent_w() = 0;
  virtual widget::ui::FloatSet *gap_w() = 0;
  virtual widget::ui::FloatSet *nudge_w() = 0;
  virtual widget::ui::Choice   *side0_w() = 0;
  virtual widget::ui::Choice   *side1_w() = 0;
  virtual widget::ui::Boolean  *custom_color_w() = 0;
  virtual widget::ui::Boolean  *shademodel_w() = 0;
  virtual widget::ui::Float    *element_size_w() = 0;
  virtual widget::ui::Widget   *hidebox_w() = 0;

  // implementation
  void _enable(uint id, bool state);
  void _model( uint material, uint model );
  void _transparent( uint id, bool state );
  void _shademodel( uint id, bool state );
  void _gap( uint id, base::ArrayX<float,2U> const &a );
  void _side( uint id, base::ArrayX<uint,2U> const &a );
  void _lit( uint id, bool state );
  void _nudge( uint id, base::ArrayX<float,2U> const &a );
  void _color( uint id, base::Color4 const &a );
  void _custom_color( uint id, bool state );
  void _ambient( uint id, base::Color3 const &a );
  void _diffuse( uint a, base::Color4 const &a );
  void _specular( uint id, base::Color3 const &a );
  void _emissive( uint id, base::Color3 const &a );
  void _shininess( uint id, float state );
  void _element_size( uint id, float a );

  // utility
  void set_ui_from_data( uint id, geom::Surface const &m );
  void set_data_from_ui( uint id, geom::Surface &m );
  void set_color_widgets();
  void set_model_widgets();

  uint _shininess_;

  struct ShininessVal {
    float specular;
    float shininess;
  };

  static uint const SHININESS_COUNT = 5U;
  static ShininessVal const _shininess_val[SHININESS_COUNT];

  // disabled copy constructor
  MaterialSet( MaterialSet const & );
  // disabled assignment operator
  MaterialSet &operator=( MaterialSet const & );

};

} // namespace ui
} // namespace geomui

#endif // geomui_ui_MaterialSet_INCLUDED
