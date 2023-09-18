/* GANG Software
 * GEOM/geom/io/Reader.H
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

#ifndef geom_io_Reader_INCLUDED
#define geom_io_Reader_INCLUDED

#include "io/Istream.H"
#include "milieu/kernel/MilieuBase.H"
#include "geom/surface/SurfaceBase.H"

namespace geom {
namespace io {

class Reader
{

public:
  // constructor
  Reader();

  // destructor
  virtual ~Reader();

  virtual void read(
    ::io::Istream &,
    ::geom::surface::SurfaceBase &G,
    ::milieu::kernel::MilieuBase &M )
    throw (::io::ReadException) = 0;

protected:

  uint _dim_minimum;
  uint _polygon_minimum;

  enum ErrorStatus { ERR_IGNORE, ERR_WARN, ERR_THROW };
  ErrorStatus _no_points;
  ErrorStatus _no_faces;
  ErrorStatus _no_surface;

  static float const DEFAULT_ALPHA;

private:

  // disabled copy constructor
  Reader( Reader const & );

  // disabled assignment operator
  Reader &operator=( Reader const & );

};

} // namespace io
} // namespace geom

#endif // geom_io_Reader_INCLUDED
