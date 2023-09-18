/* GANG Software
 * VIEWER/isightui/cmd/WindowSize.H
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

#ifndef isightui_cmd_WindowSize_INCLUDED
#define isightui_cmd_WindowSize_INCLUDED

#include "widget/cmd/IntSet.H"
#include "isightui/ui/WindowSize.H"

namespace isightui {
namespace cmd {

class WindowSize
  :
    virtual public isightui::ui::WindowSize
{

public:
  // constructor
  WindowSize();

  // destructor
  virtual ~WindowSize();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  virtual ::widget::ui::IntSet *window_size_w()
    { return &_window_size_w; }

  widget::cmd::IntSet _window_size_w;

  // disabled copy constructor
  WindowSize( WindowSize const & );
  // disabled assignment operator
  WindowSize &operator=( WindowSize const & );

};

} // namespace cmd
} // namespace isightui

#endif // isightui_cmd_WindowSize_INCLUDED
