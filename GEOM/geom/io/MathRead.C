/* GANG Software
 * GEOM/geom/io/MathRead.C
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
#include "eval/Eval.H"
#include "MathRead.H"

namespace geom {
namespace io {

MathRead::
MathRead()
    :
    Reader(),
    _list()
{
}

MathRead::
~MathRead()
{
}

void
MathRead::
read(
  ::io::Istream &in,
  ::geom::surface::SurfaceBase &G,
  ::milieu::kernel::MilieuBase &M )
  throw (::io::ReadException)
{
  _stream = &in;

  Type type = read_keyword();
  if (type == GRAPHICS3D)
  {
    // indexed
    surface0::Surface *g = new surface0::Surface;
    _list.push_back(g);
    read(g);
  }
  else { _throw("syntax error"); }

  if ( _list.empty() )
  {
    if ( _no_surface == ERR_WARN )
    { _throw("empty surface"); }
    else if ( _no_surface == ERR_THROW )
    { WARN("empty surface"); }
  }

  G.insert_no_copy( _list );
  _list.clear();

  _stream = (::io::Istream *)0;
}

void
MathRead::
read(
  surface0::Surface *g )
{
  // NOTE: should coalesce the vertices

  base::vector<geom::Vertex3> _vertex;
  base::vector<base::vector<uint> > _face;

  bool polygon = false;

  uint c = 0;
  uint p = 0;
  geom::Vertex3 v;
  v.set(0);
  base::vector<uint> f;

  // NOTE: this is a hack -- should write a bison parser

  LvalStruct lval;
  for (;;)
  {
    int t = lex(lval);

    if (t == 0) { break; }

    if (t == R_Polygon)
    {
      polygon = true;
    }
    else if (t == R_Real)
    {
      if ( ! polygon ) { _throw( "syntax error" ); }
      if (p == 3) { _throw( "too many points in vertex" ); }
      Real x = eval_real(lval.text);
      v[p++] = x;
      if (p == 3)
      {
        _vertex.push_back(v);
        v.set(0);
        f.push_back(c++);
        p = 0;
      }
    }
    else if (t == R_rightBracket)
    {
      if (!polygon) { break; }
      polygon = false;
      _face.push_back(f);
      f.clear();
    }
    else if (t == R_rightBrace)
    {
      if (!polygon) { break; }
    }
  }

  if ( _vertex.empty() )
  {
    if ( _no_points == ERR_THROW )
    { _throw( "surface contains no points" ); }
    else if ( _no_points == ERR_WARN )
    { WARN( "surface contains no points" ); }
  }

  g->import( _vertex, _face, geom::SpaceForm() );
}

Real
MathRead::
eval_real( char const *text )
{
  base::String s = text;
  base::vector<base::String> v;

  if ( base::match( "(.+)\\*\\^(.+)$", s, v ) )
  {
    s = v[1] + base::String("*10^") + v[2];
  }

  Real x;
  try { eval::evaluate( x, s ); }
  catch ( base::Exception const & )
  { _throw( "syntax error while reading real number" ); }
  return x;
}

MathRead::Type
MathRead::
read_keyword()
{
  LvalStruct lval;
  int t = lex(lval);

  Type type = NO_TYPE;
  if ( t == R_Graphics ) { type = GRAPHICS; }
  else if ( t == R_Graphics3D ) { type = GRAPHICS3D; }
  else if ( t == R_SurfaceGraphics ) { type = SURFACEGRAPHICS; }
  else { _throw( "syntax error" ); }
  return type;
}
    
void
MathRead::
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
MathRead::
_throw( char const *message )
{
  cleanup();

  throw ::io::ReadException(
    ::io::ReadException::PARSE_ERROR, _stream->filename(), _lineno,
    message );
}

} // namespace io
} // namespace geom
