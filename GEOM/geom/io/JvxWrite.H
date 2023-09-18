/* GANG Software
 * GEOM/geom/io/JvxWrite.H
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

#ifndef geom_io_JvxWrite_INCLUDED
#define geom_io_JvxWrite_INCLUDED

#include <list>
#include "base/String.H"
#include "base/System.H"
#include "io/Ostream.H"
#include "math/WriteUtil.H"
#include "geom/surface0/Surface.H"
#include "Writer.H"

namespace geom {
namespace io {

class JvxWrite
  :
    public Writer,
    public math::WriteUtil
{

public:
  // constructor
  JvxWrite();

  // destructor
  virtual ~JvxWrite() {}

  virtual void write(
    ::io::Ostream &o,
    ::geom::surface::SurfaceBase const &g,
    milieu::kernel::MilieuBase const &milieu ) const;

  mutable ::io::Ostream *_stream;
  mutable ::geom::surface::SurfaceBase const *_geomlist;
  mutable milieu::kernel::MilieuBase const *_milieu;

protected:

  virtual void write_header( ) const;
  virtual void write_footer() const;

  virtual void write_part(
    surface0::GeomObject const *g ) const;

  virtual void write_part(
    surface0::Surface const *g ) const;

private:

  // disabled copy constructor
  JvxWrite( JvxWrite const & );

  // disabled assignment operator
  JvxWrite &operator=( JvxWrite const & );

};

} // namespace io
} // namespace geom

#endif // geom_io_JvxWrite_INCLUDED
