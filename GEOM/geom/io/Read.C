/* GANG Software
 * GEOM/geom/io/Read.C
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

#include "milieu/kernel/Milieu.H"
#include "geom/surface/Surface.H"
#include "IsxRead.H"
#include "JvxRead.H"
#include "OoglRead.H"
#include "VrmlRead.H"
#include "MathRead.H"
#include "Read.H"

namespace geom {
namespace io {

// read a GeomObject
surface0::GeomObject *
read(
  ::io::Istream &in,
  FileMode filemode )
    throw( ::io::ReadException )
{
  ::milieu::kernel::Milieu M;
  return read( in, M, filemode );
}

surface0::GeomObject *
read(
  ::io::Istream &in,
  ::milieu::kernel::MilieuBase &M,
  FileMode filemode )
    throw( ::io::ReadException )
{
  ::geom::surface::Surface G;
  read( in, G, M, filemode );

  if (G.empty())
  {
    throw ::io::ReadException(::io::ReadException::ERROR, in.filename());
  }
  // NOTE: takes first element, ignoring the remainder
  surface0::GeomObject *g = G.strip();

  // set the GeomObject's name to the filename
  base::String s = in.filename();
  base::String::size_type n = s.rfind( '/' );
  if (n != base::String::npos)
  {
    s.erase( 0, n+1 );
  }
  g->name( s );

  return g;
}

void
read(
  ::io::Istream &in,
  ::geom::surface::SurfaceBase &G,
  FileMode filemode )
    throw( ::io::ReadException )
{
  ::milieu::kernel::Milieu M;
  read( in, G, M, filemode );
}

void
read(
  ::io::Istream &in,
  ::geom::surface::SurfaceBase &G,
  ::milieu::kernel::MilieuBase &M,
  FileMode filemode )
    throw( ::io::ReadException )
{
  Reader *R = reader(in, filemode);
  try {
    R->read( in, G, M );
  }
  catch ( ::io::ReadException const &e ) {
    delete R;
    throw e;
  }
  delete R;
}

Reader *
reader( ::io::Istream const &in, FileMode filemode )
{
  // figure out filemode
  if ( filemode == FILEMODE_UNSPECIFIED )
  {
    filemode = get_filemode( in.filename().c_str() );
    if ( filemode == FILEMODE_UNSPECIFIED )
    {
      // default mode
      filemode = FILEMODE_DEFAULT;
    }
  }
  if ( filemode == FILEMODE_ISX )
  {
    return new IsxRead;
  }
  else if ( filemode == FILEMODE_JVX )
  {
    return new JvxRead;
  }
  else if (filemode == FILEMODE_VRML )
  {
    return new VrmlRead;
  }
  else if ( filemode == FILEMODE_OOGL )
  {
    return new OoglRead;
  }
  else if ( filemode == FILEMODE_MATHEMATICA )
  {
    return new MathRead;
  }
  else
  {
    throw ::io::ReadException(
      ::io::ReadException::UNKNOWN_TYPE,
      in.filename() );
  }
}

} // namespace io
} // namespace geom
