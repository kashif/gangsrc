/* GANG Software
 * GEOM/milieu/gtk/GlobalLight.H
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

#ifndef milieu_gtk_GlobalLight_INCLUDED
#define milieu_gtk_GlobalLight_INCLUDED

#include "app/app/Dialog.H"
#include "milieu/ui/GlobalLight.H"
#include "GlobalLight_.H"

namespace milieu {
namespace gtk {

class GlobalLight
  :
    virtual public ui::GlobalLight,
    protected gtk::GlobalLight_,
    public ::app::app::Dialog
{

public:
  // constructor
  GlobalLight(char const *title);

  // destructor
  virtual ~GlobalLight();

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { GlobalLight_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

protected:

private:

  // widgets
  virtual widget::ui::Boolean *enable_w()
    { return _enable_w; }
  virtual widget::ui::FloatSet *ambient_w()
    { return _ambient_w; }
  virtual widget::ui::Choice *viewpoint_w()
    { return _viewpoint_w; }
  virtual widget::ui::Choice *sidedness_w()
    { return _sidedness_w; }

  // callbacks
  virtual void enable_cb()
    { ui::GlobalLight::enable_cb(); }
  virtual void reset_cb()
    { ui::GlobalLight::reset_cb(); }
  virtual void ambient_cb()
    { ui::GlobalLight::ambient_cb(); }
  virtual void sidedness_cb()
    { ui::GlobalLight::sidedness_cb(); }
  virtual void viewpoint_cb()
    { ui::GlobalLight::viewpoint_cb(); }

  // disabled copy constructor
  GlobalLight( GlobalLight const & );

  // disabled assignment operator
  GlobalLight &operator=( GlobalLight const & );

};

} // namespace gtk
} // namespace milieu

#endif // milieu_gtk_GlobalLight_INCLUDED
