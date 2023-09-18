/* GANG Software
 * GEOM/geom/surface0/TransformerMatrix.C
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

#include "TransformerMatrix.H"

namespace geom {
namespace surface0 {

// static member of TransformerMatrix
TransformerMatrix::
TransformerMatrix( math::Matrix<Real> const &a )
    :
    _a()
{
  DIE_IF(a.dim() != 4U);
  uint i;
  for (i = 0; i < 4; i++)
  {
    uint j;
    for (j = 0; j < 4; j++)
    {
      _a[i][j] = a[i][j];
    }
  }

}

void
TransformerMatrix::
function( math::VectorX<Real,4U> &x ) const
{
  _a.mul(x);
}

} // namespace surface0
} // namespace geom
