/* GANG Software
 * GEOM/triang/Triangle.C
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

//#include <stdlib.h>
#include <iostream>
#include <list>
#include "base/String.H"
#include "base/System.H"
#include "base/String.H"
#include "Exception.H"
#include "Triangle.H"

namespace triang {

Triangle::
Triangle()
    :
    _max_area(0.0),
    _min_angle(0.0),
    _current_data( (TriangleData *)0 )
{
}

Triangle::
~Triangle()
{
  if ( _current_data != (TriangleData *)0 )
  {
    delete _current_data;
  }
}

void
Triangle::
max_area( Real max_area )
{
  _max_area = std::max( max_area, 0.0 );
}

void
Triangle::
min_angle( Real min_angle )
{
  // in degrees
  _min_angle = std::max( min_angle, 0.0 );
}


Triangle::
TriangleData::
TriangleData()
{
  initialize();
}

Triangle::
TriangleData::
~TriangleData()
{
  clear();
}

void
Triangle::
TriangleData::
initialize()
{
  _.pointlist = (Real *)0;
  _.pointattributelist = (Real *)0;
  _.pointmarkerlist = (int *)0;
  _.numberofpoints = (int)0;
  _.numberofpointattributes = (int)0;

  _.trianglelist = (int *)0;
  _.triangleattributelist = (Real *)0;
  _.trianglearealist = (Real *)0;
  _.neighborlist = (int *)0;
  _.numberoftriangles = (int)0;
  _.numberofcorners = (int)0;
  _.numberoftriangleattributes = (int)0;

  _.segmentlist = (int *)0;
  _.segmentmarkerlist = (int *)0;
  _.numberofsegments = (int)0;

  _.holelist = (Real *)0;
  _.numberofholes = (int)0;

  _.regionlist = (Real *)0;
  _.numberofregions = (int)0;

  _.edgelist = (int *)0;
  _.edgemarkerlist = (int *)0;
  _.normlist = (Real *)0;
  _.numberofedges = (int)0;
}

void
Triangle::
TriangleData::
clear()
{
  free( _.pointlist );
  free( _.pointattributelist );
  free( _.pointmarkerlist );

  free( _.trianglelist );
  free( _.triangleattributelist );
  free( _.trianglearealist );
  free( _.neighborlist );

  free( _.segmentlist );
  free( _.segmentmarkerlist );

  free( _.holelist );

  free( _.regionlist );

  free( _.edgelist );
  free( _.edgemarkerlist );
  free( _.normlist );

  initialize();
}

void
Triangle::
TriangleData::
copy( TriangleData const &a )
{
  DIE();

  clear();

  // point
  _.numberofpoints = a._.numberofpoints;
  if ( _.numberofpoints > 0 &&
       a._.pointlist != (Real *)0 )
  {
    uint n = _.numberofpoints * 2 * sizeof(Real);
    _.pointlist = (Real *)_malloc( n );
    memcpy( _.pointlist, a._.pointlist, n );
  }

  // pointmarker
  if (_.numberofpoints > 0 &&
      a._.pointmarkerlist != (int *)0 )
  {
    uint n = _.numberofpoints * sizeof(int);
    _.pointmarkerlist = (int *)_malloc( n );
    memcpy( _.pointmarkerlist, a._.pointmarkerlist, n );
  }

  // pointattribute
  _.numberofpointattributes = a._.numberofpointattributes;
  if ( _.numberofpointattributes > 0 &&
       a._.pointattributelist != (Real *)0 )
  {
    // pointattribute
    uint n = _.numberofpoints * _.numberofpointattributes *
      sizeof(Real);
    _.pointattributelist = (Real *)_malloc( n );
    memcpy( _.pointattributelist, a._.pointattributelist, n );
  }

  // trianglelist
  _.numberoftriangles = a._.numberoftriangles;
  _.numberofcorners = a._.numberofcorners;
  if ( _.numberoftriangles > 0 && _.numberofcorners > 0 &&
       a._.trianglelist != (int *)0 )
  {
    uint n = _.numberoftriangles * _.numberofcorners * sizeof(int);
    _.trianglelist = (int *)_malloc( n );
    memcpy( _.trianglelist, a._.trianglelist, n );
  }

  // triangleattributes
  _.numberoftriangleattributes = a._.numberoftriangleattributes;
  if ( _.numberoftriangles > 0 && _.numberoftriangleattributes > 0 &&
       a._.triangleattributelist != (Real *)0 )
  {
    uint n = _.numberoftriangles * _.numberoftriangleattributes *
      sizeof(Real);
    _.triangleattributelist = (Real *)_malloc( n );
    memcpy( _.triangleattributelist, a._.triangleattributelist, n );
  }

  // trianglearea
  if ( _.numberoftriangles > 0 &&
       a._.trianglearealist != (Real *)0 )
  {
    uint n = _.numberoftriangles * sizeof(Real);
    _.trianglearealist = (Real *)_malloc( n );
    memcpy( _.trianglearealist, a._.trianglearealist, n );
  }

  // neighbor
  if ( _.numberoftriangles > 0 &&
       a._.neighborlist != (int *)0 )
  {
    uint n = _.numberoftriangles * 3U * sizeof(int);
    _.neighborlist = (int *)_malloc( n );
    memcpy( _.neighborlist, a._.neighborlist, n );
  }

  // segment
  _.numberofsegments = a._.numberofsegments;
  if ( _.numberofsegments > 0 &&
       a._.segmentlist != (int *)0 )
  {
    uint n = _.numberofsegments * 2U * sizeof(int);
    _.segmentlist = (int *)_malloc(n );
    memcpy( _.segmentlist, a._.segmentlist, n );
  }

  // segmentmarker
  if ( _.numberofsegments > 0 &&
       a._.segmentmarkerlist != (int *)0 )
  {
    uint n = _.numberofsegments * sizeof(int);
    _.segmentmarkerlist = (int *)_malloc( n );
    memcpy( _.segmentmarkerlist, a._.segmentmarkerlist, n );
  }

  // hole
  _.numberofholes = a._.numberofholes;
  if ( _.numberofholes > 0 &&
       a._.holelist != (Real *)0 )
  {
    uint n = _.numberofholes * 2U * sizeof(Real);
    _.holelist = (Real *)_malloc( n );
    memcpy( _.holelist, a._.holelist, n );
  }

  // region
  _.numberofregions = a._.numberofregions;
  if ( _.numberofregions > 0 &&
       a._.regionlist != (Real *)0 )
  {
    uint n = _.numberofregions * 4U * sizeof(Real);
    _.regionlist = (Real *)_malloc( n );
    memcpy( _.regionlist, a._.regionlist, n );
  }

  // edges
  _.numberofedges = a._.numberofedges;
  if ( _.numberofedges > 0 &&
       a._.edgelist != (int *)0 )
  {
    uint n = _.numberofedges * 2U * sizeof(int);
    _.edgelist = (int *)_malloc( n );
    memcpy( _.edgelist, a._.edgelist, n );
  }

  // norm
  if ( _.numberofedges > 0 &&
       a._.normlist != (Real *)0 )
  {
    uint n = _.numberofedges * 2U * sizeof(Real);
    _.normlist = (Real *)_malloc( n );
    memcpy( _.normlist, a._.normlist, n );
  }
}

void
Triangle::
triangulate(
  PointList &vertex_out,
  vector<Face> &face_out,
  vector<Curve> const &vertex_in,
  PointList &hole_in )
{
  // triangulate with holes
  // data_in -> _data

  // initialize input
  TriangleData *data_in = new TriangleData;
  data_in->import_vertex( vertex_in );
  data_in->import_hole( hole_in );

  // initialize output
#ifdef DEBUG
  TriangleData::DEBUG_COMPARE( _current_data, data_in );
#endif

  if ( _current_data != (TriangleData *)0 )
  {
    delete _current_data;
  }
  _current_data = new TriangleData;

  try {
    // triangulate
    triangulate( *_current_data, *data_in );
  }
  catch ( Exception const &e ) {
    delete data_in;
    throw e;
  }

  // export
  _current_data->export_( vertex_out, face_out );

#ifdef DEBUG
  TriangleData::DEBUG_COMPARE( _current_data, data_in );
#endif

  // clean up
  delete data_in;
}

void
Triangle::
triangulate(
  PointList &vertex_out,
  vector<Face> &face_out,
  vector<Real> const &area_in )
{
  // refine triangulation with area constraint
  // uses _data from a previous call to triangulate() with area constraints
  // _data -> data_out

  // copy the area constraints into _data
  _current_data->import_area( area_in );

  // for output
  TriangleData *data_out = new TriangleData;

  // perform the refining triangulation
  triangulate( *data_out, *_current_data, true );

#ifdef DEBUG
  TriangleData::DEBUG_COMPARE( _current_data, data_out );
#endif

  // set current_data to data_out
  delete _current_data;
  _current_data = data_out;

  // get the vertices and faces from _data
  _current_data->export_( vertex_out, face_out );
}

void
Triangle::
triangulate(
  TriangleData &data_out,
  TriangleData const &data_in,
  bool refine )
{
  /*
    p: triangulate a planar straight line graph
    Q: quiet
    a MAXAREA
    q MINANGLE (degrees)
  */

  base::String flags;
  flags += "pQ";
  if (OFFSET == 0) { flags += "z"; }

  if (refine)
  {
    // area constraints for individual triangles
    flags += "ra";
  }

  if (_max_area > 0.0)
  {
    // global area constraint
    base::String s;
    s.to_string( _max_area );
    flags += "a";
    flags += s;
  }

  if (_min_angle > 0.0)
  {
    base::String s;
    s.to_string( _min_angle );
    flags += "q";
    flags += s;
  }

  data_out.clear();

  ::triang::triangulate(
    flags.c_str(),
    data_in.data(),
    data_out.data(),
    (triangulateio *)0);

  DIE_IF( data_out.data()->numberofsegments > 0 &&
          data_out.data()->segmentlist == (int *)0 );

  // copy holelist
  // (triang::triangulate() does shallow copy)
  if (data_in.data()->holelist != (Real *)0 )
  {
    DIE_IF( data_in.data()->holelist != data_out.data()->holelist );
    DIE_IF( data_in.data()->numberofholes != data_out.data()->numberofholes );

    uint n = data_in.data()->numberofholes;
    DIE_IF( n == 0 );

    data_out.data()->holelist =
      (Real *)_malloc( n * 2 * sizeof(Real) );

    uint i;
    for (i = 0; i < n; i++ )
    {
      data_out.data()->holelist[i] = data_in.data()->holelist[i];
    }
  }
}

void
Triangle::
TriangleData::
import_vertex(
  vector<Curve> const &vertex )
{
  // count vertices, segments
  uint n = 0;
  uint s = 0;
  uint i;
  for (i = 0; i < vertex.size(); i++ )
  {
    uint m = 0;
    uint j;
    for ( j = 0; j < vertex[i].v.size(); j++ )
    {
      m += vertex[i].v[j].size();
    }
    n += m;
    s += (vertex[i].looped ? m : (m == 0 ? 0 : m-1) );
  }
  s = n;

  free( _.pointlist );
  _.pointlist = (Real *)0;
  _.numberofpoints = n;

  free( _.segmentlist );
  _.segmentlist = (int *)0;
  _.numberofsegments = s;

  if (n == 0) { return; }

  // allocate
  _.pointlist = (Real *)_malloc( n * 2 * sizeof(Real) );

  if ( s > 0 )
  {
    _.segmentlist = (int *)_malloc( s * 2 * sizeof(int) );
  }


  // set points, segments
  uint c = 0;
  uint d = 0;
  for ( i = 0; i < vertex.size(); i++ )
  {
    uint save_c = c;
    uint j;
    for ( j = 0; j < vertex[i].v.size(); j++ )
    {
      uint k;
      for ( k = 0; k < vertex[i].v[j].size(); k++ )
      {
        // insert point
        _.pointlist[2*c] = vertex[i].v[j][k].first;
        _.pointlist[2*c+1] = vertex[i].v[j][k].second;
        // insert segment (edge joining points)
        if (j > 0 || k > 0)
        {
          DIE_IF(_.segmentlist == (int *)0);
          _.segmentlist[2*d] = c-1 + OFFSET;
          _.segmentlist[2*d+1] = c + OFFSET;
          d++;
        }
        c++;
      }
    }

    if (vertex[i].looped)
    {
      // last segment
      DIE_IF(_.segmentlist == (int *)0);
      _.segmentlist[2*d] = c-1 + OFFSET;
      _.segmentlist[2*d+1] = save_c + OFFSET;
      d++;
    }
  }
}

void
Triangle::
TriangleData::
import_hole(
  PointList const &hole )
{
  if ( _.numberofholes > 0 )
  {
    _.numberofholes = 0;
    free( _.holelist );
    _.holelist = (Real *)0;
  }

  // import the holes
  uint n = hole.size();
  _.numberofholes = n;

  if ( n == 0 ) { return; }

  _.holelist = (Real *)_malloc( n * 2 * sizeof(Real) );

  uint i;
  for ( i = 0; i < n; i++ )
  {
    _.holelist[2*i] = hole[i].first;
    _.holelist[2*i+1] = hole[i].second;
  }
}

void
Triangle::
TriangleData::
import_face(
  vector<Face> const &face )
{
  free( _.trianglelist );
  _.trianglelist = (int *)0;

  // import the triangles
  uint n = face.size();
  _.numberoftriangles = n;

  if (n == 0) { return; }

  _.trianglelist = (int *)_malloc( n * 3 * sizeof(int) );

  uint i;
  for ( i = 0; i < n; i++ )
  {
    DIE_IF(face[i].size() != 3);
    _.trianglelist[3*i] = face[i][0];
    _.trianglelist[3*i+1] = face[i][1];
    _.trianglelist[3*i+2] = face[i][2];
  }
}

void
Triangle::
TriangleData::
import_area(
  vector<Real> const &area )
{
  free( _.trianglearealist );
  _.trianglearealist = (REAL *)0;

  // import the area constraints
  uint n = area.size();

  DIE_IF( n != (uint)_.numberoftriangles );

  if (n == 0) { return; }

  _.trianglearealist = (Real *)_malloc( n * sizeof(Real) );
    
  uint i;
  for ( i = 0; i < n; i++ )
  {
    _.trianglearealist[i] = area[i];
  }
}

void
Triangle::
TriangleData::
export_(
  PointList &vertex,
  vector<Face> &face ) const
{
  // export *this to vertex, face, boundary

  // vertices
  uint n = _.numberofpoints;
  if ( n == 0 )
  {
    WARN("no vertices" );
    return;
  }

  vertex.clear();
  vertex.reserve( n );

  uint i;
  for ( i = 0; i < n; i++ )
  {
    vertex.push_back(
      pair<Real, Real>( _.pointlist[2*i], _.pointlist[2*i+1]) );
  }

  // faces
  uint c = _.numberofcorners;
  DIE_IF( c != 3 );

  uint m = _.numberoftriangles;

  face.clear();
  face.reserve( m );
  for ( i = 0; i < m; i++ )
  {
    IntList f;
    uint j;
    for ( j = 0; j < c; j++ )
    {
      uint p = _.trianglelist[c*i+j];
      DIE_IF( p < OFFSET );
      DIE_IF( p >= n + OFFSET );
      f.push_back( p-OFFSET );
    }
    face.push_back( f );
  }

}

void *
Triangle::
_malloc( size_t n )
{
  if ( n==0 )
  {
    WARN( "triangulator: allocating 0 bytes" );
  }
  void *v = malloc(n);
  if ( v == (void *)0 )
  {
    throw base::Exception( "triangulator: out of memory" );
  }
  return v;
}

#ifdef DEBUG
void Triangle::TriangleData::DEBUG_COMPARE(
  TriangleData const *t1,
  TriangleData const *t2
  )
{
  // makes sure two data structures don't overlap memory
  if (t1 == (TriangleData *)0 || t2 == (TriangleData *)0) { return; }

  DIE_IF( t1 == t2 );

  DIE_IF( t1->data()->pointlist != (Real *)0 &&
      t1->data()->pointlist == t2->data()->pointlist );
  DIE_IF( t1->data()->pointattributelist != (Real *)0 &&
      t1->data()->pointattributelist == t2->data()->pointattributelist );
  DIE_IF( t1->data()->pointmarkerlist != (int *)0 &&
      t1->data()->pointmarkerlist == t2->data()->pointmarkerlist );

  DIE_IF( t1->data()->trianglelist != (int *)0 &&
      t1->data()->trianglelist == t2->data()->trianglelist );
  DIE_IF( t1->data()->triangleattributelist != (Real *)0 &&
      t1->data()->triangleattributelist == t2->data()->triangleattributelist );
  DIE_IF( t1->data()->trianglearealist != (Real *)0 &&
      t1->data()->trianglearealist == t2->data()->trianglearealist );
  DIE_IF( t1->data()->neighborlist != (int *)0 &&
      t1->data()->neighborlist == t2->data()->neighborlist );

  DIE_IF( t1->data()->segmentlist != (int *)0 &&
      t1->data()->segmentlist == t2->data()->segmentlist );
  DIE_IF( t1->data()->segmentmarkerlist != (int *)0 &&
      t1->data()->segmentmarkerlist == t2->data()->segmentmarkerlist );

  DIE_IF( t1->data()->holelist != (Real *)0 &&
      t1->data()->holelist == t2->data()->holelist );

  DIE_IF( t1->data()->regionlist != (Real *)0 &&
      t1->data()->regionlist == t2->data()->regionlist );

  DIE_IF( t1->data()->edgelist != (int *)0 &&
      t1->data()->edgelist == t2->data()->edgelist );
  DIE_IF( t1->data()->edgemarkerlist != (int *)0 &&
      t1->data()->edgemarkerlist == t2->data()->edgemarkerlist );
  DIE_IF( t1->data()->normlist != (Real *)0 &&
      t1->data()->normlist == t2->data()->normlist );
}
#endif


} // namespace triang
