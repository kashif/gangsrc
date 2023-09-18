/* GANG Software
 * BASE/math/Romberg.C
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

#include <algorithm>
#include "Romberg.H"

namespace math {

int
integrate_romberg( double x0, double x1,
                   double (*f)(double), double eps,
                   double &integral )
{
  double h = fabs(0.25 * (x1 - x0 ) );
  uint m = 17;
  double error;
  int err =
    integrate_romberg( x0, x1, f, eps, h, m, integral, error, h, m );
  return err != 0;
}


int
integrate_romberg( std::complex<double> &x0, std::complex<double> &x1,
                   std::complex<double> (*f)(std::complex<double>),
                   double eps,
                   std::complex<double> &integral )
{
  double h = std::abs(0.25 * (x1 - x0 ) );
  uint m = 17;
  double error;
  int err =
    integrate_romberg( x0, x1, f, eps, h, m, integral, error, h, m );
  return err != 0;
}

} // namespace math
