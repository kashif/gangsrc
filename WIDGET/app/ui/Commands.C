/* GANG Software
 * WIDGET/app/ui/Commands.C
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

#include "base/System.H"
#include "Commands.H"

namespace app {
namespace ui {

Commands::
Commands()
    :
    widget::ui::Dialog()
{
}

Commands::
~Commands()
{
}

void
Commands::
execute_cb()
{
  char const *s = text_w()->get();
  if ( s == (char *)0 ) { return; }
  text_w()->set((char *)0);
  execute_command(s);
}

bool
Commands::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  return false;
}

void
Commands::
command_respond(
  base::String const &text, bool raw )
{
  if ( raw )
  {
    std::cout << text << endl;
  }
  else
  {
    text_w()->set(text.c_str());
  }
}

} // namespace ui
} // namespace app
