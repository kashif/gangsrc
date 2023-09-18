/* GANG Software
 * GEOM/geom/io/IsxWrite.C
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

#include "IsxWrite.H"

namespace geom {
namespace io {

IsxWrite::
IsxWrite()
    :
    JvxWrite()
{
}

void
IsxWrite::
write(
  ::io::Ostream &o,
  ::geom::surface::SurfaceBase const &g,
  milieu::kernel::MilieuBase const &M ) const
{
  _stream = &o;
  _geomlist = &g;
  _milieu = &M;

  _stream->mode( ::io::CMODE_SCIENTIFIC );

  write_header();

  // milieu
  _milieu->dump( *_stream );

  g.dump(*_stream);

  *_stream << "\t<geometries>\n";

  std::list<surface0::GeomObject *>::const_iterator i;
  uint c;
  for ( i = g.list().begin(), c=0; i != g.list().end(); i++, c++ )
  {
    base::String name = (*i)->name();
    if (name.empty()) { name = "surface"; }
    *_stream << "\t\t<geometry name=\"" << name << "\">\n";
    write_part( *i, c );
    *_stream << "\t\t</geometry>\n";
  }

  *_stream << "\t</geometries>\n";

  write_footer();

  _stream = (::io::Ostream *)0;
  _geomlist = (::geom::surface::SurfaceBase const *)0;
  _milieu = (milieu::kernel::MilieuBase const *)0;
}

void
IsxWrite::
write_part(
  surface0::GeomObject const *g, uint part ) const
{
  if ( g->dimension() == 2U )
  {
    write_part( static_cast<surface0::Surface const *>(g), part );
  }
}

void
IsxWrite::
write_part(
  surface0::Surface const *g, uint part ) const
{
  // materials
  g->dump( *_stream );

  // position
  if ( g->position().dim() != 0U )
  {
    write_transform( *_stream, g->position(), "\t\t\t\t" );
  }

  // baseclass version
  JvxWrite::write_part( g );
}

} // namespace io
} // namespace geom
