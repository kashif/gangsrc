/* GANG Software
 * GEOM/geom/io/IsxWrite.H
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

#ifndef geom_io_IsxWrite_INCLUDED
#define geom_io_IsxWrite_INCLUDED

#include "JvxWrite.H"

namespace geom {
namespace io {

class IsxWrite
  :
    public JvxWrite
{

public:
  // constructor
  IsxWrite();

  // destructor
  virtual ~IsxWrite() {}

  virtual void
  write(
    ::io::Ostream &o,
    ::geom::surface::SurfaceBase const &g,
    milieu::kernel::MilieuBase const &milieu ) const;

protected:

private:

  virtual void write_part(
    surface0::GeomObject const *g, uint part ) const;

  virtual void write_part(
    surface0::Surface const *g, uint part ) const;

  // disabled copy constructor
  IsxWrite( IsxWrite const & );

  // disabled assignment operator
  IsxWrite &operator=( IsxWrite const & );

};

} // namespace io
} // namespace geom

#endif // geom_io_IsxWrite_INCLUDED
