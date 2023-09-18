/* GANG Software
 * GEOM/milieu/ui/Blend.H
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

#ifndef milieu_ui_Blend_INCLUDED
#define milieu_ui_Blend_INCLUDED

#include "base/ArrayX.H"
#include "base/String.H"
#include "base/Color3.H"
#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Boolean.H"
#include "widget/ui/Choice.H"
#include "widget/ui/FloatSet.H"

namespace milieu {

namespace opengl { class Blend; }

namespace ui {

class Blend
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  Blend();

  // destructor
  virtual ~Blend();

  // interface
  virtual void blend_reset();
  virtual void antialias_point(bool a)
    { antialias_point_w()->set(a); }
  virtual void antialias_line(bool a)
    { antialias_line_w()->set(a); }
  virtual void blend_enable( bool a)
    { blend_enable_w()->set(a); }
  virtual void blend_src_function( uint a )
    { blend_src_function_w()->set(a); }
  virtual void blend_dest_function( uint a )
    { blend_dest_function_w()->set(a); }
  virtual void fog_enable( bool a)
    { fog_enable_w()->set(a); }
  virtual void fog_mode( uint a )
    { fog_mode_w()->set(a); }
  virtual void fog_parameter( base::ArrayX<float,3U> const &a )
    { fog_parameter_w()->set(a.data()); }
  virtual void fog_color( base::Color3 const &a )
    { fog_color_w()->set(a.data()); }
  virtual void depth_enable( bool a)
    { depth_enable_w()->set(a); }
  virtual void depth_function( uint a)
    { depth_function_w()->set(a); }
  virtual void depth_mask( bool a)
    { depth_mask_w()->set(a); }
#if 0
  virtual void hint_point_smooth( uint a)
    { hint_point_smooth_w()->set(a); }
  virtual void hint_line_smooth( uint a)
    { hint_line_smooth_w()->set(a); }
  virtual void hint_polygon_smooth( uint a)
    { hint_polygon_smooth_w()->set(a); }
  virtual void hint_fog( uint a)
    { hint_fog_w()->set(a); }
  virtual void hint_perspective_correction( uint a)
    { hint_perspective_correction_w()->set(a); }
#endif
  virtual void blend_synchronize();

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void depth_enable_cb();
  virtual void depth_reset_cb();
  virtual void depth_function_cb();
  virtual void depth_mask_cb();
  virtual void blend_dest_function_cb();
  virtual void blend_src_function_cb();
  virtual void blend_enable_cb();
  virtual void blend_reset_cb();
  virtual void antialias_point_cb();
  virtual void antialias_line_cb();
  virtual void fog_enable_cb();
  virtual void fog_reset_cb();
  virtual void fog_mode_cb();
  virtual void fog_parameter_cb();
  virtual void fog_color_cb();

  char const *label()
    { return "Blend"; }

private:

  // pure virtuals
  virtual ::milieu::opengl::Blend *blend() = 0;
  virtual ::milieu::opengl::Blend const *blend() const = 0;

  // widgets
  virtual widget::ui::Boolean *depth_enable_w() = 0;
  virtual widget::ui::Choice *depth_function_w() = 0;
  virtual widget::ui::Choice *depth_mask_w() = 0;
  virtual widget::ui::Choice *blend_dest_function_w() = 0;
  virtual widget::ui::Choice *blend_src_function_w() = 0;
  virtual widget::ui::Boolean *blend_enable_w() = 0;
  virtual widget::ui::Boolean *antialias_point_w() = 0;
  virtual widget::ui::Boolean *antialias_line_w() = 0;
  virtual widget::ui::Boolean *fog_enable_w() = 0;
  virtual widget::ui::Choice *fog_mode_w() = 0;
  virtual widget::ui::FloatSet *fog_parameter_w() = 0;
  virtual widget::ui::FloatSet *fog_color_w() = 0;

  void fog_set_sensitive( int mode );

  Blend( Blend const & );
  Blend &operator=( Blend const & );
};

} // namespace ui
} // namespace milieu

#endif // milieu_ui_Blend_INCLUDED
