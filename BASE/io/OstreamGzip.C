/* GANG Software
 * BASE/io/OstreamGzip.C
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

#include "OstreamGzip.H"

namespace io {

OstreamGzip::
OstreamGzip( base::String const &filename )
    :
    Ostream(filename),
    _stream(),
    _gzfile()
{
  _gzfile = gzopen( filename.c_str(), "wb9" );

  if (_gzfile == (gzFile)0)
  {
    throw WriteException( WriteException::OPEN_ERROR, filename );
  }
}

OstreamGzip::
OstreamGzip( gzFile gzfile )
    :
    Ostream(),
    _stream(),
    _gzfile(gzfile)
{
}

OstreamGzip::
~OstreamGzip()
{
  flush();
  gzclose( _gzfile );
}

void
OstreamGzip::
flush()
{
  // write the strstream to a gzFile

  uint const BUFFER_SIZE = 8192;
  char *buffer = new char[BUFFER_SIZE];

  for (;;)
  {
    _stream.read( buffer, BUFFER_SIZE);
    uint n = _stream.gcount();
    if (n == 0) { break; }
    gzwrite( _gzfile, buffer, n );
  }
  delete [] buffer;
}

} // namespace io
