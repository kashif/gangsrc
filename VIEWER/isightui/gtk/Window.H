/* GANG Software
 * VIEWER/isightui/gtk/Window.H
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

#ifndef isightui_gtk_Window_INCLUDED
#define isightui_gtk_Window_INCLUDED

#include "app/app/Dialog.H"
#include "isightui/ui/Window.H"
#include "Window_.H"

namespace isightui {
namespace gtk {

class Window
  :
    virtual public ui::Window,
    protected Window_,
    public ::app::app::Dialog
{

public:
  // constructor
  Window(char const *title);

  // destructor
  virtual ~Window();

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
    { Window_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual widget::ui::List *select_window_w()
    { return _select_window_w; }
  virtual widget::ui::List const *select_window_w() const
    { return _select_window_w; }
  virtual widget::ui::Boolean *show_window_w()
    { return _show_window_w; }
  virtual widget::ui::Widget *delete_window_w()
    { return _delete_window_w; }

  // callbacks
  virtual void select_window_cb()
    { ui::Window::select_window_cb(); }
  virtual void delete_window_cb()
    { ui::Window::delete_window_cb(); }
  virtual void new_window_cb()
    { ui::Window::new_window_cb(); }
  virtual void show_window_cb()
    { ui::Window::show_window_cb(); }

  // disabled copy constructor
  Window( Window const & );
  // disabled assignment operator
  Window &operator=( Window const & );

};

} // namespace gtk
} // namespace isightui

#endif // isightui_gtk_Window_INCLUDED
