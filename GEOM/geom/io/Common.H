/* GANG Software
 * GEOM/geom/io/Common.H
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

#ifndef geom_io_Common_INCLUDED
#define geom_io_Common_INCLUDED

#include "geom/interface/Common.H"

namespace geom {
namespace io {

#if 0
enum FileMode
{
  FILEMODE_ERROR,
  FILEMODE_UNSPECIFIED,
  FILEMODE_ISX,
  FILEMODE_JVX,
  FILEMODE_VRML,
  FILEMODE_OOGL,
  FILEMODE_MATHEMATICA,
  FILEMODE_POVRAY,
  FILEMODE_DEFAULT = FILEMODE_JVX
};
#endif

geom::FileMode
get_filemode( base::String const &filename );

base::String datestamp_utc();

} // namespace io
} // namespace geom

#endif // geom_io_Common_INCLUDED
