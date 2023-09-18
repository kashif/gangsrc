/* GANG Software
 * GEOM/geom/interface/Surface.C
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

#include "geom/surface0/Surface.H"
#include "geom/surface/Surface.H"
#include "Surface.H"

namespace geom {

static surface0::Surface *first(surface::Construct *x)
{ return static_cast<surface0::Surface *>(x->first()); }

FileMode
get_filemode( base::String const &filename )
{
  return FileMode(geom::io::get_filemode(filename));
}

Surface::
Surface()
    :
    _( new surface::Surface )
{
}

Surface::
Surface(bool)
    :
    _( (surface::Surface *)0 )
{
}

Surface::
Surface( Surface const &x )
    :
    _( new surface::Surface(*x._) )
{
}

Surface::
~Surface()
{
  delete _;
}

Surface &
Surface::
operator=( Surface const &x )
{
  _->operator=(*x._);
  return *this;
}

Surface::Type
Surface::
type() const
{
  return Type( first(_)->type() );
}


uint
Surface::
vertex_count() const
{
  return _->vertex_count();
}

uint
Surface::
edge_count() const
{
  return _->edge_count();
}

uint
Surface::
face_count() const
{
  return _->face_count();
}

void
Surface::
vertex(Vertex3 &x, uint i ) const
{
  first(_)->vertex(x, i);
}

void
Surface::
vertex(Vertex4 &x, uint i ) const
{
  first(_)->vertex(x, i);
}

Real
Surface::
vertex_gaussian_curvature( uint i ) const
{
  return first(_)->vertex_gaussian_curvature(i);
}

Real
Surface::
face_area(uint i) const
{
  return first(_)->face_area(i);
}

Transform const &
Surface::
position() const
{
  return first(_)->position();
}

void
Surface::
position( Transform const &x)
{
  _->position(x);
}

void
Surface::
position( std::list<Transform> &x ) const
{
  _->position(x);
}

bool
Surface::
empty() const
{
  return _->empty();
}

void
Surface::
clear()
{
  _->clear();
}

void
Surface::
insert( Surface const &x )
{
  _->insert( *x._ );
}

#if 0
void
Surface::
insert( std::list<Surface *> const &x )
{
  std::list<Surface *>::const_iterator i;
  for ( i = x.begin(); i != x.end(); i++ )
  {
    insert( *(*i) );
  }
}

void
Surface::
insert( Surface const &x )
{
  _->insert( *_surface(x._) );
}

void
Surface::
insert_no_copy( Surface *x )
{
  _->insert( *x );
}

void
Surface::
insert_no_copy( std::list<Surface *> const &x )
{
  std::list<Surface *>::const_iterator i;
  for ( i = x.begin(); i != x.end(); i++ )
  {
    insert_no_copy( (*i) );
  }
}

Surface const &
Surface::
first() const
{
  // NOTE: invalid cast (assumes _ is the first member of geom::Surface
  return *(Surface const *)first(_);
}
#endif

void 
Surface::
read( ::io::Istream &stream,
      FileMode filemode )
  throw (::io::ReadException)
{
  _->read(stream, geom::FileMode(filemode));
}

void
Surface::
read(
  ::io::Istream &stream,
  ::milieu::kernel::MilieuBase &M,
  FileMode filemode )
  throw (::io::ReadException)
{
  _->read(stream, M, geom::FileMode(filemode));
}

void
Surface::
write(
  ::io::Ostream &stream,
  FileMode filemode ) const
  throw (::io::ReadException )
{
  _->write(stream, geom::FileMode(filemode));
}

void
Surface::
write(
  ::io::Ostream &stream,
  uint normals, uint colors,
  milieu::kernel::MilieuBase const &milieu,
  FileMode filemode ) const
  throw (::io::WriteException)
{
  _->
    write(stream, normals, colors, milieu,
          geom::FileMode(filemode) );
}

void
Surface::
transform( Transform const &a )
{
  _->transform(a);
}

void
Surface::
translate( math::VectorX<Real,3U> const &a )
{
  _->translate(a);
}

void
Surface::
reflect( math::VectorX<Real,4U> const &a )
{
  _->reflect(a);
}

void
Surface::
build_reflect( math::VectorX<Real,4U> const &a )
{
  _->build_reflect(a);
}

void
Surface::
reverse_orientation()
{
  _->reverse_orientation();
}

Real
Surface::
glue(
  uint part1, uint part2,
  std::list<uint> const &boundaryset )
{
  return _->glue(  part1, part2, boundaryset );
}

Real
Surface::
glue(
  uint part,
  std::list<uint> const &boundaryset1,
  std::list<uint> const &boundaryset2 )
{
  return _->glue_self( part, boundaryset1, boundaryset2 );
}

void
Surface::
remove_to_one()
{
  _->remove_to_one();
}

void
Surface::
relax( uint iterations )
{
  _->relax(iterations);
}

void
Surface::
color_original( base::Color4 const &p )
{
  first(_)->color_original(p);
}

void
Surface::
color_by_normal( base::Color4 const &p )
{
  first(_)->color_by_normal(p);
}

void
Surface::
color_by_direction( base::Color4 const &p )
{
  first(_)->color_by_direction(p);
}

void
Surface::
color_by_distance( base::Color4 const &p, float scale )
{
  first(_)->color_by_distance(p, scale);
}

void
Surface::
color_by_area( base::Color4 const &p, float scale )
{
  first(_)->color_by_area(p, scale);
}

void
Surface::
color_by_gaussian_curvature(
    base::Color4 const &p, float scale )
{
  first(_)->color_by_gaussian_curvature(p, scale);
}

void
Surface::
color_by_mean_curvature(
    base::Color4 const &p, float scale )
{
  first(_)->color_by_mean_curvature(p, scale);
}

void
Surface::
color_randomly( base::Color4 const &p )
{
  first(_)->color_randomly(p);
}

void
Surface::
color_checked( base::Color4 const &c0, base::Color4 const &c1 )
{
  first(_)->color_checked(c0, c1);
}

void
Surface::
alpha_fade( float alpha, float scale )
{
  first(_)->alpha_fade(alpha, scale);
}

geom::Box const &
Surface::
box() const
{
  return _->box();
}

void
Surface::
colorData(
  uint &mode,
  base::Color4 &color0,
  base::Color4 &color1,
  float &scale )
{
  first(_)->colorData(mode, color0, color1, scale);
}

bool
Surface::
has_original_color() const
{
  return first(_)->has_original_color();
}

uint
Surface::
i_count() const
{
  return first(_)->i_count();
}

uint
Surface::
j_count() const
{
  return first(_)->j_count();
}

uint
Surface::
i_begin() const
{
  return first(_)->i_begin();
}

uint
Surface::
i_step() const
{
  return first(_)->i_step();
}

uint
Surface::
j_begin() const
{
  return first(_)->j_begin();
}

uint
Surface::
j_step() const
{
  return first(_)->j_step();
}

void
Surface::
reset_clip()
{
  first(_)->reset_clip();
}

void
Surface::
set_clip(
    uint i_begin, uint i_step,
    uint j_begin, uint j_step )
{
  first(_)->set_clip( i_begin, i_step, j_begin, j_step );
}

void
Surface::
get_clip(
    uint &i_begin, uint &i_step,
    uint &j_begin, uint &j_step ) const
{
  first(_)->get_clip( i_begin, i_step, j_begin, j_step );
}


bool const &
Surface::
enable(uint id) const
{
  return _->enable(id);
}

void
Surface::
enable( uint id, bool a )
{
  _->enable(id, a);
}

bool const &
Surface::
shademodel(uint id) const
{
  return _->shademodel(id);
}

void
Surface::
shademodel( uint id, bool a )
{
  _->shademodel(id, a);
}

uint const &
Surface::
model(uint id) const
{
  return _->model(id);
}

void
Surface::
model( uint id, uint a )
{
  _->model(id, a);
}

float const &
Surface::
element_size(uint id) const
{
  return _->element_size(id);
}

void
Surface::
element_size( uint id, float a )
{
  _->element_size(id, a);
}

base::ArrayX<float,2U> const &
Surface::
gap(uint id) const
{
  return _->gap(id);
}

void
Surface::
gap( uint id, base::ArrayX<float,2U> const &a )
{
  _->gap(id, a);
}

base::Color4 const &
Surface::
color(uint id) const
{
  return _->color(id);
}

void
Surface::
color( uint id, base::Color4 const &a )
{
  _->color(id, a);
}

base::Color3 const &
Surface::
ambient(uint id) const
{
  return _->ambient(id);
}

void
Surface::
ambient( uint id, base::Color3 const &a )
{
  _->ambient(id, a);
}

base::Color4 const &
Surface::
diffuse(uint id) const
{
  return _->diffuse(id);
}

void
Surface::
diffuse( uint id, base::Color4 const &a )
{
  _->diffuse(id, a);
}

base::Color3 const &
Surface::
specular(uint id) const
{
  return _->specular(id);
}

void
Surface::
specular( uint id, base::Color3 const &a )
{
  _->specular(id, a);
}

base::Color3 const &
Surface::
emissive(uint id) const
{
  return _->emissive(id);
}

void
Surface::
emissive( uint id, base::Color3 const &a )
{
  _->emissive(id, a);
}

float const &
Surface::
shininess(uint id) const
{
  return _->shininess(id);
}

void
Surface::
shininess( uint id, float a )
{
  _->shininess(id, a);
}

base::ArrayX<uint,2U> const &
Surface::
side( uint id ) const
{
  return _->side(id);
}

void
Surface::
side( uint id, base::ArrayX<uint,2U> const &a )
{
  _->side(id, a);
}

base::ArrayX<float,2U> const &
Surface::
nudge(uint id ) const
{
  return _->nudge(id);
}

void
Surface::
nudge( uint id, base::ArrayX<float,2U> const &a )
{
  _->nudge(id, a);
}

bool const &
Surface::
lit( uint id ) const
{
  return _->lit(id);
}

void
Surface::
lit( uint id, bool a )
{
  _->lit(id, a);
}

bool const &
Surface::
transparent( uint id ) const
{
  return _->transparent(id);
}

void
Surface::
transparent( uint id, bool a )
{
  _->transparent(id, a);
}

bool const &
Surface::
custom_color( uint id ) const
{
  return _->custom_color(id);
}

void
Surface::
custom_color( uint id, bool a )
{
  _->custom_color(id, a);
}

uint
Surface::
material_count()
{
  return geom::surface::MaterialSetBase::count();
}

void
Surface::
materials( Surface const &x )
{
  _->materials( *x._ );
}

void
Surface::
reset_material()
{
  _->reset_materials();
}

void
Surface::
reset_material(uint id)
{
  _->reset_materials(id);
}

void
Surface::
import( base::vector<base::vector<base::vector<Real> > > const &vertex,
               SpaceForm const &spaceform )
{
  clear();
  geom::surface0::Surface *g = new geom::surface0::Surface;
  g->import(vertex, *(geom::SpaceForm *)&spaceform);
  _->insert_no_copy(g);
}

void
Surface::
import( base::vector<Vertex2> const &vertex,
               base::vector<base::vector<uint> > const &face,
               SpaceForm const &spaceform )
{
  clear();
  geom::surface0::Surface *g = new geom::surface0::Surface;
  g->import( vertex, face, *(geom::SpaceForm *)&spaceform );
  _->insert_no_copy(g);
}

void
Surface::
import( base::vector<base::vector<Real> > const &vertex,
               base::vector<base::vector<uint> > const &face,
               SpaceForm const &spaceform )
{
  clear();
  geom::surface0::Surface *g = new geom::surface0::Surface;
  g->import( vertex, face, *(geom::SpaceForm *)&spaceform );
  _->insert_no_copy(g);
}

void
Surface::
import_lines(
  std::list<std::list<uint> > const &line )
{
  first(_)->import_lines(line);
}

void
Surface::
import_boundary_lines( std::list<std::list<uint> > const &corner )
{
  first(_)->import_boundary_lines(corner);
}

void
Surface::
compute_face_area() const
{
  first(_)->compute_face_area();
}

void
Surface::
compute_gaussian_curvature() const
{
  first(_)->compute_gaussian_curvature();
}

base::vector<base::vector<uint> > const &
Surface::face_data() const
{
  return first(_)->face_data();
}

uint
Surface::
face_count(uint i) const
{
  return first(_)->face_count(i);
}

uint
Surface::
face_vertex(uint i, uint j) const
{
  return first(_)->face_vertex(i, j);
}

Real
Surface::
face_gaussian_curvature(uint i) const
{
  return first(_)->face_gaussian_curvature(i);
}

base::String const &
Surface::
name() const
{
  return _->name();
}

void
Surface::
name( base::String const &s )
{
  _->name(s);
}

void
Surface::
compute_boundary() const
{
  first(_)->compute_boundary();
}

std::list<std::list<uint> > const &
Surface::
line() const
{
  return first(_)->line();
}

void
Surface::
boundary( std::list<std::list<std::pair<uint,uint> > > &b ) const
{
  first(_)->boundary(b);
}

} // namespace geom
