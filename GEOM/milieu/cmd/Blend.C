/* GANG Software
 * GEOM/milieu/cmd/Blend.C
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
namespace cmd {

Blend::
Blend()
    :
    _depth_enable_w(),
    _depth_function_w(),
    _depth_mask_w(),
    _blend_dest_function_w(),
    _blend_src_function_w(),
    _blend_enable_w(),
    _antialias_point_w(),
    _antialias_line_w(),
    _fog_enable_w(),
    _fog_mode_w(),
    _fog_parameter_w(3U),
    _fog_color_w(3U)
{
}

Blend::
~Blend()
{
}

} // namespace cmd
} // namespace milieu
