/* GANG Software
 * VIEWER/isightui/gtk/WriteConfig.H
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

#ifndef isightui_gtk_WriteConfig_INCLUDED
#define isightui_gtk_WriteConfig_INCLUDED

#include "app/app/Dialog.H"
#include "isightui/ui/WriteConfig.H"
#include "WriteConfig_.H"

namespace isightui {
namespace gtk {

class WriteConfig
  :
    virtual public ui::WriteConfig,
    protected WriteConfig_,
    public ::app::app::Dialog
{

public:
  // constructor
  WriteConfig(char const *title);

  // destructor
  virtual ~WriteConfig();

protected:

private:

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { WriteConfig_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual widget::ui::Widget *reset_image_w()
    { return _reset_image_w; }
  virtual widget::ui::Widget *reset_geometry_w()
    { return _reset_geometry_w; }
  virtual widget::ui::Choice *write_normals_w()
    { return _write_normals_w; }
  virtual widget::ui::Choice const *write_normals_w() const
    { return _write_normals_w; }
  virtual widget::ui::Choice *write_colors_w()
    { return _write_colors_w; }
  virtual widget::ui::Choice const *write_colors_w() const
    { return _write_colors_w; }
  virtual widget::ui::Boolean *size_use_window_w()
    { return _size_use_window_w; }
  virtual widget::ui::Boolean const *size_use_window_w() const
    { return _size_use_window_w; }
  virtual widget::ui::IntSet *size_w()
    { return _size_w; }
  virtual widget::ui::IntSet const *size_w() const
    { return _size_w; }
  virtual widget::ui::Float *compression_w()
    { return _compression_w; }
  virtual widget::ui::Float const *compression_w() const
    { return _compression_w; }
  virtual widget::ui::Boolean const *transparent_w() const
    { return _transparent_w; }

  virtual void reset_geometry_cb()
    { ui::WriteConfig::reset_geometry_cb(); }
  virtual void reset_image_cb()
    { ui::WriteConfig::reset_image_cb(); }
  virtual void size_use_window_cb()
    { ui::WriteConfig::size_use_window_cb(); }

  // disabled copy constructor
  WriteConfig( WriteConfig const & );
  // disabled assignment operator
  WriteConfig &operator=( WriteConfig const & );

};

} // namespace gtk
} // namespace isightui

#endif // isightui_gtk_WriteConfig_INCLUDED
