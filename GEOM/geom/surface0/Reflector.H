/* GANG Software
 * GEOM/geom/surface0/Reflector.H
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

#ifndef geom_surface0_Reflector_INCLUDED
#define geom_surface0_Reflector_INCLUDED

#include "Transformer.H"

namespace geom {
namespace surface0 {

class Reflector
  :
    public Transformer
{

public:
  // constructor
  Reflector( math::VectorX<Real,4U> const &a );

  // destructor
  virtual ~Reflector() {}

  virtual void function( math::VectorX<Real,4U> &x ) const;
  
private:

  /* _a represents the plane
     _a[0] x[0] + _a[1] x[1] + _a[2] x[2] + _a[3] x[3] = 0
     _norm = _a[0]^2 + _a[1]^2 + _a[2]^2
  */
  math::VectorX<Real,4U> _a;
  Real _norm;


  // disabled copy constructor
  Reflector( Reflector const & );

  // disabled assignment operator
  Reflector &operator=( Reflector const & );

};

} // namespace surface0
} // namespace geom

#endif // geom_surface0_Reflector_INCLUDED
