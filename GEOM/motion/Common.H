/* GANG Software
 * GEOM/motion/Common.H
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

#ifndef motion_Common_INCLUDED
#define motion_Common_INCLUDED

#include "math/Matrix.H"
#include "math/Vector3.H"

namespace motion {

typedef double Real;
typedef math::Matrix<Real> Transform;
enum ProjectionMode { CENTRAL, STEREOGRAPHIC };

enum GeometryMode { PROJECTIVE=0, CONFORMAL=1, MOEBIUS=2 };
enum GeometryGroup { PARABOLIC=0, HYPERBOLIC=1, ELLIPTIC=2 };
enum MouseMode
{ MM_NOTHING=0, ROTATION=1, TRANSLATION=2, INVERSION=3, SCALE=4 };


struct Place
{
  Transform position;
  Transform rotation;
  Transform translation;
};

typedef math::Vector3<Real> Center;

} // namespace motion

#endif // motion_Common_INCLUDED
