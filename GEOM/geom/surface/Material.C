/* GANG Software
 * GEOM/geom/surface/Material.C
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

#include "io/OstreamStream.H"
#include "base/System.H"
#include "Material.H"

namespace geom {
namespace surface {

GLenum const Material::polygon_mode[3] =
{ GL_POINT, GL_LINE, GL_FILL };

GLenum const Material::polygon_offset[3] =
{
  GL_POLYGON_OFFSET_POINT,
  GL_POLYGON_OFFSET_LINE,
  GL_POLYGON_OFFSET_FILL
};

GLenum const
Material::material_model[6] =
{
  GL_AMBIENT,
  GL_DIFFUSE,
  GL_AMBIENT_AND_DIFFUSE,
  GL_SPECULAR,
  GL_EMISSION
};

Material::
Material()
{
  reset();
}

Material::
Material( Material const &a )
{
  copy( a );
}

Material::
~Material()
{
}

Material &
Material::
operator=( Material const &a )
{
  copy( a );
  return *this;
}

void
Material::
copy( Material const &a )
{
  if ( this == &a ) { return; }

  _enable = a._enable;

  _custom_color = a._custom_color;
  _lit = a._lit;
  _color = a._color;
  _ambient = a._ambient;
  _diffuse = a._diffuse;
  _specular = a._specular;
  _emissive = a._emissive;
  _shininess = a._shininess;

  _element_size = a._element_size;
  _gap = a._gap;
  _model = a._model;
  _shademodel = a._shademodel;
  _nudge = a._nudge;
  _side = a._side;
  _transparent = a._transparent;
}

void
Material::
reset()
{
  _enable = false;
  _ambient = base::Color3( 0.0f, 0.0f, 0.0f );
  _diffuse = base::Color4( 1.0f, 1.0f, 1.0f, 1.0f );
  _specular = base::Color3( 0.0f, 0.0f, 0.0f );
  _emissive = base::Color3( 0.0f, 0.0f, 0.0f );
  _shininess = 0.0f;
  _element_size = 1.0f;
  float const gap[2] = { 0.0f, 0.0f };
  _gap = gap;
  _model = 2;
  _shademodel = false;
  float const nudge[2] = { 0.0f, 0.0f };
  _nudge = base::ArrayX<float,2U>(nudge);
  uint side[2] = { 0U, 0U };
  _side = base::ArrayX<uint,2U>(side);
  _lit = true;
  _transparent = false;
  _custom_color = false;
}

void
Material::
dump( io::Ostream &o ) const
{
  char *tab = "\t\t";

  o << tab << "<material>\n";
  o << tab << "\t<enable>" << _enable << "</enable>\n";
  o << tab << "\t<color>" << _color[0] << " " << _color[1] << " "
    << _color[2] << " " << _color[3] << "</color>\n";
  o << tab << "\t<ambient>"
    <<  _ambient[0] << " " << _ambient[1] << " " << _ambient[2]
    << "</ambient>\n";
  o << tab << "\t<diffuse>"
    << _diffuse[0] << " " << _diffuse[1] << " " << _diffuse[2]
    << " " << _diffuse[3] << "</diffuse>\n";
  o << tab << "\t<specular>"
    << _specular[0] << " " << _specular[1] << " " << _specular[2]
    << "</specular>\n";
  o << tab << "\t<emissive>"
    << _emissive[0] << " " << _emissive[1] << " " << _emissive[2]
    << "</emissive>\n";
  o << tab << "\t<shininess>" << _shininess << "</shininess>\n";
  o << tab << "\t<element_size>" << _element_size << "</element_size>\n";
  o << tab << "\t<gap>" << _gap[0] << " " << _gap[1] << "</gap>\n";
  o << tab << "\t<model>" << _model << "</model>\n";
  o << tab << "\t<shademodel>" << _shademodel << "</shademodel>\n";
  o << tab << "\t<nudge>" << _nudge[0] << " " << _nudge[1] << "</nudge>\n";
  o << tab << "\t<side>" << _side[0] << " " << _side[1] << "</side>\n";
  o << tab << "\t<lit>" << _lit << "</lit>\n";
  o << tab << "\t<transparent>" << _transparent << "</transparent>\n";
  o << tab << "\t<custom_color>" << _custom_color << "</custom_color>\n";
  o << tab << "</material>\n";
}


} // namespace surface
} // namespace geom
