/* GANG Software
 * BASE/io/OstreamStream.C
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
#include "OstreamStream.H"

namespace io {

OstreamStream::
OstreamStream( base::String const &filename )
    :
    Ostream(filename),
    _stream(),
    _stream_was_allocated(false)
{
  _stream = new std::ofstream( filename.c_str() );

  if ( ! *_stream )
  {
    delete _stream;
    throw WriteException( WriteException::OPEN_ERROR, filename );
  }

  _stream_was_allocated = true;
}

OstreamStream::
OstreamStream( std::ostream &stream )
    :
    Ostream(),
    _stream(&stream),
    _stream_was_allocated(false)
{
}

OstreamStream::
~OstreamStream()
{
  if ( _stream_was_allocated )
  {
    delete _stream;
  }
}

} // namespace io
