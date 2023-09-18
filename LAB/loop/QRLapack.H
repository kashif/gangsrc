/* GANG Software
 * LAB/loop/QRLapack.H
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

#ifndef loop_QRLapack_INCLUDED
#define loop_QRLapack_INCLUDED

#include <complex>
#include "base/ArrayP.H"
#include "Common.H"

namespace loop {

/*
  Compute Projection via QR decomposition using LAPACK.
*/

class QRLapack
{

public:

  // constructor
  QRLapack( uint rows, uint cols);

  // perform QR decomposition on A. Modifies A.
  void factor( base::ArrayP<Complex> &A )
    throw (int);

  // find the orthogonal complement of B re the space spanned by A
  // A is the output of factor()
  void projection(
    base::ArrayP<Complex> const &A,
    base::ArrayP<Complex> &B,
    uint Bcols )
    throw (int);

protected:

  //
  uint _rows;
  //
  uint _cols;

  typedef Complex complex2F;
  base::ArrayP<complex2F> TAU;
  base::ArrayP<complex2F> WORK;

  //
  QRLapack( QRLapack const & );
  //
  QRLapack &operator=( QRLapack const & );
};

} // namespace loop

#endif // loop_QRLapack_INCLUDED
