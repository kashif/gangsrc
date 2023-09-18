/* GANG Software
 * GEOM/milieu/cmd/Blend.H
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

#ifndef milieu_cmd_Blend_INCLUDED
#define milieu_cmd_Blend_INCLUDED

#include "widget/cmd/Boolean.H"
#include "widget/cmd/Choice.H"
#include "widget/cmd/FloatSet.H"
#include "milieu/ui/Blend.H"

namespace milieu {
namespace cmd {

class Blend
  :
    virtual public milieu::ui::Blend
{

public:
  // constructor
  Blend();

  // destructor
  virtual ~Blend();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::Boolean *depth_enable_w()
    { return &_depth_enable_w; }
  virtual widget::ui::Choice *depth_function_w()
    { return &_depth_function_w; }
  virtual widget::ui::Choice *depth_mask_w()
    { return &_depth_mask_w; }
  virtual widget::ui::Choice *blend_dest_function_w()
    { return &_blend_dest_function_w; }
  virtual widget::ui::Choice *blend_src_function_w()
    { return &_blend_src_function_w; }
  virtual widget::ui::Boolean *blend_enable_w()
    { return &_blend_enable_w; }
  virtual widget::ui::Boolean *antialias_point_w()
    { return &_antialias_point_w; }
  virtual widget::ui::Boolean *antialias_line_w()
    { return &_antialias_line_w; }
  virtual widget::ui::Boolean *fog_enable_w()
    { return &_fog_enable_w; }
  virtual widget::ui::Choice *fog_mode_w()
    { return &_fog_mode_w; }
  virtual widget::ui::FloatSet *fog_parameter_w()
    { return &_fog_parameter_w; }
  virtual widget::ui::FloatSet *fog_color_w()
    { return &_fog_color_w; }

  // widgets
  widget::cmd::Boolean _depth_enable_w;
  widget::cmd::Choice _depth_function_w;
  widget::cmd::Choice _depth_mask_w;
  widget::cmd::Choice _blend_dest_function_w;
  widget::cmd::Choice _blend_src_function_w;
  widget::cmd::Boolean _blend_enable_w;
  widget::cmd::Boolean _antialias_point_w;
  widget::cmd::Boolean _antialias_line_w;
  widget::cmd::Boolean _fog_enable_w;
  widget::cmd::Choice _fog_mode_w;
  widget::cmd::FloatSet _fog_parameter_w;
  widget::cmd::FloatSet _fog_color_w;

  // disabled copy constructor
  Blend( Blend const & );
  // disabled assignment operator
  Blend &operator=( Blend const & );

};

} // namespace cmd
} // namespace milieu

#endif // milieu_cmd_Blend_INCLUDED
