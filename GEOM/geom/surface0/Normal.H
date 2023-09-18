/* GANG Software
 * GEOM/geom/surface0/Normal.H
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

#ifndef geom_surface0_Normal_INCLUDED
#define geom_surface0_Normal_INCLUDED

#include "base/vector.H"
#include "Common.H"
#include "Boundary.H"

namespace geom {

namespace surface0 {

class Normal
  :
    public Boundary
{

public:
  // constructor
  Normal();

  // copy constructor
  Normal( Normal const & );

  // destructor
  virtual ~Normal();

  // assignment operator
  Normal &operator=( Normal const & );

  void clear();
  void clear_normal();

#if 0
  bool use_normal() const
    { return _use_normal && !_face_normal.empty() && !_vertex_normal.empty(); }
#endif

  void compute_normal() const;

  Normal3 const &face_normal(uint i) const
    { return _face_normal[face_index(i)]; }

  Normal3 const &vertex_normal(uint i) const
    { return _vertex_normal[vertex_index(i)]; }

  void face_normal(
    Normal3 &q,
    uint k,
    Transform const &transform_inv,
    ProjectionMode mode ) const;
  void vertex_normal(
    Normal3 &q,
    uint k,
    Transform const &transform_inv,
    ProjectionMode mode ) const;

  void import_face_normal(
    base::vector<Normal3> const & );
  void import_vertex_normal(
    base::vector<Normal3> const & );
  void import_face_normal(
    base::vector<base::vector<Normal3> > const & );
  void import_vertex_normal(
    base::vector<base::vector<Normal3> > const & );

  virtual void apply( Transformer const & );

/*
  Smooth a mesh.
  relaxes a mesh by replacing each point by the average of its
  adjacent points
  boundary points are omitted
  the points are relaxed in random order to prevent lopsidedness
  iterations is approximately how many cycles through all the vertices
  typically < 10
*/
  void relax( uint iterations );

protected:

private:

  void _compute_normal() const;
  void _compute_vertex_normal() const;
  void _compute_face_normal() const;

  void
  _compute_normal(
    Normal3 &y,
    Normal3 const &x,
    Vertex4 const &v,
    Transform const &transform_inv,
    ProjectionMode mode ) const;

  // normal to the surface for each face
  mutable base::vector<Normal3> _face_normal;

  // normal to the surface for each vertex
  mutable base::vector<Normal3> _vertex_normal;

#if 0
  mutable bool _use_normal;
#endif
};

} // namespace surface0
} // namespace geom

#endif // geom_surface0_Normal_INCLUDED
