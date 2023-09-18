/* GANG Software
 * VIEWER/isightui/cmd/Ui.H
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

#ifndef isightui_cmd_Ui_INCLUDED
#define isightui_cmd_Ui_INCLUDED

#include "isightui/ui/Ui.H"
#include "Geometry.H"
#include "Mouse.H"
#include "WindowSize.H"
#include "Read.H"
#include "Write.H"
#include "GeomObject.H"
#include "Window.H"
#include "Style.H"
#include "WriteConfig.H"

namespace isightui {
namespace cmd {

class Ui
  :
    public ::isightui::ui::Ui,
    public Geometry,
    public Mouse,
    public WindowSize,
    public Read,
    public Write,
    public GeomObject,
    public Window,
    public Style,
    public WriteConfig
{

public:
  // constructor
  Ui();

  // destructor
  virtual ~Ui();

protected:

private:

  // disabled copy constructor
  Ui( Ui const & );
  // disabled assignment operator
  Ui &operator=( Ui const & );
};

} // namespace cmd
} // namespace isightui

#endif // isightui_cmd_Ui_INCLUDED
