/* GANG Software
 * BASE/io/IstreamCfile.C
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

#include "IstreamCfile.H"

namespace io {

IstreamCfile::
IstreamCfile( base::String const &filename_, char const *mode )
    :
    Istream(filename_),
    _cfile()
{
  _cfile = fopen( filename().c_str(), mode );
  if ( _cfile == (FILE *)0 )
  { throw ReadException( ReadException::OPEN_ERROR, filename() ); }
}

IstreamCfile::
IstreamCfile( FILE *cfile )
    :
    Istream(),
    _cfile(cfile)
{
}

IstreamCfile::
~IstreamCfile()
{
  fclose(_cfile);
}

uint
IstreamCfile::
read( char unsigned *buffer, uint buffer_len )
{
  int r = fread( buffer, 1, buffer_len, _cfile );
  if ( r == 0 && ferror(_cfile) )
  {
    throw ReadException(ReadException::READ_ERROR, filename() );
  }
  return (uint)r;
}

uint
IstreamCfile::
read( char *buffer, uint buffer_len )
{
  return read( (char unsigned *)buffer, buffer_len );
}


} // namespace io
