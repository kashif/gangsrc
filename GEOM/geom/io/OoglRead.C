/* GANG Software
 * GEOM/geom/io/OoglRead.C
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
#include "base/Color4.H"
#include "base/Regex.H"
#include "OoglRead.H"

namespace geom {
namespace io {

OoglRead::
OoglRead()
    :
    Reader(),
    OoglLexer(),
    _list(),
    _type(NO_TYPE),
    _color_flag(false),
    _normal_flag(false),
    _dim(0),
    _vertex_count(0),
    _face_count(0),
    _i_count(0),
    _j_count(0),
    _grid_minimum(2)
{
}

OoglRead::
~OoglRead()
{
}

void
OoglRead::
read(
  ::io::Istream &in,
  ::geom::surface::SurfaceBase &G,
  ::milieu::kernel::MilieuBase &M )
  throw (::io::ReadException)
{
  _stream = &in;

  for (;;)
  {
    // get keyword
    read_keyword();
    if (_type == NO_TYPE)
    { break; }
    else if (_type == INDEXED)
    {
      // indexed
      surface0::Surface *g = new surface0::Surface;
      _list.push_back(g);
      read_indexed(g);
    }
    else if (_type == GRID)
    {
      // grid
      surface0::Surface *g = new surface0::Surface;
      _list.push_back(g);
      read_grid(g);
    }
    else { _throw( "internal error" ); }
  }

  if ( _list.empty() )
  {
    if ( _no_surface == ERR_THROW )
    { _throw("empty surface"); }
    else if ( _no_surface == ERR_WARN )
    { WARN("empty surface"); }
  }

  G.insert_no_copy( _list );
  _list.clear();

  _stream = (::io::Istream *)0;
}

void
OoglRead::
read_indexed(
  surface0::Surface *g )
{
  base::vector<base::vector<Real> > _vertex;
  base::vector<base::vector<uint> > _face;
  base::vector<base::Color4> _color;
  base::vector<Normal3> _normal;

  // read vertices

  uint i;
  for ( i = 0; i < _vertex_count; i++ )
  {
    base::vector<Real> w;
    w.reserve(_dim);

    uint k;
    for ( k = 0; k < _dim; k++ )
    {
      w.push_back( read_real() );
    }
    _vertex.push_back(w);

    // read normal
    if ( _normal_flag )
    {
      geom::Normal3 n;
      uint k;
      for (k = 0; k < _dim; k++)
      {
        Real x = read_real();
        n[k] = x;
      }
      _normal.push_back(n);
    }
    // read color
    if ( _color_flag )
    {
      base::Color4 c;
      uint k;
      for (k = 0; k < 4; k++)
      {
        float x = read_float();
        if (x < 0.0f || x > 1.0f)
        {
          _throw( "color specification is out of range" );
        }
        c[k] = x;
      }
      _color.push_back( c );
    }
  }

  // read faces
  for ( i = 0; i < _face_count; i++ )
  {
    // read faces
    uint n = read_uint();
    if ( n < _polygon_minimum )
    {
      _throw( "polygon has too few vertices" );
    }

    base::vector<uint> f;
    f.reserve(n);

    uint k;
    for ( k = 0; k < n; k++ )
    {
      uint p = read_uint();
      if ( p >= _vertex_count )
      {
        _throw( "face index is out of range" );
      }
      f.push_back(p);
    }
    _face.push_back(f);

    // cannot read face colors
  }

  if ( _vertex.empty() )
  {
    if ( _no_points == ERR_THROW )
    { _throw( "surface contains no points" ); }
    else if ( _no_points == ERR_WARN )
    { WARN( "surface contains no points" ); }
  }
  if ( _face.empty() )
  {
    if ( _no_faces == ERR_THROW )
    { _throw( "surface contains no faces" ); }
    else if ( _no_faces == ERR_WARN )
    { WARN( "surface contains no faces" ); }
  }

  g->import(
    _vertex, _face,
    geom::SpaceForm(_dim, geom::SpaceForm::SPACEFORM_R) );
  if (_color_flag) { g->import_vertex_color( _color ); }
  if (_normal_flag) { g->import_vertex_normal( _normal ); }
}


void
OoglRead::
read_grid(
  geom::surface0::Surface *g )
{
  base::vector<base::vector<base::vector<Real> > >  _vertex;
  base::vector<base::vector<base::Color4> > _color;
  base::vector<base::vector<geom::Normal3> > _normal;

  uint i;
  for ( i = 0; i < _i_count; i++ )
  {
    base::vector<base::vector<Real> > vertex;
    vertex.reserve(_j_count);
    base::vector<base::Color4 > color;
    if ( _color_flag ) { color.reserve(_j_count); }
    base::vector<geom::Normal3 > normal;
    if ( _normal_flag ) { normal.reserve(_j_count); }

    uint j;
    for ( j = 0; j < _j_count; j++ )
    {
      // read vertex
      base::vector<Real> w;
      w.reserve(_dim);

      uint k;
      for ( k = 0; k < _dim; k++ )
      {
        w.push_back( read_real() );
      }
      vertex.push_back(w);

      // read color
      if ( _color_flag )
      {
        base::Color4 c;
        uint k;
        for ( k = 0; k < 4; k++ )
        {
          float x = read_float();
          if (x < 0.0f || x > 1.0f)
          {
            _throw( "color specification is out of range" );
          }
          c[k] = x;
        }
        color.push_back(c);
      }

      // read normal
      if ( _normal_flag )
      {
        geom::Normal3 n;
        uint k;
        for ( k = 0; k < 3; k++ )
        {
          n[k] = read_real();
        }
        normal.push_back(n);
      }
    }
    _vertex.push_back(vertex);
    if (_color_flag) { _color.push_back(color); }
    if (_normal_flag) { _normal.push_back(normal); }
  }

  if ( _vertex.empty() )
  {
    if ( _no_points == ERR_THROW )
    { _throw( "surface contains no points" ); }
    else if ( _no_points == ERR_WARN )
    { WARN( "surface contains no points" ); }
  }

  // import
  g->import(
    _vertex,
    geom::SpaceForm(_dim, geom::SpaceForm::SPACEFORM_R) );
  if (_color_flag) { g->import_vertex_color( _color ); }
  if (_normal_flag) { g->import_vertex_normal( _normal ); }
}

Real
OoglRead::
read_real()
{
  _expectToken = P_REAL;

  LvalStruct lval;
  int t = lex(lval);
  if (t == 0)
  {
    _throw( "file ended before surface specification was complete" );
  }

  Real x;
  try {
    base::String(lval.text).to_number(x);
  }
  catch ( base::Exception const & )
  { _throw( "syntax error while reading real number" ); }
  return x;
}

float
OoglRead::
read_float()
{
  _expectToken = P_REAL;

  LvalStruct lval;
  int t = lex(lval);
  if (t == 0)
  {
    _throw( "file ended before surface specification was complete" );
  }
  float x;
  try {
    base::String(lval.text).to_number(x);
  }
  catch (base::Exception const &)
  { _throw( "syntax error while reading real number" ); }
  return x;
}

uint
OoglRead::
read_uint()
{
  _expectToken = P_UINT;

  LvalStruct lval;
  int t = lex(lval);
  if (t == 0)
  {
    _throw( "file ended before surface specification was complete" );
  }
  uint x;
  try {
    base::String(lval.text).to_number(x);
  }
  catch (base::Exception const &)
  { _throw( "syntax error while reading integer" ); }
  return x;
}

void
OoglRead::
read_keyword()
{
  _expectToken = P_KEYWORD;

  LvalStruct lval;
  int t = lex(lval);
  if (t == 0)
  {
    // done
    _type = NO_TYPE;
    return;
  }

  char const *s = lval.text;

  base::vector<base::String> w;
  if (t == R_OFF)
  {
    if ( ! base::match( "(C?)(N?)(4?)OFF", s, w ) )
    { _throw( "error reading keyword" ); }
    _type = INDEXED;
    _color_flag = ! w[1].empty();
    _normal_flag = ! w[2].empty();

    // dimension
    _dim = (w[3].empty() ? 3U : 4U);
    if ( _dim < _dim_minimum ) { _throw( "dimension too small" ); }

    // vertex count
    _vertex_count = read_uint();
    if ( _vertex_count == 0 )
    {
      if ( _no_points == ERR_THROW )
      { _throw( "surface has no vertices" ); }
      else if ( _no_points == ERR_WARN )
      { WARN( "surface has no vertices" ); }
    }

    // face count
    _face_count = read_uint();
    if ( _face_count == 0 )
    {
      if ( _no_faces == ERR_THROW )
      { _throw( "surface has no faces" ); }
      else if ( _no_faces == ERR_WARN )
      { WARN( "surface has no faces" ); }
    }

    // edge count (unused)
    read_uint();
  }
  else if (t == R_nOFF)
  {
    if ( !base::match( "(C?)(N?)nOFF", s, w ) )
    { _throw( "error reading keyword" ); }
    _type = INDEXED;
    _color_flag = ! w[1].empty();
    _normal_flag = ! w[2].empty();

    // dimension
    _dim = read_uint();
    if ( _dim < _dim_minimum ) { _throw( "dimension too small" ); }

    // vertex count
    _vertex_count = read_uint();
    if ( _vertex_count == 0 )
    {
      if ( _no_points == ERR_THROW )
      { _throw( "surface has no points" ); }
      else if ( _no_points == ERR_WARN )
      { WARN( "surface has no points" ); }
    }

    // face count
    _face_count = read_uint();
    if ( _face_count == 0 )
    {
      if ( _no_faces == ERR_THROW )
      { _throw( "surface has no faces" ); }
      else if ( _no_faces == ERR_WARN )
      { WARN( "surface has no faces" ); }
    }

    // edge count (unused)
    read_uint();
  }
  else if (t == R_GRID)
  {
    if ( ! base::match( "(C?)(N?)(4?)MESH", s, w ) )
    { _throw( "error reading keyword" ); }
    _type = GRID;
    _color_flag = ! w[1].empty();
    _normal_flag = ! w[2].empty();
    _dim = (w[3].empty() ? 3U : 4U);
    if ( _dim < _dim_minimum ) { _throw( "dimension too small" ); }

    // j count
    _j_count = read_uint();
    if ( _j_count < _grid_minimum )
    { _throw( "first grid count is too small" ); }

    // i count
    _i_count = read_uint();
    if ( _j_count < _grid_minimum )
    {
      _throw( "second grid count is too small" );
    }
  }
  else if (t == R_nGRID)
  {
    if ( ! base::match( "(C?)(N?)nMESH", s, w ) )
    { _throw( "error reading keyword" ); }
    _type = GRID;
    _color_flag = ! w[1].empty();
    _normal_flag = ! w[2].empty();
    _dim = read_uint();
    if ( _dim < _dim_minimum ) { _throw( "dimension too small" ); }

    // j count
    _j_count = read_uint();

    if ( _j_count < _grid_minimum )
    { _throw( "first grid count is too small" ); }

    // i count
    _i_count = read_uint();
    if ( _j_count < _grid_minimum )
    { _throw( "second grid count is zero" ); }
  }
}
    
void
OoglRead::
cleanup()
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = _list.begin(); i != _list.end(); i++ )
  {
    delete *i;
  }
  _list.clear();
}

void
OoglRead::
_throw( char const *message )
{
  cleanup();

  throw ::io::ReadException(
    ::io::ReadException::PARSE_ERROR, _stream->filename(), _lineno,
    message );
}

} // namespace io
} // namespace geom
