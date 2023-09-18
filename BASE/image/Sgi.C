/* GANG Software
 * BASE/image/Sgi.C
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

#include <algorithm>
#include "Sgi.H"

namespace image {

Sgi::
Sgi()
{
}

Sgi::
~Sgi()
{
}

void
Sgi::
read( io::Istream &o, Image &image )
{
  uint N;
  if ( image.mode == Image::RGB ) { N = 3U; }
  else if ( image.mode == Image::RGBA ) { N = 4U; }
  else { DIE(); }

  char unsigned header[24] =
  {
    0x01, 0xda,             // MAGIC (SGI image file magic number)
    0x00,                   // STORAGE (storage format)
    0x01,                   // BPC (number of bytes per channel)
    0x00, 0x03,             // DIMENSION (number of dimensions)
    0x00, 0x00,             // XSIZE (x size in pixels)
    0x00, 0x00,             // YSIZE (y size in pixels)
    0x00, 0x00,             // ZSIZE (number of channels)
    0x00, 0x00, 0x00, 0x00, // PIXMIN (minimum pixel value)
    0x00, 0x00, 0x00, 0xff, // PIXMAX (maximum pixel value)
    0x00, 0x00, 0x00, 0x00  // DUMMY (ignored)
  };

  char unsigned buffer[24];

  // check syntax of header
  uint n = o.read( buffer, 24U );
  if (n < 24 || buffer[0] != 0x01 || buffer[1] != 0xda)
  {
    throw io::ReadException(
      io::ReadException::WRONG_TYPE, "file not in SGI image format" );
  }
  uint i;
  for (i = 6; i < 12; i++) {header[i] = buffer[i];}
  for (i = 2; i < 24; i++)
  {
    if (buffer[i] != header[i])
    {
      throw io::ReadException(
        io::ReadException::WRONG_TYPE,
        "compressed SGI image format not supported" );
    }
  }
  image.xsize = 256*uint(buffer[6]) + uint(buffer[7]);
  image.ysize = 256*uint(buffer[8]) + uint(buffer[9]);
  uint M = buffer[11];
  image.buffer = new char unsigned[N * image.xsize * image.ysize];

  uint c;
  for ( c = 0; c < std::min(N, M); c++ )
  {
    uint j;
    for ( j = 0; j < image.ysize; j++ )
    {
      uint j1 = image.ysize - j - 1;
      uint i;
      for ( i = 0; i < image.xsize; i++ )
      {
        uint n = o.read( image.buffer + N*(j1*image.xsize + i) + c, 1 );
        if ( n == 0 )
        {
          throw io::ReadException(
            io::ReadException::PARSE_ERROR,
            "file ended before data was read" );
        }
      }
    }
  }
  // set alpha
  if ( M == 3 && N == 4 )
  {
    uint j;
    for ( j = 0; j < image.ysize; j++ )
    {
      uint j1 = image.ysize - j - 1;
      uint i;
      for ( i = 0; i < image.xsize; i++ )
      {
        image.buffer[N*(j1*image.xsize+i)+3] = 0xff;
      }
    }
  }
}

void
Sgi::
write( io::Ostream &o, Image const &image ) const
{
  if (image.xsize == 0 || image.ysize == 0 )
  {
    throw io::WriteException(
      io::WriteException::ERROR, o.filename() );
  }
  if ( image.buffer == (char unsigned *)0 )
  {
    throw io::WriteException(
      io::WriteException::ERROR, o.filename() );
  }

  char unsigned header[24] =
  {
    0x01, 0xda,             // MAGIC (SGI image file magic number)
    0x00,                   // STORAGE (storage format)
    0x01,                   // BPC (number of bytes per channel)
    0x00, 0x03,             // DIMENSION (number of dimensions)
    0x00, 0x00,             // XSIZE (x size in pixels)
    0x00, 0x00,             // YSIZE (y size in pixels)
    0x00, 0x00,             // ZSIZE (number of channels)
    0x00, 0x00, 0x00, 0x00, // PIXMIN (minimum pixel value)
    0x00, 0x00, 0x00, 0xff, // PIXMAX (maximum pixel value)
    0x00, 0x00, 0x00, 0x00  // DUMMY (ignored)
  };

  header[6] = (char unsigned)(image.xsize >> 8);
  header[7] = (char unsigned)image.xsize;
  header[8] = (char unsigned)(image.ysize >> 8);
  header[9] = (char unsigned)image.ysize;

  uint N = 0;
  if ( image.mode == Image::RGB ) { N = 3U; }
  else if ( image.mode == Image::RGBA ) { N = 4U; }
  else { DIE(); }

  header[11] = (char unsigned)N;

  o.write( (char *)header, 24 );

  char unsigned zero = 0;

  uint i;
  for ( i = 0; i < 80 + 4 + 404; i++ )
  {
    o.write( (char *)&zero, 1);
  }

  // write SGI image file data
  // write all the red bytes, all the green, then all the blue.

  uint c;
  for ( c = 0; c < N; c++ )
  {
    uint j;
    for ( j = 0; j < image.ysize; j++ )
    {
      uint j1 = image.ysize - j - 1;
      uint i;
      for ( i = 0; i < image.xsize; i++ )
      {
        o.write( image.buffer + N*(j1*image.xsize + i) + c, 1 );
      }
    }
  }
}

} // namespace image
