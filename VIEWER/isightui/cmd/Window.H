/* GANG Software
 * VIEWER/isightui/cmd/Window.H
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

#ifndef isightui_cmd_Window_INCLUDED
#define isightui_cmd_Window_INCLUDED

#include "widget/cmd/Boolean.H"
#include "widget/cmd/List.H"
#include "isightui/ui/Window.H"

namespace isightui {
namespace cmd {

class Window
  :
    virtual public isightui::ui::Window
{

public:
  // constructor
  Window();

  // destructor
  virtual ~Window();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::List *select_window_w()
    { return &_select_window_w; }
  virtual widget::ui::List const *select_window_w() const
    { return &_select_window_w; }
  virtual widget::ui::Boolean *show_window_w()
    { return &_show_window_w; }
  virtual widget::ui::Widget *delete_window_w()
    { return &_delete_window_w; }

  // widgets
  widget::cmd::List _select_window_w;
  widget::cmd::Boolean _show_window_w;
  widget::cmd::Widget _delete_window_w;

  // disabled copy constructor
  Window( Window const & );
  // disabled assignment operator
  Window &operator=( Window const & );

};

} // namespace cmd
} // namespace isightui

#endif // isightui_cmd_Window_INCLUDED
