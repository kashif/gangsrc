/* GANG Software
 * BASE/image/Png.C
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

#include <png.h>
#include "Png.H"

namespace image {


static void error_fn(
  png_structp png_ptr,
  png_const_charp text )
{
  std::cerr << text;
  DIE();
}

static void warning_fn(
  png_structp png_ptr,
  png_const_charp text )
{
  std::cerr << text;
}

Png::
Png()
    :
    _compression(7U)
{
}

void
Png::
read( FILE *file, Image &image )
{
  if ( file == (FILE *)0 )
  {
    throw io::ReadException(
      io::ReadException::ERROR,
      base::String("Internal error reading PNG image file") );
  }

  // Create and initialize the png_struct
  png_structp png_ptr =
    png_create_read_struct(PNG_LIBPNG_VER_STRING,
                           (void *)0,
                           error_fn, warning_fn);

  if (png_ptr == 0)
  {
    throw io::ReadException(
      io::ReadException::ERROR, base::String() );
  }

  // Allocate/initialize the memory for image information
  png_infop info_ptr = png_create_info_struct(png_ptr);


  if (info_ptr == 0)
  {
    png_destroy_read_struct(&png_ptr, (png_infopp)0, (png_infopp)0);
    throw io::ReadException(
      io::ReadException::ERROR,
      base::String("Error reading PNG image file") );
  }


  /* Set up the input control if you are using standard C streams */

  png_init_io(png_ptr, file);

  // read initial data
  png_uint_32 width, height;
  int bit_depth, color_type, interlace_type;
  int compression_type, filter_method;

  png_read_info( png_ptr, info_ptr );
  png_get_IHDR( png_ptr, info_ptr,
                &width, &height,
                &bit_depth, &color_type, &interlace_type,
                &compression_type, &filter_method );
  image.xsize = width;
  image.ysize = height;

  uint N = 0;
  if ( image.mode == Image::RGB ) { N = 3U; }
  else if ( image.mode == Image::RGBA ) { N = 4U; }
  else { DIE(); }

  image.buffer = new char unsigned[N*image.xsize*image.ysize];

  // convert depth 16 to 8
  if (bit_depth == 16)
      png_set_strip_16(png_ptr);

  // expand palette
  if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);

  // expand grayscale
  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
      png_set_gray_1_2_4_to_8(png_ptr);

  // convert grayscale to rgb
  if (color_type == PNG_COLOR_TYPE_GRAY ||
      color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png_ptr);


  if ( image.mode == Image::RGB )
  {
    // strip alpha
    if (color_type & PNG_COLOR_MASK_ALPHA)
        png_set_strip_alpha(png_ptr);

    // set up row_pointer
    char unsigned const **row_pointer =
      new char unsigned const *[image.ysize];
    uint j;
    for ( j = 0; j < image.ysize; j++ )
    {
      row_pointer[j] = image.buffer + N * j * image.xsize;
    }
    png_set_rows( png_ptr, info_ptr, (png_byte **)row_pointer );

    // read the image
    png_read_image(png_ptr, (png_byte **)row_pointer );

    delete [] row_pointer;
  }
  else if ( image.mode == Image::RGBA )
  {
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    {
      // image has alpha
      png_set_tRNS_to_alpha(png_ptr);

      // set up row_pointer
      char unsigned const **row_pointer =
        new char unsigned const *[image.ysize];
      uint j;
      for ( j = 0; j < image.ysize; j++ )
      {
        row_pointer[j] = image.buffer + N * j * image.xsize;
      }
      png_set_rows( png_ptr, info_ptr, (png_byte **)row_pointer );

      // read the image
      png_read_image(png_ptr, (png_byte **)row_pointer );

      delete [] row_pointer;
    }
    else
    {
      // image doesn't have alpha

      // temporary buffer
      char unsigned *buffer =
        new char unsigned [3*image.xsize*image.ysize];
      uint i;
      for ( i = 0; i < image.xsize*image.ysize; i++ )
      {
        buffer[3*i+0] = image.buffer[4*i+0];
        buffer[3*i+1] = image.buffer[4*i+1];
        buffer[3*i+2] = image.buffer[4*i+2];
      }

      char unsigned const **row_pointer =
        new char unsigned const *[image.ysize];

      uint j;
      for ( j = 0; j < image.ysize; j++ )
      {
        row_pointer[j] = image.buffer + N * j * image.xsize;
      }
      png_set_rows( png_ptr, info_ptr, (png_byte **)row_pointer );

      // read the image
      png_read_image(png_ptr, (png_byte **)row_pointer );

      delete [] row_pointer;
      delete [] buffer;
      
    }
  }
  else { DIE(); }



  // free any memory allocated
  png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)0);
}


void
Png::
write( FILE *file, Image const &image ) const
{
  if ( file == (FILE *)0 )
  {
    throw io::WriteException(
      io::WriteException::ERROR,
      base::String("Internal error writing PNG image file") );
  }
  if ( image.xsize == 0 || image.ysize == 0 )
  {
    throw io::WriteException(
      io::WriteException::ERROR,
      base::String("Internal error writing PNG image file") );
  }
  if ( image.buffer == (char unsigned *)0 )
  {
    throw io::WriteException(
      io::WriteException::ERROR,
      base::String("Internal error writing PNG image file") );
  }

  // create a png_struct
  png_structp png_ptr =
    png_create_write_struct( PNG_LIBPNG_VER_STRING,
                             (void *)0,
                             error_fn, warning_fn );

  if (png_ptr == (png_structp)0)
  {
    throw io::WriteException(
      io::WriteException::ERROR,
      base::String("Error writing PNG image file") );
  }

  // allocate and initialize the image information data
  png_infop info_ptr =
    png_create_info_struct(png_ptr);
  if (info_ptr == (png_infop)0)
  {
    png_destroy_write_struct(&png_ptr,  (png_infopp)0);
      throw io::WriteException(
        io::WriteException::ERROR,
        base::String("Error writing PNG image file") );
  }

  // set up the output control
  png_init_io(png_ptr, file);

  uint N = 0;
  if ( image.mode == Image::RGB ) { N = 3U; }
  else if ( image.mode == Image::RGBA ) { N = 4U; }
  else { DIE(); }

  // compression level
  png_set_compression_level( png_ptr, _compression ); 

  // set up row_pointer
  char unsigned const **row_pointer = new char unsigned const *[image.ysize];
  uint j;
  for ( j = 0; j < image.ysize; j++ )
  {
    row_pointer[j] = image.buffer + N * j * image.xsize;
  }

  png_set_rows( png_ptr, info_ptr, (png_byte **)row_pointer );

  uint mode = 0;
  if (image.mode == Image::RGB )
  { mode = PNG_COLOR_TYPE_RGB; }
  else if (image.mode == Image::RGBA )
  { mode = PNG_COLOR_TYPE_RGB_ALPHA; }
  else { DIE(); }

  // configure info_ptr
  png_set_IHDR( png_ptr, info_ptr,
                image.xsize, image.ysize,
                8, // bit depth
                mode, // RGB or RGBA,
                PNG_INTERLACE_NONE,
                PNG_COMPRESSION_TYPE_DEFAULT,
                PNG_FILTER_TYPE_DEFAULT );

  // write the image
  png_write_png( png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, (void *)0 );

  delete row_pointer;

  // free any memory allocated
  png_destroy_write_struct(&png_ptr, &info_ptr);

}

} // namespace image
 
