/* GANG Software
 * GEOM/milieu/gtk/Blend.H
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

#ifndef milieu_gtk_Blend_INCLUDED
#define milieu_gtk_Blend_INCLUDED

#include "app/app/Dialog.H"
#include "milieu/ui/Blend.H"
#include "Blend_.H"

namespace milieu {
namespace gtk {

class Blend
  :
    virtual public ui::Blend,
    protected gtk::Blend_,
    public ::app::app::Dialog
{

public:
  // constructor
  Blend(char const *title);

  // destructor
  virtual ~Blend();

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { Blend_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

protected:

private:

  // widgets
  virtual widget::ui::Boolean *depth_enable_w()
    { return _depth_enable_w; }
  virtual widget::ui::Choice *depth_function_w()
    { return _depth_function_w; }
  virtual widget::ui::Choice *depth_mask_w()
    { return _depth_mask_w; }
  virtual widget::ui::Choice *blend_dest_function_w()
    { return _blend_dest_function_w; }
  virtual widget::ui::Choice *blend_src_function_w()
    { return _blend_src_function_w; }
  virtual widget::ui::Boolean *blend_enable_w()
    { return _blend_enable_w; }
  virtual widget::ui::Boolean *antialias_point_w()
    { return _antialias_point_w; }
  virtual widget::ui::Boolean *antialias_line_w()
    { return _antialias_line_w; }
  virtual widget::ui::Boolean *fog_enable_w()
    { return _fog_enable_w; }
  virtual widget::ui::Choice *fog_mode_w()
    { return _fog_mode_w; }
  virtual widget::ui::FloatSet *fog_parameter_w()
    { return _fog_parameter_w; }
  virtual widget::ui::FloatSet *fog_color_w()
    { return _fog_color_w; }

  // callbacks
  virtual void depth_enable_cb()
    { ui::Blend::depth_enable_cb(); }
  virtual void depth_reset_cb()
    { ui::Blend::depth_reset_cb(); }
  virtual void depth_function_cb()
    { ui::Blend::depth_function_cb(); }
  virtual void depth_mask_cb()
    { ui::Blend::depth_mask_cb(); }
  virtual void blend_src_function_cb()
    { ui::Blend::blend_src_function_cb(); }
  virtual void blend_dest_function_cb()
    { ui::Blend::blend_dest_function_cb(); }
  virtual void blend_enable_cb()
    { ui::Blend::blend_enable_cb(); }
  virtual void blend_reset_cb()
    { ui::Blend::blend_reset_cb(); }
  virtual void antialias_point_cb()
    { ui::Blend::antialias_point_cb(); }
  virtual void antialias_line_cb()
    { ui::Blend::antialias_line_cb(); }
  virtual void fog_enable_cb()
    { ui::Blend::fog_enable_cb(); }
  virtual void fog_reset_cb()
    { ui::Blend::fog_reset_cb(); }
  virtual void fog_mode_cb()
    { ui::Blend::fog_mode_cb(); }
  virtual void fog_parameter_cb()
    { ui::Blend::fog_parameter_cb(); }
  virtual void fog_color_cb()
    { ui::Blend::fog_color_cb(); }

  // disabled copy constructor
  Blend( Blend const & );

  // disabled assignment operator
  Blend &operator=( Blend const & );

};

} // namespace gtk
} // namespace milieu

#endif // milieu_gtk_Blend_INCLUDED
