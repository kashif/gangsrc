/* GANG Software
 * BASE/math/Math.C
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

#include "Math.H"

namespace math {

#ifdef M_PI
double const pi = M_PI;
#else
double const pi = acos(-1.0);
#endif

// factorial
// this function is not thread-safe

double
factorial( uint n )
{
  static double const fact[] = {
    1.0000000000000000e00,  // 0!
    1.0000000000000000e00,
    2.0000000000000000e00,
    6.0000000000000000e00,
    2.4000000000000000e01,
    1.2000000000000000e02,
    7.2000000000000000e02,
    5.0400000000000000e03,
    4.0320000000000000e04,
    3.6288000000000000e05,
    3.6288000000000000e06,
    3.9916800000000000e07,
    4.7900160000000000e08,
    6.2270208000000000e09,
    8.7178291200000000e10,
    1.3076743680000000e12,
    2.0922789888000000e13,
    3.5568742809600000e14,
    6.4023737057280000e15,
    1.2164510040883200e17,
    2.4329020081766400e18,
    5.1090942171709440e19,
    1.1240007277776077e21,
    2.5852016738884977e22,
    6.2044840173323944e23,
    1.5511210043330986e25  // 25!
  };
  double const FACTORIAL_OVERFLOW = -1.0;
  USE(FACTORIAL_OVERFLOW);

  if ( n <= 25 ) { return fact[n]; }

  double y = gamma( double(n)+1 );

#if defined(LN_MAXDOUBLE)
  return ( y > LN_MAXDOUBLE ? FACTORIAL_OVERFLOW : signgam * exp(y) );
#else
  return signgam * exp(y);
#endif
}

} // namespace math
