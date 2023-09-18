/* GANG Software
 * VIEWER/isightui/ui/Write.H
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

#ifndef isightui_ui_Write_INCLUDED
#define isightui_ui_Write_INCLUDED

#include "base/String.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/File.H"

namespace isight { namespace kernel { class ViewerBase; } }

namespace isightui {
namespace ui {

class Write
  :
    public widget::ui::Dialog
{

public:
  // constructor
  Write() {}

  // destructor
  virtual ~Write() {}

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void write_cb();

  char const *label() const
    { return "Save iSight File"; }

private:

  virtual isight::kernel::ViewerBase *viewer() = 0;
  virtual isight::kernel::ViewerBase const *viewer() const = 0;

  // widgets
  virtual widget::ui::File *write_w() = 0;

  void _write( char const *filename );

  // disabled copy constructor
  Write( Write const & );
  // disabled assignment operator
  Write &operator=( Write const & );

};

} // namespace ui
} // namespace isightui

#endif // isightui_ui_Write_INCLUDED
