/* GANG Software
 * GEOM/geom/surface0/BoundingBox.C
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

#include "Surface.H"
#include "BoundingBox.H"

namespace geom {
namespace surface0 {

BoundingBox::
BoundingBox()
    :
    Box(),
    _computed(false)
{
  clear();
}

BoundingBox::
BoundingBox( BoundingBox const &b )
    :
    Box( b ),
    _computed(false)
{
}

BoundingBox &
BoundingBox::
operator=( BoundingBox const &b )
{
  if (this == &b) { return *this; }
  _computed = false;
  BoundingBox::operator=(b);
  return *this;
}

void
BoundingBox::
box( Box &b ) const
{
  b = static_cast<Box>(*this);
}

void
BoundingBox::
clear()
{
  _computed = false;
  xmin = 0.0f;
  xmax = 0.0f;
  ymin = 0.0f;
  ymax = 0.0f;
  zmin = 0.0f;
  zmax = 0.0f;
}

void
BoundingBox::
compute( GeomObject const *g_, bool force )
{
  if ( _computed && !force) { return; }

  if ( g_->dimension() != 2U ) { return; }

  Surface const *g = static_cast<Surface const *>(g_);

  // return cached bounding box data
  // NOTE: when surface is changed, this doesn't get updated
  //  if (! force && _computed) { return; }

  uint vertex_count_ = g->vertex_count();

  if ( vertex_count_ == 0U )
  {
    WARN( "empty Surface");
    clear();
    return;
  }

  initialize();

  Vertex3 v;

  uint i;
  for ( i = 0; i < vertex_count_; i++ )
  {
    g->vertex( v, i );
    merge( v.x, v.x, v.y, v.y, v.z, v.z );
  }
}

void
BoundingBox::
compute( std::list<GeomObject *> const &L, bool force )
{
  if ( _computed && !force) { return; }

  if (L.empty())
  {
    WARN( "empty GeomObject");
    clear();
    return;
  }

  initialize();

  std::list<surface0::GeomObject *>::const_iterator i;
  for ( i = L.begin(); i != L.end(); i++ )
  {
    if ( (*i)->dimension() != 2U ) { continue; }
    Surface const *g = static_cast<Surface const *>(*i);

    // update *this's boundaries
    merge( g->box() );
  }
}

void
BoundingBox::
initialize()
{
  Real M;
  if (sizeof(Real)==sizeof(double))
  {
    M = DBL_MAX;
  }
  else if (sizeof(Real)==sizeof(float))
  {
    M = FLT_MAX;
  }
  else
  {
    DIE();
  }

  xmin = M;
  xmax = -M;
  ymin = M;
  ymax = -M;
  zmin = M;
  zmax = -M;
//  _computed = true;
}

void
BoundingBox::
merge( Box const &b )
{
  merge( b.xmin, b.xmax, b.ymin, b.ymax, b.zmin, b.zmax );
}

void
BoundingBox::
merge(
  Real xmin_, Real xmax_, Real ymin_, Real ymax_, Real zmin_, Real zmax_ )
{
  if ( xmin_ < xmin ) { xmin = xmin_; }
  if ( xmax_ > xmax ) { xmax = xmax_; }
  if ( ymin_ < ymin ) { ymin = ymin_; }
  if ( ymax_ > ymax ) { ymax = ymax_; }
  if ( zmin_ < zmin ) { zmin = zmin_; }
  if ( zmax_ > zmax ) { zmax = zmax_; }
}

} // namespace surface0
} // namespace geom
