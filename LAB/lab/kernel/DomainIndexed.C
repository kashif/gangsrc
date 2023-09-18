/* GANG Software
 * LAB/lab/kernel/DomainIndexed.C
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

#include "base/System.H"
#include "io/IstreamStream.H"
#include "DomainIndexed.H"

namespace lab {
namespace kernel {

DomainIndexed::
DomainIndexed(
  DomainBase *base )
    :
    Domain2D( base ),
    _surface( (geom::Surface *)0 ),
    _triangulator( (triang::Triangulator *)0 )
{
  clear();
}

DomainIndexed::
~DomainIndexed()
{
  if ( _triangulator != (triang::Triangulator *)0 )
  { delete _triangulator; }
  if ( _surface != (geom::Surface *)0 )
  { delete _surface; }
}

void
DomainIndexed::
clear()
{
  _start_index = UINT_MAX;
  _adjacency.clear();
  _edge.clear();
  delete _surface;
  _surface = (geom::Surface *)0;
}

Complex
DomainIndexed::
z(uint i) const
  throw()
{
  geom::Vertex4 v;
  _surface->vertex(v, i);
  return Complex(v[0],v[1])/double(v[3]);
}

void
DomainIndexed::
initialize(
  Complex const &zstart )
{
  if ( configuration().empty() )
  {
    throw Exception( Exception::ERR_UNCONFIGURED );
  }

  base::vector<base::String> v;

  if ( base::match( "^[ \n\r\t]*file[ \t]([^\n]+)",
                    configuration(), v ) )
  {
    // domain from file
    initialize_file( v[1] );
  }
  else if ( base::match( "^[ \n\r\t]*triangulated[ \n\r\t]+(.*)$",
                         configuration(), v ) )
  {
    // triangulated domain
    initialize_triangulated( v[1] );
  }
  else
  {
    DIE();
  }

  // WARNING: if the Indexed is not connnected, this
  // will fail (e.g. if it has vertices which don't lie in faces)
  _start_index = find_closest( zstart );

  // create adjacency information
  compute_adjacency();

  // compute edge information
  compute_edge();
}

void
DomainIndexed::
initialize_file(
  base::String const &filename )
{
  // domain from file
  
  // clear data
  clear();

  // ---NEW---
  io::IstreamStream in( filename.c_str() );

  if (_surface != (geom::Surface *)0) { delete _surface; }
  _surface = new geom::Surface;
  _surface->read( in );

#if 0
  if (_surface->type() != 1 )
  {
    // NOTE: does not report the exact problem (surface is not indexed)
    delete g;
    throw Exception( Exception::ERR_FILE_INPUT );
  }
#endif
}

void
DomainIndexed::
initialize_triangulated( base::String const &s )
{
  // triangulated domain

  // clear data
  clear();
  
  if ( _triangulator != (triang::Triangulator *)0 )
  { delete _triangulator; }
  _triangulator = new triang::Triangulator;

  _triangulator->read_string(s);
  
  if ( _surface != (geom::Surface *)0 )
  { delete _surface; }
  _surface = new geom::Surface;

  _triangulator->triangulate(_surface);
}

void
DomainIndexed::
initialize_pass2(
  Complex const &zstart,
  base::vector<Real> const &area )
{
  if ( _surface != (geom::Surface *)0 )
  { delete _surface; }
  _surface = new geom::Surface;

  _triangulator->triangulate(_surface, area);

  // WARNING: if the Indexed is not connnected, this
  // will fail (e.g. if it has vertices which don't lie in faces)
  _start_index = find_closest( zstart );

  // create adjacency information
  compute_adjacency();

  // compute edge information
  compute_edge();
}

void
DomainIndexed::
compute_adjacency()
  throw( base::Exception )
{
  _adjacency.clear();

  uint i, p, x0, x1;

  std::slist<uint> dummy;
  uint vertex_count = _surface->vertex_count();
  _adjacency.fill( dummy, vertex_count );

  uint face_count = _surface->face_count();

  for ( i = 0; i < face_count; i++ )
  {
    p = _surface->face_count(i);
    if ( p != 3 )
    {
      throw Exception( Exception::ERR_NOT_TRIANGLE );
    }

    x0 = _surface->face_vertex(i,0U);
    x1 = _surface->face_vertex(i,1U);
    _adjacency[x0].push_front(x1);
    _adjacency[x1].push_front(x0);

    x0 = _surface->face_vertex(i,1U);
    x1 = _surface->face_vertex(i,2U);
    _adjacency[x0].push_front(x1);
    _adjacency[x1].push_front(x0);

    x0 = _surface->face_vertex(i,2U);
    x1 = _surface->face_vertex(i,0U);
    _adjacency[x0].push_front(x1);
    _adjacency[x1].push_front(x0);
  }
  for ( i = 0; i < vertex_count; i++ )
  {
    _adjacency[i].sort();
    _adjacency[i].unique();
  }
}

void
DomainIndexed::
compute_edge()
  throw( base::Exception )
{
  _edge.clear();

  uint i;

  // ok is an slist
  std::slist<uint> vertex_queue;

  uint vertex_count = _surface->vertex_count();
  if ( _adjacency.size() != vertex_count )
  { throw Exception( Exception::ERR_INTERNAL ); }

  if (_start_index >= vertex_count )
  { throw Exception( Exception::ERR_INTERNAL ); }

  enum Status {UNCONNECTED, CONNECTED_TO, DONE};
  // status is an array of vertex_count ints, initially UNCONNECTED

  Status *status = new Status[vertex_count];
  for ( i = 0; i < vertex_count; i++ )
  {
    status[i] = UNCONNECTED;
  }

  // vertex_queue starts with first point
  vertex_queue.push_front( _start_index );

  // as long as vertex_queue not empty:
  while ( ! vertex_queue.empty() )
  {
    // take vertex k from the front
    uint k = vertex_queue.front();

    // sanity check
    if ( k >= vertex_count )
    { throw Exception( Exception::ERR_INTERNAL ); }

    // remove k from vertex_queue
    vertex_queue.pop_front();
    // mark vertex k as done
    status[k] = DONE;

    // cycle through the points adjacent to k
    std::slist<uint>::iterator i;
    for ( i = _adjacency[k].begin(); i != _adjacency[k].end(); i++ )
    {
      // j is the index of an adjacent point
      uint j = (*i);

      // if vertex j is not connected
      if ( status[j] == UNCONNECTED )
      {
        // add (k,j) to list
        _edge.push_back( std::pair<uint, uint>( k, j ) );
        // vertex j needs to be connected
        vertex_queue.push_front( j );
        // mark vertex j as a second
        status[j] = CONNECTED_TO;
      }
    }
  }
  delete [] status;

  if ( _edge.size() == 0 )
  { throw Exception( Exception::ERR_EDGE ); }
}

uint
DomainIndexed::
find_closest( Complex const &z )
  throw( base::Exception )
{
  uint start = UINT_MAX;

  double d = FLT_MAX;

  uint i;
  for ( i = 0; i < _surface->vertex_count(); i++ )
  {
    geom::Vertex4 v;
    _surface->vertex(v, i);
    Complex w( v[0]/v[3], v[1]/v[3] );
    double a = std::abs( z - w );
    if ( a < d )
    {
      d = a;
      start = i;
    }
  }

  if (start == UINT_MAX)
  { throw Exception( Exception::ERR_START_INDEX ); }

  return start;
}

void
DomainIndexed::
compute()
{
  initialize( base()->zstart_v() );
  compute_sub();

  uint i;
  for ( i = 0; i < _triangulator->refine(); i++)
  {
    // refine the triangulation
    compute_refine();
  }
}

void
DomainIndexed::
compute_sub()
{
  // initialize check data
  _check_total = edge_count();
  _check_count = 0;

  // start_all
  base()->start_all_v( vertex_count(), edge_count(), THREAD_COUNT );

  // start on first point
  uint k0 = _edge[0].first;
  base()->start_v( z(k0), k0, THREAD_ID );

  if (edge_count() == 0) { WARN("edge count == 0"); }

  check_stopped();

  base()->check_v( 0, _check_total );

  uint i;
  for ( i = 0; i < edge_count(); i++ )
  {
    check_stopped();

    uint k0 = _edge[i].first;
    uint k1 = _edge[i].second;

    base()->step_v( z(k0), z(k1), k0, k1, THREAD_ID );

    // increment check count
    _check_count++;
    DIE_IF( _check_count > _check_total );
    base()->check_v( _check_count, _check_total );
  }

  base()->end_v();

  base()->end_all_v( vertex_count(), edge_count(), THREAD_COUNT );
}

void
DomainIndexed::
compute_refine()
{
  // compute a refined triangulation

  // compute area of domain faces
  geom::Surface const *surface0 = surface();
  surface0->compute_face_area();

  // compute area of surface faces
  geom::Surface const *surface1 = export_();
  surface1->compute_face_area();

  // compute curvature of surface at each face of surface
  surface1->compute_gaussian_curvature();

  // compute area constraint. Put into area1.
  // constrains area of domain based on area of surface
  // for high curvature (>cutoff), constraining number is smaller
  Real max_area = _triangulator->max_area2();
  if (math::effectively_zero(max_area) || max_area <= 0.0)
  { max_area = 1.0; }

  Real curvature_cut = _triangulator->curvature_cut();
  if (math::effectively_zero(curvature_cut) || curvature_cut <= 0.0)
  { curvature_cut = 1.0; }

  Real curvature_exp = _triangulator->curvature_exp();
  if (math::effectively_zero(curvature_exp) || curvature_exp <= 0.0)
  { curvature_exp = 1.0; }

  Real w = math::pow( curvature_cut, curvature_exp );

  base::vector<Real> area_constraint;
  area_constraint.reserve( surface0->face_count() );

  uint i;
  for (i = 0; i < surface1->face_count(); i++ )
  {
    Real v = max_area;
    Real c = math::abs( surface1->face_gaussian_curvature(i) );
    if (c > curvature_cut) {
      // stronger constraint for high curvature
      v = max_area * w * math::pow(c, -curvature_exp);
    }
    area_constraint.push_back( v * surface0->face_area(i) /
                               surface1->face_area(i) );
  }
  delete surface1;
  
  initialize_pass2( base()->zstart_v(), area_constraint );

  compute_sub();
}

geom::Surface *
DomainIndexed::
export_() const
{
  // NOTE this is inefficient because it involves
  // a superfluous copy into a Indexed

  uint n = vertex_count();

  base::vector<base::vector<Real> > v;
  base::vector<Real> v0;
  v0.fill( 0.0, dim() );
  v.fill( v0, n );

  uint i;
  for ( i = 0; i < n; i++ )
  {
    base()->export_fn_v( v[i], i );
  }

  // ---NEW---
  geom::Surface *x = new geom::Surface;
  
  x->geom::Surface::import(
    v, surface()->face_data(), spaceform() );

  x->import_lines( surface()->line() );

  return x;
}

#ifdef DEBUG
void
DomainIndexed::
dump_adjacency( std::ostream &o ) const
{
  o << "ADJACENCY\n";
  uint i;
  for ( i = 0; i < _adjacency.size(); i++ )
  {
    o << i << " [";
    std::slist<uint>::const_iterator j;
    for ( j = _adjacency[i].begin(); j != _adjacency[i].end(); j++ )
    {
      o << *j << " ";
    }
    o << "]\n";
  }
}

void
DomainIndexed::
dump_edge( std::ostream &o ) const
{
  o << "EDGE\n";
  uint i;
  for ( i = 0; i < _edge.size(); i++ )
  {
    o << i
      << " ["
      << _edge[i].first << " "
      << _edge[i].second << "]\n";
  }
}
#endif

} // namespace kernel
} // namespace lab
