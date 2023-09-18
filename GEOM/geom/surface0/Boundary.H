/* GANG Software
 * GEOM/geom/surface0/Boundary.H
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

#ifndef geom_surface0_Boundary_INCLUDED
#define geom_surface0_Boundary_INCLUDED

#include <map>
#include <slist>
#include "base/vector.H"
#include "math/Matrix4.H"
#include "Common.H"
#include "SurfaceBase.H"

namespace geom {
namespace surface0 {

/*
  Boundary connectivity information.

  An element of an EdgeMap represents an edge and is of the form
    { (i,j), {f0,f1,...} }.
    (i,j) represents an edge, and F = {f0,f1,...} a list of faces adjacent
    to the edge.

    length(F) is normally either 1 (boundary edge) or 2 (interior edge).

  compute_line_boundary()
     Computes _boundary, indices into _vertex making up the surface
     boundary.

     Each pair of unsigned ints represents a line segment.
     Algorithm: call compute_edge(). Put all edges with count=1 into
     _boundary

  compute_adjacency_list()
     Computes _adjacency_list. _adjacency_list[i] is a list of the vertices
     adjacent to i

  compute_edge()
     Compute a list of edges and the faces they bound.
     compute an associative array of edges, together
     with a list of the faces of which they are edges

     algorithm: cycle through all the faces, making a hash
       of all edges
     every time an edge occurs in a face, increment a counter.

     note: this could possibly be done with a hash rather than a
       map, but a hash function wants a number-like key. Here
       a pair of ints is the key
     note: this could possibly be done with a set, by counting
       occurences of edges only mod 2. This would assume that
       each edge occurs in at most 2 faces

  compute_pushoff()
    computes _pushoff, a lookup table each edge vertices to an
    adjacent interior vertex. Used for mean/gaussian curvature

    If i is an interior point, _pushoff[i] is set to INTERIOR_POINT
    If i is a boundary point, _pushoff[i] is set to the index of
      an adjacent interior point (if one exists)
    If no adjacent interior point exists, _pusoff[i] is set to UNKNOWN

    _pushoff is for coloring edges by gaussian/mean curvature
    via adjacent interior points

    NOTE: Each boundary vertex occurs in two boundary edges,
    so this inefficiently computes pushoff's twice for each boundary vertex
  */

class Boundary
  :
    public SurfaceBase
{

public:
  // constructor
  Boundary();

  // copy constructor
  Boundary( Boundary const & );

  // destructor
  virtual ~Boundary();

  // assignment operator
  Boundary &operator=( Boundary const & );

  void clear();

  typedef std::pair<uint, uint> uint_pair;

  // comparison funtion for the _edge map
  struct uint_pair_lt
  {
    //
    bool operator()( uint_pair const &a, uint_pair const &b ) const
      {
        return a.first < b.first ||
          ( a.first == b.first && a.second < b.second );
      }
  };

  typedef std::map< uint_pair, base::vector<uint>, uint_pair_lt >
  EdgeMap;


  uint edge_count() const;

  EdgeMap const &edge() const
    { return _edge; }

  void compute_boundary() const;

  // export the boundary
  void boundary( std::list<std::list<uint_pair> > &b ) const;

  // adjacency list
  void compute_adjacency_list() const;

  std::slist<uint> const &adjacency_list(uint i) const
    { return _adjacency_list[i]; }

  void
  import_boundary_lines(
    std::list<std::list<uint> > const &corner );
  
  Real glue(
    Boundary const *g,
    std::list<uint> const &boundaryset );

  Real glue_self(
    std::list<uint> const &boundaryset1,
    std::list<uint> const &boundaryset2 );

protected:

  static
  inline
  uint
  prev( uint i, uint n )
    { return i == 0 ? n - 1 : i - 1; }

  static
  inline
  uint
  next( uint i, uint n )
    { return i == n - 1 ? 0 : i + 1; }


  void compute_edge() const;

  void compute_pushoff() const;
  uint pushoff( uint i ) const
    { return _pushoff[i]; }

  EdgeMap const &edge()
    { return _edge; }

  uint
  third_vertex(
    uint vertex1, uint vertex2, uint face ) const;

private:

  void dump_edge( std::ostream &o ) const;

  mutable EdgeMap _edge;
  mutable std::list<std::list<uint_pair> > _boundary;
  mutable base::vector<std::slist<uint> > _adjacency_list;
  mutable base::vector<uint> _pushoff;

};

} // namespace surface0
} // namespace geom

#endif // geom_surface0_Boundary_INCLUDED
