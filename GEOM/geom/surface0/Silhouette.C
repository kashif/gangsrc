/* GANG Software
 * GEOM/geom/surface0/Silhouette.C
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

#include "Silhouette.H"

namespace geom {
namespace surface0 {

Silhouette::
Silhouette()
    :
    Normal(),
    _silhouette_vector()
{
}

Silhouette::
Silhouette( Silhouette const &a )
    :
    Normal(a),
    _silhouette_vector( a._silhouette_vector )
{
}

Silhouette::
~Silhouette()
{
}

Silhouette &
Silhouette::
operator=( Silhouette const &a )
{
  if ( this == &a ) { return *this; }

  Normal::operator=(a);
  _silhouette_vector = a._silhouette_vector;

  return *this;
}

void
Silhouette::
clear()
{
  Normal::clear();
  clear_silhouette();
}

void
Silhouette::
clear_silhouette()
{
  _silhouette_vector.clear();
}

bool
Silhouette::
first_silhouette_segment(
  EdgeMap::const_iterator &i,
  math::Matrix4<Real> const &transform ) const
{
  /*
    Returns iterator pointing to next edge which is a visual boundary

    Algorithm:

    1. If (r1, r2, r3, r4) is a plane (i.e. the plane with equation
       r1 x1 + r2 x2 + r3 x3 + r4 x4 = 0), and T is a transform
       (4x4 matrix), then r T^{-1} is the transform of r.
       Proof: Let s be the transform of r. Then r.p = 0 iff s.Tp = 0.

    2. The plane through a point (p1, p2, p3, p4)^t with normal
       n=(n1, n2, n3) is r=(n1, n2, n3, y), where y = -(n1*p1+n2*p2+n3*p3)/p4.
       Proof: the first three coordinates say that the n is normal to r.
       The last coordinate y is found by solving r.p=0.

    3. Let z = (0, 0, 0, 1). This is the direction toward the camera,
       since OpenGL always projects this way after a transformation.
       We want the dot product
         <r.M^{-1}, z> = (r.M^{-1}).z^t = r.(M^{-1}.z^t)
   */

  compute_edge();
  compute_normal();

  // precompute a vector needed to compute the visual boundary
  // _silhouette_vector = T^{-1}.(0,0,1,0)^t

  _silhouette_vector[0] = 0.0;
  _silhouette_vector[1] = 0.0;
  _silhouette_vector[2] = 1.0;
  _silhouette_vector[3] = 0.0;

  math::Matrix4<Real> t;
  t.inv(transform);

  t.mulleft( _silhouette_vector );

  i = edge().begin();
  return next_silhouette_segment_(i);
}


bool
Silhouette::
next_silhouette_segment(
  EdgeMap::const_iterator &i ) const
{
  i++;
  return next_silhouette_segment_(i);
}


bool
Silhouette::
next_silhouette_segment_(
  EdgeMap::const_iterator &i ) const
{
  Vertex4 &w = _silhouette_vector;

  for(;;)
  {
    if ( i == edge().end() ) { break; }
    if ( (*i).second.size() == 2 )
    {
      Vertex4 p;
      vertex( p, (*i).first.first );
      if (p[3]<0.0f) { p = -p; }

      DIE_IF( (*i).second[0] >= face_count() );
      Normal3 const &n1 = face_normal( (*i).second[0] );

      Real r0 =
        n1.x*(w[0]*p[3] - w[3]*p[0]) +
        n1.y*(w[1]*p[3] - w[3]*p[1]) +
        n1.z*(w[2]*p[3] - w[3]*p[2]);

      vertex( p, (*i).first.second );
      if (p[3]<0.0f) { p = -p; }

      DIE_IF( (*i).second[1] >= face_count() );
      Normal3 const &n2 = face_normal( (*i).second[1] );

      Real r1 =
        n2.x*(w[0]*p[3] - w[3]*p[0]) +
        n2.y*(w[1]*p[3] - w[3]*p[1]) +
        n2.z*(w[2]*p[3] - w[3]*p[2]);

      if ( (r0 >= 0.0f && r1 <= 0.0f) || (r0 <= 0.0f && r1 >= 0.0f) )
      {
        break;
      }
    }
    i++;
  }
  return i == edge().end();
}

} // namespace surface0
} // namespace geom
