/* GANG Software
 * BASE/image/Jpeg.C
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

#include <stdio.h>
extern "C" {
#include <jpeglib.h>
}
#include "Jpeg.H"

namespace image {

Jpeg::
Jpeg()
    :
    _quality(75)
{
}

void
Jpeg::
read( FILE *file, Image &image )
{
  if ( file == (FILE *)0 )
  {
    throw io::ReadException(
      io::ReadException::ERROR,
      base::String("Internal error reading JPEG image file") );
  }

  // jpeg compress structure
  jpeg_decompress_struct cinfo;

  // set up the error handler
  jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error( &jerr );

  // initialize the JPEG decompression object. */
  jpeg_create_decompress( &cinfo );

  // specify data source (eg, a file)
  jpeg_stdio_src( &cinfo, file );

  // read file parameters with jpeg_read_header()
  jpeg_read_header( &cinfo, TRUE );

  // set parameters for decompression

  image.xsize = cinfo.image_width;
  image.ysize = cinfo.image_height;
  if ( image.mode == Image::RGB )
  { image.buffer = new char unsigned[3*image.xsize*image.ysize]; }
  else if ( image.mode == Image::RGBA )
  { image.buffer = new char unsigned[4*image.xsize*image.ysize]; }
  else { DIE(); }

  // Start decompressor
  jpeg_start_decompress( &cinfo );

  if ( image.mode == Image::RGB )
  {
    uint j;
    for ( j = 0; j < image.ysize; j++ )
    {
      char unsigned *p = image.buffer + 3*j*image.xsize;
      jpeg_read_scanlines( &cinfo, (JSAMPROW *)&p, 1 );
    }
  }
  else
  {
    // RGBA
    char unsigned *buffer = new char unsigned[3 * image.xsize];

    uint j;
    for ( j = 0; j < image.ysize; j++ )
    {
      jpeg_read_scanlines(&cinfo, (JSAMPROW *)(&buffer), 1);
      uint i;
      for ( i = 0; i < image.xsize; i++ )
      {
        image.buffer[4*(j*image.xsize + i) + 0] = buffer[3*i + 0];
        image.buffer[4*(j*image.xsize + i) + 1] = buffer[3*i + 1];
        image.buffer[4*(j*image.xsize + i) + 2] = buffer[3*i + 2];
        image.buffer[4*(j*image.xsize + i) + 3] = 255;
      }
    }
    delete [] buffer;
  }

  // finish decompression
  jpeg_finish_decompress( &cinfo );

  // deallocate the JPEG decompression object
  jpeg_destroy_decompress( &cinfo );
}

void
Jpeg::
write( FILE *file, Image const &image ) const
{
  if ( file == (FILE *)0 )
  {
    throw io::WriteException(
      io::WriteException::ERROR,
      base::String("Internal error writing JPEG image file") );
  }
  if ( image.xsize == 0 || image.ysize == 0 )
  {
    throw io::WriteException(
      io::WriteException::ERROR,
      base::String("Internal error writing JPEG image file") );
  }
  if ( image.buffer == (char unsigned *)0 )
  {
    throw io::WriteException(
      io::WriteException::ERROR,
      base::String("Internal error writing JPEG image file") );
  }

  // jpeg compress structure
  jpeg_compress_struct cinfo;

  // set up the error handler
  jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);

  // initialize the jpeg compression object
  jpeg_create_compress(&cinfo);

  // specify the destination
  jpeg_stdio_dest(&cinfo, file);

  // specify the image
  cinfo.image_width      = image.xsize;
  cinfo.image_height     = image.ysize;
  cinfo.input_components = 3;
  cinfo.in_color_space   = JCS_RGB;
  jpeg_set_defaults(&cinfo);

  // quality
  jpeg_set_quality(&cinfo, _quality, TRUE);

  // initialize compression
  jpeg_start_compress(&cinfo, TRUE);

  // compress
  if ( image.mode == Image::RGB )
  {
    // RGB
    uint j;
    for ( j = 0; j < image.ysize; j++ )
    {
      char unsigned *p = image.buffer + 3*j*image.xsize;
      jpeg_write_scanlines( &cinfo, (JSAMPROW *)&p, 1 );
    }
  }
  else
  {
    // RGBA
    char unsigned *buffer = new char unsigned[3 * image.xsize];

    uint j;
    for ( j = 0; j < image.ysize; j++ )
    {
      uint i;
      for ( i = 0; i < image.xsize; i++ )
      {
        buffer[3*i + 0] = image.buffer[4*(j*image.xsize + i) + 0];
        buffer[3*i + 1] = image.buffer[4*(j*image.xsize + i) + 1];
        buffer[3*i + 2] = image.buffer[4*(j*image.xsize + i) + 2];
      }
      jpeg_write_scanlines( &cinfo, (JSAMPROW *)(&buffer), 1 );
    }
    delete [] buffer;
  }

  // finish compression
  jpeg_finish_compress( &cinfo );

  // release memory
  jpeg_destroy_compress( &cinfo );
}

} // namespace image
