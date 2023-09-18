/* GANG Software
 * VIEWER/isight/kernel/Write.C
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
#include "base/Regex.H"
#include "io/Common.H"
#include "io/OstreamStream.H"
#include "io/OstreamGzip.H"
#include "image/Common.H"
#include "geom/io/Common.H"
#include "Write.H"

namespace isight {
namespace kernel {

Write::
Write()
    :
    Read()
{
}

Write::
~Write()
{
}

void
Write::
write(
  io::Ostream &stream,
  geom::FileMode filemode ) const
  throw(::io::WriteException)
{
  try
  {
    if (
      filemode == geom::FILEMODE_ISX ||
      filemode == geom::FILEMODE_JVX ||
      filemode == geom::FILEMODE_VRML ||
      filemode == geom::FILEMODE_OOGL ||
      filemode == geom::FILEMODE_MATHEMATICA ||
      filemode == geom::FILEMODE_POVRAY )
    {
      _write_geometry( stream, filemode );
      return;
    }
    
    else
    {
      throw io::WriteException( io::WriteException::UNKNOWN_TYPE,
                                stream.filename() );
    }
  }
  catch ( io::WriteException const &e )
  {
    message( e.message() );
  }
}

void
Write::
write(
  base::String const &filename,
  geom::FileMode filemode ) const
  throw(::io::WriteException)
{
  try
  {
    if (filemode == geom::FILEMODE_UNSPECIFIED)
    {
      filemode = geom::io::get_filemode(filename);
    }
    if (
      filemode == geom::FILEMODE_ISX ||
      filemode == geom::FILEMODE_JVX ||
      filemode == geom::FILEMODE_VRML ||
      filemode == geom::FILEMODE_OOGL ||
      filemode == geom::FILEMODE_MATHEMATICA ||
      filemode == geom::FILEMODE_POVRAY )
    {
      io::OstreamStream stream(filename);
      _write_geometry( stream, filemode );
      return;
    }
    
    ::image::FileMode filemode =
        ::image::get_filemode( filename );
    
    if ( filemode == image::FILEMODE_PS )
    {
      _write_postscript( filename, false );
    }
    else if ( filemode == image::FILEMODE_EPS )
    {
      _write_postscript( filename, true );
    }
    else if ( filemode == image::FILEMODE_PNG ||
              filemode == image::FILEMODE_SGI ||
              filemode == image::FILEMODE_JPEG ||
              filemode == image::FILEMODE_TIFF )
    {
      context()->write_image( filename );
    }
    else
    {
      throw io::WriteException( io::WriteException::UNKNOWN_TYPE, filename );
    }
  }
  catch ( io::WriteException const &e )
  {
    message( e.message() );
  }
}

void
Write::
_write_geometry(
  base::String const &filename ) const
{
  if ( ! surface_exists() )
  {
    message( "No surface is selected." );
    return;
  }

  try
  { 
    ::io::Ostream *stream;
    if ( ::io::is_compressed( filename ) )
    { stream = new ::io::OstreamGzip(filename); }
    else
    { stream = new ::io::OstreamStream(filename); }

    _write_geometry( *stream, geom::get_filemode( filename ) );
    delete stream;
  }
  catch ( io::WriteException const &e )
  {
    message( e.message() );
  }
}

void
Write::
_write_postscript(
  base::String const &filename, bool EPS ) const
{
  if ( ! surface_exists() )
  {
    message( "No surface is selected." );
    return;
  }
  try
  {
    ::io::Ostream *stream;
    if ( ::io::is_compressed( filename ) )
    { stream = new ::io::OstreamGzip(filename); }
    else
    { stream = new ::io::OstreamStream(filename); }
    context()->write_postscript( *stream, EPS );
    delete stream;
  }
  catch ( io::WriteException const &e )
  {
    message( e.message() );
  }
}

void
Write::
_write_geometry(
  io::Ostream &stream,
  geom::FileMode filemode ) const
{
  uint id = viewer_ui()->selected_geomobject();
  DIE_IF( id == uint(-1) );

  write_geomobject( id, stream,
                    viewer_ui()->write_normals(),
                    viewer_ui()->write_colors(),
                    *context()->milieu(), filemode );
}

bool
Write::
surface_exists() const
{
  uint id = viewer_ui()->selected_geomobject();
  return id != uint(-1);
}

} // namespace kernel
} // namespace isight
