/* GANG Software
 * GEOM/geom/surface/Material.H
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

#ifndef geom_surface_Material_INCLUDED
#define geom_surface_Material_INCLUDED

#include <GL/gl.h>
#include "base/ArrayX.H"
#include "base/Color3.H"
#include "base/Color4.H"
#include "io/Ostream.H"
#include "geom/surface0/Common.H"

namespace geom {
namespace surface {

/*
  Materials for an OpenGL drawable surface, such as color and shininess.
 */

class Material
{
public:

  // void constructor
  Material();

  // destructor.
  ~Material();

  // copy constructor
  Material( Material const & );

  // assignment operator
  Material &operator=(  Material const & );

  void copy( Material const & );

  /*
     returns:
     false if object is invisible either because
     show==false or size is too small
     true otherwise
  */
  void reset();
  void dump( ::io::Ostream &o ) const;

  bool const &enable() const
    { return _enable; }
  base::Color4 const &color() const
    { return _color; }
  base::Color3 const &ambient() const
    { return _ambient; }
  base::Color4 const &diffuse() const
    { return _diffuse; }
  base::Color3 const &specular() const
    { return _specular; }
  base::Color3 const &emissive() const
    { return _emissive; }
  float const &shininess() const
    { return _shininess; }
  float const &element_size() const
    { return _element_size; }
  base::ArrayX<float,2U> const &gap() const
    { return _gap; }
  uint const &model() const
    { return _model; }
  bool const &shademodel() const
    { return _shademodel; }
  base::ArrayX<float,2U> const &nudge() const
    { return _nudge; }
  base::ArrayX<uint,2U>const &side() const
    { return _side; }
  bool const &lit() const
    { return _lit; }
  bool const &transparent() const
    { return _transparent; }
  bool const &custom_color() const
    { return _custom_color; }

  void enable( bool a )
    { _enable = a; }
  void color( base::Color4 const &a )
    { _color = a; }
  void ambient( base::Color3 const &a )
    { _ambient = a; }
  void diffuse( base::Color4 const &a )
    { _diffuse = a; }
  void specular( base::Color3 const &a )
    { _specular = a; }
  void emissive( base::Color3 const &a )
    { _emissive = a; }
  void shininess( float a )
    { _shininess = a; }
  void element_size( float a )
    { _element_size = a; }
  void gap( base::ArrayX<float,2U> const &a )
    { _gap = a; }
  void model( uint const &a )
    { _model = a; }
  void shademodel( bool a )
    { _shademodel = a; }
  void nudge( base::ArrayX<float,2U> const &a )
    { _nudge = a; }
  void side( base::ArrayX<uint,2U> const &a )
    { _side = a; }
  void lit( bool a )
    { _lit = a; }
  void transparent( bool a )
    { _transparent = a; }
  void custom_color( bool a )
    { _custom_color = a; }
  
protected:

  // false means don't draw the object
  bool _enable;

  // material attributes
  // colors are in RGB or RGBA format
  base::Color4 _color;
  base::Color3 _ambient;
  base::Color4 _diffuse;
  base::Color3 _specular;
  base::Color3 _emissive;
  float _shininess;

  // size: size of element (point size, line width, face size)
  float _element_size;

  base::ArrayX<float,2U> _gap;


  /* material model:
     0 = GL_FALSE
     1 = GL_AMBIENT
     2 = GL_DIFFUSE
     3 = GL_AMBIENT_AND_DIFFUSE
     4 = GL_SPECULAR
     5 = GL_EMISSION
  */

  uint _model;
  bool _custom_color;

  /* what shademodel to draw the surface
     0 = GL_FLAT
     1 = GL_SMOOTH
  */
  bool _shademodel;

  // used by glPolygonOffset
  base::ArrayX<float,2U> _nudge;

  // which sides to sho
  // 0=none, 1=point 2=line 3=fill
  base::ArrayX<uint,2U> _side;

  bool _lit;
  bool _transparent;

  static GLenum const material_model[6];

  static GLenum const polygon_mode[3];
  static GLenum const polygon_offset[3];

private:

};

} // namespace surface
} // namespace geom

#endif // geom_surface_Material_INCLUDED
