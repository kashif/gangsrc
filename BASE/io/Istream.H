/* GANG Software
 * BASE/io/Istream.H
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

#ifndef io_Istream_INCLUDED
#define io_Istream_INCLUDED

#include "base/String.H"
#include "Type.H"
#include "ReadException.H"

namespace io {

/*
  Read from a variety of streams.
  NOTE: should be implemented as separate classes.
*/

class Istream
{

public:

  virtual ~Istream() {}

  virtual uint read( char *buffer, uint buffer_len ) = 0;
  virtual uint read( char unsigned *buffer, uint buffer_len ) = 0;

  virtual base::String const &filename() const
    { return _filename; }
  virtual StreamType type() const = 0;

protected:

  Istream( base::String const &filename) : _filename()
    {
      if ( filename.empty() )
      { throw ReadException( ReadException::OPEN_ERROR, filename ); }
      _filename = filename;
    }

  Istream() : _filename() {}

private:

  base::String _filename;

  // disabled copy constructor
  Istream( Istream const & );
  // disabled assignment operator
  Istream &operator=( Istream const & );

};

} // namespace io

#endif // io_Istream_INCLUDED
