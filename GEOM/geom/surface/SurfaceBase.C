/* GANG Software
 * GEOM/geom/surface/SurfaceBase.C
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

#include <fstream>
#include <algorithm>
#include "base/System.H"
#include "base/Regex.H"
#include "geom/io/Read.H"
#include "geom/io/Write.H"
#include "geom/surface0/Surface.H"
#include "milieu/kernel/Milieu.H"
#include "SurfaceBase.H"

namespace geom {
namespace surface {

SurfaceBase::
SurfaceBase()
    :
    MaterialSetBase(),
    _name()
{
}

SurfaceBase::
SurfaceBase( SurfaceBase const &g )
    :
    MaterialSetBase(g),
    _name(g._name)
{
  insert(g);
}

SurfaceBase::
~SurfaceBase()
{
  clear();
}

SurfaceBase &
SurfaceBase::
operator=( SurfaceBase const &g )
{
  if ( this == &g ) { return *this; }
  clear();
  insert(g);
  MaterialSetBase::operator=(g);
  _name = g._name;
  return *this;
}

surface0::Surface *
SurfaceBase::
surface( surface0::GeomObject *s )
{
  DIE_IF( s->dimension() != 2U );
  return static_cast<surface0::Surface *>(s);
}

surface0::Surface const *
SurfaceBase::
surface( surface0::GeomObject const *s )
{
  DIE_IF( s->dimension() != 2U );
  return static_cast<surface0::Surface const *>(s);
}

void
SurfaceBase::
changed() const
{
  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    (*i)->changed(true);
  }
}

void
SurfaceBase::
insert( surface0::GeomObject const &g )
{
  insert_no_copy( new surface0::Surface( *surface(&g) ) );
}

void
SurfaceBase::
insert( std::list<surface0::GeomObject *> const &L )
{
  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = L.begin(); i != L.end(); i++ )
  {
    insert( **i );
  }
}

void
SurfaceBase::
insert( SurfaceBase const &G )
{
  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = G.list().begin(); i != G.list().end(); i++ )
  {
    insert( **i );
  }
}

void
SurfaceBase::
insert_no_copy( surface0::GeomObject *g )
{
  // insert the object
  list().push_back(g);

  // recompute the bounding box
  _box.compute( list() );
}

void
SurfaceBase::
insert_no_copy( std::list<surface0::GeomObject *> const &L )
{
  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = L.begin(); i != L.end(); i++ )
  {
    insert_no_copy( *i );
  }
}

void
SurfaceBase::
read(
  ::io::Istream &stream,
  ::geom::FileMode filemode )
  throw (::io::ReadException)
{
  clear();
  io::read( stream, *this, filemode );
}

void
SurfaceBase::
read(
  ::io::Istream &stream,
  ::milieu::kernel::MilieuBase &M,
  ::geom::FileMode filemode )
  throw (::io::ReadException)
{
  clear();
  io::read( stream, *this, M, filemode );
}

void
SurfaceBase::
write(
  ::io::Ostream &stream,
  uint normals, uint colors,
  milieu::kernel::MilieuBase const &milieu,
  ::geom::FileMode filemode ) const
  throw (::io::WriteException)
{
  io::write( stream, *this, milieu, normals, colors, filemode );
}

void
SurfaceBase::
write(
  ::io::Ostream &stream,
  ::geom::FileMode filemode ) const
  throw (::io::WriteException)
{
  milieu::kernel::Milieu milieu;
  io::write( stream, *this, milieu, false, false, filemode );
}

void
SurfaceBase::
clear()
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    delete *i;
  }
  list().clear();
}

#if 0
void
SurfaceBase::
color_fixed(
  base::Color4 const &p )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( (*i)->dimension() == 2U )
    {
      (*i)->color_fixed( p );
    }
  }
}
#endif
void
SurfaceBase::
color_original(
  base::Color4 const &p )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      surface(*i)->color_original( p );
    }
  }
}

void
SurfaceBase::
color_by_normal(
  base::Color4 const &p )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      surface(*i)->color_by_normal( p );
    }
  }
}

void
SurfaceBase::
color_by_direction(
  base::Color4 const &p )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      surface(*i)->color_by_direction( p );
    }
  }
}

void
SurfaceBase::
color_by_distance(
  base::Color4 const &p, float scale )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      surface(*i)->color_by_distance( p, scale );
    }
  }
}

void
SurfaceBase::
color_by_area(
  base::Color4 const &p, float scale )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      surface(*i)->color_by_area( p, scale );
    }
  }
}

void
SurfaceBase::
color_by_gaussian_curvature(
  base::Color4 const &p, float scale )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      surface(*i)->color_by_gaussian_curvature( p, scale );
    }
  }
}

void
SurfaceBase::
color_by_mean_curvature(
  base::Color4 const &p, float scale )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      surface(*i)->color_by_mean_curvature( p, scale );
    }
  }
}

void
SurfaceBase::
color_randomly(
  base::Color4 const &p )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      surface(*i)->color_randomly( p );
    }
  }
}

void
SurfaceBase::
color_checked(
  base::Color4 const &p0,
  base::Color4 const &p1 )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      if ( surface(*i)->type() == ::geom::surface0::Surface::GRID )
      {
        surface(*i)->color_checked( p0, p1 );
      }
    }
  }
}

void
SurfaceBase::
alpha_fade(
  float alph, float scale )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      surface(*i)->alpha_fade( alph, scale );
    }
  }
}

void
SurfaceBase::
relax( uint iterations )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      surface(*i)->relax( iterations );
    }
  }
}

uint
SurfaceBase::
vertex_count() const
{
  uint a = 0U;
  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      a += surface(*i)->vertex_count();
    }
  }
  return a;
}

uint
SurfaceBase::
edge_count() const
{
  uint a = 0U;
  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      a += surface(*i)->edge_count();
    }
  }
  return a;
}

uint
SurfaceBase::
face_count() const
{
  uint a = 0U;
  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( surface(*i)->dimension() == 2U )
    {
      a += surface(*i)->face_count();
    }
  }
  return a;
}

void
SurfaceBase::
dump( ::io::Ostream &o ) const
{
  MaterialSetBase::dump_materials(o);
}

void
SurfaceBase::
materials( surface::MaterialSetBase const &m )
{
  *static_cast< surface::MaterialSetBase *>(this) = m;
  changed();
}

void
SurfaceBase::
materials( uint n, Material const &m )
{
  static_cast< surface::MaterialSetBase *>(this)->operator[](n) = m;
//  MaterialSet::operator[](n) = m;
  changed();
}

surface::Material const &
SurfaceBase::
materials(uint i) const
{
  return static_cast< surface::MaterialSetBase const *>(this)->operator[](i);
}

geom::Box const &
SurfaceBase::
box() const
{
  _box.compute( list() );
  return _box;
}

surface0::GeomObject *
SurfaceBase::
strip()
{
  DIE_IF( empty() );
  surface0::GeomObject *G = list().front();
  list().erase(list().begin());
  clear();
  return G;
}

void
SurfaceBase::
position( geom::Transform const &x )
{
  std::list<surface0::GeomObject *>::iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    surface(*i)->position(x);
  }
}

void
SurfaceBase::
position( std::list<geom::Transform> &x ) const
{
  x.clear();
  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    x.push_back( (*i)->position() );
  }
}


} // namespace surface
} // namespace geom
