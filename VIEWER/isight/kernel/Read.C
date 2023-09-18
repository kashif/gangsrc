/* GANG Software
 * VIEWER/isight/kernel/Read.C
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

#include "io/Common.H"
#include "io/IstreamStream.H"
#include "io/IstreamGzip.H"
#include "Read.H"

namespace isight {
namespace kernel {

Read::
Read()
    :
    ContextSet()
{
}

Read::
~Read()
{
}

void
Read::
read(
  base::String const &filename,
  geom::FileMode filemode )
  throw(::io::ReadException)
{
  try
  {
    ::io::Istream *stream;
    if ( ::io::is_compressed( filename ) )
    { stream = new ::io::IstreamGzip(filename); }
    else
    { stream = new ::io::IstreamStream(filename); }

    Read::read( *stream, geom::FILEMODE_UNSPECIFIED );
    delete stream;
  }
  catch ( base::Exception const &e )
  {
    message( e.message() );
  }
}

void
Read::
read(
  base::vector<base::String> const &filename,
  geom::FileMode filemode )
  throw(::io::ReadException)
{
  enable_draw(false);
  uint i;
  for ( i = 0; i != filename.size(); i++ )
  {
    Read::read(filename[i], filemode);
  }
  enable_draw(true);
  refresh_all();
}

void
Read::
read(
  io::Istream &stream,
  geom::FileMode filemode )
  throw(::io::ReadException)
{
  // read a surface from a stream
  geom::SurfaceGL *g = new geom::SurfaceGL;

  enable_draw(false);

  try
  {
    g->read( stream, *context()->milieu(), filemode );
  }
  catch ( io::ReadException const &e )
  {
    enable_draw(true);
    message( e.message() );
    delete g;
    return;
  }

  g->name( stream.filename() );
  insert_geomobject( g );
  enable_draw(true);
  refresh_all();
}

} // namespace kernel
} // namespace isight
