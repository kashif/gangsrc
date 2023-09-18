/* GANG Software
 * WIDGET/app/ui/Ui.C
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

#include "Ui.H"

namespace app {
namespace ui {

Ui::
Ui()
    :
    About(),
    Commands(),
    Message(),
    Shortcut()
{
}

Ui::
~Ui()
{
}

void
Ui::
hide_all()
{
  _about()->show_d(false);
  _commands()->show_d(false);
  _message()->show_d(false);
  _shortcut()->show_d(false);
}

void
Ui::
enable_tooltips( bool state )
{
  _about()->enable_tooltips_d(state);
  _commands()->enable_tooltips_d(state);
  _message()->enable_tooltips_d(state);
  _shortcut()->enable_tooltips_d(state);
}

bool
Ui::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  return
    _about()->command( command, argument, response ) ||
    _commands()->command( command, argument, response ) ||
    _message()->command( command, argument, response ) ||
    _shortcut()->command( command, argument, response );
}

} // namespace ui
} // namespace app
