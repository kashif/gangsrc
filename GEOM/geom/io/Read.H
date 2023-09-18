/* GANG Software
 * GEOM/geom/io/Read.H
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

#ifndef geom_io_Read_INCLUDED
#define geom_io_Read_INCLUDED

#include <list>
#include "base/System.H"
#include "io/Istream.H"
#include "io/Ostream.H"
#include "Common.H"
#include "Reader.H"
#include "Writer.H"

namespace geom {

namespace surface0 { class GeomObject; }

namespace io {

// read a GeomObject
surface0::GeomObject *
read(
  ::io::Istream &stream,
  FileMode filemode = FILEMODE_DEFAULT )
    throw( ::io::ReadException );

// read a GeomObject and Milieu
surface0::GeomObject *
read(
  ::io::Istream &stream,
  ::milieu::kernel::MilieuBase &M,
  FileMode filemode = geom::FILEMODE_DEFAULT )
    throw( ::io::ReadException );

// read a SurfaceBase
void
read(
  ::io::Istream &stream,
  ::geom::surface::SurfaceBase &G,
  FileMode filemode = FILEMODE_DEFAULT )
    throw( ::io::ReadException );

// read a list<GeomObject *> and Milieu
void
read(
  ::io::Istream &stream,
  ::geom::surface::SurfaceBase &G,
  ::milieu::kernel::MilieuBase &M,
  FileMode filemode = FILEMODE_DEFAULT )
    throw( ::io::ReadException );


Reader *
reader(
  ::io::Istream const &in,
  FileMode filemode = FILEMODE_UNSPECIFIED );


} // namespace io
} // namespace geom

#endif // geom_io_Read_INCLUDED
