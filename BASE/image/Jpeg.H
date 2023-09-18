/* GANG Software
 * BASE/image/Jpeg.H
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

#ifndef image_Jpeg_INCLUDED
#define image_Jpeg_INCLUDED

#include "io/IstreamCfile.H"
#include "io/OstreamCfile.H"
#include "Reader.H"
#include "Writer.H"

namespace image {

class Jpeg
  :
    public Reader,
    public Writer
{
public:

  Jpeg();
  ~Jpeg() {}

  // read from filename
  virtual void read( base::String const &filename, Image &image )
    {
      io::IstreamCfile stream(filename);
      read( stream, image );
    }

  // read from stream
  void read( io::Istream &stream, Image &image )
    {
      DIE_IF( stream.type() != io::CFILE );
      read( static_cast<io::IstreamCfile *>(&stream)->cfile(),
             image );
    }

  // read from FILE
  void read( FILE *file, Image &image );

  // write to filename
  virtual void write( base::String const &filename,
                      Image const &image ) const
    {
      io::OstreamCfile stream(filename);
      write( stream, image );
    }

  // write to stream
  void write( io::Ostream &stream, Image const &image ) const
    {
      DIE_IF( stream.type() != io::CFILE );
      write( static_cast<io::OstreamCfile *>(&stream)->cfile(),
             image );
    }

  // write to FILE
  void write( FILE *file, Image const &image ) const;

  /*
    Set the image quality.
    quality should be in [1,100]
  */
  void quality( uint q )
    {
      DIE_IF( q < 1 || q > 100 );
      _quality = q;
    }

private:
  uint _quality;

  // disabled copy constructor
  Jpeg( Jpeg const & );
  // dispabled assignment operator
  Jpeg &operator=( Jpeg const & );
};

} // namespace image

#endif // image_Jpeg_INCLUDED
