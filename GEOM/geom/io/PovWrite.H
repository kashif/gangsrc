/* GANG Software
 * GEOM/geom/io/PovWrite.H
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

#ifndef geom_io_PovWrite_INCLUDED
#define geom_io_PovWrite_INCLUDED

#include <list>
#include "base/String.H"
#include "base/System.H"
#include "io/Ostream.H"
#include "geom/surface0/Surface.H"
#include "Writer.H"

namespace geom {
namespace io {

class PovWrite
  :
    public Writer
{

public:
  // constructor
  PovWrite();

  // destructor
  virtual ~PovWrite();

  virtual void write(
    ::io::Ostream &o,
    ::geom::surface::SurfaceBase const &g,
    milieu::kernel::MilieuBase const &milieu ) const;

protected:

private:
  void write_header() const;
  void write_footer(uint count) const;
  void write_part( surface0::GeomObject const *g, uint i ) const;
  void write_part( surface0::Surface const *g, uint i ) const;

  void write_triangle( surface0::Surface const *g,
                       uint a, uint b, uint c ) const;
  void write_smooth_triangle( surface0::Surface const *g,
                              uint a, uint b, uint c ) const;
  void write_vertex( surface0::Surface const *g,
                     uint a ) const;
  void write_normal( surface0::Surface const *g,
                     uint a ) const;

  mutable ::io::Ostream *_stream;
  mutable ::geom::surface::SurfaceBase const *_geomlist;
  mutable milieu::kernel::MilieuBase const *_milieu;

  // disabled copy constructor
  PovWrite( PovWrite const & );
  // disabled assignment operator
  PovWrite &operator=( PovWrite const & );

};

} // namespace io
} // namespace geom

#endif // geom_io_PovWrite_INCLUDED
