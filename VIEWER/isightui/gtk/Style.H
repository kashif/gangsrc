/* GANG Software
 * VIEWER/isightui/gtk/Style.H
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

#ifndef isightui_gtk_Style_INCLUDED
#define isightui_gtk_Style_INCLUDED

#include "app/app/Dialog.H"
#include "isightui/ui/Style.H"
#include "Style_.H"

namespace isightui {
namespace gtk {

class Style
  :
    virtual public ui::Style,
    protected Style_,
    public ::app::app::Dialog
{

public:
  // constructor
  Style(char const *title);

  // destructor
  virtual ~Style();

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
    { Style_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  // widgets
  virtual widget::ui::Boolean *axes_w()
    { return _axes_w; }
  virtual widget::ui::Boolean *sphere_w()
    { return _sphere_w; }
  virtual widget::ui::Boolean *stars_w()
    { return _stars_w; }

  // callbacks
  virtual void style0_cb()
    { ui::Style::style0_cb(); }
  virtual void style1_cb()
    { ui::Style::style1_cb(); }
  virtual void style2_cb()
    { ui::Style::style2_cb(); }
  virtual void style3_cb()
    { ui::Style::style3_cb(); }
  virtual void style4_cb()
    { ui::Style::style4_cb(); }
  virtual void style5_cb()
    { ui::Style::style5_cb(); }
  virtual void style6_cb()
    { ui::Style::style6_cb(); }
  virtual void style7_cb()
    { ui::Style::style7_cb(); }
  virtual void axes_cb()
    { ui::Style::axes_cb(); }
  virtual void sphere_cb()
    { ui::Style::sphere_cb(); }
  virtual void stars_cb()
    { ui::Style::stars_cb(); }

  // disabled copy constructor
  Style( Style const & );

  // disabled assignment operator
  Style &operator=( Style const & );

};

} // namespace gtk
} // namespace isightui

#endif // isightui_gtk_Style_INCLUDED
