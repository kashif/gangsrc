/* GANG Software
 * GEOM/geom/surface0/Vertex.C
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

#include "Vertex.H"


namespace geom {
namespace surface0 {

std::ostream &
operator<<( std::ostream &o, Vertex const &v )
{
  uint i;
  o << "{";
  for ( i = 0; i < v._spaceform.dim; i++ )
  {
    o << v._x[i] << ", ";
  }
  o << v._xp << ", " << v._x0 << ", " << v._xi << "}";
  return o;
}

void
Vertex::
mulleft( Real const *a, Real *b, uint k )
{
  // compute b := b * a
  //   a is a k-by-k matrix
  //   b is a k-vector

  if ( k == 4 )
  {
    uint const n = 4U;
    Real c[n];

    uint j;
    for ( j = 0; j < n; j++ )
    {
      c[j] = 0.0f;
      uint i;
      for ( i = 0; i < n; i++ )
      {
        c[j] += b[i] * a[n*i + j];
      }
    }
    uint i;
    for ( i = 0; i < n; i++ )
    {
      b[i] = c[i];
    }
  }
  else if ( k == 5 )
  {
    uint const n = 5U;
    Real c[n];

    uint j;
    for ( j = 0; j < n; j++ )
    {
      c[j] = 0.0f;
      uint i;
      for ( i = 0; i < n; i++ )
      {
        c[j] += b[i] * a[n*i + j];
      }
    }
    uint i;
    for ( i = 0; i < n; i++ )
    {
      b[i] = c[i];
    }
  }
  else if ( k == 6 )
  {
    uint const n = 6U;
    Real c[n];

    uint j;
    for ( j = 0; j < n; j++ )
    {
      c[j] = 0.0f;
      uint i;
      for ( i = 0; i < n; i++ )
      {
        c[j] += b[i] * a[n*i + j];
      }
    }
    uint i;
    for ( i = 0; i < n; i++ )
    {
      b[i] = c[i];
    }
  }
  else
  {
    DIE();
  }
}

} // namespace surface0
} // namespace geom
