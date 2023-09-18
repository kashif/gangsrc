/* GANG Software
 * GEOM/geom/surface0/Geometry.C
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

#include "base/Stl.H"
#include "Geometry.H"

namespace geom {
namespace surface0 {

Geometry::
Geometry()
    :
    Silhouette(),
    _vertex_gaussian_curvature(),
    _face_gaussian_curvature(),
    _face_mean_curvature(),
    _face_area()
{
}

Geometry::
Geometry( Geometry const &a )
    :
    Silhouette(a),
    _vertex_gaussian_curvature( a._vertex_gaussian_curvature ),
    _face_gaussian_curvature( a._face_gaussian_curvature ),
    _face_mean_curvature( a._face_mean_curvature ),
    _face_area( a._face_area )
{
}

Geometry::
~Geometry()
{
}

Geometry &
Geometry::
operator=( Geometry const &a )
{
  if ( this == &a ) { return *this; }

  Silhouette::operator=(a);

  _vertex_gaussian_curvature = a._vertex_gaussian_curvature;
  _face_gaussian_curvature = a._face_gaussian_curvature;
  _face_mean_curvature = a._face_mean_curvature;
  _face_area = a._face_area;

  return *this;
}

void
Geometry::
clear()
{
  Silhouette::clear();
  clear_geometry();
}

void
Geometry::
clear_geometry()
{
  _vertex_gaussian_curvature.clear();
  _face_gaussian_curvature.clear();
  _face_mean_curvature.clear();
  _face_area.clear();
}

void
Geometry::
compute_face_gaussian_curvature() const
{
  // computes the gaussian curvature for each face
  // (used by triangulator)
  // algorithm: compute the vertex gaussian curvature, then
  //   average

  if ( ! _vertex_gaussian_curvature.empty() ) { return; }

  compute_vertex_gaussian_curvature();

  uint face_count_ = face_count();
  _face_gaussian_curvature.reserve( face_count_ );

  // cycle through the faces
  uint i;
  for ( i = 0; i < face_count_; i++ )
  {
    // cycle through the vertices of this face
    Real c = 0.0;
    uint j;
    uint face_count_ = face_count(i);
    for ( j = 0; j < face_count_; j++ )
    {
      uint f = face_vertex(i, j);
      c += _vertex_gaussian_curvature[f];
    }
    _face_gaussian_curvature.push_back( c/face_count_ );
  }
}

void
Geometry::
compute_vertex_gaussian_curvature() const
{
  if ( ! _vertex_gaussian_curvature.empty() ) { return; }

  changed(true);

  uint const INTERIOR_POINT = UINT_MAX;

  // compute the edges
  // the curvature on a point on the surface boundary is assigned the
  // curvature of an adjacent interior point. (Approximating curvature
  // on the boundary by angles and areas doesn't work.)

  compute_pushoff();

  // compute Gaussian curvature

  CurvatureData p = { 0.0f, 0.0f, 0, false };
  base::vector<CurvatureData> curvature;
  uint vertex_count_ = vertex_count();
  curvature.fill( p, vertex_count_ );

  // Cycle through faces. for each face, cycle through its vertices
  // for each vertex, compute the area and angle of the triangle spanned by
  // it and the two adjacent vertices
  // accumulate the area and angle

  Vertex3 tmp1, tmp2, tmp3;

  uint i;
  uint face_count_ = face_count();
  for ( i = 0; i < face_count_; i++ )
  {
    uint j;
    uint face_count_ = face_count(i);
    for ( j = 0; j < face_count_; j++ )
    {
      uint j0 = prev( j, face_count_ );
      uint j1 = next( j, face_count_ );

      uint k0 = face_vertex(i, j0);
      uint k  = face_vertex(i, j);
      uint k1 = face_vertex(i, j1);

      vertex( tmp1, k0 );
      vertex( tmp2, k );
      vertex( tmp3, k1 );

      // accumulate the angle and area
      curvature[k].angle += Vertex3::angle( tmp1, tmp2, tmp3 );
      curvature[k].area += Vertex3::area( tmp1, tmp2, tmp3 );
      curvature[k].count++;
    }
  }

  _vertex_gaussian_curvature.reserve(vertex_count_);

  // compute gaussian curvature at each point
  for ( i = 0; i < vertex_count_; i++ )
  {
    Real K = 0.0f;
    if ( pushoff(i) == INTERIOR_POINT )
    {
      Real d = curvature[i].area;
      if ( !math::effectively_zero(d) )
      {
        K = (( curvature[i].boundary ? math::pi : 2.0f*math::pi ) -
             curvature[i].angle )/d;
        K *= 2.0f;
      }
    }
    _vertex_gaussian_curvature.push_back(K);
  }

  // compute gaussian curvature along boundary
  for ( i = 0; i < vertex_count_; i++ )
  {
    if ( pushoff(i) < UINT_MAX - 1 )
    {
      _vertex_gaussian_curvature[i] = _vertex_gaussian_curvature[pushoff(i)];
    }
  }

}

void
Geometry::
compute_face_mean_curvature() const
{
  if ( ! _face_mean_curvature.empty() ) { return; }

  changed(true);

  compute_pushoff();

  _face_mean_curvature.fill( Real(0.0), face_count() );

  base::vector<uint> count;
  count.fill( (uint)0, face_count() );


  // cycle through edges
  EdgeMap::const_iterator o;
  for ( o = edge().begin(); o != edge().end(); o++ )
  {
    // skip o if it is not an interior edge
    if ( (*o).second.size() != 2 ) { continue; }

    // o is an interior edge

    // set f0 and f1 to the indices of the faces adjacent to edge o
    uint f0 = (*o).second[0];
    uint f1 = (*o).second[1];

    // skip faces with fewer than 3 vertices
    if ( face_count(f0) < 3 ||
         face_count(f1) < 3 ) { continue; }

    // set (v0, v1) to the indices of the vertices of edge o
    uint v0 = (*o).first.first;
    uint v1 = (*o).first.second;

    uint t0, t1;

    /* set t0, t1 to make this diagram:

                 v1
                 |
            f0   |   f1
                 |
        t0 ----- v0 ----- t1
    */
    t0 = third_vertex( f0, v0, v1 );
    t1 = third_vertex( f1, v0, v1 );

    // compute the mean curvature at v0
    Real H1 = mean_curvature( v0, v1, t0, t1 );

    /* set t0, t1 to make this diagram:

        t0 ----- v1 ----- t1
                 |
            f0   |   f1
                 |
                v0
    */
    t1 = third_vertex( f1, v1, v0 );
    t0 = third_vertex( f0, v1, v0 );

    // compute the mean curvature at v1
    Real H2 = mean_curvature( v1, v0, t1, t0 );

    _face_mean_curvature[f0] += H1;
    count[f0]++;
    _face_mean_curvature[f1] += H2;
    count[f1]++;
  }

  uint i;
  for (i = 0; i < face_count(); i++ )
  {
    if (count[i] != 0)
    {
      _face_mean_curvature[i] /= count[i];
    }
  }
}

void
Geometry::
compute_face_area() const
{
  if ( ! _face_area.empty() ) { return; }

  // computes the area of each face; put results into 'area'

  // initialize _area
  uint face_count_ = face_count();
  _face_area.reserve( face_count_ );

  Vertex3 tmp1, tmp2, tmp3;

  // cycle through the faces computing the area of each
  uint i;
  for ( i = 0; i < face_count_; i++ )
  {
    // compute the area of this face
    Real a = 0;
    uint j;
    uint face_count_ = face_count(i);
    for ( j = 0; j < face_count_; j++ )
    {
      uint j0 = prev( j, face_count_ );
      uint j1 = next( j, face_count_ );

      uint k0 = face_vertex(i, j0);
      uint k  = face_vertex(i, j);
      uint k1 = face_vertex(i, j1);

      vertex( tmp1, k0 );
      vertex( tmp2, k );
      vertex( tmp3, k1 );

      a += Vertex3::area( tmp1, tmp2, tmp3 );
    }
    _face_area.push_back( a );
  }
}

Real
Geometry::
mean_curvature(
  uint v0,
  uint v1,
  uint t0,
  uint t1 ) const
{
  /*
    Returns the discrete mean curvature along the edge v0 -- v1.
    The two edges v0 -- t0 and v0 -- t1 are adjacent to the edge v0 -- v1
    as shown:

                 v1
                 |
         face0   |   face1
                 |
        t0 ----- v0 ----- t1


    The discrete mean curvature is

         mean_curvature = angle * length / area

    where
         angle = dihedral_angle( face0, face1 )
         length = length(v0, v1)
         area = area(face0) + area(face1)
  */

  Vertex3 v0_, v1_, t0_, t1_;

  vertex( v0_, v0 );
  vertex( v1_, v1 );
  vertex( t0_, t0 );
  vertex( t1_, t1 );

  Real angle =  Vertex3::dihedral_angle( v0_, v1_, t0_, t1_ );

  Real area = Vertex3::area( t0_, v0_, v1_ ) +
    Vertex3::area( v1_, v0_, t1_ );

  Real length = Vertex3::length( v0_, v1_ );

  if (math::effectively_zero(area))
  {
    return 0.0f;
  }
  return angle * length / area;
}

} // namespace surface0
} // namespace geom
