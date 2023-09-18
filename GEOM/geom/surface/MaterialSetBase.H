/* GANG Software
 * GEOM/geom/surface/MaterialSetBase.H
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

#ifndef geom_surface_MaterialSetBase_INCLUDED
#define geom_surface_MaterialSetBase_INCLUDED

#include "base/System.H"
#include "io/Ostream.H"
#include "Material.H"

namespace geom {
namespace surface {

class MaterialSetBase
{

public:
  // constructor
  MaterialSetBase();

  // copy constructor
  MaterialSetBase( MaterialSetBase const & );

  // destructor
  virtual ~MaterialSetBase();

  // assignment operator
  MaterialSetBase &operator=( MaterialSetBase const & );

  void reset_materials();
  void reset_materials( uint n );
  void dump_materials( ::io::Ostream &o ) const;
  void dump_materials( uint i, ::io::Ostream &o ) const;

  bool const &enable(uint id) const
    { return operator[](id).enable(); }
  bool const &shademodel(uint id) const
    { return operator[](id).shademodel(); }
  uint const &model(uint id) const
    { return operator[](id).model(); }
  float const &element_size(uint id) const
    { return operator[](id).element_size(); }
  base::ArrayX<float,2U> const &gap(uint id) const
    { return operator[](id).gap(); }
  base::Color4 const &color(uint id) const
    { return operator[](id).color(); }
  base::Color3 const &ambient(uint id) const
    { return operator[](id).ambient(); }
  base::Color4 const &diffuse(uint id) const
    { return operator[](id).diffuse(); }
  base::Color3 const &specular(uint id) const
    { return operator[](id).specular(); }
  base::Color3 const &emissive(uint id) const
    { return operator[](id).emissive(); }
  float const &shininess(uint id) const
    { return operator[](id).shininess(); }
  base::ArrayX<uint,2U> const &side( uint id ) const
    { return operator[](id).side(); }
  base::ArrayX<float,2U> const &nudge(uint id ) const
    { return operator[](id).nudge(); }
  bool const &lit( uint id ) const
    { return operator[](id).lit(); }
  bool const &transparent( uint id ) const
    { return operator[](id).transparent(); }
  bool const &custom_color( uint id ) const
    { return operator[](id).custom_color(); }

  void enable( uint id, bool a )
    { operator[](id).enable(a); changed(); }
  void shademodel( uint id, bool a )
    { operator[](id).shademodel(a); changed(); }
  void model( uint id, uint a )
    { operator[](id).model(a); changed(); }
  void element_size( uint id, float a )
    { operator[](id).element_size(a); changed(); }
  void gap( uint id, base::ArrayX<float,2U> const &a )
    { operator[](id).gap(a); changed(); }
  void color( uint id, base::Color4 const &a )
    { operator[](id).color(a); changed(); }
  void ambient( uint id, base::Color3 const &a )
    { operator[](id).ambient(a); changed(); }
  void diffuse( uint id, base::Color4 const &a )
    { operator[](id).diffuse(a); changed(); }
  void specular( uint id, base::Color3 const &a )
    { operator[](id).specular(a); changed(); }
  void emissive( uint id, base::Color3 const &a )
    { operator[](id).emissive(a); changed(); }
  void shininess( uint id, float a )
    { operator[](id).shininess(a); changed(); }
  void side( uint id, base::ArrayX<uint,2U> const &a )
    { operator[](id).side(a); changed(); }
  void nudge( uint id, base::ArrayX<float,2U> const &a )
    { operator[](id).nudge(a); changed(); }
  void lit( uint id, bool a )
    { operator[](id).lit(a); changed(); }
  void transparent( uint id, bool a )
    { operator[](id).transparent(a); changed(); }
  void custom_color( uint id, bool a )
    { operator[](id).custom_color(a); changed(); }

  virtual Material &operator[](uint n) = 0;
  virtual Material const &operator[](uint n) const = 0;

  static uint count()
    { return MATERIALS_COUNT; }

  enum Meaning
  {
    FACE = 0,
    EDGE = 1,
    VERTEX = 2,
    FACE2 = 3,
    LINE = 4,
    POINT = 5,
    BOUNDARY = 6,
    SILHOUETTE = 7,
    BBOX = 8
  };

protected:

  virtual void changed() const {}

  void _reset();

  static uint const MATERIALS_COUNT = 9U;

private:

  void _reset(uint n);
};

} // namespace surface
} // namespace geom

#endif // geom_surface_MaterialSetBase_INCLUDED
