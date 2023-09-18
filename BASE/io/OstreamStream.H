/* GANG Software
 * BASE/io/OstreamStream.H
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

#ifndef io_OstreamStream_INCLUDED
#define io_OstreamStream_INCLUDED

#include "base/PrintNumber.H"
#include "Ostream.H"

namespace io {

class OstreamStream
  :
    public Ostream
{

public:
  // constructor
  OstreamStream( base::String const &filename );
  OstreamStream( std::ostream & );

  // destructor
  virtual ~OstreamStream();

  virtual std::ostream &stream()
    { return *_stream; }

  virtual StreamType type() const
    { return STREAM; }

protected:

private:

  std::ostream *_stream;
  bool _stream_was_allocated;

  // disabled copy constructor
  OstreamStream( OstreamStream const & );
  // disabled assignment operator
  OstreamStream &operator=( OstreamStream const & );

};

} // namespace io

#endif // io_OstreamStream_INCLUDED
