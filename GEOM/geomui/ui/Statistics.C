/* GANG Software
 * GEOM/geomui/ui/Statistics.C
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

#include "Statistics.H"

namespace geomui {
namespace ui {

Statistics::
Statistics()
    :
    widget::ui::Dialog(),
    base::ReadUtil()
{
}

Statistics::
~Statistics()
{
}

void
Statistics::
statistics_synchronize()
{
  base::String s;

  int vertex = geomlist()->vertex_count();
  int edge = geomlist()->edge_count();
  int face = geomlist()->face_count();

  s.to_string( vertex );
  stat0_w()->set( s.c_str() );

  s.to_string( edge );
  stat1_w()->set( s.c_str() );

  s.to_string( face );
  stat2_w()->set( s.c_str() );

  s.to_string( vertex-edge+face );
  stat3_w()->set( s.c_str() );
}

bool
Statistics::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;


  return r;
}

} // namespace ui
} // namespace geomui
