/* GANG Software
 * BASE/io/IstreamCfile.H
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

#ifndef io_IstreamCfile_INCLUDED
#define io_IstreamCfile_INCLUDED

#include <stdio.h>
#include "Istream.H"

namespace io {

class IstreamCfile
  :
    public Istream
{

public:
  // constructor
  IstreamCfile( base::String const &filename, char const *mode = "rb" );
  IstreamCfile( FILE *cfile );

  // destructor
  virtual ~IstreamCfile();

  virtual uint read( char *buffer, uint buffer_len );
  virtual uint read( char unsigned *buffer, uint buffer_len );

  FILE *cfile()
    { return _cfile; }

  virtual StreamType type() const
    { return CFILE; }

protected:

private:

  base::String _filename;
  FILE *_cfile;

  // disabled copy constructor
  IstreamCfile( IstreamCfile const & );
  // disabled assignment operator
  IstreamCfile &operator=( IstreamCfile const & );

};

} // namespace io

#endif // io_IstreamCfile_INCLUDED
