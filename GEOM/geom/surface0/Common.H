/* GANG Software
 * GEOM/geom/surface0/Common.H
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

#ifndef geom_surface0_Common_INCLUDED
#define geom_surface0_Common_INCLUDED

#include "base/String.H"
#include "math/Vector2.H"
#include "math/Vector3Math.H"
#include "math/VectorX.H"
#include "math/Vector.H"
#include "math/Matrix.H"
#include "geom/interface/Common.H"

namespace geom {

#if 0
typedef double Real;

// inhomogeneous vertex
typedef math::Vector2<Real> Vertex2;

// inhomogeneous vertex
typedef math::Vector3Math<Real> Vertex3;

// homogeneous vertex
typedef math::VectorX<Real,4U> Vertex4;

//
typedef math::Matrix<Real> Transform;
#endif

//
enum ProjectionMode { CENTRAL, STEREOGRAPHIC };

// normal vector in R^3
typedef math::Vector3Math<geom::Real> Normal3;

#if 0
struct Box
{
  Real xmin, xmax;
  Real ymin, ymax;
  Real zmin, zmax;
};

struct SpaceForm
{
  enum Space { SPACEFORM_R, SPACEFORM_S, SPACEFORM_H };

  SpaceForm(uint dim_, Space space_) : dim(dim_), space(space_) {}
  SpaceForm() : dim(3U), space(SPACEFORM_R) {}

  uint dim;
  Space space;
};
#endif

} // namespace geom

#endif // geom_surface0_Common_INCLUDED
