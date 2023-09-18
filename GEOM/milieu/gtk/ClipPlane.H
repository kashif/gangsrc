/* GANG Software
 * GEOM/milieu/gtk/ClipPlane.H
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

#ifndef milieu_gtk_ClipPlane_INCLUDED
#define milieu_gtk_ClipPlane_INCLUDED

#include "app/app/Dialog.H"
#include "milieu/ui/ClipPlane.H"
#include "ClipPlane_.H"

namespace milieu {
namespace gtk {

class ClipPlane
  :
    virtual public ui::ClipPlane,
    protected gtk::ClipPlane_,
    public ::app::app::Dialog
{

public:
  // constructor
  ClipPlane(char const *title);

  // destructor
  virtual ~ClipPlane();

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { ClipPlane_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

protected:

private:

  // widgets
  virtual widget::ui::Choice *id_w()
    { return _id_w; }
  virtual widget::ui::Boolean *enable_w()
    { return _enable_w; }
  virtual widget::ui::Boolean *moving_w()
    { return _moving_w; }
  virtual widget::ui::Boolean *show_w()
    { return _show_w; }
  virtual widget::ui::Boolean *attached_w()
    { return _attached_w; }

  // callbacks
  virtual void id_cb()
    { ui::ClipPlane::id_cb(); }
  virtual void enable_cb()
    { ui::ClipPlane::enable_cb(); }
  virtual void moving_cb()
    { ui::ClipPlane::moving_cb(); }
  virtual void show_cb()
    { ui::ClipPlane::show_cb(); }
  virtual void attached_cb()
    { ui::ClipPlane::attached_cb(); }
  virtual void reset_cb()
    { ui::ClipPlane::reset_cb(); }

  // disabled copy constructor
  ClipPlane( ClipPlane const & );

  // disabled assignment operator
  ClipPlane &operator=( ClipPlane const & );

};

} // namespace gtk
} // namespace milieu

#endif // milieu_gtk_ClipPlane_INCLUDED
