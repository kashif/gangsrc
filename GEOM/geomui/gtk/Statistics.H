/* GANG Software
 * GEOM/geomui/gtk/Statistics.H
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

#ifndef geomui_gtk_Statistics_INCLUDED
#define geomui_gtk_Statistics_INCLUDED

#include "widget/ui/String.H"
#include "app/app/Dialog.H"
#include "geomui/ui/Statistics.H"
#include "Statistics_.H"

namespace geomui {
namespace gtk {

class Statistics
  :
    virtual public ui::Statistics,
    protected gtk::Statistics_,
    public ::app::app::Dialog
{

public:
  // constructor
  Statistics(char const *title);

  // destructor
  virtual ~Statistics();

protected:

private:

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }
  virtual void enable_tooltips_d( bool state = true )
    { Statistics_::enable_tooltips(state); }

  // widgets
  virtual widget::ui::String *stat0_w()
    { return _stat0_w; }
  virtual widget::ui::String *stat1_w()
    { return _stat1_w; }
  virtual widget::ui::String *stat2_w()
    { return _stat2_w; }
  virtual widget::ui::String *stat3_w()
    { return _stat3_w; }

  // disabled copy constructor
  Statistics( Statistics const & );

  // disabled assignment operator
  Statistics &operator=( Statistics const & );

};

} // namespace gtk
} // namespace geomui

#endif // geomui_gtk_Statistics_INCLUDED
