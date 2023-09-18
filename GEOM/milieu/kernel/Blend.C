/* GANG Software
 * GEOM/milieu/kernel/Blend.C
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

#include "Blend.H"

namespace milieu {
namespace kernel {


Blend::
Blend()
{
  clear();
}

Blend::
Blend( Blend const &a )
{
  copy(a);
}

Blend::
~Blend()
{
}

Blend &
Blend::
operator=( Blend const &a )
{
  copy(a);
  return *this;
}

void
Blend::
clear()
{
  _blend_enable = false;
  _blend_src_function = 4;
  _blend_dest_function = 6;

  _depth_enable = true;
  _depth_function = 2;
  _depth_mask = true;

  _fog_enable = false;
  _fog_mode = 0;
  _fog_parameter[0] = 0.1;
  _fog_parameter[1] = 6.0;
  _fog_parameter[2] = 12.0;

  _fog_color = base::Color3(1.0f, 1.0f, 1.0f);

#if 0
  _hint_point_smooth = false;
  _hint_line_smooth = false;
  _hint_polygon_smooth = false;
  _hint_fog = false;
  _hint_perspective_correction = false;
#endif
}

void
Blend::
copy( Blend const &a )
{
  if ( this == &a ) { return; }

  _blend_enable = a._blend_enable;
  _blend_src_function = a._blend_src_function;
  _blend_dest_function = a._blend_dest_function;
  _depth_enable = a._depth_enable;
  _depth_function = a._depth_function;
  _depth_mask = a._depth_mask;
  _fog_enable = a._fog_enable;
  _fog_mode = a._fog_mode;
  _fog_parameter = a._fog_parameter;
  _fog_color = a._fog_color;

#if 0
  _hint_point_smooth = a._hint_point_smooth;
  _hint_line_smooth = a._hint_line_smooth;
  _hint_polygon_smooth = a._hint_polygon_smooth;
  _hint_fog = a._hint_fog;
  _hint_perspective_correction = a._hint_perspective_correction;
#endif
}

void
Blend::
dump( io::Ostream &o ) const
{
  char const *tab = "\t\t";

  // depth
  o << tab << "<depth>\n";
  o << tab << "\t<enable>" << _depth_enable << "</enable>\n";
  o << tab << "\t<function>" << _depth_function << "</function>\n";
  o << tab << "\t<mask>" << _depth_mask << "</mask>\n";
  o << tab << "</depth>\n";

  // blend
  o << tab << "<blend>\n";
  o << tab << "\t<enable>" << _blend_enable << "</enable>\n";
  o << tab << "\t<source_function>" << _blend_src_function << "</source_function>\n";
  o << tab << "\t<destination_function>" << _blend_dest_function << "</destination_function>\n";
  o << tab << "</blend>\n";

  // fog
  o << tab << "<fog>\n";
  o << tab << "\t<enable>" << _fog_enable << "</enable>\n";
  o << tab << "\t<mode>" << _fog_mode << "</mode>\n";
  o << tab << "\t<parameters>" << _fog_parameter[0] << " "
    << _fog_parameter[1] << " " << _fog_parameter[2] << "</parameters>\n";
  o << tab << "\t<color>";
  o << tab <<  _fog_color[0] << " ";
  o << tab <<  _fog_color[1] << " ";
  o << tab <<  _fog_color[2] << "</color>\n";
  o << tab << "</fog>\n";

#if 0
  // hints
  o << tab << "<hints>\n";
  o << tab << "\t<hint_point_smooth>"
    << _hint_point_smooth << "</hint_point_smooth>\n";
  o << tab << "\t<hint_line_smooth>"
    << _hint_line_smooth << "</hint_line_smooth>\n";
  o << tab << "\t<hint_polygon_smooth>"
    << _hint_polygon_smooth << "</hint_polygon_smooth>\n";
  o << tab << "\t<hint_fog>"
    << _hint_fog << "</hint_fog>\n";
  o << tab << "\t<hint_perspective_correction>"
    << _hint_perspective_correction << "</hint_perspective_correction>\n";
  o << tab << "</hints>\n";
#endif
}

} // namespace kernel
} // namespace milieu
