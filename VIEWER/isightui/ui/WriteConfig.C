/* GANG Software
 * VIEWER/isightui/ui/WriteConfig.C
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

#include "WriteConfig.H"

/*
  max image size: 2048 x 1200
*/

namespace isightui {
namespace ui {

WriteConfig::
WriteConfig()
{
}

WriteConfig::
~WriteConfig()
{
}


void
WriteConfig::
size_use_window_cb()
{
  bool state = size_use_window_w()->get();
  size_w()->set_sensitive( ! state );
}

void
WriteConfig::
reset_geometry_cb()
{
  write_normals_w()->set(2U);
  write_colors_w()->set(2U);
}

void
WriteConfig::
reset_image_cb()
{
  size_use_window_w()->set(false);
  int const a[2] = {500U, 500U};
  size_w()->set(a);
  compression_w()->set(0.75f);
}

bool
WriteConfig::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "imageSizeUseContext" )
  {
    image_size_use_window( read_bool(argument) );
    r = true;
  }
  if ( command == "imageSize" )
  {
    base::vector<uint> x;
    read_list( x, 2, argument );
    set_image_size( x[0], x[1] );
    r = true;
  }
  if ( command == "imageCompression" )
  {
    image_compression( read_real(argument) );
    r = true;
  }
  if ( command == "writeNormals" )
  {
    write_normals( read_uint(argument) );
    r = true;
  }
  if ( command == "writeColors" )
  {
    write_colors( read_uint(argument) );
    r = true;
  }
  return r;
}

} // namespace ui
} // namespace isightui
