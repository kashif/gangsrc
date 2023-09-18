/* GANG Software
 * GEOM/geom/surface0/SurfaceBase.H
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

#ifndef geom_surface0_SurfaceBase_INCLUDED
#define geom_surface0_SurfaceBase_INCLUDED

#include <iostream>
#include <fstream>
#include "base/vector.H"
#include <map>
#include "math/Matrix4.H"
#include "Common.H"
#include "Vertex.H"
#include "GeomObject.H"
#include "BoundingBox.H"
#include "LineSet.H"
#include "Transformer.H"

namespace geom {

class Normal;

namespace surface0 {

/*
  Geometric Surface
*/

class SurfaceBase
  :
    public GeomObject,
    public BoundingBox,
    public LineSet
{

public:

  // constructor
  SurfaceBase();

  // copy constructor
  SurfaceBase( SurfaceBase const & );

  // destructor
  virtual ~SurfaceBase();

  // assignment operator
  SurfaceBase &operator=( SurfaceBase const & );

  virtual uint dimension() const
    { return 2U; }

  // returns the total number of vertices in the geometry object
  virtual uint vertex_count() const;

  Vertex const &vertex( uint i ) const
    { return _vertex[vertex_index(i)]; }

  template <class A>
  void vertex( A &v, uint i ) const
    { _vertex[vertex_index(i)].export_(v); }

  void vertex(
    Vertex4 &v, uint i, Transform const &t, ProjectionMode mode ) const
    { _vertex[vertex_index(i)].export_(v, t, mode); }


  // returns the total number of faces in the geometry object
  virtual uint face_count() const;

  // returns the number of vertices of the 'n'th face
  virtual uint face_count(uint n) const;

  // returns index of the v'th vertex of face f
  virtual uint face_vertex(uint f, uint v) const;

  SpaceForm const &spaceform() const
    { return _spaceform; }
  Box const &box() const
    { return _box; }

  base::vector<Vertex> const &vertex_data() const
    { return _vertex; }
  base::vector<base::vector<uint> > const &face_data() const
    { return _face; }

  template <class A>
  void import(
    base::vector<A> const &vertex,
    base::vector<base::vector<uint> > const &face,
    SpaceForm const &spaceform );

  void import(
    base::vector<Vertex> const &vertex,
    base::vector<base::vector<uint> > const &face,
    SpaceForm const &spaceform );

  template <class A>
  void import(
    base::vector<base::vector<A> > const &vertex,
    SpaceForm const &spaceform );

  void import(
    base::vector<base::vector<Vertex> > const &vertex,
    SpaceForm const &spaceform );

  void reverse_orientation();

  virtual void clear();

  enum Type { EMPTY, INDEXED, GRID };
  Type type() const
    { return _type; }

  uint i_count() const
  { return _i_count; }
  uint j_count() const
  { return _j_count; }
  uint i_begin() const
  { return _i_begin; }
  uint i_step() const
  { return _i_step; }
  uint j_begin() const
  { return _j_begin; }
  uint j_step() const
  { return _j_step; }

  void reset_clip();
  void set_clip(
    uint i_begin, uint i_step,
    uint j_begin, uint j_step );
  void get_clip(
    uint &i_begin, uint &i_step,
    uint &j_begin, uint &j_step ) const;

  void compute_face_center() const;
  Vertex3 const &face_center(uint i) const
    { return _face_center[i]; }

  virtual void apply( Transformer const & );
  void transform( geom::Transform const &a );
  void translate( math::VectorX<Real,3U> const &a );
  void reflect( math::VectorX<Real,4U> const &a );

protected:

  void compute_bounding_box()
    { _box.compute(this); }

  virtual void replace_vertex( uint p, Vertex2 const &v )
    { _vertex[p].import(v); }

  Vertex &vertex( uint i )
    { return _vertex[vertex_index(i)]; }

  uint vertex_index( uint n ) const;
  uint face_index( uint n ) const;

  virtual void spaceform( SpaceForm s )
    { _spaceform = s; }

  // positions in R^3
  base::vector<Vertex> _vertex;

  // base::vector of face indices
  base::vector<base::vector<uint> > _face;

  uint index( uint i, uint j ) const
    { DIE_IF( _type != GRID ); return i * _j_count + j; }

private:
  void insert_grid_boundary();

  Type _type;

  SpaceForm _spaceform;

  mutable BoundingBox _box;

  uint _i_count, _j_count;
  uint _i_begin, _i_step;
  uint _j_begin, _j_step;

  mutable base::vector<Vertex3> _face_center;
};

template <class A>
void
SurfaceBase::
import(
  base::vector<A> const &vertex,
  base::vector<base::vector<uint> > const &face,
  SpaceForm const &spaceform_ )
{
//  WARN_IF(vertex.size() == 0, "vertex count = 0");
//  WARN_IF(face.size() == 0, "face count = 0");

  clear();
  _type = INDEXED;

  spaceform(spaceform_);
  Vertex v(spaceform());

  uint i;
  for ( i = 0; i < vertex.size(); i++ )
  {
    v.import(vertex[i]);
    _vertex.push_back(v);
  }

  _face = face;

  _box.compute(this);
}


template <class A>
void
SurfaceBase::
import(
  base::vector<base::vector<A> > const &vertex,
  SpaceForm const &spaceform_ )
{
  if (vertex.size() <= 1 )
  { throw base::Exception( "i_count <= 1" ); }
  if (vertex[0].size() <= 1 )
  { throw base::Exception( "j_count <= 1" ); }

  clear();
  _type = GRID;
  spaceform(spaceform_);

  _i_count = vertex.size();
  _j_count = vertex[0].size();
  _i_begin = 0U;
  _i_step = _i_count;
  _j_begin = 0U;
  _j_step = _j_count;
  
  Vertex v(spaceform());

  base::vector<base::vector<A> >::const_iterator i;
  for ( i = vertex.begin(); i != vertex.end(); i++ )
  {
    base::vector<A>::const_iterator j;
    {
      for ( j = (*i).begin(); j != (*i).end(); j++ )
      {
        v.import(*j);
        _vertex.push_back(v);
      }
    }
  }

  insert_grid_boundary();

  _box.compute(this);
}

} // namespace surface0
} // namespace geom


#endif // geom_surface0_SurfaceBase_INCLUDED
