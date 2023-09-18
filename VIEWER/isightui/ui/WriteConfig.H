/* GANG Software
 * VIEWER/isightui/ui/WriteConfig.H
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

#ifndef isightui_ui_WriteConfig_INCLUDED
#define isightui_ui_WriteConfig_INCLUDED

#include "base/String.H"
#include "base/ArrayX.H"
#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Boolean.H"
#include "widget/ui/Choice.H"
#include "widget/ui/Float.H"
#include "widget/ui/IntSet.H"

namespace isightui {
namespace ui {

class WriteConfig
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:
  // constructor
  WriteConfig();

  // destructor
  virtual ~WriteConfig();

  virtual bool image_size_use_window() const
    { return size_use_window_w()->get(); }
  virtual void image_size_use_window( bool state )
    { size_use_window_w()->set(state); }
  virtual bool transparent() const
    { return transparent_w()->get(); }
  virtual void get_image_size( uint &width, uint &height ) const
    { int x[2]; size_w()->get(x); width = x[0]; height = x[1]; }
  virtual void set_image_size( uint width, uint height )
    { int x[2]; x[0]=width; x[1]=height; size_w()->set(x); }
  virtual float image_compression() const
    { return compression_w()->get(); }
  virtual void image_compression( float compression )
    {  compression_w()->set( compression); }
  virtual uint write_normals() const
    { return write_normals_w()->get(); }
  virtual void write_normals( uint state )
    {  write_normals_w()->set(state); }
  virtual uint write_colors() const
    { return write_colors_w()->get(); }
  virtual void write_colors( uint state )
    { write_colors_w()->set(state); }
  virtual void writcconfig_reset_geometry()
    { reset_geometry_cb(); }
  virtual void writcconfig_reset_image()
    { reset_image_cb(); }
  virtual void writcconfig_reset()
    { reset_geometry_cb();
    reset_image_cb(); }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void size_use_window_cb();
  virtual void reset_geometry_cb();
  virtual void reset_image_cb();

  char const *label() const
    { return "Write Config"; }

private:

  // widgets
  virtual widget::ui::Choice *write_normals_w() = 0;
  virtual widget::ui::Choice const *write_normals_w() const = 0;
  virtual widget::ui::Choice *write_colors_w() = 0;
  virtual widget::ui::Choice const *write_colors_w() const = 0;
  virtual widget::ui::Boolean *size_use_window_w() = 0;
  virtual widget::ui::Boolean const *size_use_window_w() const = 0;
  virtual widget::ui::Boolean const *transparent_w() const = 0;
  virtual widget::ui::IntSet *size_w() = 0;
  virtual widget::ui::IntSet const *size_w() const = 0;
  virtual widget::ui::Float *compression_w() = 0;
  virtual widget::ui::Float const *compression_w() const = 0;

  // disabled copy constructor
  WriteConfig( WriteConfig const & );
  // disabled assignment operator
  WriteConfig &operator=( WriteConfig const & );

};

} // namespace ui
} // namespace isightui

#endif // isightui_ui_WriteConfig_INCLUDED
