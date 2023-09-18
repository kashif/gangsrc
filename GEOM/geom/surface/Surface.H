/* GANG Software
 * GEOM/geom/surface/Surface.H
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

#ifndef geom_surface_Surface_INCLUDED
#define geom_surface_Surface_INCLUDED

#include "MaterialSet.H"
#include "Construct.H"

namespace geom {
namespace surface {

class Surface
  :
    public Construct,
    public MaterialSet
{

public:
  // constructor
  Surface();

  // copy constructor
  Surface( Surface const & );
  Surface( Construct const & );

  // destructor
  virtual ~Surface();

  // assignment operator
  Surface &operator=( Surface const & );

  virtual Material &operator[](uint n)
    { return MaterialSet::operator[](n); }
  virtual Material const &operator[](uint n) const
    { return MaterialSet::operator[](n); }

protected:

private:

};

} // namespace surface
} // namespace geom

#endif // geom_surface_Surface_INCLUDED
