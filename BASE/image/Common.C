/* GANG Software
 * BASE/image/Common.C
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

#include "base/Regex.H"
#include "math/Math.H"
#include "Common.H"

namespace image {

FileMode
get_filemode( base::String const &filename )
{
  FileMode filemode = FILEMODE_ERROR;

  if ( base::match( "^.+\\.ps(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_PS;
  }
  else if ( base::match( "^.+\\.eps(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_EPS;
  }
  else if ( base::match( "^.+\\.png(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_PNG;
  }
  else if ( base::match( "^.+\\.jpe?g(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_JPEG;
  }
  else if ( base::match( "^.+\\.(sgi|rgb)(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_SGI;
  }
  else if ( base::match( "^.+\\.tiff(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_TIFF;
  }
  else
  {
    filemode = FILEMODE_ERROR;
  }

  return filemode;
}

void
reverse( Image &image )
{
  uint N = 0;
  if ( image.mode == Image::RGB ) { N = 3U; }
  else if ( image.mode == Image::RGBA ) { N = 4U; }
  else { DIE(); }

  // reverse the image
  uint j;
  for ( j = 0; j < image.ysize/2; j++ )
  {
    uint j1 = image.ysize - j - 1;
    uint i;
    for ( i = 0; i < N*image.xsize; i++ )
    {
      math::swap( image.buffer[N*j*image.xsize + i],
                  image.buffer[N*j1*image.xsize + i] );
    }
  }
}

} // namespace image
