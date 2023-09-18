/* GANG Software
 * GEOM/geom/surface0/BoundingBox.H
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

#ifndef geom_surface0_BoundingBox_INCLUDED
#define geom_surface0_BoundingBox_INCLUDED

#include <list>
#include "Common.H"
#include "GeomObject.H"

namespace geom {
namespace surface0 {

class GeomObject;

class BoundingBox
  :
    public Box
{

public:
  BoundingBox();
  BoundingBox( BoundingBox const & );
  virtual ~BoundingBox() {}
  BoundingBox &operator=( BoundingBox const & );

  void box( Box &b ) const;
  void compute( GeomObject const *, bool force = false );
  void compute( std::list<GeomObject *> const &, bool force = false );

  void clear();
  void initialize();

  void merge( Box const & );
  void merge( Real xmin, Real xmax,
              Real ymin, Real ymax,
              Real zmin, Real zmax );

protected:

private:

  bool _computed;

};

} // namespace surface0
} // namespace geom

#endif // geom_surface0_BoundingBox_INCLUDED
