/* GANG Software
 * GEOM/geom/surface0/SurfaceBase.C
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
#include <slist>
#include <iomanip>
#include "base/Regex.H"
#include "base/Stl.H"
#include "TransformerMatrix.H"
#include "Translator.H"
#include "Reflector.H"
#include "SurfaceBase.H"

namespace geom {
namespace surface0 {

SurfaceBase::
SurfaceBase()
    :
    GeomObject(),
    BoundingBox(),
    LineSet(),
    _vertex(),
    _face(),
    _type(EMPTY),
    _spaceform(),
    _box(),
    _i_count(0U),
    _j_count(0U),
    _i_begin(0U),
    _i_step(0U),
    _j_begin(0U),
    _j_step(0U),
    _face_center()
{
}

SurfaceBase::
SurfaceBase( SurfaceBase const &a )
    :
    GeomObject(a),
    BoundingBox(a),
    LineSet(a),
    _vertex(a._vertex),
    _face(a._face),
    _type(a._type),
    _spaceform( a._spaceform ),
    _box( a._box ),
    _i_count(a._i_count),
    _j_count(a._j_count),
    _i_begin(a._i_begin),
    _i_step(a._i_step),
    _j_begin(a._j_begin),
    _j_step(a._j_step),
    _face_center(a._face_center)
{
}

SurfaceBase::
~SurfaceBase()
{
}

SurfaceBase &
SurfaceBase::
operator=( SurfaceBase const &a )
{
  if ( this == &a ) { return *this; }

  GeomObject::operator=(a);
  BoundingBox::operator=(a);
  LineSet::operator=(a);
  _type = a._type;
  _spaceform =  a._spaceform;
  _box = a._box;
  _i_count = a._i_count;
  _j_count = a._j_count;
  _i_begin = a._i_begin;
  _i_step = a._i_step;
  _j_begin = a._j_begin;
  _j_step = a._j_step;
  _face_center = a._face_center;

  return *this;
}

void
SurfaceBase::
clear()
{
  _type = EMPTY;
  changed(true);
  _spaceform = SpaceForm();

  Transform t;
  t.identity(4U);
  position(t);
  projection_mode(CENTRAL);

  BoundingBox::clear();
  LineSet::clear();

  _i_count = 0;
  _j_count = 0;
  _i_begin = 0;
  _i_step = 0;
  _j_begin = 0;
  _j_step = 0;

  _face_center.clear();

  _box.clear();
}

uint
SurfaceBase::
vertex_count() const
{
  if ( _type == INDEXED )
  {
    return (uint)_vertex.size();
  }
  else if ( _type == GRID )
  {
    return _i_step * _j_step;
  }
  else
  {
    DIE();
  }
  return 0;
}

uint
SurfaceBase::
face_count() const
{
  if ( _type == INDEXED )
  {
    return (uint)_face.size();
  }
  else if ( _type == GRID )
  {
    return (_i_step  - 1)*(_j_step - 1);
  }
  else
  {
    DIE();
  }
  return 0;
}


uint
SurfaceBase::
face_vertex(uint f, uint v) const
{
  if ( _type == INDEXED )
  {
    return (uint)_face[f][v];
  }
  else if ( _type == GRID )
  {
    uint r = 0;
    DIE_IF( v >= 4 );
    DIE_IF( _i_step == 0 );
    DIE_IF( _j_step == 0 );

    uint base =
      _j_step * ( f / ( _j_step-1) ) +
      math::mod(f, _j_step-1 );

    if ( v == 0 ) { r = base; }
    else if ( v == 1 ) { r = base + 1; }
    else if ( v == 2 ) { r = base + 1 + _j_step; }
    else if ( v == 3 ) { r = base + _j_step; }

    return r;
  }
  else
  {
    DIE();
  }
  return 0;
}

uint
SurfaceBase::
face_count(uint i) const
{
  if ( _type == INDEXED )
  {
    return (uint)_face[i].size();
  }
  else if ( _type == GRID )
  {
    return 4U;
  }
  else
  {
    DIE();
  }
  return 0;
}

void
SurfaceBase::
import(
  base::vector<Vertex> const &vertex,
  base::vector<base::vector<uint> > const &face,
  SpaceForm const &spaceform_ )
{
// WARN_IF(vertex.size() == 0, "vertex count = 0");
// WARN_IF(face.size() == 0, "face count = 0");

  clear();
  _type = INDEXED;
  spaceform(spaceform_);
  _vertex = vertex;
  _face = face;

  _box.compute( this );
}

uint
SurfaceBase::
vertex_index( uint n ) const
{
  if ( _type == INDEXED )
  {
    return n;
  }
  else if ( _type == GRID )
  {
    uint i = _i_begin + (n / _j_step);
    uint j = _j_begin + math::mod(n, _j_step);
    return index(i, j);
  }
  else
  {
    DIE();
  }
  return 0;
}

uint
SurfaceBase::
face_index( uint n ) const
{
  if ( _type == INDEXED )
  {
    return n;
  }
  else if ( _type == GRID )
  {
    uint i = _i_begin + (n / (_j_step-1));
    uint j = _j_begin + math::mod(n, (_j_step-1));
    return i * (_j_count-1) + j;
  }
  else
  {
    DIE();
  }
  return 0;
}

void
SurfaceBase::
reverse_orientation()
{
  uint i;
  for (i = 0; i < face_count(); i++)
  {
    std::reverse( _face[i].begin(), _face[i].end() );
  }
}

void
SurfaceBase::
reset_clip()
{
  _i_begin = 0;
  _i_step = _i_count;
  _j_begin = 0;
  _j_step = _j_count;
  changed(true);
}

void
SurfaceBase::
set_clip(
  uint i_begin, uint i_step,
  uint j_begin, uint j_step )
{
  _i_begin = i_begin;
  _i_step = i_step;
  _j_begin = j_begin;
  _j_step = j_step;
  changed(true);
}

void
SurfaceBase::
get_clip(
    uint &i_begin, uint &i_step,
    uint &j_begin, uint &j_step )
  const
{
  i_begin = _i_begin;
  i_step = _i_step;
  j_begin = _j_begin;
  j_step = _j_step;
}

void
SurfaceBase::
import(
  base::vector<base::vector<Vertex> > const &vertex,
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

  base::vector<base::vector<Vertex> >::const_iterator i;
  for ( i = vertex.begin(); i != vertex.end(); i++ )
  {
    _vertex.insert( _vertex.end(), (*i).begin(), (*i).end() );
  }

  insert_grid_boundary();

  _box.compute( this );
}


void
SurfaceBase::
compute_face_center() const
{
  if ( ! _face_center.empty() ) { return; }

  uint i;
  uint n = face_count();
  for( i = 0; i < n; i++ )
  {
    // compute center of face
    uint m = face_count(i);
  
    Vertex3 c;
    Vertex3 v;
    uint j;
    for (j = 0; j < m; j++)
    {
      uint k = face_vertex(i,j);
      vertex(v, k);
      c += v;
    }
    c /= m; 
    _face_center.push_back(c);
  }
}

void
SurfaceBase::
apply( Transformer const &T )
{
  // NOTE: ignores color (mean curvatature, etc)
  WARN_IF( _spaceform.dim != 3U || _spaceform.space != SpaceForm::SPACEFORM_R,
           "transform applied to non-standard geometry: may be incorrect");

  if (_spaceform.dim == 3U)
  {
    Vertex4 v;

    uint i;
    for ( i = 0; i < vertex_count(); i++ )
    {
      vertex(v, i);
      T.function(v);
      _vertex[i].import(v);
    }
  }
  else if (_spaceform.dim == 4U)
  {
    // NOTE: hack for hyperbolic geometry
//    Vertex4 v;
    SpaceForm s;
    s.dim = 3U;
    s.space = SpaceForm::SPACEFORM_H;
    spaceform(s);

    Vertex4 v;

    math::Vector<Real> w;
    w.allocate(4U);

    uint i;
    for ( i = 0; i < vertex_count(); i++ )
    {
      vertex(v, i);
      T.function(v);
      v /= v[3];

      w[0] = v[0];
      w[1] = v[1];
      w[2] = v[2];
      w[3] = 0.0;
      _vertex[i].import(w);
    }
  }
  else
  {
    return;
  }

  changed(true);
}

void
SurfaceBase::
transform(
  geom::Transform const &a )
{
  geom::surface0::TransformerMatrix T(a);
  apply( T );
}

void
SurfaceBase::
translate(
  math::VectorX<Real,3U> const &a )
{
  surface0::Translator T(a);
  apply( T );
}

void
SurfaceBase::
reflect(
  math::VectorX<Real,4U> const &a )
{
  surface0::Reflector T(a);
  apply( T );
}

void
SurfaceBase::
insert_grid_boundary()
{
  // boundary lines
  std::list<uint> segment;
  std::list<std::list<uint> > component;
  uint n = _i_count * _j_count;
  uint i, j;

  // boundary 1
  for ( j = 0; j < _j_count; j++ )
  {
    segment.push_back(j);
  }
  component.push_back(segment);
  segment.clear();

  // boundary 2
  for ( i = 0; i < _i_count; i++ )
  {
    segment.push_back( _j_count - 1 + i*_j_count);
  }
  component.push_back(segment);
  segment.clear();

  // boundary 3
  for ( j = 0; j < _j_count; j++ )
  {
    segment.push_back( n - 1 - j );
  }
  component.push_back(segment);
  segment.clear();

  // boundary 4
  for ( i = 0; i < _i_count; i++ )
  {
    segment.push_back( n - _j_count - i*_j_count);
  }
  component.push_back(segment);
  segment.clear();

  import_lines( component );
}


} // namespace surface0
} // namespace geom
