/* GANG Software
 * LAB/loop/Birkhoff.H
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

#ifndef loop_Birkhoff_INCLUDED
#define loop_Birkhoff_INCLUDED

#include "base/System.H"
#include "base/ArrayP.H"
#include "Common.H"
#include "loop/Loop4.H"
#include "loop/LULapack.H"

namespace loop {

//using namespace ::loop::kernel;

class Birkhoff
{

public:

  // constructor
  // polylen is the size of the input loop (highest exponent)
  Birkhoff( uint polylen, bool upper_triangular_correction );

  // destructor
  virtual ~Birkhoff();

  /* Performs Birkhoff factorization X = X- * X+.
     Returns the "minus" part X- in X_minus.
     Returns 0 iff no error.
  */
  void factor_minus_plus( Loop4 &X_minus, Loop4 const &X );

  /* Performs Birkhoff factorization X = X+ * X-.
     Returns the "plus" part X+ in X_plus.
     Returns 0 iff no error.
  */
  void factor_plus_minus( Loop4 &X_plus, Loop4 const &X );

protected:

private:

  // polylen is the size of the input loop (highest exponent)
  uint _polylen;
  bool _upper_triangular_correction;

  Loop4 *_T;
  Loop4 *_R;

  base::ArrayP<Complex> _Ax;
  base::ArrayP<Complex> _Bx;

  LULapack *_LU;

  void setup_A( Loop4 const &X );
  void setup_B();
  void setup_T() const;

  void
  upper_triangular_correction(
    Loop4 &X, Loop4 const &R );

  // disabled copy constructor
  Birkhoff( Birkhoff const & );

  // disabled assignment operator
  Birkhoff &operator=( Birkhoff const & );

};

} // namespace loop

#endif // loop_Birkhoff_INCLUDED
