/* GANG Software
 * GEOM/geomui/cmd/CustomColor.H
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

#ifndef geomui_cmd_CustomColor_INCLUDED
#define geomui_cmd_CustomColor_INCLUDED

#include "widget/cmd/Choice.H"
#include "widget/cmd/Float.H"
#include "widget/cmd/FloatSet.H"
#include "geomui/ui/CustomColor.H"

namespace geomui {
namespace cmd {

class CustomColor
  :
    virtual public geomui::ui::CustomColor
{

public:
  // constructor
  CustomColor();

  // destructor
  virtual ~CustomColor();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::Choice   *color_choice_w()
    { return &_color_choice_w; }
  virtual widget::ui::FloatSet *color0_w()
    { return &_color0_w; }
  virtual widget::ui::FloatSet *color1_w()
    { return &_color1_w; }
  virtual widget::ui::FloatSet *color2_w()
    { return &_color2_w; }
  virtual widget::ui::Float    *scale2_w()
    { return &_scale2_w; }
  virtual widget::ui::FloatSet *color3_w()
    { return &_color3_w; }
  virtual widget::ui::Float    *scale3_w()
    { return &_scale3_w; }
  virtual widget::ui::FloatSet *color4_w()
    { return &_color4_w; }
  virtual widget::ui::Float    *scale4_w()
    { return &_scale4_w; }
  virtual widget::ui::FloatSet *color5_w()
    { return &_color5_w; }
  virtual widget::ui::FloatSet *color6_w()
    { return &_color6_w; }
  virtual widget::ui::Float    *scale6_w()
    { return &_scale6_w; }
  virtual widget::ui::FloatSet *color7_w()
    { return &_color7_w; }
  virtual widget::ui::FloatSet *color8a_w()
    { return &_color8a_w; }
  virtual widget::ui::FloatSet *color8b_w()
    { return &_color8b_w; }
  virtual widget::ui::FloatSet *color9_w()
    { return &_color9_w; }

  // widgets
  widget::cmd::Choice _color_choice_w;
  widget::cmd::FloatSet _color0_w;
  widget::cmd::FloatSet _color1_w;
  widget::cmd::FloatSet _color2_w;
  widget::cmd::Float _scale2_w;
  widget::cmd::FloatSet _color3_w;
  widget::cmd::Float _scale3_w;
  widget::cmd::FloatSet _color4_w;
  widget::cmd::Float _scale4_w;
  widget::cmd::FloatSet _color5_w;
  widget::cmd::FloatSet _color6_w;
  widget::cmd::Float _scale6_w;
  widget::cmd::FloatSet _color7_w;
  widget::cmd::FloatSet _color8a_w;
  widget::cmd::FloatSet _color8b_w;
  widget::cmd::FloatSet _color9_w;

  // disabled copy constructor
  CustomColor( CustomColor const & );
  // disabled assignment operator
  CustomColor &operator=( CustomColor const & );

};

} // namespace cmd
} // namespace geomui

#endif // geomui_cmd_CustomColor_INCLUDED
