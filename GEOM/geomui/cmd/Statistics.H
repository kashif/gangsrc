/* GANG Software
 * GEOM/geomui/cmd/Statistics.H
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

#ifndef geomui_cmd_Statistics_INCLUDED
#define geomui_cmd_Statistics_INCLUDED

#include "widget/cmd/String.H"
#include "geomui/ui/Statistics.H"

namespace geomui {
namespace cmd {

class Statistics
  :
    virtual public geomui::ui::Statistics
{

public:
  // constructor
  Statistics();

  // destructor
  virtual ~Statistics();

  // connector functions
  virtual void raise_d( bool state = true ) {}
  virtual void show_d( bool state = true ) {}
  virtual void toggle_raise_show_d() {}
  virtual void enable_tooltips_d( bool state = true ) {}
  virtual int key_press_event_d( uint key, uint state ) { return 0; }

protected:

private:

  // widgets
  virtual widget::ui::String *stat0_w()
    { return &_stat0_w; }
  virtual widget::ui::String *stat1_w()
    { return &_stat1_w; }
  virtual widget::ui::String *stat2_w()
    { return &_stat2_w; }
  virtual widget::ui::String *stat3_w()
    { return &_stat3_w; }

  // widgets
  widget::cmd::String _stat0_w;
  widget::cmd::String _stat1_w;
  widget::cmd::String _stat2_w;
  widget::cmd::String _stat3_w;

  // disabled copy constructor
  Statistics( Statistics const & );
  // disabled assignment operator
  Statistics &operator=( Statistics const & );

};

} // namespace cmd
} // namespace geomui

#endif // geomui_cmd_Statistics_INCLUDED
