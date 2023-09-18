/* GANG Software
 * GEOM/milieu/kernel/Light.C
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
namespace kernel {

Light::
Light()
    :
    _enable(false),
    _moving(false),
    _show(false),
    _attached(false),
    _position()
{
  _position.identity(4U);

#if 0
  // default light in HSV
  _default_light._diffuse[0] = 0.0f;
  _default_light._diffuse[1] = 0.0f;
  _default_light._diffuse[2] = 1.0f;

  _default_light._specular[0] = 0.0f;
  _default_light._specular[1] = 0.0f;
  _default_light._specular[2] = 1.0f;
#endif

  reset();
}

Light::
Light( Light const &a )
{
  copy(a);
}

Light::
~Light()
{
}

Light &
Light::
operator=( Light const &a )
{
  copy(a);
  return *this;
}

void
Light::
reset()
{
  _enable = false;
  _moving = false;
  _show = false;
  _attached = false;

  _ambient = base::Color3( 0.0f, 0.0f, 0.0f );
  _diffuse = base::Color3( 0.5f, 0.5f, 0.5f );
  _specular = base::Color3( 1.0f, 1.0f, 1.0f );

  _spot[0] = 0.0;
  _spot[1] = 0.0;
  _spot[2] = -1.0;
  _spot[3] = 0.0;
  _spot[4] = 1.0;

  _attenuation[0] = 1.0;
  _attenuation[1] = 0.0;
  _attenuation[2] = 0.0;

}

void
Light::
copy( Light const &a )
{
  if ( this == &a ) { return; }

  _ambient = a._ambient;
  _diffuse = a._diffuse;
  _specular = a._specular;
  _spot = a._spot;
  _attenuation = a._attenuation;
}

void
Light::
dump( io::Ostream &o ) const
{
  char const *tab = "\t\t\t";
  o << tab << "<light>\n";
  o << tab << "\t<enable>" << _enable << "</enable>\n";
  o << tab << "\t<ambient>"
    << _ambient[0] << " " << _ambient[1] << " " << _ambient[2]
    << "</ambient>\n";
  o << tab << "\t<diffuse>"
    << _diffuse[0] << " " << _diffuse[1] << " " << _diffuse[2]
    << "</diffuse>\n";
  o << tab << "\t<specular>"
    << _specular[0] << " " << _specular[1] << " " << _specular[2]
    << "</specular>\n";
  o << tab << "\t<spot>"
    << _spot[0] << " " << _spot[1] << " " << _spot[2] << " "
    << _spot[3] << " " << _spot[4]
    << "</spot>\n";
  o << tab << "\t<attenuation>"
    << _attenuation[0] << " " << _attenuation[1] << " " << _attenuation[2]
    << "</attenuation>\n";
  write_transform( o, position(), "\t\t\t\t" );
  o << tab << "</light>\n";
}

} // namespace kernel
} // namespace milieu
