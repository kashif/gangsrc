/* GANG Software
 * BASE/image/Sgi.H
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

#ifndef image_Sgi_INCLUDED
#define image_Sgi_INCLUDED

#include "io/Common.H"
#include "io/IstreamStream.H"
#include "io/OstreamStream.H"
#include "io/OstreamGzip.H"
#include "Reader.H"
#include "Writer.H"

namespace image {

/*
  For the SGI image file format specification, see
  http://reality.sgi.com/grafica/sgiimage.html .
*/
class Sgi
  :
    public Reader,
    public Writer
{

public:
  // constructor
  Sgi();

  // destructor
  virtual ~Sgi();

  // read from filename
  virtual void read(
    base::String const &filename, Image &image )
    {
      io::IstreamStream stream(filename);
      read( stream, image );
    }

  // read from stream
  void read( io::Istream &stream, Image &image );

  // write to a filename
  virtual void
  write( base::String const &filename, Image const &image ) const
    {     
      if ( ::io::is_compressed(filename) )
      {
        io::OstreamGzip stream(filename);
        write( stream, image );
      }
      else
      {
        io::OstreamStream stream(filename);
        write( stream, image );
      }
    }
  // write to a stream
  void
  write( io::Ostream &stream, Image const &image ) const;


protected:

private:

  // disabled copy constructor
  Sgi( Sgi const & );
  // disabled assignment operator
  Sgi &operator=( Sgi const & );

};

} // namespace image

#endif // image_Sgi_INCLUDED
