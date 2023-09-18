/* GANG Software
 * VIEWER/isightui/ui/Read.H
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

#ifndef isightui_ui_Read_INCLUDED
#define isightui_ui_Read_INCLUDED

#include "base/String.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/ReadFile.H"

namespace isight { namespace kernel { class ViewerBase; } }

namespace isightui {
namespace ui {

class Read
  :
    public widget::ui::Dialog
{

public:
  // constructor
  Read() {}

  // destructor
  virtual ~Read() {}

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  void set_lib_env_path( char const *lib_env_path );

  // callbacks
  virtual void read_cb();

  char const *label() const
    { return "Open iSight File"; }

private:

  virtual isight::kernel::ViewerBase *viewer() = 0;
  virtual isight::kernel::ViewerBase const *viewer() const = 0;

  // widgets
  virtual widget::ui::ReadFile *read_w() = 0;

  virtual void _read( char const *filename );

  // disabled copy constructor
  Read( Read const & );
  // disabled assignment operator
  Read &operator=( Read const & );

};

} // namespace ui
} // namespace isightui

#endif // isightui_ui_Read_INCLUDED
