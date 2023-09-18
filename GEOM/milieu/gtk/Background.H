/* GANG Software
 * GEOM/milieu/gtk/Background.H
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

#ifndef milieu_gtk_Background_INCLUDED
#define milieu_gtk_Background_INCLUDED

#include "app/app/Dialog.H"
#include "milieu/ui/Background.H"
#include "Background_.H"

namespace milieu {
namespace gtk {

class Background
  :
    virtual public ui::Background,
    protected gtk::Background_,
    public ::app::app::Dialog
{

public:
  // constructor
  Background(char const *title);

  // destructor
  virtual ~Background();

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { Background_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

protected:

private:

  // widgets
  virtual widget::ui::FloatSet *color_w()
    { return _color_w; }

  // callbacks
  virtual void reset_cb()
    { ui::Background::reset_cb(); }
  virtual void bgcolor0_cb()
    { ui::Background::bgcolor0_cb(); }
  virtual void bgcolor1_cb()
    { ui::Background::bgcolor1_cb(); }
  virtual void bgcolor2_cb()
    { ui::Background::bgcolor2_cb(); }
  virtual void bgcolor3_cb()
    { ui::Background::bgcolor3_cb(); }
  virtual void color_cb()
    { ui::Background::color_cb(); }
  virtual void image_cb()
    { ui::Background::image_cb(); }

  // disabled copy constructor
  Background( Background const & );

  // disabled assignment operator
  Background &operator=( Background const & );

};

} // namespace gtk
} // namespace milieu

#endif // milieu_gtk_Background_INCLUDED
