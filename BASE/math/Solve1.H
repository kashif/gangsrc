/* GANG Software
 * BASE/math/Solve1.H
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

#ifndef math_Solve1_INCLUDED
#define math_Solve1_INCLUDED

#include <float.h>

namespace math {

class Solve1
{

public:
  // constructor
  Solve1();

  // destructor
  virtual ~Solve1();

  void solve(
    double &x,
    double &y,
    uint &status,
    double x1,
    double x2,
    double tol,
    uint max_iter);


  // number of iterations of last solve
  uint iterations() const
    { return _iteration; }

  // set tracing
  bool trace() const
    { return _trace; }
  void trace(bool state)
    { _trace = state; }

protected:

  virtual double f( double ) = 0;

private:

  static double adjust_sign( double x, double s );

  uint _iteration;
  bool _trace;
  static double const rel_precision = 4 * DBL_EPSILON;

  // disabled copy constructor
  Solve1( Solve1 const & );
  // disabled assignment operator
  Solve1 &operator=( Solve1 const & );

};

} // namespace math

#endif // math_Solve1_INCLUDED
