/* GANG Software
 * GEOM/triang/Triangulator.C
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

#include "base/String.H"
#include "base/System.H"
#include "base/String.H"
#include "base/Stl.H"
#include "io/IstreamStream.H"
#include "eval/Eval.H"
#include "Triangulator.H"

namespace triang {

Triangulator::
Triangulator()
    :
    _data(),
    _smooth(0),
    _refine(0),
    _max_area2(0),
    _curvature_cut(0),
    _curvature_exp(0),
    _boundary_str(),
    _vertex_v(),
    _vertex_v_v(),
    _hole_v(),
    _face_v()
{
  initialize();
}

Triangulator::
~Triangulator()
{
}

void
Triangulator::
initialize()
{
  _smooth = 0;
}


void
Triangulator::
read( char const *filename )
{
  ::io::IstreamStream in( filename );
  read( in );
}

void
Triangulator::
read( ::io::Istream &stream )
{
  initialize();

  // parse the input data
  _data.parse(stream);
  set_data();

  // parse the boundary
  parse(
    _boundary_str,
    _vertex_v_v,
    _hole_v,
    _data.get("boundary") );
}

void
Triangulator::
read_string( char const *s )
{
  initialize();

  _data.parse(base::String(s));

  set_data();

  // parse the boundary
  parse(
    _boundary_str,
    _vertex_v_v,
    _hole_v,
    _data.get("boundary") );
}

void
Triangulator::
read_string( base::String const &s )
{
  initialize();

  // parse the whole string
  _data.parse(s);

  set_data();

  // parse the boundary
  parse(
    _boundary_str,
    _vertex_v_v,
    _hole_v,
    _data.get("boundary") );
}

void
Triangulator::
set_data()
{
  uint const LINE_NUMBER = 0;

  try { eval::evaluate( _max_area, _data.get("max_area") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_MAX_AREA, LINE_NUMBER ); }

  try { eval::evaluate( _min_angle, _data.get("min_angle") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_MIN_ANGLE, LINE_NUMBER ); }

  try { eval::evaluate( _smooth, _data.get("smooth") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_SMOOTH, LINE_NUMBER ); }

  try { eval::evaluate( _refine, _data.get("refine") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_REFINE, LINE_NUMBER ); }

  try { eval::evaluate( _max_area2, _data.get("max_area2") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_MAX_AREA2, LINE_NUMBER ); }

  try { eval::evaluate( _curvature_exp, _data.get("curvature_exp") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CURVATURE_EXP, LINE_NUMBER ); }

  try { eval::evaluate( _curvature_cut, _data.get("curvature_cut") ); }
  catch ( base::Exception const & )
  { throw Exception( Exception::ERR_CURVATURE_CUT, LINE_NUMBER ); }
}

void
Triangulator::
triangulate(
  geom::Surface *surface )
  throw ( base::Exception )
{
  if (_vertex_v_v.size() == 0)
  {
    WARN("no vertices");
    throw Exception( Exception::ERR_INTERNAL );
  }

  try
  {
    Triangle::triangulate(
      _vertex_v,
      _face_v,
      _vertex_v_v,
      _hole_v );
  }
  catch ( int )
  {
    WARN();
    throw Exception( Exception::ERR_INTERNAL );
  }

  base::vector< geom::Vertex2 > vertex;
  copy( vertex, _vertex_v );

  surface->clear();
  geom::SpaceForm s( 2U, geom::SpaceForm::SPACEFORM_R );
  surface->import( vertex, _face_v, s );

  std::list<std::list<uint> > corner;
  corners(corner, _vertex_v_v);
  surface->import_boundary_lines(corner);
  surface->relax( _smooth );

#if 0
  //==================================
  // DEBUG TEST (force refinement)
  {
    geom::Real a[3] = {0.2, 0.1, 0.05};
    uint i;
    for (i=0; i<3; i++)
    {
      WARN("refine %d", i);
      base::vector<geom::Real> area;
      base::fill( area, a[i]+0.01*math::random(), _face_v.size() );
      triangulate( surface, area );
    }
  }
  //==================================
#endif
}

void
Triangulator::
triangulate(
  geom::Surface *surface,
  base::vector< geom::Real> const &area )
  throw ( base::Exception )
{
  // re-triangulate with area constraint (pass 2)

  DIE_IF( _face_v.size() != area.size() );

  try
  {
    Triangle::triangulate(
      _vertex_v,
      _face_v,
      area );
  }
  catch ( int )
  {
    WARN();
    throw Exception( Exception::ERR_INTERNAL );
  }

  base::vector< geom::Vertex2 > vertex;
  copy( vertex, _vertex_v );
  surface->clear();
  geom::SpaceForm s( 2U, geom::SpaceForm::SPACEFORM_R );
  surface->import( vertex, _face_v, s );

  std::list<std::list<uint> > corner;
  corners(corner, _vertex_v_v);
  surface->import_boundary_lines(corner);
  surface->relax( _smooth );
}

void
Triangulator::
copy(
  base::vector< geom::Vertex2 > &b,
  base::vector< std::pair< geom::Real,geom::Real> > const &a )
{
  // copy b to a
  b.clear();
  b.reserve( a.size() );
  uint i;
  for ( i = 0; i < a.size(); i++ )
  {
    b.push_back( geom::Vertex2( a[i].first, a[i].second ) );
  }
}

void
Triangulator::
corners(
  list<list<uint> > &corner,
  base::vector<Curve> const &boundary )
{
  // Return a list of corners in 'corner'

  corner.clear();

  uint c = 0;

  list<uint> corner0;

  // for each boundary component
  uint i;
  for (i= 0; i < _vertex_v_v.size(); i++)
  {
    base::vector<base::vector<std::pair<Real,Real> > > const &v =
      _vertex_v_v[i].v;
    // for each part of the boundary component
    uint j;
    for (j = 0; j < v.size(); j++)
    {
      if ( ! v[j].empty() )
      {
        corner0.push_back(c);
      }
      c += v[j].size();
    }
    corner.push_back(corner0);
    corner0.clear();
  }
}

} // namespace triang
