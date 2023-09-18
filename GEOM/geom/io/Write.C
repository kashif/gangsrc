/* GANG Software
 * GEOM/geom/io/Write.C
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

#include "milieu/kernel/Milieu.H"
#include "geom/surface/Surface.H"
#include "IsxWrite.H"
#include "JvxWrite.H"
#include "OoglWrite.H"
#include "VrmlWrite.H"
#include "PovWrite.H"
#include "MathWrite.H"
#include "Write.H"

namespace geom {
namespace io {


void
write(
  ::io::Ostream &out,
  surface0::GeomObject const *g,
  FileMode filemode )
    throw( ::io::WriteException )
{
  milieu::kernel::Milieu M;
  ::geom::surface::Surface G;
  // NOTE: remove const
  G.insert_no_copy( (::geom::surface0::GeomObject *)g );
  uint normals = 2;
  uint colors = 2;
  write( out, G, M, normals, colors, filemode );
  G.clear_no_delete();
}

void
write(
  ::io::Ostream &out,
  ::geom::surface::SurfaceBase const &G,
  milieu::kernel::MilieuBase const &milieu,
  uint normals, uint colors,
  FileMode filemode )
    throw( ::io::WriteException )
{
  Writer *W = writer( out, filemode );
  try {
    W->write_normals( normals );
    W->write_colors( colors );
    W->write( out, G, milieu );
  }
  catch ( ::io::WriteException const &e ) {
    delete W;
    throw e;
  }
  delete W;
}


Writer *
writer( ::io::Ostream const &out, FileMode filemode )
{
  // figure out filemode
  if ( filemode == FILEMODE_UNSPECIFIED )
  {
    if (out.filename().empty())
    {
      filemode = FILEMODE_DEFAULT;
    }
    else
    {
      filemode = get_filemode( out.filename() );
      if ( filemode == FILEMODE_UNSPECIFIED )
      {
        // default mode
        filemode = FILEMODE_DEFAULT;
      }
    }
  }

  if ( filemode == FILEMODE_ISX )
  {
    return new IsxWrite;
  }
  else if ( filemode == FILEMODE_JVX )
  {
    return new JvxWrite;
  }
  else if (filemode == FILEMODE_VRML )
  {
    return new VrmlWrite;
  }
  else if ( filemode == FILEMODE_OOGL )
  {
    return new OoglWrite;
  }
  else if ( filemode == FILEMODE_POVRAY )
  {
    return new PovWrite;
  }
  else if ( filemode == FILEMODE_MATHEMATICA )
  {
    return new MathWrite;
  }
  else
  {
    throw ::io::WriteException(
      ::io::WriteException::UNKNOWN_TYPE,
      out.filename() );
  }
}

} // namespace io
} // namespace geom
