/* GANG Software
 * GEOM/geom/io/VrmlRead.C
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

#include "base/Color4.H"
#include "geom/surface0/Surface.H"
#include "VrmlRead.H"

namespace geom {
namespace io {

VrmlRead::
VrmlRead()
    :
    Reader(),
    vrml::Parser(),
    _list(),
    _istream((::io::Istream *)0)
{
}

void
VrmlRead::
read(
  ::io::Istream &in,
  ::geom::surface::SurfaceBase &G,
  ::milieu::kernel::MilieuBase &M )
    throw (::io::ReadException)
{
  _istream = &in;
  vrml::Parser::read( in );

  if ( _list.empty() )
  {
    if ( _no_surface == ERR_THROW )
    { error("empty surface"); }
    else if ( _no_surface == ERR_WARN )
    { WARN("empty surface"); }
  }

  G.insert_no_copy( _list );
  _list.clear();

  _istream = (::io::Istream *)0;
}

void
VrmlRead::
indexedFaceSet( IndexedFaceSet const &s )
{
  base::vector<geom::Vertex3> vertex_v;
  base::vector<base::vector<uint> > face_v;
  base::vector<base::Color4> color_v;

  // read vertices
  uint i;
  geom::Vertex3 v;
  for ( i = 0; i < s.coord.size(); i += 3 )
  {
    v[0] = s.coord[i];
    v[1] = s.coord[i+1];
    v[2] = s.coord[i+2];
    vertex_v.push_back(v);
  }
  if ( vertex_v.empty() )
  {
    if ( _no_points == ERR_THROW )
    { _throw( "surface has no points" ); }
    else if ( _no_points == ERR_WARN )
    { WARN( "surface has no points" ); }
  }

  // read faces
  base::vector<uint> f;
  for ( i = 0; i < s.coordIndex.size(); i++ )
  {
    if ( s.coordIndex[i] >= 0 )
    {
      f.push_back(s.coordIndex[i]);
    }
    else
    {
      if ( f.size() < _polygon_minimum )
      { _throw( "face has too few vertices" ); }
      face_v.push_back(f);
      f.clear();
    }
  }
  if ( face_v.empty() )
  {
    if (_no_faces == ERR_THROW )
    { _throw( "surface has no faces" ); }
    else if (_no_faces == ERR_WARN )
    { WARN( "surface has no faces" ); }
  }

  // read color
  base::Color4 c;
  c[3] = 1.0;
  for ( i = 0; i < s.color.size(); i += 3 )
  {
    c[0] = s.color[i];
    c[1] = s.color[i+1];
    c[2] = s.color[i+2];
    color_v.push_back(c);
  }

  if ( ! color_v.empty() && vertex_v.size() != color_v.size() )
  { _throw( "number of colors unequal to number of vertices" ); }

  surface0::Surface *g = new surface0::Surface;

  g->import( vertex_v, face_v, geom::SpaceForm() );

  if ( ! color_v.empty() )
  {
    g->import_vertex_color( color_v );
  }
  _list.push_back(g);
}

void
VrmlRead::
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
VrmlRead::
_throw( char const *message )
{
  cleanup();

  throw( ::io::ReadException(
           ::io::ReadException::PARSE_ERROR,
           _istream->filename(), _lineno, message) );
}

} // namespace io
} // namespace geom
