/* GANG Software
 * VIEWER/isightui/cmd/Write.H
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

#ifndef isightui_cmd_Write_INCLUDED
#define isightui_cmd_Write_INCLUDED

#include "widget/cmd/File.H"
#include "isightui/ui/Write.H"

namespace isightui {
namespace cmd {

class Write
  :
    virtual public isightui::ui::Write
{

public:
  // constructor
  Write();

  // destructor
  virtual ~Write();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  virtual widget::ui::File *write_w()
    { return &_write_w; }

  widget::cmd::File _write_w;

  // disabled copy constructor
  Write( Write const & );
  // disabled assignment operator
  Write &operator=( Write const & );

};

} // namespace cmd
} // namespace isightui

#endif // isightui_cmd_Write_INCLUDED
