/* GANG Software
 * GEOM/geom/surfacegl/Material.C
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

#include "Material.H"

namespace geom {
namespace surfacegl {

Material::
Material()
    :
    geom::surface::Material()
{
}

Material::
Material( Material const &a )
    :
    geom::surface::Material(a)
{
}

Material::
~Material()
{
}

Material &
Material::
operator=( Material const &a )
{
  if ( this == &a ) { return *this; }
  geom::surface::Material::operator=(a);
  return *this;
}



bool
Material::
draw() const
{
  return _enable && _element_size != 0;
}

bool
Material::
draw_color() const
{
  return _custom_color;
}

bool
Material::
draw_normal() const
{
  return _lit;
}

void
Material::
begin() const
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  GLenum const s = GL_FRONT_AND_BACK;

  if ( _lit )
  {
    /*
      Set the meaning of subsequent glColor() calls.
      If _model==0, subsequent calls to glColor() will have no effect.
    */
    if ( _custom_color )
    {
      /*
        E.g. The call
          glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT )
        means that subsequent calls to glColor(c) color the element with
        ambient color c (i.e. matching ambient lighting).

        Note: a subsequent call to glColor() overrides the color set by
          glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, c )

        These only have an effect when lighting is on.
      */
      glEnable( GL_COLOR_MATERIAL );
      glColorMaterial( s, material_model[_model] );
    }

    /*
      Set the material colors/shininess.

      E.g. The call
        glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, c )
      means that elements are drawn with ambient color c (i.e. matching
      ambient lighting), irrespective of subsequent calls to glColor()

      These only have an effect when lighting is on.
    */
    glMaterialfv( s, GL_AMBIENT, _ambient.data() );
    glMaterialfv( s, GL_DIFFUSE, _diffuse.data() );
    glMaterialfv( s, GL_SPECULAR, _specular.data() );
    glMaterialfv( s, GL_EMISSION, _emissive.data() );
    glMaterialf( s, GL_SHININESS, 128.0f * _shininess );

  }
  else
  {
    glDisable(GL_LIGHTING);
  }
  /*
    Default color. This sets the color that elements are drawn in,
    until subsequent glColor() calls are made.

    This only have an effect when lighting is off.
  */
  ::opengl::glColor( _color );


#if defined(__sgi)
  glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, 1 );
#endif

  // showing faces
  if ( _side[0] == _side[1] )
  {
    if ( _side[0] > 0 )
    {
      // both positive
      glPolygonMode( GL_FRONT_AND_BACK, polygon_mode[_side[0]-1] );
      glDisable(GL_CULL_FACE);
    }
    else
    {
      // both zero
      glEnable(GL_CULL_FACE);
      glCullFace( GL_FRONT_AND_BACK );
    }
  }
  else
  {
    if ( _side[0] > 0 && _side[1] > 0 )
    {
      // show front and back
      glPolygonMode( GL_FRONT, polygon_mode[_side[0]-1] );
      glPolygonMode( GL_BACK, polygon_mode[_side[1]-1] );
      glDisable(GL_CULL_FACE);
    }
    else if ( _side[0] > 0 )
    {
      // show front; cull back
      glPolygonMode( GL_FRONT, polygon_mode[_side[0]-1] );
      glEnable(GL_CULL_FACE);
      glCullFace( GL_BACK );
    }
    else
    {
      // show back; cull front
      glPolygonMode( GL_BACK, polygon_mode[_side[1]-1] );
      glEnable(GL_CULL_FACE);
      glCullFace( GL_FRONT );
    }
  }

  // shademodel (Gourand shading on/off)
  if ( _shademodel )
  {
    glShadeModel(GL_SMOOTH);
  }
  else
  {
    glShadeModel(GL_FLAT);
  }

  // point size
  glPointSize( int(_element_size) );

  // line size
  glLineWidth( int(_element_size) );

  // polygon offset
  if (_side[1] > 0 )
  {
    glEnable( polygon_offset[_side[1]-1] );
    glPolygonOffset( _nudge[0], _nudge[1] );
  }

  // transparency
  if ( _transparent )
  {
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
  }
}


void
Material::
end() const
{
  glPopAttrib();
}

} // namespace surfacegl
} // namespace geom
