/* GANG Software
 * GEOM/geom/io/Common.C
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
#include "Common.H"

namespace geom {
namespace io {

geom::FileMode
get_filemode( base::String const &filename )
{
  FileMode filemode = FILEMODE_ERROR;

  if ( base::match( "^.+\\.isx(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_ISX;
  }
  else if ( base::match( "^.+\\.jvx(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_JVX;
  }
  else if ( base::match( "^.+\\.wrl(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_VRML;
  }
  else if ( base::match( "^.+\\.(off|mesh|oogl)(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_OOGL;
  }
  else if ( base::match( "^.+\\.(pov)(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_POVRAY;
  }
  else if ( base::match( "^.+\\.(math)(\\.gz)?$", filename ) )
  {
    filemode = FILEMODE_MATHEMATICA;
  }
  else
  {
    filemode = FILEMODE_ERROR;
  }
  return filemode;
}

base::String
datestamp_utc()
{
  time_t rawtime;
  time ( &rawtime );
  tm *ptm = gmtime( &rawtime );
  base::String s( asctime(ptm), 24 );
  s.insert( 20, "UTC " );
  return s;
}

} // namespace io
} // namespace geom
