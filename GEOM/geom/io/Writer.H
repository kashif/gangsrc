/* GANG Software
 * GEOM/geom/io/Writer.H
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

#ifndef geom_io_Writer_INCLUDED
#define geom_io_Writer_INCLUDED

#include "io/Ostream.H"
#include "milieu/kernel/MilieuBase.H"
#include "geom/surface/SurfaceBase.H"

namespace geom {
namespace io {

class Writer
{

public:
  // constructor
  Writer();

  // destructor
  virtual ~Writer();
#if 0
  virtual void write(
    ::io::Ostream &o,
    surface0::GeomObject const *g ) const = 0;
#endif

  virtual void write(
    ::io::Ostream &o,
    ::geom::surface::SurfaceBase const &g,
    milieu::kernel::MilieuBase const &M ) const = 0;

  void write_normals( uint state )
    { _write_normal = state; }
  void write_colors( uint state )
    { _write_color = state; }

protected:

  uint _write_normal;
  uint _write_color;
  mutable bool _write_normal0;
  mutable bool _write_color0;

private:

  // disabled copy constructor
  Writer( Writer const & );

  // disabled assignment operator
  Writer &operator=( Writer const & );

};

} // namespace io
} // namespace geom

#endif // geom_io_Writer_INCLUDED
