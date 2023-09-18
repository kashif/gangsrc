/* GANG Software
 * BASE/image/Io.C
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
#include "io/Common.H"
#include "Common.H"
#include "Png.H"
#include "Jpeg.H"
#include "Sgi.H"
#include "Tiff.H"
#include "Io.H"

namespace image {

void
read( base::String const &filename, Image &image )
{
  Reader *R = reader(filename);
  R->read( filename, image );
  delete R;
}

void
write( base::String const &filename, Image const &image )
{
  Writer *W = writer(filename);
  W->write( filename, image );
  delete W;
}


Reader *
reader( base::String const &filename )
{
  // NOTE: should support sgi.gz

  Reader *reader = (Reader *)0;

  if ( io::is_compressed(filename) )
  {
    throw ( io::WriteException(
              io::WriteException::UNKNOWN_TYPE, filename ) );
  }
  FileMode filemode = get_filemode( filename );
  if ( filemode == FILEMODE_PNG )
  {
    reader = new Png;
  }
  else if ( filemode == FILEMODE_JPEG )
  {
    reader = new Jpeg;
  }
  else if ( filemode == FILEMODE_SGI )
  {
    reader = new Sgi;
  }
  else if ( filemode == FILEMODE_TIFF )
  {
    reader = new Tiff;
  }
  else
  {
    throw ( io::WriteException(
              io::WriteException::UNKNOWN_TYPE, filename ) );
  }
  return reader;
}

Writer *
writer( base::String const &filename )
{
  Writer *writer = (Writer *)0;

  FileMode filemode = get_filemode( filename );
  if ( filemode == FILEMODE_PNG )
  {
    if ( io::is_compressed(filename) )
    {
      throw ( io::WriteException(
                io::WriteException::UNKNOWN_TYPE, filename ) );
    }
    writer = new Png;
  }
  else if ( filemode == FILEMODE_JPEG )
  {
    if ( io::is_compressed(filename) )
    {
      throw ( io::WriteException(
                io::WriteException::UNKNOWN_TYPE, filename ) );
    }
    writer = new Jpeg;
  }
  else if ( filemode == FILEMODE_SGI )
  {
    writer = new Sgi;
  }
  else if ( filemode == FILEMODE_TIFF )
  {
    if ( io::is_compressed(filename) )
    {
      throw ( io::WriteException(
                io::WriteException::UNKNOWN_TYPE, filename ) );
    }
    writer = new Tiff;
  }
  else
  {
    throw ( io::WriteException(
              io::WriteException::UNKNOWN_TYPE, filename ) );
  }
  return writer;
}

} // namespace image
