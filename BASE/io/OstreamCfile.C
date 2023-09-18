/* GANG Software
 * BASE/io/OstreamCfile.C
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

#include "OstreamCfile.H"

namespace io {

OstreamCfile::
OstreamCfile( base::String const &filename, char const *mode )
    :
    Ostream(filename),
    _stream(),
    _cfile()
{
  _cfile = fopen( filename.c_str(), mode );

  if ( _cfile == (FILE *)0 )
  {
    throw WriteException( WriteException::OPEN_ERROR, filename );
  }
}

OstreamCfile::
OstreamCfile( FILE *file )
    :
    Ostream(),
    _stream(),
    _cfile(file)
{
}

OstreamCfile::
~OstreamCfile()
{
  flush();
  fclose( _cfile );
}

void
OstreamCfile::
flush()
{
  // write the strstream to the cfile

  uint const BUFFER_SIZE = 8192;
  char *buffer = new char[BUFFER_SIZE];

  for (;;)
  {
    _stream.read( buffer, BUFFER_SIZE);
    uint n = _stream.gcount();
    if (n == 0) { break; }
    fwrite( buffer, n, 1, _cfile );
  }
  delete [] buffer;
}

} // namespace io
