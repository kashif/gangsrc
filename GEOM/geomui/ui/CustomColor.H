/* GANG Software
 * GEOM/geomui/ui/CustomColor.H
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

#ifndef geomui_ui_CustomColor_INCLUDED
#define geomui_ui_CustomColor_INCLUDED

#include "base/Color4.H"
#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Float.H"
#include "widget/ui/Int.H"
#include "widget/ui/FloatSet.H"
#include "widget/ui/IntSet.H"
#include "widget/ui/Choice.H"
#include "geom/interface/Surface.H"

namespace geomui {
namespace ui {

class CustomColor
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  CustomColor();

  // destructor
  virtual ~CustomColor();

  // interface
  virtual void customcolor_reset();
  virtual void customcolor_select( uint id );
  virtual void customcolor_original(
    base::Color4 const &c );
  virtual void customcolor_by_normal(
    base::Color4 const &c );
  virtual void customcolor_by_gaussian_curvature(
    base::Color4 const &c, float scale );
  virtual void customcolor_by_mean_curvature(
    base::Color4 const &c, float scale );
  virtual void customcolor_by_area(
    base::Color4 const &c, float scale );
  virtual void customcolor_by_direction(
    base::Color4 const &c );
  virtual void customcolor_by_distance(
    base::Color4 const &c, float scale );
  virtual void customcolor_randomly(
    base::Color4 const &c );
  virtual void customcolor_checked(
    base::Color4 const &c1, base::Color4 const &c2 );
  virtual void customcolor_fade(
    base::ArrayX<float,2U> const &a );
  virtual void customcolor_prev();
  virtual void customcolor_next();
  //
  virtual void customcolor_synchronize();

  // set the color of the geomobject to the current custom color choice
  void synchronize_color_choice() 
   { color_choice_cb(); }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void color_choice_cb();
  virtual void color0_cb()
    { customcolor_set_color0(); refresh_all(); }
  virtual void color1_cb()
    { customcolor_set_color1(); refresh_all(); }
  virtual void color2_cb()
    { customcolor_set_color2(); refresh_all(); }
  virtual void color3_cb()
    { customcolor_set_color3(); refresh_all(); }
  virtual void color4_cb()
    { customcolor_set_color4(); refresh_all(); }
  virtual void color5_cb()
    { customcolor_set_color5(); refresh_all(); }
  virtual void color6_cb()
    { customcolor_set_color6(); refresh_all(); }
  virtual void color7_cb()
    { customcolor_set_color7(); refresh_all(); }
  virtual void color8_cb()
    { customcolor_set_color8(); refresh_all(); }
  virtual void color9_cb()
    { customcolor_set_color9(); refresh_all(); }
  virtual void color_reset0_cb();
  virtual void color_reset1_cb();
  virtual void color_reset2_cb();
  virtual void color_reset3_cb();
  virtual void color_reset4_cb();
  virtual void color_reset5_cb();
  virtual void color_reset6_cb();
  virtual void color_reset7_cb();
  virtual void color_reset8_cb();
  virtual void color_reset9_cb();

  char const *label() const
    { return "Custom Color"; }

private:

  // pure virtuals
  virtual geom::Surface *geomlist() = 0;
  virtual geom::Surface const *geomlist() const = 0;
  virtual void refresh_all() = 0;
  virtual void material_custom_color(uint id, bool x) = 0;

  virtual void customcolor_set_color0();
  virtual void customcolor_set_color1();
  virtual void customcolor_set_color2();
  virtual void customcolor_set_color3();
  virtual void customcolor_set_color4();
  virtual void customcolor_set_color5();
  virtual void customcolor_set_color6();
  virtual void customcolor_set_color7();
  virtual void customcolor_set_color8();
  virtual void customcolor_set_color9();

  // widgets
  virtual widget::ui::Choice   *color_choice_w() = 0;
  virtual widget::ui::FloatSet *color0_w() = 0;
  virtual widget::ui::FloatSet *color1_w() = 0;
  virtual widget::ui::FloatSet *color2_w() = 0;
  virtual widget::ui::Float    *scale2_w() = 0;
  virtual widget::ui::FloatSet *color3_w() = 0;
  virtual widget::ui::Float    *scale3_w() = 0;
  virtual widget::ui::FloatSet *color4_w() = 0;
  virtual widget::ui::Float    *scale4_w() = 0;
  virtual widget::ui::FloatSet *color5_w() = 0;
  virtual widget::ui::FloatSet *color6_w() = 0;
  virtual widget::ui::Float    *scale6_w() = 0;
  virtual widget::ui::FloatSet *color7_w() = 0;
  virtual widget::ui::FloatSet *color8a_w() = 0;
  virtual widget::ui::FloatSet *color8b_w() = 0;
  virtual widget::ui::FloatSet *color9_w() = 0;


  static base::Color4 const color_surface_default_orig;
  static base::Color4 const color_surface_default;
  static float const scale_default;

  // disabled copy constructor
  CustomColor( CustomColor const & );
  // disabled assignment operator
  CustomColor &operator=( CustomColor const & );

};

} // namespace ui
} // namespace geomui

#endif // geomui_ui_CustomColor_INCLUDED
