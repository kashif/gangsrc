/* GANG Software
 * GEOM/geomui/gtk/MaterialSet.H
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

#ifndef geomui_gtk_MaterialSet_INCLUDED
#define geomui_gtk_MaterialSet_INCLUDED

#include "app/app/Dialog.H"
#include "geomui/ui/MaterialSet.H"
#include "MaterialSet_.H"

namespace geomui {
namespace gtk {

class MaterialSet
  :
    virtual public ui::MaterialSet,
    protected gtk::MaterialSet_,
    public ::app::app::Dialog
{

public:
  // constructor
  MaterialSet(char const *title);

  // destructor
  virtual ~MaterialSet();

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
    { MaterialSet_::enable_tooltips(state); }

  // widgets
  virtual widget::ui::Choice   *id_w()
    { return _id_w; }
  virtual widget::ui::Boolean  *enable_w()
    { return _enable_w; }
  virtual widget::ui::FloatSet *color_w()
    { return _color_w; }
  virtual widget::ui::FloatSet *ambient_w()
    { return _ambient_w; }
  virtual widget::ui::FloatSet *diffuse_w()
    { return _diffuse_w; }
  virtual widget::ui::FloatSet *specular_w()
    { return _specular_w; }
  virtual widget::ui::FloatSet *emissive_w()
    { return _emissive_w; }
  virtual widget::ui::Float    *shininess_w()
    { return _shininess_w; }
  virtual widget::ui::Choice   *model_w()
    { return _model_w; }
  virtual widget::ui::Boolean  *lit_w()
    { return _lit_w; }
  virtual widget::ui::Boolean  *transparent_w()
    { return _transparent_w; }
  virtual widget::ui::FloatSet *gap_w()
    { return _gap_w; }
  virtual widget::ui::FloatSet *nudge_w()
    { return _nudge_w; }
  virtual widget::ui::Choice   *side0_w()
    { return _side0_w; }
  virtual widget::ui::Choice   *side1_w()
    { return _side1_w; }
  virtual widget::ui::Boolean  *custom_color_w()
    { return _custom_color_w; }
  virtual widget::ui::Boolean  *shademodel_w()
    { return _shademodel_w; }
  virtual widget::ui::Float    *element_size_w()
    { return _element_size_w; }
  virtual widget::ui::Widget    *hidebox_w()
    { return _hidebox_w; }

  // callbacks
  virtual void id_cb()
    { ui::MaterialSet::id_cb(); }
  virtual void enable_cb()
    { ui::MaterialSet::enable_cb(); }
  virtual void transparent_cb()
    { ui::MaterialSet::transparent_cb(); }
  virtual void reset_cb()
    { ui::MaterialSet::reset_cb(); }
  virtual void shademodel_cb()
    { ui::MaterialSet::shademodel_cb(); }
  virtual void element_size_cb()
    { ui::MaterialSet::element_size_cb(); }
  virtual void gap_cb()
    { ui::MaterialSet::gap_cb(); }
  virtual void side_cb()
    { ui::MaterialSet::side_cb(); }
  virtual void nudge_cb()
    { ui::MaterialSet::nudge_cb(); }

  virtual void reset_color_cb()
    { ui::MaterialSet::reset_color_cb(); }
  virtual void custom_color_cb()
    { ui::MaterialSet::custom_color_cb(); }
  virtual void lit_cb()
    { ui::MaterialSet::lit_cb(); }
  virtual void model_cb()
    { ui::MaterialSet::model_cb(); }
  virtual void color_cb()
    { ui::MaterialSet::color_cb(); }
  virtual void ambient_cb()
    { ui::MaterialSet::ambient_cb(); }
  virtual void diffuse_cb()
    { ui::MaterialSet::diffuse_cb(); }
  virtual void specular_cb()
    { ui::MaterialSet::specular_cb(); }
  virtual void emissive_cb()
    { ui::MaterialSet::emissive_cb(); }
  virtual void shininess_cb()
    { ui::MaterialSet::shininess_cb(); }

  // disabled copy constructor
  MaterialSet( MaterialSet const & );

  // disabled assignment operator
  MaterialSet &operator=( MaterialSet const & );

};

} // namespace gtk
} // namespace geomui

#endif // geomui_gtk_MaterialSet_INCLUDED
