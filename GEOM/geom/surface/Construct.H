/* GANG Software
 * GEOM/geom/surface/Construct.H
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

#ifndef geom_surface_Construct_INCLUDED
#define geom_surface_Construct_INCLUDED

#include "geom/surface0/Common.H"
#include "geom/surface0/Transformer.H"
#include "SurfaceBase.H"

namespace geom {
namespace surface {

class Construct
  :
    public SurfaceBase
{

public:
  typedef geom::Real Real;

  // constructor
  Construct();

  // copy constructor
  Construct( Construct const & );

  // destructor
  virtual ~Construct();

  // assignment operator
  Construct &operator=( Construct const & );

  void apply( geom::surface0::Transformer const &f );
  void transform( geom::Transform const &a );
  void translate( math::VectorX<Real,3U> const &a );
  void reflect( math::VectorX<Real,4U> const &a );
  void build_reflect( math::VectorX<Real,4U> const &a );

  void reverse_orientation();
  void remove_to_one();

  geom::Real glue(
    uint g0, uint g1,
    std::list<uint> const &boundaryset );

  geom::Real glue_self(
    uint part,
    std::list<uint> const &boundaryset1,
    std::list<uint> const &boundaryset2 );

protected:

private:
};

} // namespace surface
} // namespace geom

#endif // geom_surface_Construct_INCLUDED
