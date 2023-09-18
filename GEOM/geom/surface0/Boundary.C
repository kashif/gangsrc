/* GANG Software
 * GEOM/geom/surface0/Boundary.C
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

#include <algorithm>
#include "base/Stl.H"
#include "Boundary.H"

namespace geom {
namespace surface0 {

Boundary::
Boundary()
    :
    SurfaceBase(),
  _edge(),
  _boundary(),
  _adjacency_list(),
  _pushoff()
{
}

Boundary::
Boundary( Boundary const &a )
    :
    SurfaceBase(a),
  _edge( a._edge ),
  _boundary( a._boundary ),
  _adjacency_list(),
  _pushoff( a._pushoff )
{
}

Boundary::
~Boundary()
{
}

Boundary &
Boundary::
operator=( Boundary const &a )
{
  if ( this == &a ) { return *this; }

  SurfaceBase::operator=(a);

  _edge = a._edge;
  _boundary = a._boundary;
  _adjacency_list = a._adjacency_list;
  _pushoff = a._pushoff;

  return *this;
}

void
Boundary::
clear()
{
  SurfaceBase::clear();
//  _pushoff.clear();
  _edge.clear();
  _boundary.clear();
}

#if 0
uint
Boundary::
boundary_count() const
{
  if ( type() == INDEXED )
  {
    return _boundary.size();
  }
  else if ( type() == GRID )
  {
    return 2*((i_step() - 1) + (j_step() - 1));
  }
  else
  {
    DIE();
  }
  return 0;
}

Boundary::uint_pair
Boundary::
boundary(uint component, uint i) const
{
  if ( type() == INDEXED )
  {
    return _boundary[component][i];
  }
  else if ( type() == GRID )
  {
    if (n < j_step()-1)
    {
      return uint_pair(n,n+1);
    }
    n -= j_step()-1;
    if (n < i_step()-1)
    {
      return uint_pair((n+1)*j_step()-1, (n+2)*j_step()-1);
    }
    n -= i_step()-1;
    if (n < j_step()-1)
    {
      return uint_pair(i_step()*j_step()-1-n, i_step()*j_step()-2-n);
    }
    n -= j_step()-1;
    return uint_pair( (i_step()-1-n)*j_step(), (i_step()-2-n)*j_step() );
  }
  else
  {
    DIE();
  }
  return uint_pair(0,0);
}
#endif

void
Boundary::
boundary( std::list<std::list<uint_pair> > &b ) const
{
  if ( type() == INDEXED )
  {
    b.clear();
    b = _boundary;
  }
  else if ( type() == GRID )
  {
    b.clear();
    std::list<uint_pair> x;
    uint i;

    // boundary segment 1
    for ( i = 0; i < j_step()-1; i++ )
    {
      x.push_back(uint_pair(i,i+1));
    }

    // boundary segment 2
    for ( i = 0; i < i_step()-1; i++ )
    {
      x.push_back( uint_pair((i+1)*j_step()-1, (i+2)*j_step()-1) );
    }

    // boundary segment 3
    for ( i = 0; i < j_step()-1; i++ )
    {
      x.push_back( uint_pair(i_step()*j_step()-1-i, i_step()*j_step()-2-i) );
    }

    // boundary segment 4
    for ( i = 0; i < i_step()-1; i++ )
    {
      x.push_back( uint_pair( (i_step()-1-i)*j_step(),
                              (i_step()-2-i)*j_step() ) );
    }
    b.push_back(x);
  }
  else
  {
    DIE();
  }
}

uint
Boundary::
edge_count() const
{
  compute_edge();
  return (uint)_edge.size();
}

void
Boundary::
compute_edge() const
{
  // NOTE: deal with when length(F) =0 or >3
  // NOTE why a list of faces, when there are at most 2?
  // should be much more efficient with a pair of faces

  if ( !_edge.empty() ) { return; }

  changed(true);

  // computes a list of edges and the faces they bound

  // cycle through the faces
  // count how many times each edge occurs in a face
  uint i;
  for ( i = 0; i < face_count(); i++ )
  {
    // for each face, cycle through its edges
    uint c =face_count(i);
    uint j;
    for ( j = 0; j < c; j++ )
    {
      uint j0, j1;
      if ( j != c - 1 )
      {
        j0 = j;
        j1 = j+1;
      }
      else
      {
        j0 = c-1;
        j1 = 0;
      }
      uint_pair key(
        std::min( face_vertex(i,j0), face_vertex(i,j1) ),
        std::max( face_vertex(i,j0), face_vertex(i,j1) ) );

      _edge[key].push_back(i);
    }
  }
}

void
Boundary::
compute_boundary() const
{
  if ( !_boundary.empty() ) { return; }

  std::list<uint_pair> boundary;

  changed(true);

  compute_edge();

  EdgeMap::const_iterator k;
  for ( k = _edge.begin(); k != _edge.end(); k++ )
  {
    if ( (*k).second.size() == 1 )
    {
      // orient the edge so that its adjacent face is on its left
      uint_pair e = (*k).first;

      uint f = (*k).second[0];
      DIE_IF(face_count(f) < 3, "face has fewer than three edges" );

      // cycle through the vertices of the adjacent face,
      // looking for e.first
      uint p;
      for (p = 0; p < face_count(f); p++)
      {
        if ( face_vertex(f,p) == e.first ) { break; }
      }
      DIE_IF( p == face_count(f), "face does not contain edge" );

      uint p_prev;
      uint p_next;
      p_prev = ( p == 0 ? face_count(f)-1 : p-1 );
      p_next = ( p == face_count(f)-1 ? 0 : p+1 );

      // face is on right of edge: insert edge reversed
      if ( e.second == face_vertex(f, p_prev) )
      {
        e = uint_pair( e.second, e.first );
        boundary.push_back( e );
      }
      // face is on left of edge: insert edge
      else if ( e.second == face_vertex(f, p_next) )
      {
        boundary.push_back( e );
      }
      else
      {
        DIE( "face does not contain edge" );
      }
    }
  }

  // sort boundary
  for (;;)
  {
    if (boundary.empty()) { break; }

    // find point in boundary with lowest index
    uint n = UINT_MAX;
    std::list<uint_pair>::iterator i;
    std::list<uint_pair>::iterator i0;
    for (i = boundary.begin(); i != boundary.end(); i++)
    {
      if ( (*i).first < n)
      {
        n = (*i).first;
        i0 = i;
        if (n == 0) { break; }
      }
    }
//    std::cerr << "first point=" << n << "\n";

    // insert boundary segment
    std::list<uint_pair> b;
//    b.push_back( *i0 );
//    boundary.erase( i0 );

    // find and insert connected edges
    for (;;)
    {
//      std::cerr << "looking for n=" << n << "\n";
      // find n in boundary
      std::list<uint_pair>::iterator j;
      for (j = boundary.begin(); j != boundary.end(); j++)
      {
        if ( (*j).first == n ) { break; }
      }
      if (j == boundary.end() )
      {
        // n not in boundary
//        std::cerr << "not found n=" << n << "\n";
        break;
      }
//      std::cerr << "found n=" << n << "\n";
      b.push_back(*j);
      n = (*j).second;
//      std::cerr << "new n=" << n << "\n";
      boundary.erase(j);
    }
    _boundary.push_back(b);
  }
}

void
Boundary::
compute_pushoff() const
{
  uint const INTERIOR_POINT = UINT_MAX;
  uint const UNKNOWN = UINT_MAX - 1;

  if ( !_pushoff.empty() ) { return; }

  changed(true);

  compute_edge();

  uint vertex_count_ = vertex_count();

  _pushoff.fill( INTERIOR_POINT, vertex_count_ );

#if 0
  base::vector<bool> boundary;
  boundary.fill( false, vertex_count_ );
#endif

  base::vector<int> boundary;
  boundary.fill( 0, vertex_count_ );

  // cycle through edges
  // mark boundary[i]=true iff i is a boundary point
  EdgeMap::const_iterator o;
  for ( o = _edge.begin(); o != _edge.end(); o++ )
  {
    // skip interior edges
    if ( (*o).second.size() != 1 ) { continue; }

    // o is a boundary edge
    // mark edge vertices as UNKNOWN

    // set v0, v1 to the vertices of edge o
    uint v0 = (*o).first.first;
    uint v1 = (*o).first.second;
    boundary[v0] = true;
    boundary[v1] = true;
  }

  // cycle through edges
  // compute pushoff
  for ( o = _edge.begin(); o != _edge.end(); o++ )
  {
    // skip interior edges
    if ( (*o).second.size() != 1 ) { continue; }

    /* o is a boundary edge
       set v0, v1 to the (indices of the) vertices of edge o
       set f to the (index of the) face adjacent to edge o

       f0

       v0 -------- v1
    */
    uint f = (*o).second[0];

    // skip faces with fewer than 3 vertices
    if ( face_count(f) < 3 ) { continue; }

    uint v0 = (*o).first.first;
    uint v1 = (*o).first.second;

    // try to compute pushoff for vertex v0:
    // try to find an interior point of f
    // search at most 2 vertices along f on the side of v0 away from v1
    // NOTE: search all vertices in face for an interior point
    uint v = third_vertex( f, v0, v1 );

    if (boundary[v])
    {
      v = third_vertex( f, v, v0 );
    }
    _pushoff[v0] = ( boundary[v] ? UNKNOWN : v );

    // try to compute pushoff for vertex v1:
    // try to find an interior point of f
    // search at most 2 vertices along f on the side of v1 away from v0
    v = third_vertex( f, v1, v0 );

    if (boundary[v])
    {
      v = third_vertex( f, v, v1 );
    }
    _pushoff[v1] = ( boundary[v] ? UNKNOWN : v );
  }
}

uint
Boundary::
third_vertex(
  uint f,
  uint v0,
  uint v1 ) const
{
  /*
    Returns the vertex v of f such that v, v0, v1 are in order
    v0 and v1 must be adjacent vertices in face f
    Returns UINT_MAX if f has fewer than 3 edges
  */

  // search for v0 in f
  uint i;
  uint n = face_count(f);
  for (i = 0; i < n; i++)
  {
    uint v = face_vertex(f, i);
    if ( v == v0 )
    {
      if ( face_vertex( f, prev(i, n) ) == v1 )
      {
        return face_vertex(f, next(i,n));
      }
      else if ( face_vertex( f, next(i, n) ) == v1 )
      {
        return face_vertex(f, prev(i,n));
      }
      else
      {
        // NOTE v0, v1 are not adjacent vertices in f
#if 0
        WARN();
#endif
      }
    }
  }
  // could not find vertex v0 in face f
  DIE();
  return UINT_MAX;
}

void
Boundary::
compute_adjacency_list() const
{
  if (_adjacency_list.size() != 0) { return; }

  compute_boundary();

  _adjacency_list.reserve( vertex_count() );
  std::slist<uint> v;

  // initialize _adjacency_list
  uint i;
  for ( i = 0; i < vertex_count(); i++ )
  {
    _adjacency_list.push_back(v);
  }

  // compute _adjacency_list
  for ( i = 0; i < face_count(); i++ )
  {
    uint j, t0, t1, m;
    m = face_count(i);
    DIE_IF( m == 0 );

    for ( j = 0; j < m - 1; j++ )
    {
      t0 = face_vertex(i, j);
      t1 = face_vertex(i, j+1);
      _adjacency_list[t0].push_front(t1);
      _adjacency_list[t1].push_front(t0);
    }
    t0 = face_vertex(i, m-1);
    t1 = face_vertex(i, 0);
    _adjacency_list[t0].push_front(t1);
    _adjacency_list[t1].push_front(t0);
  }

  // remove boundary points from _adjacency list
  {
    std::list<std::list<uint_pair> >::const_iterator i;
    for ( i = _boundary.begin(); i != _boundary.end(); i++ )
    {
      std::list<uint_pair>::const_iterator j;
      for ( j = (*i).begin(); j != (*i).end(); j++ )
      {
        _adjacency_list[(*j).first].clear();
        _adjacency_list[(*j).second].clear();
      }
    }
  }

  // sort and unique-ify
  for ( i = 0; i < vertex_count(); i++ )
  {
    if ( _adjacency_list[i].size() > 0 )
    {
      _adjacency_list[i].sort();
      _adjacency_list[i].unique();
    }
  }
}

void
Boundary::
import_boundary_lines(
  std::list<std::list<uint> > const &corner )
{
  // insert a set of lines broken up at corners

  using std::list;

  // compute boundary
  compute_boundary();

  std::list<std::list<uint> > boundary;

  DIE_IF(corner.size() != _boundary.size());

  // for each boundary component
  list<list<uint_pair> >::const_iterator i;
  list<list<uint> >::const_iterator c;
  for (i = _boundary.begin(), c = corner.begin(); i != _boundary.end(); i++, c++)
  {
    DIE_IF( (*i).empty() );
    DIE_IF( (*c).empty() );
    // for each boundary segement
    list<uint_pair>::const_iterator j = (*i).begin();
    list<uint>::const_iterator d = (*c).begin();
    d++;
    if (d == (*c).end()) { d = (*c).begin(); }
    for (;;)
    {
      // set 'x' to a list of firsts in L from (*i).first till *d
      list<uint> x;
      x.push_back((*j).first);
      j++;
      // insert points up to *d
      for (;;)
      {
        if (j == (*i).end()) { break; }
        x.push_back((*j).first);
        if ( (*j).first == *d )
        {
          d++;
          if (d == (*c).end()) { d = (*c).begin(); }
          break;
        }
        j++;
      }
      if (j == (*i).end())
      {
        // insert first point in the boundary component to complete the loop
        x.push_back( (*(*i).begin()).first );
      }
      boundary.push_back(x);
      if (j == (*i).end()) { break; }
    }
  }
  import_lines(boundary);
}

Real
Boundary::
glue(
  Boundary const *g,
  std::list<uint> const &boundary )
{
  /*
    Glue *g to *this along boundary.
    boundary is a list of lines in *this along which to glue
    the lines boundary[i] are indices of points.
    Uses the same points in *this as in *g
  */


#if 0
  {
    std::list<uint>::const_iterator i;
    for (i = boundary.begin(); i != boundary.end(); i++)
    {
      std::cerr << "gluing point " << *i << "\n";
    }
  }
#endif

  std::list<std::list<uint> > const &LINE = line();
  base::vector<std::list<uint> > LINEV;
  base::vector<base::vector<uint> > LINEVV;

  {
    std::list<std::list<uint> >::const_iterator i;
    for (i = LINE.begin(); i != LINE.end(); i++)
    {
      LINEV.push_back(*i);
      std::list<uint>::const_iterator j;
      base::vector<uint> t;
      for (j = (*i).begin(); j != (*i).end(); j++)
      {
        t.push_back(*j);
      }
      LINEVV.push_back(t);
    }
  }

  // insert all the boundary points into boundary1
  std::list<uint> boundary1;

  std::list<uint>::const_iterator i;
  for ( i = boundary.begin(); i != boundary.end(); i++ )
  {
    DIE_IF( *i >= LINEV.size() );
    boundary1.splice( boundary1.end(), LINEV[*i] );
  }

  boundary1.sort();
  boundary1.unique();

  // replace boundary points with averages
  Real gluesep = 0.0;
  math::Vector3Math<Real> x, y;
  // NOTE: using default SpaceForm
  SpaceForm s;
  Vertex z( s );
  std::list<uint>::const_iterator l;
  for ( l = boundary1.begin(); l != boundary1.end(); l++ )
  {
    vertex(*l).export_(x);
    g->vertex(*l).export_(y);
    Real e = math::Vector3<Real>::length(x, y);
    if (e > gluesep) { gluesep = e; }
    math::Vector3Math<Real> z1 = 0.5*(x+y);
    z.import(z1);
    vertex(*l) = z;
  }

  // make an index for renumbering
  // index[old number] = new number
  // index[i]=j means that g's ith vertex will get index j in the glued surface
  base::vector<uint> index;
  uint k = g->vertex_count();
  index.fill( 0U, k );

  {
    uint i;
    for ( i = 0; i < g->vertex_count(); i++ )
    {
      if ( std::find( boundary1.begin(), boundary1.end(), i ) !=
           boundary1.end() )
      {
        index[i] = i;
      }
      else
      {
        index[i] = k++;
        _vertex.push_back( g->_vertex[i] );
      }
    }
  }

  // merge the vertices
  {
    // append g->_faces to _face
    uint i;
    for ( i = 0; i < g->face_count(); i++ )
    {
      base::vector<uint> f;
      uint j;
      for ( j = 0; j != g->face_count(i); j++ )
      {
        f.push_back( index[g->face_vertex(i, j)] );
      }
      _face.push_back(f);
      f.clear();
    }
  }
  // fix the new boundary: b will be the new boundary

  // put unglued boundaries into b
  std::list<std::list<uint> > b1, b2;
  {
    uint i;
    for ( i = 0; i < LINEV.size(); i++ )
    {
      if ( std::find( boundary.begin(), boundary.end(), i ) == boundary.end() )
      {
        // put unglued line into b1
        b1.push_back( LINEV[i] );

        // put reindexed line into b2
        std::list<uint> l;
        uint j;
        for ( j = 0; j != LINEV[i].size(); j++ )
        {
          l.push_back( index[LINEVV[i][j]] );
        }
        b2.push_back(l);

        l.clear();
      }
    }
  }
  b1.insert( b1.end(), b2.begin(), b2.end() );
  import_lines(b1);

  return gluesep;
}

Real
Boundary::
glue_self(
  std::list<uint> const &boundaryset1,
  std::list<uint> const &boundaryset2 )
{
  /*
    Glue the surface to itself, gluing boundaryset1 to boundaryset2
    boundaryset1 and boundaryset2 are lists of lines
    NOTE: boundaryset2 is reversed
  */

  // copy boundary set into a vector for easy access
  std::list<std::list<uint> > const &LINE = line();
  base::vector<std::list<uint> > LINEV;
  base::vector<base::vector<uint> > LINEVV;

  {
    std::list<std::list<uint> >::const_iterator i;
    for (i = LINE.begin(); i != LINE.end(); i++)
    {
      LINEV.push_back(*i);
      std::list<uint>::const_iterator j;
      base::vector<uint> t;
      for (j = (*i).begin(); j != (*i).end(); j++)
      {
        t.push_back(*j);
      }
      LINEVV.push_back(t);
    }
  }

  // check sizes are same
  {
    if (boundaryset1.size() != boundaryset2.size())
    {
      throw base::Exception( "geom::surface0::Boundary::glue_self(): boundary sets have different numbers of lines" );
    }
    std::list<uint>::const_iterator i, j;
    for ( i = boundaryset1.begin(), j=boundaryset2.begin();
          i != boundaryset1.end(); i++, j++ )
    {
      if ( LINEV[*i].size() != LINEV[*j].size() )
      {

        std::cerr << "i=" << *i << " j=" << *j << "\n";
        std::cerr << LINEV[*i].size() << " " << LINEV[*j].size() << "\n";

        throw base::Exception( "geom::surface0::Boundary::glue_self(): corresponding lines in boundary sets have different numbers of points" );
      }
    }
  }

  WARN_IF( boundaryset1.size() == 0, "boundary set no lines in it");


  // insert all the boundary1 points into boundary1
  std::list<uint> boundary1;

  {
    std::list<uint>::const_iterator i;
    for ( i = boundaryset1.begin(); i != boundaryset1.end(); i++ )
    {
      DIE_IF( *i >= LINEV.size() );
      boundary1.splice( boundary1.end(), LINEV[*i] );
    }
  }

  // insert all the boundary1 points into boundary1
  // NOTE: BOUNDARY 2 IS REVERSED
  std::list<uint> boundary2;

  {
    std::list<uint>::const_iterator i;
    for ( i = boundaryset1.begin(); i != boundaryset1.end(); i++ )
    {
      DIE_IF( *i >= LINEV.size() );
      boundary2.splice( boundary2.end(), LINEV[*i] );
    }
  }
  boundary2.reverse();

  // replace boundary points with averages
  Real gluesep = 0.0;
  math::Vector3Math<Real> x1, x2;
  // NOTE: using default SpaceForm
  SpaceForm s;
  Vertex z( s );
  std::list<uint>::const_iterator l1, l2;
  for ( l1 = boundary1.begin(), l2=boundary2.begin();
        l1 != boundary1.end(); l1++,l2++ )
  {
    uint n1 = *l1;
    uint n2 = *l2;
    std::cerr << "gluing " << n1 << " " << n2 << "\n";
    vertex(n1).export_(x1);
    vertex(n2).export_(x2);
    Real e = math::Vector3<Real>::length(x1, x2);
    if (e > gluesep) { gluesep = e; }
    math::Vector3Math<Real> z1 = 0.5*(x1 + x2);
    z.import(z1);
    vertex(n1) = z;
  }

  // make an index for renumbering
  // index[old number] = new number

  base::vector<uint> index;
  index.fill( 0U, vertex_count() );

  uint k = 0;

  base::vector<Vertex> new_vertex;
  // step one: count the vertices which will be in the new surface
  uint i;
  for ( i = 0; i < vertex_count(); i++ )
  {
    std::list<uint>::const_iterator p =
      std::find( boundary2.begin(), boundary2.end(), i );

    if ( p == boundary2.end() )
    {
      index[i] = k++;
      new_vertex.push_back( vertex(i) );
    }
  }
  // step two: index the vertices which will be excluded from the new surface
  for ( i = 0; i < vertex_count(); i++ )
  {
    std::list<uint>::const_iterator p =
      std::find( boundary2.begin(), boundary2.end(), i );

    if ( p != boundary2.end() )
    {
      std::list<uint>::const_iterator q1;
      std::list<uint>::const_iterator q2;
      for ( q1 = boundary1.begin(),q2 = boundary2.begin();
            q2 != boundary2.end(); q1++,q2++ )
      {
        if ( p == q2 ) { break; }
      }
      index[i] = index[*q1];
    }
  }


  // renumber the faces
  base::vector<base::vector<uint> > new_face;
  for ( i = 0; i < face_count(); i++ )
  {
    base::vector<uint> f;
    uint j;
    for ( j = 0; j != face_count(i); j++ )
    {
      f.push_back( index[face_vertex(i, j)] );
    }
    new_face.push_back(f);
    f.clear();
  }
  

  // fix boundaries
  std::list<std::list<uint> > new_line;
  for ( i = 0; i < LINE.size(); i++ )
  {
    if ( std::find( boundaryset1.begin(), boundaryset1.end(), i ) ==
         boundaryset1.end() &&
         std::find( boundaryset2.begin(), boundaryset2.end(), i ) ==
         boundaryset2.end() )
    {
      // put reindexed line into b2
      std::list<uint> l;
      uint j;
      for ( j = 0; j != LINEV[i].size(); j++ )
      {
        l.push_back( index[LINEVV[i][j]] );
      }
      new_line.push_back(l);
      l.clear();
    }
  }
  _vertex = new_vertex;
  _face = new_face;
  import_lines(new_line);

  return gluesep;
}

#ifdef DEBUG
void
Boundary::
dump_edge( std::ostream &o ) const
{
  o << "EDGE DUMP\n";

  EdgeMap::iterator u;
  for ( u = _edge.begin(); u != _edge.end(); u++ )
  {
    o << (*u).first.first << " " << (*u).first.second << " ";
    o << "=" << (*u).second.size() << " ";
    uint i;
    for ( i = 0; i < (*u).second.size(); i++ )
    {
      o << (*u).second[i];
      if ( i < (*u).second.size() - 1 )
      {
        o << " ";
      }
      else
      {
        o << "\n";
      }
    }
  }
}
#endif


} // namespace surface0
} // namespace geom
