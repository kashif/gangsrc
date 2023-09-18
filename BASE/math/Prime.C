/* GANG Software
 * BASE/math/Prime.C
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

#include <math.h>
#include "Prime.H"

namespace math {

/*
  returns least factor
  */
int unsigned long factor(int unsigned long n)
{
  if (n <= 1) { return 1; }

  if (!(n & 1)) { return 2; }

  if (!(n % 3)) { return 3; }

  int unsigned long s = (int)sqrt((double)n);
  int unsigned long c = 2;
  int unsigned long d = 2;
  int unsigned long i = 5;

  while (i <= s)
  {
    if (!(n % i)) { return i; }
    i += d;
    d += c;
    c = -c;
  }
  return n;
}

} // namespace math
