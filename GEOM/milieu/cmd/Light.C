/* GANG Software
 * GEOM/milieu/cmd/Light.C
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

#include "Light.H"

namespace milieu {
namespace cmd {

Light::
Light()
    :
    _id_w(),
    _enable_w(),
    _moving_w(),
    _attached_w(),
    _ambient_w(3U),
    _diffuse_w(3U),
    _specular_w(3U),
    _spot_w(5U),
    _attenuation_w(3U),
    _hidebox_w()
{
}

Light::
~Light()
{
}

} // namespace cmd
} // namespace milieu
