/* GANG Software
 * BASE/image/Reader.H
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

#ifndef image_Reader_INCLUDED
#define image_Reader_INCLUDED

#include "base/System.H"
#include "io/Istream.H"
#include "Common.H"

namespace image {

class Reader
{

public:
  // constructor
  Reader() {}

  // destructor
  virtual ~Reader() {}

  /*
    read file into buffer
  */
  virtual void read( base::String const &filename, Image &image ) = 0;

protected:

private:

  // disabled copy constructor
  Reader( Reader const & );
  // disabled assignment operator
  Reader &operator=( Reader const & );

};

} // namespace image

#endif // image_Reader_INCLUDED
