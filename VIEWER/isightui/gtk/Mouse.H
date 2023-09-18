/* GANG Software
 * VIEWER/isightui/gtk/Mouse.H
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

#ifndef isightui_gtk_Mouse_INCLUDED
#define isightui_gtk_Mouse_INCLUDED

#include "app/app/Dialog.H"
#include "isightui/ui/Mouse.H"
#include "Mouse_.H"

namespace isightui {
namespace gtk {

class Mouse
  :
    virtual public ui::Mouse,
    protected gtk::Mouse_,
    public ::app::app::Dialog
{

public:
  // constructor
  Mouse(char const *title);

  // destructor
  virtual ~Mouse();

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
    { Mouse_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual ::widget::ui::Choice *viewmode_w()
    { return _viewmode_w; }
  virtual ::widget::ui::Boolean *inertia_enable_w()
    { return _inertia_enable_w; }
  virtual ::widget::ui::Boolean *inertia_decay_enable_w()
    { return _inertia_decay_enable_w; }
  virtual ::widget::ui::Float *inertia_decay_rate_w()
    { return _inertia_decay_rate_w; }
  virtual ::widget::ui::FloatSet *mouse_speed_w()
    { return _mouse_speed_w; }

  // callbacks
  virtual void viewmode_cb()
    { ui::Mouse::viewmode_cb(); }
  virtual void reset0_cb()
    { ui::Mouse::reset0_cb(); }
  virtual void reset1_cb()
    { ui::Mouse::reset1_cb(); }
  virtual void inertia_enable_cb()
    { ui::Mouse::inertia_enable_cb(); }
  virtual void inertia_decay_enable_cb()
    { ui::Mouse::inertia_decay_enable_cb(); }
  virtual void inertia_decay_rate_cb()
    { ui::Mouse::inertia_decay_rate_cb(); }
  virtual void mouse_speed_cb()
    { ui::Mouse::mouse_speed_cb(); }

  // disabled copy constructor
  Mouse( Mouse const & );

  // disabled assignment operator
  Mouse &operator=( Mouse const & );

};

} // namespace gtk
} // namespace isightui

#endif // isightui_gtk_Mouse_INCLUDED
