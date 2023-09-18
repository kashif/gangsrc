/* GANG Software
 * BASE/image/Common.H
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

#ifndef image_Common_INCLUDED
#define image_Common_INCLUDED

#include "base/String.H"

namespace image {

enum FileMode
{
  FILEMODE_ERROR,
  FILEMODE_UNSPECIFIED,
  FILEMODE_PNG,
  FILEMODE_SGI,
  FILEMODE_JPEG,
  FILEMODE_TIFF,
  FILEMODE_PS,
  FILEMODE_EPS,
  FILEMODE_DEFAULT = FILEMODE_PNG
};

FileMode
get_filemode( base::String const &filename );

struct Image
{ 
  enum Mode {RGB, RGBA};
  Image( char unsigned *b, uint x, uint y, Mode m )
      : buffer(b), xsize(x), ysize(y), mode(m) {}
  Image()
      : buffer((char unsigned *)0), xsize(0), ysize(0), mode(RGB) {}
  char unsigned *buffer;
  uint xsize, ysize;
  Mode mode;
};

void reverse( Image &image );

} // namespace image

#endif // image_Common_INCLUDED
