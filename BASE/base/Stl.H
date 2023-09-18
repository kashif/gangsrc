/* GANG Software
 * BASE/base/Stl.H
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

#ifndef base_Stl_INCLUDED
#define base_Stl_INCLUDED

#include "vector.H"

namespace base {

#if 0
/*
   fill a base::vector with 'count' 'points'.
*/

template<class A>
void
fill( base::vector<A> &vect, A const &point, size_t count )
{
  vect.clear();
  vect.reserve(count);
  vect.insert( vect.end(), count, point );
#if 0
  size_t i;
  for ( i = 0; i < count; i++ )
  {
    vect.push_back(point);
  }
#endif
}
#endif

/*
   fill a matrix with 'i_count'-by-'j_count' 'points'.
*/

template<class A>
void
fill( base::vector<base::vector<A> > &matrix, A const &point,
                 size_t i_count, size_t j_count )
{
  matrix.clear();
  matrix.reserve(i_count);

  base::vector<A> vect;
  vect.fill( point, j_count );
  matrix.fill( vect, i_count );
}

} // namespace base

#endif // base_Stl_INCLUDED
