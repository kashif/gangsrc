/* GANG Software
 * GEOM/geom/io/MathRead.H
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

#ifndef geom_io_MathRead_INCLUDED
#define geom_io_MathRead_INCLUDED

#include <list>
#include "io/Ostream.H"
#include "MathLexer.H"
#include "geom/surface0/Surface.H"
#include "Reader.H"

namespace geom {
namespace io {

class MathRead
  :
    public Reader,
    public MathLexer
{

public:
  typedef geom::Real Real;

  MathRead();
  virtual ~MathRead();

  void read(
    ::io::Istream &o,
    ::geom::surface::SurfaceBase &G,
    ::milieu::kernel::MilieuBase &M )
    throw (::io::ReadException);

protected:

private:

  void error( char const *message ) {}

  void read( surface0::Surface *g );

  enum Type { NO_TYPE, GRAPHICS, GRAPHICS3D, SURFACEGRAPHICS };

  Type read_keyword();
  Real eval_real(char const *);

  virtual void cleanup();
  void _throw( char const *message );

  std::list<surface0::GeomObject *> _list;

  // disabled copy constructor
  MathRead( MathRead const & );
  // disabled assignement operator
  MathRead &operator=(MathRead const &);
};

} // namespace io
} // namespace geom

#endif // geom_io_MathRead_INCLUDED
