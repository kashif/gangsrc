/* GANG Software
 * VIEWER/isightui/ui/Read.C
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

#include "base/Regex.H"
#include "isight/kernel/ViewerBase.H"
#include "Read.H"

namespace isightui {
namespace ui {

void
Read::
set_lib_env_path(char const *lib_env_path)
{
  read_w()->set_lib_env_path(lib_env_path);
}

void
Read::
read_cb()
{
  if ( read_w()->button() == 1 )
  {
    _read( read_w()->get() );
  }
  show_d(false);
}

void
Read::
_read( char const *filename )
{
  // read a surface from a file

  if ( filename == (char *)0 || strlen(filename) == 0) { return; }
  if ( base::match( "\\/$", filename ) ) { return; }
  viewer()->read(filename);
}

bool
Read::
command(
  base::String const &command, 
  base::String const &argument,
  base::String &response )
{
  bool r = false;
  if ( command == "read" )
  {
    viewer()->read(argument);
    r = true;
  }
  return r;
}

} // namespace ui
} // namespace isightui
