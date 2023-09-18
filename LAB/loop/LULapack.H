/* GANG Software
 * LAB/loop/LULapack.H
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

#ifndef loop_LULapack_INCLUDED
#define loop_LULapack_INCLUDED

#include <complex>
#include "base/ArrayP.H"
#include "Common.H"

namespace loop {

class LULapack
{

public:

  // constructor
  LULapack( uint rows, uint cols )
    { _rows = rows; _cols = cols; }

  // destructor
  virtual ~LULapack() {}

  /*
     Performs LU factorization on A, computing A = L U
       where L is lower triangular with 1's on the diagonal,
       and U is upper triangular.
     Upon completion, L and U are packed into A with the diagonal omitted.

     A matrix in Lapack is stored as, e.g.
       a0 a3
       a1 a4
       a2 a5
     i.e. the entries go down the columns (counterintuitive)
  */

  int factor( base::ArrayP<Complex > &A );
  int solve(
    base::ArrayP<Complex > &a,
    base::ArrayP<Complex > &b, uint b_cols );

protected:

  //
  uint _rows;
  //
  uint _cols;

private:

  LULapack( LULapack const & ) { LOOP_DIE(); }
  LULapack &operator=( LULapack const & ) { LOOP_DIE(); return *this; }
};

} // namespace loop

#endif // loop_LULapack_INCLUDED
