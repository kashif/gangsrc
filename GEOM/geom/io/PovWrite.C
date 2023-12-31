/* GANG Software
 * GEOM/geom/io/PovWrite.C
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

#include "PovWrite.H"

namespace geom {
namespace io {

PovWrite::
PovWrite()
    :
    Writer(),
    _stream((::io::Ostream *)0),
    _geomlist((::geom::surface::SurfaceBase const *)0),
    _milieu((milieu::kernel::MilieuBase const *)0)
{
  _write_normal0 = true;
  _write_color0 = false;
}

PovWrite::
~PovWrite()
{
}

void
PovWrite::
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

  std::list<surface0::GeomObject *>::const_iterator i;
  int c;
  for ( i = g.list().begin(), c = 0; i != g.list().end(); i++, c++ )
  {
    write_part( *i, c );
  }

  write_footer( g.list().size() );

  _stream = (::io::Ostream *)0;
  _geomlist = (::geom::surface::SurfaceBase const *)0;
  _milieu = (milieu::kernel::MilieuBase const *)0;
}

void
PovWrite::
write_header() const
{
  *_stream << "// POV-Ray 3.1\n";

  // name
  base::String name = _geomlist->name();
  if ( ! name.empty() ) {
    *_stream << "// " << name << "\n";
  }

  // generated by / date
  *_stream << "// " << "Generated by GANGLab Software v"
    << base::system->version() << "\n"
    << "//   " << datestamp_utc() << "\n\n";

  // background color
  {
    base::Color3 const &c = _milieu->color();
    *_stream << "#declare background0 =\n"
      "  rgb <"
      << c[0] << ", "
      << c[1] << ", "
      << c[2] << ">;\n\n";
  }

  // default light
  *_stream <<  "#declare light0 =\n"
    "union {\n"
    "  light_source { <1, 0, 0> color rgb <0.5, 0.5, 0.5> }\n"
    "  light_source { <0, 1, 0> color rgb <0.5, 0.5, 0.5> }\n"
    "  light_source { <0, 0, 1> color rgb <0.5, 0.5, 0.5> }\n"
    "}\n\n";

  // default texture
  *_stream << "#declare texture0 =\n"
    "texture {\n"
    "  pigment { rgb <1.0, 1.0, 1.0> }\n"
    "  finish {\n"
    "    ambient 0.2\n"
    "    diffuse 0.35\n"
    "    specular 0.12\n"
    "    roughness 0.1\n"
    "  }\n"
    "}\n\n";

  // camera
  *_stream << "#declare camera0 =\n";

  uint window_width, window_height;
  _milieu->get_window_size( window_width, window_height );
  float aspect = 1.0;
  if( window_width!=0 & window_height!=0) {
    aspect = float(window_width) / float(window_height);
  }
  else {
    WARN( "window has zero width or height" );
  }

  milieu::Camera const &cam = _milieu->get_camera();

  // camera
  if ( cam.mode == milieu::PERSPECTIVE)
  {
    float angle = 2.0f * 180.0f /math::pi * ::atan(2.0f * cam.fov);
    // perspective camera
    *_stream << "camera {\n"
      "  perspective\n"
      "  location  <0, 0, -1>\n"
      "  angle     " << angle << "\n"
      "  up        <0, 1, 0>\n"
      "  right     <" << aspect << ", 0, 0>\n"
      "  look_at   <0, 0, 0>\n"
      "}\n\n";
  }
  else if (cam.mode == milieu::ORTHOGRAPHIC)
  {
    float scale = 2.0f * cam.zoom;
    // orthographic camera
    *_stream << "camera {\n"
      "  orthographic\n"
      "  location  <0, 0, -1>\n"
      "  up        <0, " << scale << ", 0>\n";
    *_stream << "  right     <" << scale*aspect << ", 0, 0>\n"
      "  look_at   <0, 0, 0>\n"
      "}\n\n";
  }
  else
  {
    // default camera
    *_stream << "camera {\n"
      "  perspective\n"
      "  location  <0, 0, -1>\n"
      "  look_at   <0, 0, 0>\n"
      "}\n\n";
  }

#if 0
  // dump camera data
  if (mode == milieu::kernel::Camera::CAMERA_PERSPECTIVE)
  {
    *_stream << "// camera: perspective\n//  "
      << milieu().perspective_camera()[0] << " "
      << milieu().perspective_camera()[1] << " "
      << milieu().perspective_camera()[2] << " "
      << milieu().perspective_camera()[3] << "\n\n";
  }
  else if (mode == milieu::kernel::Camera::CAMERA_ORTHOGRAPHIC)
  {
    *_stream << "// camera: orthographic\n//  "
      << milieu().orthographic_camera()[0] << " "
      << milieu().orthographic_camera()[1] << " "
      << milieu().orthographic_camera()[2] << " "
      << milieu().orthographic_camera()[3] << "\n\n";
  }
  else
  {
    *_stream << "// camera: default\n\n";
  }
#endif

}

void
PovWrite::
write_footer( uint count ) const
{
  *_stream << "#ifndef (INCLUDED)\n"
    "camera { camera0 }\n"
    "background { color background0 }\n"
    "light0\n"
    "object {\n";
  uint i;
  for ( i = 0; i < count; i++ )
  {
    *_stream << "  object" << i << "\n";
  }
  *_stream << "  texture { texture0 }\n"
    "  transform transform0\n"
    "}\n"
    "#end\n";
}

void
PovWrite::
write_part(
  surface0::GeomObject const *g,
  uint i ) const
{
  if ( g->dimension() == 2U )
  {
    write_part( static_cast<surface0::Surface const *>(g), i );
  }
}

void
PovWrite::
write_part(
  surface0::Surface const *g,
  uint part ) const
{
  _write_normal0 = _write_normal == 0 ? false : true;

  _write_color0 = _write_color == 1 ? true : false;
  _write_color0 &= g->has_array_color();

  g->compute_normal();

  *_stream << "#declare transform0 =\n"
    "transform {\n";

  geom::Transform const &t = g->position();
  DIE_IF( t.dim() != 4U );
  if (t.dim() == 4)
  {
    *_stream << "matrix<\n";
    *_stream << "  " << t[0][0] << ", " << t[0][1] << ", "
             << -t[0][2] << ",\n";
    *_stream << "  " << t[1][0] << ", " << t[1][1] << ", "
             << -t[1][2] << ",\n";
    *_stream << "  " << t[2][0] << ", " << t[2][1] << ", "
             << -t[2][2] << ",\n";
    *_stream << "  " << t[3][0] << ", " << t[3][1] << ", "
             << -t[3][2] << ">\n";
  }
  *_stream << "}\n\n";

  *_stream << "#declare object" << part << " =\n"
    "object {\n";
  *_stream << "mesh {\n";

  uint i;
  for ( i = 0; i < g->face_count(); i++ )
  {
    // write face
    uint n = g->face_count(i);
    if (n < 3) { throw base::Exception(""); }

    // tessellate the face (0,1,2), (0,2,3), etc
    uint j;
    for ( j = 1; j < n-1; j++)
    {
      if ( _write_normal0 )
      {
        write_smooth_triangle( g,
                               g->face_vertex(i, 0),
                               g->face_vertex(i, j),
                               g->face_vertex(i, j+1) );
      }
      else
      {
        write_triangle( g,
                        g->face_vertex(i, 0),
                        g->face_vertex(i, j),
                        g->face_vertex(i, j+1) );
      }
    }
  }
  *_stream << "}\n"; // mesh
  *_stream << "}\n\n"; // object
}

void
PovWrite::
write_triangle(
  surface0::Surface const *g,
  uint a, uint b, uint c ) const
{
/*
  write triangle
  triangle { <x1,y1,z1>, <x2,y2,z2>, <x3,y3,z3> }
*/
  geom::Vertex3 v;
  *_stream << "triangle {\n";
  write_vertex( g, a );
  *_stream << ",\n";
  write_vertex( g, b );
  *_stream << ",\n";
  write_vertex( g, c );
  *_stream << "\n";
  *_stream << "}\n";
}

void
PovWrite::
write_smooth_triangle(
  surface0::Surface const *g,
  uint a, uint b, uint c ) const
{
  /*
    write vertex and normal
    format:
    smooth_triangle { X1, N1, X2, N2, X3, N3 }
    where Xi = <Xi1,Xi2,Xi3> is a vertex
    Ni = <Ni1,Ni2,Ni3> is a normal
  */
  *_stream << "smooth_triangle {\n";
  write_vertex( g, a );
  *_stream << ",\n";
  write_normal( g, a );
  *_stream << ",\n";
  write_vertex( g, b );
  *_stream << ",\n";
  write_normal( g, b );
  *_stream << ",\n";
  write_vertex( g, c );
  *_stream << ",\n";
  write_normal( g, c );
  *_stream << "\n";
  *_stream << "}\n";
}

void
PovWrite::
write_vertex(
  surface0::Surface const *g,
  uint a ) const
{
  geom::Vertex3 v;
  g->vertex( v, a );
  *_stream << "<" << v[0] << ", " << v[1] << ", " << v[2] << ">";
}

void
PovWrite::
write_normal(
  surface0::Surface const *g,
  uint a ) const
{
  geom::Normal3 const &x = g->vertex_normal(a);
  *_stream << "<" << x[0] << ", " << x[1] << ", " << x[2] << ">";
}

} // namespace io
} // namespace geom
