/* GANG Software
 * BASE/math/Solve1.C
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
#include <iostream>
#include <algorithm>
#include "base/PrintNumber.H"
#include "Solve1.H"

namespace math {

Solve1::
Solve1()
    :
    _iteration(0U),
    _trace(false)
{
}

Solve1::
~Solve1()
{
}

void
Solve1::
solve(
  double &x,
  double &y,
  uint &status,
  double x1,
  double x2,
  double tol,
  uint max_iter)
{
  uint i = 0;
  double a = x1;
  double b = x2;
  double c = x2;
  double d=0.0, e=0.0, min1, min2;
  double fa = f(a);
  double fb = f(b);
  double fc, p, q, r, s, tol1, xm;

  uint method = 0;
  if (_trace)
  {
    std::cout.width(4);
    std::cout << 1 << "  ";
    std::cout << "(";
    base::print( std::cout, a );
    base::print( std::cout, fa );
    std::cout << ")\n";
    std::cout.width(4);
    std::cout << 2 << "  ";
    std::cout << "(";
    base::print( std::cout, a );
    base::print( std::cout, fa );
    std::cout << ")\n";
  }

  status = 0;
  x = 0.0;
  y = 0.0;

  if ((fa > 0.0 && fb > 0.0) || (fa < 0.0 && fb < 0.0))
  {
    // root not bracketed
    status = 1;
  }
  else
  {
    fc = fb;
    for (i = 0; i < max_iter; i++)
    {
      if ((fb > 0.0 && fc > 0.0) || (fb < 0.0 && fc < 0.0))
      {
        c = a;
        fc = fa;
        e = d = b - a;
      }
      if (fabs(fc) < fabs(fb))
      {
        a = b;
        b = c;
        c = a;
        fa = fb;
        fb = fc;
        fc = fa;
      }
      // convergence check
      tol1 = 2.0 * rel_precision * fabs(b) + 0.5 * tol;
      xm = 0.5 * (c - b);
      if (fabs(xm) <= tol1 || fb == 0.0)
      {
        r = true;
        x = b;
        y = fb;
        break;
      }
      if (fabs(e) >= tol1 && fabs(fa) > fabs(fb))
      {
        // inverse quadratic interpolation
        s = fb / fa;
        if (a == c)
        {
          p = 2.0 * xm * s;
          q = 1.0 - s;
        }
        else
        {
          q = fa / fc;
          r = fb / fc;
          p = s * (2.0 * xm * q * (q - r) - (b - a) * (r - 1.0));
          q = (q - 1.0) * (r - 1.0) * (s - 1.0);
        }
        if (p > 0.0)
        {
          q = -q;
        }
        p = fabs(p);
        min1 = 3.0 * xm * q - fabs(tol1 * q);
        min2 = fabs(e * q);
        if (2.0 * p < std::min( min1, min2 ))
        {
          // interpolation succeeded
          e = d;
          d = p / q;
          method = 2;
        }
        else
        {
          // interpolation failed: use bisection
          d = xm;
          e = d;
          method = 1;
        }
      }
      else
      {
        // bounds decreasing too slowly, use bisection
        d = xm;
        e = d;
        method = 1;
      }
      a = b;
      fa = fb;
      if (fabs(d) > tol1)
      {
        b += d;
      }
      else
      {
        b += adjust_sign(tol1, xm);
      }
      fb = f(b);
      if (_trace) {
        std::cout.width(4);
        std::cout << i + 3 << "  ";
        std::cout << "(";
        base::print( std::cout, b );
        base::print( std::cout, fb );
        std::cout << ")";
        char *m = "?";
        if ( method == 1 ) { m = "bisection"; }
        if ( method == 2 ) { m = "quadratic"; }
        std::cout << "  " << m << std::endl;
        method = 0;
      }
    }
    if ( i == max_iter ) { status = 2; }
  }
  _iteration = i;
}

inline
double
Solve1::
adjust_sign( double x, double s )
{
  // return the number with absolute value x and sign of s
  return( s >= 0.0 ? fabs(x) : -fabs(x) );
}

} // namespace math
