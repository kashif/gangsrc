/* GANG Software
 * GEOM/geom/interface/Common.H
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

#ifndef geom_Common_INCLUDED
#define geom_Common_INCLUDED

#include "math/Vector2.H"
#include "math/Vector3Math.H"
#include "math/VectorX.H"
#include "math/Matrix.H"

namespace geom {

typedef double Real;
typedef math::Vector2<Real> Vertex2;
typedef math::Vector3Math<Real> Vertex3;
typedef math::VectorX<Real,4U> Vertex4;
typedef math::Matrix<Real> Transform;

struct Box { Real xmin, xmax, ymin, ymax, zmin, zmax; };

enum FileMode
{
  FILEMODE_ERROR,
  FILEMODE_UNSPECIFIED,
  FILEMODE_ISX,
  FILEMODE_JVX,
  FILEMODE_VRML,
  FILEMODE_OOGL,
  FILEMODE_MATHEMATICA,
  FILEMODE_POVRAY,
  FILEMODE_DEFAULT = FILEMODE_JVX
};

FileMode get_filemode( base::String const &filename );

enum MaterialMeaning
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


struct SpaceForm
{
  enum Space { SPACEFORM_R, SPACEFORM_S, SPACEFORM_H };

  SpaceForm(uint dim_, Space space_) : dim(dim_), space(space_) {}
  SpaceForm() : dim(3U), space(SPACEFORM_R) {}

  uint dim;
  Space space;
};

} // namespace geom

#endif // geom_Common_INCLUDED
