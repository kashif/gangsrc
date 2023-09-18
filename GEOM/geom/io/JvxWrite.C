/* GANG Software
 * GEOM/geom/io/JvxWrite.C
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

#include <iomanip>
#include "base/Color4.H"
#include "JvxWrite.H"

namespace geom {
namespace io {

JvxWrite::
JvxWrite()
    :
    Writer(),
    math::WriteUtil(),
    _stream((::io::Ostream *)0),
    _geomlist((::geom::surface::SurfaceBase const *)0),
    _milieu((milieu::kernel::MilieuBase const *)0)
{
}

void
JvxWrite::
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

  char const *tab = "\t";
  o << tab << "<geometries>\n";

  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = g.list().begin(); i != g.list().end(); i++ )
  {
    base::String name = (*i)->name();
    if (name.empty()) { name = "surface"; }
    o << tab << "\t<geometry name=\"" << name << "\">\n";
    write_part( *i );
    o << tab << "\t</geometry>\n";
  }
  o << tab << "</geometries>\n";

  write_footer();

  _stream = (::io::Ostream *)0;
  _geomlist = (::geom::surface::SurfaceBase const *)0;
  _milieu = (milieu::kernel::MilieuBase const *)0;
}

void
JvxWrite::
write_header() const
{
  base::String name = _geomlist->name();
  if (name.empty()) { name = "surface"; }

  // header
  *_stream
    << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" standalone=\"yes\"?>\n"
    << "<jvx-model>\n"
    << "\t<meta generator=\"GANGLab Software v"
    << base::system->version() << "\"/>\n"
    << "\t<meta date=\"" << datestamp_utc() << "\"/>\n"
    << "\t<version type=\"dump\">0.10</version>\n"
    << "\t<title>" << name << "</title>\n";
}
void
JvxWrite::
write_footer() const
{
  *_stream << "</jvx-model>\n";
}

void
JvxWrite::
write_part(
  surface0::GeomObject const *g ) const
{
  if ( g->dimension() == 2U )
  {
    write_part( static_cast<surface0::Surface const *>(g) );
  }
}

void
JvxWrite::
write_part(
  surface0::Surface const *g ) const
{
  _write_normal0 = _write_normal == 1 ? true : false;
  _write_color0 = _write_color == 1 ? true : false;
  _write_color0 &= g->has_array_color();

  char const *tab = "\t\t\t";

  g->compute_normal();

  uint dim =
    ( g->spaceform().space == ::geom::SpaceForm::SPACEFORM_R ?
      g->spaceform().dim : g->spaceform().dim + 1 );

  *_stream
    << tab << "<pointSet dim=\"" << dim
    << "\" point=\"hide\">\n";

  // ------------------------------------
  // vertices
  uint m = g->vertex_count();
  WARN_IF(m==0, "0 vertices");

  *_stream
    << tab << "\t<points num=\""
    << m << "\">\n";

  uint i;
  math::Vector<Real> v;
  v.allocate( dim );

  bool standard_geometry = ( g->position().dim() == 4U &&
                             g->projection_mode() == geom::CENTRAL );

  for ( i = 0; i < m; i++ )
  {
    if (standard_geometry)
    {
      g->vertex( v, i );
    }
    else
    {
      // project to R^3
      // NOTE: this should be an option
      geom::Vertex4 w;
      g->vertex( w, i, g->position(),
                 // g->projection_mode()
                 geom::STEREOGRAPHIC
                 );
      v[0] = w[0]/w[3];
      v[1] = w[1]/w[3];
      v[2] = w[2]/w[3];
    }

    *_stream << tab << "\t\t<p>";
    uint j;
    for ( j = 0; j < dim; j++ )
    {
      *_stream << v[j];
      if (j+1 != dim)
      { *_stream << " "; }
    }
    *_stream << "</p>\n";
  }

  *_stream
    << tab << "\t</points>\n"
    << tab << "</pointSet>\n";

  // ------------------------------------
  // FACES

  m = g->face_count();
  WARN_IF(m==0, "0 faces");

  *_stream
    << tab << "<faceSet face=\"show\" edge=\"show\">\n";

  // faces
  *_stream
    << tab << "\t<faces num=\""
    << m
    << "\">\n";

  for ( i = 0; i < m; i++ )
  {
    uint n = g->face_count(i);
    uint j;
    *_stream
      << tab << "\t\t<f>";
    for ( j = 0; j < n; j++ )
    {
      *_stream
        << g->face_vertex(i,j);
      if ( j != n-1 ) { *_stream
        << " "; }
    }
    *_stream
      << "</f>\n";
  }

  *_stream
    << tab << "\t</faces>\n";

  // face normals colors
  if (_write_normal0)
  {
    *_stream
      << tab << "\t<normals>\n";
    for ( i = 0; i < m; i++ )
    {
      geom::Normal3 const &n = g->face_normal(i);
      *_stream
        << tab << "\t\t<n>"
        << n[0] << " " << n[1] << " " << n[2] <<
        "</n>\n";
    }
    *_stream
      << tab << "\t</normals>\n";
  }

  // face colors
  if (_write_color0)
  {
    *_stream
      << tab << "\t<colors type=\"rgba\">\n";
    for ( i = 0; i < m; i++ )
    {
      base::Color4 const &c = g->face_color(i);
      uint c0 = (uint)(255.0f * c[0] + 0.5);
      uint c1 = (uint)(255.0f * c[1] + 0.5);
      uint c2 = (uint)(255.0f * c[2] + 0.5);
      uint c3 = (uint)(255.0f * c[3] + 0.5);
      *_stream
        << tab << "\t\t<c>"
        << c0 << " " << c1 << " " << c2 << " " << c3
        << "</c>\n";
    }
    *_stream
      << tab << "\t</colors>\n";
  }

  *_stream
    << tab << "</faceSet>\n";

  // ------------------------------------
  // lines
  std::list<std::list<uint> > const &line = g->line();
  if ( ! line.empty() )
  {
    *_stream
      << tab << "<lineSet line=\"show\">\n"
      << tab << "\t<lines num=\""
      << line.size()
      << "\">\n";

    std::list<std::list<uint> >::const_iterator i;
    for ( i = line.begin(); i != line.end(); i++ )
    {
      *_stream << tab << "\t\t<l>";

      std::list<uint>::const_iterator j;
      std::list<uint>::const_iterator next_to_last = (*i).end();
      next_to_last--;
      for ( j = (*i).begin(); j != (*i).end(); j++ )
      {
        *_stream << *j;
        if ( j != next_to_last ) { *_stream << " "; }
      }
      *_stream << "</l>\n";
    }

    *_stream
      << tab << "\t</lines>\n"
      << tab << "</lineSet>\n";
  }
}

} // namespace io
} // namespace geom
