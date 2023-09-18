/* GANG Software
 * VIEWER/isightui/cmd/Style.H
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

#ifndef isightui_cmd_Style_INCLUDED
#define isightui_cmd_Style_INCLUDED

#include "widget/cmd/Boolean.H"
#include "isightui/ui/Style.H"

namespace isightui {
namespace cmd {

class Style
  :
    virtual public isightui::ui::Style
{

public:
  // constructor
  Style();

  // destructor
  virtual ~Style();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::Boolean *axes_w()
    { return &_axes_w; }
  virtual widget::ui::Boolean *sphere_w()
    { return &_sphere_w; }
  virtual widget::ui::Boolean *stars_w()
    { return &_stars_w; }

  // widgets
  widget::cmd::Boolean _axes_w;
  widget::cmd::Boolean _sphere_w;
  widget::cmd::Boolean _stars_w;

  // disabled copy constructor
  Style( Style const & );
  // disabled assignment operator
  Style &operator=( Style const & );

};

} // namespace cmd
} // namespace isightui

#endif // isightui_cmd_Style_INCLUDED
