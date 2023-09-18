/* GANG Software
 * BASE/image/Tiff.H
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

#ifndef image_Tiff_INCLUDED
#define image_Tiff_INCLUDED

#include "io/IstreamCfile.H"
#include "io/OstreamCfile.H"
#include "Reader.H"
#include "Writer.H"

namespace image {

class Tiff
  :
    public Reader,
    public Writer
{
public:

  Tiff();
  ~Tiff() {}

  // read from filename
  virtual void read( base::String const &filename, Image &image );

  // write to filename
  virtual void write( base::String const &filename,
                      Image const &image ) const;

private:

  // disabled copy constructor
  Tiff( Tiff const & );
  // dispabled assignment operator
  Tiff &operator=( Tiff const & );
};

} // namespace image

#endif // image_Tiff_INCLUDED
