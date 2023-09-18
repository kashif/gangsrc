/* GANG Software
 * GEOM/geom/surface0/Normal.C
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
#include "Normal.H"

namespace geom {
namespace surface0 {

Normal::
Normal()
    :
    Boundary(),
    _face_normal(),
    _vertex_normal()
//    _use_normal(true)
{
}

Normal::
Normal( Normal const &a )
    :
    Boundary(a),
    _face_normal( a._face_normal ),
    _vertex_normal( a._vertex_normal )
//    _use_normal(a._use_normal)
{
}

Normal::
~Normal()
{
}

Normal &
Normal::
operator=( Normal const &a )
{
  if ( this == &a ) { return *this; }

  Boundary::operator=(a);
  _face_normal = a._face_normal;
  _vertex_normal = a._vertex_normal;
//  _use_normal = a._use_normal;

  return *this;
}

void
Normal::
clear()
{
  Boundary::clear();
  clear_normal();
}

void
Normal::
clear_normal()
{
  _face_normal.clear();
  _vertex_normal.clear();
}

void
Normal::
compute_normal() const
{
  _compute_normal();
  _compute_vertex_normal();
}

void
Normal::
_compute_normal() const
{
  if( !_face_normal.empty() ) { return; }

  // Cycle through faces
  // compute the normal for each face
  // (1) assumes each face has at least 3 vertices
  // (2) assumes each face is a planar polygon NOTE


  Vertex3 v1, v2, v3;

  uint face_count_ = face_count();
  uint i;
  for ( i = 0; i < face_count_; i++ )
  {
    Normal3 x;
    if ( face_count(i) >= 3 )
    {
      uint n = face_count(i);
      uint j;
      Real err = -FLT_MAX;
      for ( j = 0; j < n; j++ )
      {
        uint j0 = (j == 0 ? n-1 : j-1); // prev
        uint j1 = (j == n-1 ? 0 : j+1); // next
        uint k0 = face_vertex(i,j0);
        uint k1 = face_vertex(i,j);
        uint k2 = face_vertex(i,j1);
        vertex( v1, k0 );
        vertex( v2, k1 );
        vertex( v3, k2 );

        math::Vector3Math<Real> u, v, w;
        u.cross( v1, v2 );
        v.cross( v2, v3 );
        w.cross( v3, v1 );

        math::Vector3<Real> p;
        p.x = u.x + v.x + w.x;
        p.y = u.y + v.y + w.y;
        p.z = u.z + v.z + w.z;
      
        Real r = p.norm();
        if (r > err)
        {
          err = r;
          x.normal( v1, v2, v3 );
        }
      }
    }
    else
    {
#if 0
      WARN( "face %d has %d vertices", i, face_count(i) );
#endif
      x[0] = 1.0;
      x[1] = 0.0;
      x[2] = 0.0;
    }
    _face_normal.push_back( x );
  }
}

void
Normal::
_compute_vertex_normal() const
{
  if ( ! _vertex_normal.empty() ) { return; }

  Normal3 c;
  c.set(0.0);
  _vertex_normal.fill( c, vertex_count() );

  uint i;
  for ( i = 0; i < face_count(); i++ )
  {
    c.set(0.0f);
    uint j;
    for (j = 0; j < face_count(i); j++ )
    {
      uint k = face_vertex(i, j);
      _vertex_normal[k] += face_normal(i);
    }
  }

  for ( i = 0; i < vertex_count(); i++ )
  {
    int r = _vertex_normal[i].normalize();
    if ( r != 0 )
    {
#if 0
      WARN( "normal at vertex %d is 0", i);
#endif
      _vertex_normal[i][0] = 1.0;
      _vertex_normal[i][1] = 0.0;
      _vertex_normal[i][2] = 0.0;
    }
  }
}

void
Normal::
face_normal(
  Normal3 &y,
  uint k,
  Transform const &transform_inv,
  ProjectionMode mode ) const
{
  compute_face_center();

  // the kth vertex
  Vertex3 const &v3 = face_center(k);
  Vertex4 v;
  v[0] = v3[0];
  v[1] = v3[1];
  v[2] = v3[2];
  v[3] = 1.0;

  _compute_normal( y, face_normal(k), v, transform_inv, mode );
}

void
Normal::
vertex_normal(
  Normal3 &y,
  uint k,
  Transform const &transform_inv,
  ProjectionMode mode ) const
{
  // the kth vertex
  Vertex4 v;
  vertex( v, k );
  
  _compute_normal( y, vertex_normal(k), v, transform_inv, mode );
}

void
Normal::
_compute_normal(
  Normal3 &y,
  Normal3 const &x,
  Vertex4 const &v,
  Transform const &transform_inv,
  ProjectionMode mode ) const
{
  /*
    Transform the kth normal via the transform 'transform_inv'. Put the
    result into y.
    'transform_inv' is the inverse of the current vertex transformation.

    Algorithm

    If (r1, r2, r3, r4) is a plane (i.e. the plane with equation
    r1 x1 + r2 x2 + r3 x3 + r4 x4 = 0), and T is a transform
    (4x4 matrix), then r T^{-1} is the transform of r.
    Proof: Let s be the transform of r. Then r.p = 0 iff s.Tp = 0.

    NOTE: this is wrong for conformal geometry
  */

  uint matrix_dim = transform_inv.dim();
  DIE_IF( matrix_dim < 4 );

  // p represents the tangent plane through v with normal x
  math::Vector<Real> p;
  p.allocate(matrix_dim);
  p.set(0.0f);
  p[0] = x[0];
  p[1] = x[1];
  p[2] = x[2];
  p[3] = -(x[0]*v[0]+x[1]*v[1]+x[2]*v[2])/v[3];

  // transform the tangent plane
  transform_inv.mulleft( p );

  // set q to the normal of the transformed tangent plane
  y.x = p[0];
  y.y = p[1];
  y.z = p[2];
  y.normalize();
}

void
Normal::
import_face_normal(
  base::vector<Normal3> const &face_normal )
{
  // import INDEXED face normals
  DIE_IF( type() != INDEXED );
  DIE_IF( face_normal.size() != face_count() );
  _face_normal = face_normal;
  _compute_vertex_normal();
}

void
Normal::
import_vertex_normal(
  base::vector<Normal3> const &vertex_normal )
{
  // import INDEXED vertex normal
  DIE_IF( vertex_normal.size() != vertex_count() );
  _vertex_normal = vertex_normal;
  _compute_face_normal();
}

void
Normal::
import_face_normal(
  base::vector<base::vector<Normal3> > const &face_normal )
{
  // import GRID face normal
  DIE_IF( face_normal.size() != face_count() );
 
  clear_normal();

  // insert face_normal into _face_normal
  base::vector<base::vector<Normal3> >::const_iterator i;
  for ( i = face_normal.begin(); i != face_normal.end(); i++ )
  {
    _face_normal.insert(
      _face_normal.end(), (*i).begin(), (*i).end() );
  }

  _compute_vertex_normal();
}

void
Normal::
import_vertex_normal(
  base::vector<base::vector<Normal3> > const &vertex_normal )
{
  // import GRID vertex normal
  DIE_IF( vertex_normal.size() != vertex_count() );

  clear_normal();

  // insert vertex_normal into _vertex_normal
  base::vector<base::vector<Normal3> >::const_iterator i;
  for ( i = vertex_normal.begin(); i != vertex_normal.end(); i++ )
  {
    _vertex_normal.insert(
      _vertex_normal.end(), (*i).begin(), (*i).end() );
  }

  _compute_face_normal();
}

void
Normal::
_compute_face_normal() const
{
  if ( ! _face_normal.empty() ) { return; }

  // compute face normal from vertex normal
  // the normal of a face is the average of the normals of the vertices

  uint i;
  for ( i = 0; i < face_count(); i++ )
  {
    Normal3 d;
    d.set(0.0f);
    uint j;
    for ( j = 0; j < face_count(i); j++ )
    {
      uint k = face_vertex(i, j);
      Normal3 const &c = vertex_normal(k);
      d[0] += c[0];
      d[1] += c[1];
      d[2] += c[2];
    }
    if ( face_count(i) != 0 )
    {
      d[0] /= face_count(i);
      d[1] /= face_count(i);
      d[2] /= face_count(i);
    }
    _face_normal.push_back(d);
  }
}


void
Normal::
apply( Transformer const &T )
{
  SurfaceBase::apply(T);
  clear_normal();
  compute_normal();
  changed(true);
  compute_bounding_box();
}


void
Normal::
relax( uint iterations )
{
  /*
    Relax a surface.
    Algorithm: replace a vertex with the average of its adjacent vertices
    do over the whole surface 'iteration' times, choosing a random order
    NOTE: should really do each vertex, in random order. right now
    it could miss some and do others multiply
  */

  if (iterations == 0) { return; }

  if ( spaceform().space != SpaceForm::SPACEFORM_R || 
       spaceform().dim != 2U ) { WARN(); return; }

  math::random_seed(0xabcd1234);

  compute_adjacency_list();

  uint n = vertex_count();

  uint i;
  for ( i = 0; i < iterations * n; i++ )
  {
    // pick a random vertex p to relax
    uint p = (uint)floor( math::random( double(n) ) );
    if ( p >= n ) { p = n-1; }

    // A is the list of vertices adjacent to p
    std::slist<uint> const &A = adjacency_list(p);

    // compute the average v of the adjacent vertices
    Vertex2 v;
    v.set(0.0);
    uint count = 0;

    std::slist<uint>::const_iterator j;
    for ( j = A.begin(); j != A.end(); j++ )
    {
      Vertex2 t;
      vertex( t, *j );
      v += t;
      count++;
    }

    // replace vertex p with the average v
    if ( count > 0 )
    {
      v /= Real(count);
      {
        Vertex2 u;
        vertex( u, p );
      }
      replace_vertex( p, v );
    }
  }
  compute_bounding_box();
  changed(true);
}

} // namespace surface0
} // namespace geom
