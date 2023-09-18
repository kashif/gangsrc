/* GANG Software
 * GEOM/geom/io/JvxRead.C
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
#include "JvxRead.H"

namespace geom {
namespace io {

JvxRead::
JvxRead()
    :
    _milieu( (::milieu::kernel::MilieuBase *)0 ),
    _geomlist( (::geom::surface::SurfaceBase *)0 ),
    _list(),
    _error(false),
    _stream( (::io::Istream *)0 ),
    _dim(0),
    _mode(NO_MODE),
    _colormode(NO_COLORMODE),
    _point(),
    _line(),
    _face(),
    _point_color(),
    _line_color(),
    _face_color(),
    _point_normal(),
    _line_normal(),
    _face_normal(),
    _error_filename(),
    _error_line(0),
    _error_message( (char *)0 )
{
}

JvxRead::
~JvxRead()
{
}

void
JvxRead::
read(
  ::io::Istream &in,
  ::geom::surface::SurfaceBase &G,
  ::milieu::kernel::MilieuBase &M )
  throw (::io::ReadException)
{
  _stream = &in;
  _milieu = &M;
  _geomlist = &G;

  try
  {
    parse(in);
  }
  catch ( base::Exception const & )
  {
    // XML parse error
    error( message() );
  }

  if ( _list.empty() )
  {
    if ( _no_surface == ERR_THROW )
    { error("empty surface"); }
    else if ( _no_surface == ERR_WARN )
    { WARN("empty surface"); }
  }

  // NOTE: cannot throw exceptions through expat (since expat is a C library)
  if ( _error )
  {
    finalize();
    _stream = (::io::Istream *)0;
    throw ::io::ReadException(
      ::io::ReadException::PARSE_ERROR,
      _error_filename, _error_line, _error_message );
  }

  G.insert_no_copy( _list );
  _list.clear();

  _finalize();

  _stream = (::io::Istream *)0;
  _geomlist = (::geom::surface::SurfaceBase *)0;
  _milieu = (::milieu::kernel::MilieuBase *)0;
}

void
JvxRead::
initialize()
{
  _list.clear();
  _dim = 0;
  _mode = NO_MODE;
  _colormode = NO_COLORMODE;
  _point.clear();
  _line.clear();
  _face.clear();
  _point_color.clear();
  _line_color.clear();
  _face_color.clear();
  _point_normal.clear();
  _line_normal.clear();
  _face_normal.clear();
}

void
JvxRead::
finalize()
{
  _dim = 0;
  _mode = NO_MODE;
  _colormode = NO_COLORMODE;
  _point.clear();
  _line.clear();
  _face.clear();
  _point_color.clear();
  _line_color.clear();
  _face_color.clear();
  _point_normal.clear();
  _line_normal.clear();
  _face_normal.clear();
}

void
JvxRead::
start_tag_cb(
  char const *tag,
  AttributeList const &attributes )
{
  if (_error) { return; }
  // std::cerr << "tag=[" << tag << "]\n";

  if ( equal( tag, "geometries" ) )
  {
  }
  if ( equal( tag, "geometry" ) )
  {
  }
  else if ( equal( tag, "pointSet" ) )
  {
    _mode = POINT;

    _dim = 0U;

    char const *dim = find( attributes, "dim" );
    if (dim == (char *)0)
    {
      error( "missing dim attribute in <pointSet>" );
      return;
    }

    try {
      base::String(dim).to_number(_dim );
    }
    catch( base::Exception const & )
    {
      error( "invalid dim attribute value in <pointSet>" );
      return;
    }
    if ( _dim < _dim_minimum )
    {
      error( "dimension too small" );
      return;
    }
  }
  else if ( equal( tag, "faceSet" ) )
  {
    _mode = FACE;
  }
  else if ( equal( tag, "lineSet" ) )
  {
    _mode = LINE;
  }
  else if ( equal( tag, "colors" ) )
  {
    char const *type = find(attributes, "type");
    if (type == (char *)0)
    {
      _colormode = RGB;
    }
    else
    {
      if ( equal( type, "grey" ) ) { _colormode = GREY; }
      else if ( equal( type, "rgb" ) ) { _colormode = RGB; }
      else if ( equal( type, "rgba" ) ) { _colormode = RGBA; }
      else
      {
        error( "unknown color mode" );
        return;
      }
    }
  }
}

void
JvxRead::
end_tag_cb( char const *tag )
{
  if (_error) { return; }
  // std::cerr << "tag=[" << tag << "] text=[" << text() << "]\n";

  if ( equal( tag, "geometries" ) )
  {
  }
  else if ( equal( tag, "geometry" ) )
  {
    // check for right number of point colors
    if (_point_color.size() != 0 &&
        _point_color.size() != _point.size() )
    {
      error( "number of point colors unequal to number of points" );
      return;
    }
    // check for right number of line colors
    if (_line_color.size() != 0 &&
        _line_color.size() != _line.size() )
    {
      error( "number of line colors unequal to number of lines" );
      return;
    }
    // check for right number of face colors
    if (_face_color.size() != 0 &&
        _face_color.size() != _face.size() )
    {
      error( "number of face colors unequal to number of faces" );
      return;
    }
    // check for right number of point normals
    if (_point_normal.size() != 0 &&
        _point_normal.size() != _point.size() )
    {
      error( "number of point normals unequal to number of points" );
      return;
    }
    // check for right number of line normals
    if (_line_normal.size() != 0 &&
        _line_normal.size() != _line.size() )
    {
      error( "number of line normals unequal to number of lines" );
      return;
    }
    // check for right number of face normals
    if (_face_normal.size() != 0 &&
        _face_normal.size() != _face.size() )
    {
      error( "number of face normals unequal to number of faces" );
      return;
    }

    // no points
    if ( _point.empty() )
    {
      if ( _no_points == ERR_THROW )
      {
        error( "surface contains no points" );
        return;
      }
      else if ( _no_points == ERR_WARN )
      { WARN( "surface contains no points" ); }
    }

    // no faces
    if ( _face.empty() )
    {
      if ( _no_faces == ERR_THROW )
      {
        error( "surface contains no faces" );
        return;
      }
      else if ( _no_faces == ERR_WARN )
      { WARN( "surface contains no faces" ); }
    }

    // new Surface
    surface0::Surface *s = new surface0::Surface;

    // import geometry data
    s->import(
      _point, _face, geom::SpaceForm(_dim, geom::SpaceForm::SPACEFORM_R) );

    _point.clear();
    _face.clear();

    if ( ! _face_color.empty() )
    {
      s->import_face_color( _face_color );
      _face_color.clear();
    }
#if 0
    if ( ! _face_normal.empty() )
    {
      s->import_face_normal( _face_normal );
      _face_normal.clear();
    }
#endif
    // import line
    s->import_lines( _line );
    _line.clear();

    end_geometry(*s);

    // put the Surface into list
    _list.push_back( s );
  }
  else if ( equal( tag, "pointSet" ) )
  {
    _mode = NO_MODE;
  }
  else if ( equal( tag, "points" ) )
  {
  }
  else if ( equal( tag, "p" ) )
  {
    // read vertex
    base::vector<Real> v;
    read_list(v, _dim, text());
    _point.push_back(v);
  }
  else if ( equal( tag, "faceSet" ) )
  {
    _mode = NO_MODE;
  }
  else if ( equal( tag, "faces" ) )
  {
  }
  else if ( equal( tag, "f" ) )
  {
    // read face

    base::vector<base::String> w;
    text().split( w );

    if ( w.size() < _polygon_minimum )
    {
      error( "face has too few vertices" );
      return;
    }

    base::vector<uint> f;
    uint i;
    for ( i = 0; i < w.size(); i++ )
    {
      uint x;
      try {
        w[i].to_number( x );
      }
      catch ( base::Exception const & )
      {
        error( "unknown text in <f>" );
        return;
      }
      if (x >= _point.size())
      {
        error( "face index is out of range" );
        return;
      }
      f.push_back(x);
    }
    _face.push_back(f);
  }
  else if ( equal( tag, "lineSet" ) )
  {
    _mode = NO_MODE;
  }
  else if ( equal( tag, "lines" ) )
  {
  }
  else if ( equal( tag, "l" ) )
  {
    // read line

    base::vector<base::String> w;
    text().split( w );
    std::list<uint> l;
    uint i;
    for ( i = 0; i < w.size(); i++ )
    {
      uint x;
      try {
        w[i].to_number( x );
      }
      catch (base::Exception const &) {
        error( "unknown text in <l>" );
        return;
      }
      l.push_back(x);
    }
    _line.push_back(l);
  }
  else if ( equal( tag, "colors" ) )
  {
  }
  else if ( equal( tag, "c" ) )
  {
    // read colors
    base::Color4 c;
    read_color(c, text(), _colormode, true);
    if (_mode == POINT)
    {
      _point_color.push_back(c);
    }
    else if (_mode == LINE)
    {
      _line_color.push_back(c);
    }
    else if (_mode == FACE)
    {
      _face_color.push_back(c);
    }
  }
  else if ( equal( tag, "n" ) )
  {
    // read normals
    geom::Normal3 n;

    base::vector<Real> v;
    read_list( v, 3U, text() );
    n[0] = v[0];
    n[1] = v[1];
    n[2] = v[2];

    if (_mode == POINT)
    {
      _point_normal.push_back(n);
    }
    else if (_mode == LINE)
    {
      _line_normal.push_back(n);
    }
    else if (_mode == FACE)
    {
      _face_normal.push_back(n);
    }
  }
}

void
JvxRead::
read_color(
  base::Color4 &c,
  base::String const &s,
  ColorMode colormode,
  bool Uint )
{
  base::vector<base::String> w;
  s.split( w );

  if ( colormode == GREY )
  {
    if ( w.size() != 1)
    {
      error( "wrong number of entries in <c>" );
      return;
    }
  }
  else if ( colormode == RGB )
  {
    if ( w.size() != 3)
    {
      error( "wrong number of entries in <c>" );
      return;
    }
  }
  else if ( colormode == RGBA )
  {
    if ( w.size() != 4)
    {
      error( "wrong number of entries in <c>" );
      return;
    }
  }
  else
  {
    DIE();
  }
  base::vector<float> v;
  uint i;
  for ( i = 0; i < w.size(); i++ )
  {
    if ( Uint )
    {
      uint x;
      try {
        w[i].to_number( x );
      }
      catch (base::Exception const &) {
        error( "unknown text in <c>" );
        return;
      }
      if (x > 255)
      {
        error( "color entry is out of range" );
        return;
      }
      v.push_back( float(x)/255.0f );
    }
    else
    {
      float x;
      try {
        w[i].to_number( x );
      }
      catch (base::Exception const &) {
        error( "unknown text in <c>" );
        return;
      }
      if (x < 0.0f || x > 1.0f)
      {
        error( "color entry is out of range" );
        return;
      }
      v.push_back( x );
    }
  }

  if ( colormode == GREY )
  {
    c[0] = v[0];
    c[1] = v[0];
    c[2] = v[0];
    c[3] = DEFAULT_ALPHA;
  }
  else if ( colormode == RGB )
  {
    c[0] = v[0];
    c[1] = v[1];
    c[2] = v[2];
    c[3] = DEFAULT_ALPHA;
  }
  else if ( colormode == RGBA )
  {
    c[0] = v[0];
    c[1] = v[1];
    c[2] = v[2];
    c[3] = v[3];
  }
  else
  {
    DIE();
  }
}

void
JvxRead::
read_color(
  base::Color3 &c,
  base::String const &s,
  ColorMode colormode,
  bool Uint )
{
  base::Color4 c4;
  read_color( c4, s, colormode, Uint );
  c[0] = c4[0];
  c[1] = c4[1];
  c[2] = c4[2];
}

void
JvxRead::
error( char const *message )
{
  if (_error) { return; }

  std::list<surface0::GeomObject *>::iterator i;
  for ( i = _list.begin(); i != _list.end(); i++ )
  {
    delete *i;
  }
  _list.clear();

  _error = true;
  _error_filename = _stream->filename();
  _error_line = line_number();
  _error_message = message;
}

} // namespace io
} // namespace geom
