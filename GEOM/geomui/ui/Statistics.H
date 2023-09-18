/* GANG Software
 * GEOM/geomui/ui/Statistics.H
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

#ifndef geomui_ui_Statistics_INCLUDED
#define geomui_ui_Statistics_INCLUDED

#include "base/String.H"
#include "base/ReadUtil.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/String.H"
#include "geom/interface/Surface.H"

namespace geomui {
namespace ui {

class Statistics
  :
    public widget::ui::Dialog,
    public base::ReadUtil
{

public:
  // constructor
  Statistics();

  // destructor
  virtual ~Statistics();

  // interface
  virtual void statistics_reset() {}

  //
  virtual void statistics_synchronize();

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  char const *label()
    { return "Statistics"; }

private:

  // pure virtuals
  virtual geom::Surface *geomlist() = 0;
  virtual geom::Surface const *geomlist() const = 0;
  virtual void refresh_all() = 0;

  // widgets
  virtual widget::ui::String *stat0_w() = 0;
  virtual widget::ui::String *stat1_w() = 0;
  virtual widget::ui::String *stat2_w() = 0;
  virtual widget::ui::String *stat3_w() = 0;

  // disabled copy constructor
  Statistics( Statistics const & );
  // disabled assignment operator
  Statistics &operator=( Statistics const & );
};

} // namespace ui
} // namespace geomui

#endif // geomui_ui_Statistics_INCLUDED
