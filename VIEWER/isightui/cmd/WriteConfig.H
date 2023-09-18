/* GANG Software
 * VIEWER/isightui/cmd/WriteConfig.H
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

#ifndef isightui_cmd_WriteConfig_INCLUDED
#define isightui_cmd_WriteConfig_INCLUDED

#include "widget/cmd/Boolean.H"
#include "widget/cmd/Float.H"
#include "widget/cmd/IntSet.H"
#include "widget/cmd/Choice.H"
#include "isightui/ui/WriteConfig.H"

namespace isightui {
namespace cmd {

class WriteConfig
  :
    virtual public isightui::ui::WriteConfig
{

public:
  // constructor
  WriteConfig();

  // destructor
  virtual ~WriteConfig();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::Choice *write_normals_w()
    { return &_write_normals_w; }
  virtual widget::ui::Choice const *write_normals_w() const
    { return &_write_normals_w; }
  virtual widget::ui::Choice *write_colors_w()
    { return &_write_colors_w; }
  virtual widget::ui::Choice const *write_colors_w() const
    { return &_write_colors_w; }
  virtual widget::ui::Boolean *size_use_window_w()
    { return &_size_use_window_w; }
  virtual widget::ui::Boolean const *size_use_window_w() const
    { return &_size_use_window_w; }
  virtual widget::ui::Boolean const *transparent_w() const
    { return &_transparent_w; }
  virtual widget::ui::IntSet *size_w()
    { return &_size_w; }
  virtual widget::ui::IntSet const *size_w() const
    { return &_size_w; }
  virtual widget::ui::Float *compression_w()
    { return &_compression_w; }
  virtual widget::ui::Float const *compression_w() const
    { return &_compression_w; }

  // widgets
  widget::cmd::Choice _write_normals_w;
  widget::cmd::Choice _write_colors_w;
  widget::cmd::Boolean _size_use_window_w;
  widget::cmd::Boolean _transparent_w;
  widget::cmd::IntSet _size_w;
  widget::cmd::Float _compression_w;

  // disabled copy constructor
  WriteConfig( WriteConfig const & );
  // disabled assignment operator
  WriteConfig &operator=( WriteConfig const & );

};

} // namespace cmd
} // namespace isightui

#endif // isightui_cmd_WriteConfig_INCLUDED
