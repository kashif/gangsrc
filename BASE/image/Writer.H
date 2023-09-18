/* GANG Software
 * BASE/image/Writer.H
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

#ifndef image_Writer_INCLUDED
#define image_Writer_INCLUDED

#include "io/Ostream.H"
#include "Common.H"

namespace image {

class Writer
{

public:
  // constructor
  Writer() {}

  // destructor
  virtual ~Writer() {}

  /*
    write a buffer to a stream
  */
  virtual void write( base::String const &filename,
                      Image const &image ) const= 0;

protected:

private:

  // disabled copy constructor
  Writer( Writer const & );
  // disabled assignment operator
  Writer &operator=( Writer const & );

};

} // namespace image

#endif // image_Writer_INCLUDED
