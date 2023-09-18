/* GANG Software
 * GEOM/geomui/cmd/MaterialSet.H
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

#ifndef geomui_cmd_MaterialSet_INCLUDED
#define geomui_cmd_MaterialSet_INCLUDED

#include "widget/cmd/Boolean.H"
#include "widget/cmd/Choice.H"
#include "widget/cmd/Float.H"
#include "widget/cmd/FloatSet.H"
#include "geomui/ui/MaterialSet.H"

namespace geomui {
namespace cmd {

class MaterialSet
  :
    virtual public geomui::ui::MaterialSet
{

public:
  // constructor
  MaterialSet();

  // destructor
  virtual ~MaterialSet();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::Choice   *id_w()
    { return &_id_w; }
  virtual widget::ui::Boolean  *enable_w()
    { return &_enable_w; }
  virtual widget::ui::FloatSet *color_w()
    { return &_color_w; }
  virtual widget::ui::FloatSet *ambient_w()
    { return &_ambient_w; }
  virtual widget::ui::FloatSet *diffuse_w()
    { return &_diffuse_w; }
  virtual widget::ui::FloatSet *specular_w()
    { return &_specular_w; }
  virtual widget::ui::FloatSet *emissive_w()
    { return &_emissive_w; }
  virtual widget::ui::Float    *shininess_w()
    { return &_shininess_w; }
  virtual widget::ui::Choice   *model_w()
    { return &_model_w; }
  virtual widget::ui::Boolean  *lit_w()
    { return &_lit_w; }
  virtual widget::ui::Boolean  *transparent_w()
    { return &_transparent_w; }
  virtual widget::ui::FloatSet *gap_w()
    { return &_gap_w; }
  virtual widget::ui::FloatSet *nudge_w()
    { return &_nudge_w; }
  virtual widget::ui::Choice   *side0_w()
    { return &_side0_w; }
  virtual widget::ui::Choice   *side1_w()
    { return &_side1_w; }
  virtual widget::ui::Boolean  *custom_color_w()
    { return &_custom_color_w; }
  virtual widget::ui::Boolean  *shademodel_w()
    { return &_shademodel_w; }
  virtual widget::ui::Float    *element_size_w()
    { return &_element_size_w; }
  virtual widget::ui::Widget    *hidebox_w()
    { return &_hidebox_w; }

  // widgets
  widget::cmd::Choice _id_w;
  widget::cmd::Boolean _enable_w;
  widget::cmd::FloatSet _color_w;
  widget::cmd::FloatSet _ambient_w;
  widget::cmd::FloatSet _diffuse_w;
  widget::cmd::FloatSet _specular_w;
  widget::cmd::FloatSet _emissive_w;
  widget::cmd::Float _shininess_w;
  widget::cmd::Choice _model_w;
  widget::cmd::Boolean _lit_w;
  widget::cmd::Boolean _transparent_w;
  widget::cmd::FloatSet _gap_w;
  widget::cmd::FloatSet _nudge_w;
  widget::cmd::Choice _side0_w;
  widget::cmd::Choice _side1_w;
  widget::cmd::Boolean _custom_color_w;
  widget::cmd::Boolean _shademodel_w;
  widget::cmd::Float _element_size_w;
  widget::cmd::Widget _hidebox_w;

  // disabled copy constructor
  MaterialSet( MaterialSet const & );
  // disabled assignment operator
  MaterialSet &operator=( MaterialSet const & );

};

} // namespace cmd
} // namespace geomui

#endif // geomui_cmd_MaterialSet_INCLUDED
