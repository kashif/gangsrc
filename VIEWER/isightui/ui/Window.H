/* GANG Software
 * VIEWER/isightui/ui/Window.H
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

#ifndef isightui_ui_Window_INCLUDED
#define isightui_ui_Window_INCLUDED

#include "base/String.H"
#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/Boolean.H"
#include "widget/ui/List.H"

namespace isight { namespace kernel { class ViewerBase; } }

namespace isightui {
namespace ui {

class Window
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:

  // constructor
  Window();

  // destructor
  virtual ~Window();

  // interface
  virtual void new_window();
  virtual void select_window( uint id )
    { select_window_w()->set(id); }
  virtual void show_window( uint id, bool state )
    { select_window_w()->set(id);  show_window_w()->set(state); }
  virtual void delete_window( uint id )
    { select_window_w()->set(id);  delete_window_cb(); }
  virtual void reset_position();
  virtual void stop_motion();
  

  virtual uint selected_window() const
    { return select_window_w()->get(); }

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

  // no row is selected
  static uint const NONE = (uint)-1;

protected:

  // callbacks
  virtual void new_window_cb();
  virtual void select_window_cb();
  virtual void show_window_cb();
  virtual void delete_window_cb();

  char const *label() const
    { return "Select Window"; }

private:

  virtual isight::kernel::ViewerBase *viewer() = 0;
  virtual isight::kernel::ViewerBase const *viewer() const = 0;

  void synchronize();
  void set_sensitive();
  uint item_count() const
    { return select_window_w()->item_count(); }

  // widgets
  virtual widget::ui::List *select_window_w() = 0;
  virtual widget::ui::List const *select_window_w() const = 0;
  virtual widget::ui::Boolean *show_window_w() = 0;
  virtual widget::ui::Widget *delete_window_w() = 0;

  Window( Window const & );
  Window &operator=( Window const & );

};

} // namespace ui
} // namespace isightui

#endif // isightui_ui_Window_INCLUDED
