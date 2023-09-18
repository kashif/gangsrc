/* GANG Software
 * BASE/image/Tiff.C
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

#include <tiffio.h>
#include <iomanip.h>
#include "Tiff.H"

namespace image {

Tiff::
Tiff()
{
}

void
Tiff::
read( base::String const &filename, Image &image )
{
  TIFF *tiff_struct = TIFFOpen( filename.c_str(), "r" );
  if ( tiff_struct == (TIFF *)0 )
  {
    throw io::ReadException(
      io::ReadException::ERROR,
      base::String("Internal error reading TIFF image file") );
  }

  uint32 xsize, ysize;

  // get width and height
  TIFFGetField(tiff_struct, TIFFTAG_IMAGEWIDTH, &xsize);
  TIFFGetField(tiff_struct, TIFFTAG_IMAGELENGTH, &ysize);
  image.xsize = xsize;
  image.ysize = ysize;

  uint N = 0;
  if ( image.mode == Image::RGB ) { N = 3U; }
  else if ( image.mode == Image::RGBA ) { N = 4U; }
  else { DIE(); }

  // allocate image.buffer
  image.buffer = new char unsigned[N * image.xsize * image.ysize];

  // allocate a temporary buffer
  uint32 *buffer = new uint32[image.xsize * image.ysize];

  int b = TIFFReadRGBAImage(tiff_struct, image.xsize, image.ysize, buffer, 0);
  if ( b != 1 )
  {
    throw io::ReadException(
      io::ReadException::ERROR,
      base::String("Error reading TIFF image file") );
  }

  // copy buffer into image
  uint j;
  for ( j = 0; j < image.ysize; j++ )
  {
    uint j1 = image.ysize - j - 1;
    uint i;
    for ( i = 0; i < image.xsize; i++ )
    {
      image.buffer[N*(j*image.xsize+i)+0] =
        (char unsigned)((buffer[j1*image.xsize+i]>>0) & 0xff);
      image.buffer[N*(j*image.xsize+i)+1] =
        (char unsigned)((buffer[j1*image.xsize+i]>>8) & 0xff);
      image.buffer[N*(j*image.xsize+i)+2] =
        (char unsigned)((buffer[j1*image.xsize+i]>>16) & 0xff);
      if ( N == 4 )
      {
        image.buffer[N*(j*image.xsize+i)+3] =
          (char unsigned)((buffer[j1*image.xsize+i]>>24) & 0xff);
      }
    }
  }
  delete [] buffer;

  TIFFClose(tiff_struct);
}

void
Tiff::
write( base::String const &filename, Image const &image ) const
{
  if ( image.xsize == 0 || image.ysize == 0 )
  {
    throw io::WriteException(
      io::WriteException::ERROR, base::String() );
  }
  if ( image.buffer == (char unsigned *)0 )
  {
    throw io::WriteException(
      io::WriteException::ERROR, base::String() );
  }

  // initialize the TIFF structure
  TIFF *tiff_struct = TIFFOpen( filename.c_str(), "w" );
  if ( tiff_struct == (TIFF *)0 )
  {
    throw io::WriteException(
      io::WriteException::ERROR, base::String() );
  }

  // configure the image
  TIFFSetField( tiff_struct, TIFFTAG_IMAGEWIDTH, image.xsize );
  TIFFSetField( tiff_struct, TIFFTAG_IMAGELENGTH, image.ysize );
  TIFFSetField( tiff_struct, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG );
  TIFFSetField( tiff_struct, TIFFTAG_COMPRESSION, COMPRESSION_PACKBITS );
  TIFFSetField( tiff_struct, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB );

  if ( image.mode == Image::RGB )
  {
    TIFFSetField( tiff_struct, TIFFTAG_SAMPLESPERPIXEL, 3 );
    TIFFSetField( tiff_struct, TIFFTAG_BITSPERSAMPLE, 8 );

    uint j;
    for ( j = 0; j < image.ysize; j++ )
    {
      // write the row
      int b = TIFFWriteScanline( tiff_struct,
                                 image.buffer + 3*j*image.xsize, j);
      if ( b != 1 )
      {
        throw io::WriteException(
          io::WriteException::ERROR,
          base::String( "Error writing TIFF image file") );
      }
    }
  }
  else if ( image.mode == Image::RGBA )
  { 
    TIFFSetField( tiff_struct, TIFFTAG_BITSPERSAMPLE, 8 );
    TIFFSetField( tiff_struct, TIFFTAG_SAMPLESPERPIXEL, 4 );
    short x = EXTRASAMPLE_ASSOCALPHA;
    TIFFSetField( tiff_struct, TIFFTAG_EXTRASAMPLES, 1, &x );

    uint j;
    for ( j = 0; j < image.ysize; j++ )
    {
      // write the row
      int b = TIFFWriteScanline( tiff_struct,
                                 image.buffer + 4*j*image.xsize, j);
      if ( b != 1 )
      {
        throw io::WriteException(
          io::WriteException::ERROR,
          base::String( "Error writing TIFF image file") );
      }
    }

#if 0
    // allocate a temporary buffer to hold one row
    char unsigned *buffer = new char unsigned[3 * image.xsize];

    uint j;
    for ( j = 0; j < image.ysize; j++ )
    {
      uint i;
      for ( i = 0; i < image.xsize; i++ )
      {
        buffer[3*i+0] = image.buffer[4*(j*image.xsize + i)+0];
        buffer[3*i+1] = image.buffer[4*(j*image.xsize + i)+1];
        buffer[3*i+2] = image.buffer[4*(j*image.xsize + i)+2];
      }
      // write the row
      int b = TIFFWriteScanline( tiff_struct, buffer, j);
      if ( b != -1 )
      {
        throw io::WriteException(
          io::WriteException::ERROR,
          base::String( "Error writing TIFF image file") );
      }
    }
    // delete the temporary buffer
    delete [] buffer;
#endif
  }
  else { DIE(); }

  // close the tiff_struct
  TIFFClose(tiff_struct);
}

} // namespace image
