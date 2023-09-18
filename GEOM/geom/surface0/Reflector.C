/* GANG Software
 * GEOM/geom/surface0/Reflector.C
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

#include "Reflector.H"

namespace geom {
namespace surface0 {

// static member of Reflector
Reflector::
Reflector( math::VectorX<Real,4U> const &a )
    :
    _a(a),
    _norm(math::norm(a[0], a[1], a[2]))
{
}

void
Reflector::
function( math::VectorX<Real,4U> &x ) const
{
  /*
    replaces 'x' with its reflection across the plane 'a'
      reflected_point = <pa,pa>x - 2<a,x>pa,
      where pa is the projection of a to the first three coordinates
      p(a0,a1,a2,a3)=(a0,a1,a2,0)
      note that a is normalized so that <pa,pa>=1
  */

  Real q = -2.0 * _a.dot(x);
  x *= _norm;
  x[0] += q * _a[0];
  x[1] += q * _a[1];
  x[2] += q * _a[2];

  // hack
  x[0] /= x[3];
  x[1] /= x[3];
  x[2] /= x[3];
}

} // namespace surface0
} // namespace geom
