/* GANG Software
 * VIEWER/isightui/cmd/Mouse.H
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

#ifndef isightui_cmd_Mouse_INCLUDED
#define isightui_cmd_Mouse_INCLUDED

#include "widget/cmd/Boolean.H"
#include "widget/cmd/Choice.H"
#include "widget/cmd/Float.H"
#include "widget/cmd/FloatSet.H"
#include "isightui/ui/Mouse.H"

namespace isightui {
namespace cmd {

class Mouse
  :
    virtual public isightui::ui::Mouse
{

public:
  // constructor
  Mouse();

  // destructor
  virtual ~Mouse();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::Choice *viewmode_w()
    { return &_viewmode_w; }
  virtual widget::ui::Boolean *inertia_enable_w()
    { return &_inertia_enable_w; }
  virtual widget::ui::Boolean *inertia_decay_enable_w()
    { return &_inertia_decay_enable_w; }
  virtual widget::ui::Float *inertia_decay_rate_w()
    { return &_inertia_decay_rate_w; }
  virtual widget::ui::FloatSet *mouse_speed_w()
    { return &_mouse_speed_w; }

  // widgets
  widget::cmd::Choice _viewmode_w;
  widget::cmd::Boolean _inertia_enable_w;
  widget::cmd::Boolean _inertia_decay_enable_w;
  widget::cmd::Float _inertia_decay_rate_w;
  widget::cmd::FloatSet _mouse_speed_w;

  // disabled copy constructor
  Mouse( Mouse const & );
  // disabled assignment operator
  Mouse &operator=( Mouse const & );

};

} // namespace cmd
} // namespace isightui

#endif // isightui_cmd_Mouse_INCLUDED
