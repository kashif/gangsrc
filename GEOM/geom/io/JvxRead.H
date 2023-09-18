/* GANG Software
 * GEOM/geom/io/JvxRead.H
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

#ifndef geom_io_JvxRead_INCLUDED
#define geom_io_JvxRead_INCLUDED

#include <list>
#include "parser/Xml.H"
#include "geom/surface0/Surface.H"
#include "math/ReadUtil.H"
#include "Reader.H"

namespace geom {
namespace io {

class JvxRead
  :
  public math::ReadUtil,
  public Reader,
  public parser::Xml
{

public:

  typedef geom::Real Real;

  JvxRead();
  virtual ~JvxRead();

  virtual void read(
    ::io::Istream &,
    ::geom::surface::SurfaceBase &G,
    ::milieu::kernel::MilieuBase &M )
    throw (::io::ReadException);

protected:

  virtual void initialize();
  virtual void finalize();
  virtual void start_tag_cb(
    char const *tag,
    AttributeList const &attributes );
  virtual void end_tag_cb( char const *tag );

  enum ColorMode { NO_COLORMODE, GREY, RGB, RGBA };
  void read_color( base::Color4 &c, base::String const &s,
                   ColorMode colormode, bool Uint );
  void read_color( base::Color3 &c, base::String const &s,
                   ColorMode colormode, bool Uint );

  virtual void error( char const *message );

  virtual void end_geometry( geom::surface0::Surface & ) {}

  ::milieu::kernel::MilieuBase *_milieu;
  ::geom::surface::SurfaceBase *_geomlist;
  std::list<surface0::GeomObject *> _list;

  bool _error;
private:
  virtual void _finalize() {}

  ::io::Istream *_stream;

  uint _dim;
  enum Mode { NO_MODE, POINT, LINE, FACE } _mode;
  ColorMode _colormode;
  base::vector<base::vector<Real> > _point;
  std::list<std::list<uint> > _line;
  base::vector<base::vector<uint> > _face;
  base::vector<base::Color4> _point_color;
  base::vector<base::Color4> _line_color;
  base::vector<base::Color4> _face_color;
  base::vector<geom::Normal3> _point_normal;
  base::vector<geom::Normal3> _line_normal;
  base::vector<geom::Normal3> _face_normal;

  base::String _error_filename;
  uint _error_line;
  char const *_error_message;

  // disabled copy constructor
  JvxRead( JvxRead const & );
  // disabled assignement operator
  JvxRead &operator=(JvxRead const &);
};

} // namespace io
} // namespace geom

#endif // geom_io_JvxRead_INCLUDED
