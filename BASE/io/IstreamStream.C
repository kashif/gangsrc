/* GANG Software
 * BASE/io/IstreamStream.C
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

#include <fstream>
#include "IstreamStream.H"

namespace io {

IstreamStream::
IstreamStream( base::String const &filename_ )
    :
    Istream(filename_),
    _stream(),
    _stream_was_allocated(false)
{
  _stream = new std::ifstream( filename().c_str() );

  if (! *_stream)
  {
    delete _stream;
    throw ReadException( ReadException::OPEN_ERROR, filename() );
  }

  _stream_was_allocated = true;
}

IstreamStream::
IstreamStream( std::istream &stream )
    :
    Istream(),
    _stream( &stream ),
    _stream_was_allocated(false)
{
}

IstreamStream::
~IstreamStream()
{
  if ( _stream_was_allocated && _stream != (std::istream *)0 )
  {
    delete _stream;
  }
}

uint
IstreamStream::
read( char unsigned *buffer, uint buffer_len )
{
  _stream->read( (char *)buffer, buffer_len );
  return _stream->gcount();
}

uint
IstreamStream::
read( char *buffer, uint buffer_len )
{
  _stream->read( buffer, buffer_len );
  return _stream->gcount();
}

#if 0
bool
IstreamStream::
ok()
{
  return !(! *_stream);
}

void
IstreamStream::
get( char &c )
{
  _stream->get(c);
}

void
IstreamStream::
get( char unsigned &c )
{
  _stream->get(c);
}

void
IstreamStream::
getline( base::String &s )
{
  s.erase();

  char c;
  for (;;)
  {
    get(c);
    if ( ! ok() ) { break; }
    s += c;
    if (c == '\n') { break; }
  }
}
#endif

} // namespace io
