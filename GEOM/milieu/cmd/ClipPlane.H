/* GANG Software
 * GEOM/milieu/cmd/ClipPlane.H
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

#ifndef milieu_cmd_ClipPlane_INCLUDED
#define milieu_cmd_ClipPlane_INCLUDED

#include "widget/cmd/Boolean.H"
#include "widget/cmd/Choice.H"
#include "milieu/ui/ClipPlane.H"

namespace milieu {
namespace cmd {

class ClipPlane
  :
    virtual public milieu::ui::ClipPlane
{

public:
  // constructor
  ClipPlane();

  // destructor
  virtual ~ClipPlane();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::Choice *id_w()
    { return &_id_w; }
  virtual widget::ui::Boolean *enable_w()
    { return &_enable_w; }
  virtual widget::ui::Boolean *moving_w()
    { return &_moving_w; }
  virtual widget::ui::Boolean *show_w()
    { return &_show_w; }
  virtual widget::ui::Boolean *attached_w()
    { return &_attached_w; }

  // widgets
  widget::cmd::Choice _id_w;
  widget::cmd::Boolean _enable_w;
  widget::cmd::Boolean _moving_w;
  widget::cmd::Boolean _show_w;
  widget::cmd::Boolean _attached_w;

  // disabled copy constructor
  ClipPlane( ClipPlane const & );
  // disabled assignment operator
  ClipPlane &operator=( ClipPlane const & );

};

} // namespace cmd
} // namespace milieu

#endif // milieu_cmd_ClipPlane_INCLUDED
