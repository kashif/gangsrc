/* GANG Software
 * GEOM/geom/surfacegl/Surface.C
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
#include "base/System.H"
#include "base/Regex.H"
#include "SurfDrawer.H"
#include "Surface.H"
#include "geom/surface0/Surface.H"

namespace geom {
namespace surfacegl {

Surface::
Surface()
    :
    surface::Construct(),
    surfacegl::MaterialSet()
{
  // NOTE: this must be done here to avoid calling virtuals in the constructor
  MaterialSet::reset_materials();
  _surf_drawer.set_materials( this );
}

Surface::
Surface( Surface const &a )
    :
    surface::Construct(a),
    surfacegl::MaterialSet(a)
{
}

Surface::
~Surface()
{
  clear();
}

Surface &
Surface::
operator=( Surface const &a )
{
  if ( this == &a ) { return *this; }
  MaterialSet::operator=(a);
  surface::SurfaceBase::operator=(a);
  return *this;
}

void
Surface::
materials( surface::MaterialSetBase const &m )
{
  surface::MaterialSetBase::operator=(m);
  changed();
}

void
Surface::
materials( uint n, surface::Material const &m )
{
  static_cast<surface::MaterialSetBase *>(this)->operator[](n) = m;
  changed();
}

void
Surface::
draw() const
{
  // NOTE: id is the compile id for OpenGL
  // id's 1, 2, ... are used
  // This won't work for more than one GeomSurface
  // because another Surface will use the same id's
  // erasing the first

  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( (*i)->dimension() == 2U )
    {
      ::geom::surface0::Surface *s =
          static_cast< ::geom::surface0::Surface *>(*i);
      s->compute_normal();
      s->compute_boundary();
      s->compute_face_center();
      _surf_drawer.draw( *i );
    }
  }
}

void
Surface::
draw(
  geom::Transform const &transform,
  geom::ProjectionMode mode ) const
{
  // draw transformed
  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = list().begin(); i != list().end(); i++ )
  {
    if ( (*i)->dimension() == 2U )
    {
      _surf_drawer.draw( *i, transform, mode );
    }
  }
}

void
Surface::
dump( ::io::Ostream &o ) const
{
  MaterialSet::dump_materials(o);
  geom::surface::SurfaceBase::dump(o);
}

} // namespace surfacegl
} // namespace geom
