/* GANG Software
 * BASE/io/IstreamStream.H
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

#ifndef io_IstreamStream_INCLUDED
#define io_IstreamStream_INCLUDED

#include <fstream>
#include "Istream.H"

namespace io {

class IstreamStream
  :
    public Istream
{

public:
  // constructor
  IstreamStream( base::String const &filename );
  IstreamStream( std::istream &stream );

  // destructor
  virtual ~IstreamStream();

  virtual uint read( char *buffer, uint buffer_len );
  virtual uint read( char unsigned *buffer, uint buffer_len );

#if 0
  virtual bool ok();
  virtual void get( char & );
  virtual void get( char unsigned & );
  virtual void getline( base::String & );
#endif

  std::istream &stream()
    { return *_stream; }

  virtual StreamType type() const
    { return STREAM; }

protected:

private:

  base::String _filename;
  std::istream *_stream;
  bool _stream_was_allocated;

  // disabled copy constructor
  IstreamStream( IstreamStream const & );
  // disabled assignment operator
  IstreamStream &operator=( IstreamStream const & );

};

} // namespace io

#endif // io_IstreamStream_INCLUDED
