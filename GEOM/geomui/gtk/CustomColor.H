/* GANG Software
 * GEOM/geomui/gtk/CustomColor.H
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

#ifndef geomui_gtk_CustomColor_INCLUDED
#define geomui_gtk_CustomColor_INCLUDED

#include "app/app/Dialog.H"
#include "geomui/ui/CustomColor.H"
#include "CustomColor_.H"

namespace geomui {
namespace gtk {

class CustomColor
  :
    virtual public ui::CustomColor,
    protected gtk::CustomColor_,
    public ::app::app::Dialog
{

public:
  // constructor
  CustomColor(char const *title);

  // destructor
  virtual ~CustomColor();

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
    { CustomColor_::enable_tooltips(state); }

  // widgets
  virtual widget::ui::Choice   *color_choice_w()
    { return _color_choice_w; }
  virtual widget::ui::FloatSet *color0_w()
    { return _color0_w; }
  virtual widget::ui::FloatSet *color1_w()
    { return _color1_w; }
  virtual widget::ui::FloatSet *color2_w()
    { return _color2_w; }
  virtual widget::ui::Float    *scale2_w()
    { return _scale2_w; }
  virtual widget::ui::FloatSet *color3_w()
    { return _color3_w; }
  virtual widget::ui::Float    *scale3_w()
    { return _scale3_w; }
  virtual widget::ui::FloatSet *color4_w()
    { return _color4_w; }
  virtual widget::ui::Float    *scale4_w()
    { return _scale4_w; }
  virtual widget::ui::FloatSet *color5_w()
    { return _color5_w; }
  virtual widget::ui::FloatSet *color6_w()
    { return _color6_w; }
  virtual widget::ui::Float    *scale6_w()
    { return _scale6_w; }
  virtual widget::ui::FloatSet *color7_w()
    { return _color7_w; }
  virtual widget::ui::FloatSet *color8a_w()
    { return _color8a_w; }
  virtual widget::ui::FloatSet *color8b_w()
    { return _color8b_w; }
  virtual widget::ui::FloatSet *color9_w()
    { return _color9_w; }

  // callbacks
  virtual void color_choice_cb()
    { ui::CustomColor::color_choice_cb(); }
  virtual void color0_cb()
    { ui::CustomColor::color0_cb(); }
  virtual void color1_cb()
    { ui::CustomColor::color1_cb(); }
  virtual void color2_cb()
    { ui::CustomColor::color2_cb(); }
  virtual void color3_cb()
    { ui::CustomColor::color3_cb(); }
  virtual void color4_cb()
    { ui::CustomColor::color4_cb(); }
  virtual void color5_cb()
    { ui::CustomColor::color5_cb(); }
  virtual void color6_cb()
    { ui::CustomColor::color6_cb(); }
  virtual void color7_cb()
    { ui::CustomColor::color7_cb(); }
  virtual void color8_cb()
    { ui::CustomColor::color8_cb(); }
  virtual void color9_cb()
    { ui::CustomColor::color9_cb(); }
  virtual void color_reset0_cb()
    { ui::CustomColor::color_reset0_cb(); }
  virtual void color_reset1_cb()
    { ui::CustomColor::color_reset1_cb(); }
  virtual void color_reset2_cb()
    { ui::CustomColor::color_reset2_cb(); }
  virtual void color_reset3_cb()
    { ui::CustomColor::color_reset3_cb(); }
  virtual void color_reset4_cb()
    { ui::CustomColor::color_reset4_cb(); }
  virtual void color_reset5_cb()
    { ui::CustomColor::color_reset5_cb(); }
  virtual void color_reset6_cb()
    { ui::CustomColor::color_reset6_cb(); }
  virtual void color_reset7_cb()
    { ui::CustomColor::color_reset7_cb(); }
  virtual void color_reset8_cb()
    { ui::CustomColor::color_reset8_cb(); }
  virtual void color_reset9_cb()
    { ui::CustomColor::color_reset9_cb(); }

  // disabled copy constructor
  CustomColor( CustomColor const & );

  // disabled assignment operator
  CustomColor &operator=( CustomColor const & );

};

} // namespace gtk
} // namespace geomui

#endif // geomui_gtk_CustomColor_INCLUDED
