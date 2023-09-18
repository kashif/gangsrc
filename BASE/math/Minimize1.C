/* GANG Software
 * BASE/math/Minimize1.C
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

#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include "Math.H"
#include "Minimize1.H"

namespace math {

double const minimize1::smallreal_double = 100 * DBL_MIN;

minimize1::
minimize1()
{
  _precision_goal = 1.0e-6;
  _accuracy_goal = 1.0e-12;
  _iteration_limit = 100;
  _iteration_count = 0;
}

minimize1::
~minimize1()
{
}

int
minimize1::
find_minimum(
  double &x_,
  double &y_,
  double ax,
  double bx,
  double cx )

{
  static double const golden = 0.5*(3.0 - sqrt(5.0));
  double tmp_a;
  double tmp_b;
  double tmp_c;

  int status = MINIMIZE_OK;

  double a, b, d=0.0, etemp, fu, fv, fw, fx, p, q, r,
    tol, u, v, w, x, xm;
  double e = 0.0;

  x_ = 0.0;
  y_ = 0.0;

  // check input
  if ( !( (ax < bx && bx < cx)||(ax > bx && bx > cx) ) )
  {
    // b is not between a and c
    status = MINIMIZE_INPUT_NOT_SORTED;
    goto end;
  }
  // this is inefficient:
  tmp_a = function(ax);
  tmp_b = function(bx);
  tmp_c = function(cx);
  if ( !( tmp_b < tmp_a && tmp_b < tmp_c ) )
  {
    // function is not bracketed
    status = MINIMIZE_INPUT_NOT_BRACKETED;
    goto end;
  }

  a = (ax < cx ? ax : cx);
  b = (ax > cx ? ax : cx);
  x = w = v = bx;
  fw = fv = fx = function(x);

  while( _iteration_count < _iteration_limit )
  {
    xm = 0.5 * (a + b);
    tol = std::max(_precision_goal * math::abs(x), smallreal_double);
    if (
      fabs(x - xm) <= (2.0*tol - 0.5 * (b - a))
      ||
      fabs(x - xm) <= _accuracy_goal
      )
    {
      x_ = x;
      y_ = fx;
      // found minimum
      goto end;
    }
    if (fabs(e) > tol)
    {
      // construct a trial parabolic fit
      r = (x - w) * (fx - fv);
      q = (x - v) * (fx - fw);
      p = (x - v) * q - (x - w) * r;
      q = 2.0 * (q - r);
      if (q > 0.0)
      {
	p = -p;
      }
      q = fabs(q);
      etemp = e;
      e = d;
      if (fabs(p) >= fabs(0.5 * q * etemp) ||
          p <= q * (a - x) || p >= q * (b - x))
      {
	d = golden * (e = (x >= xm ? a - x : b - x));
      }
      else
      {
        // take parabolic step
	d = p / q;
	u = x + d;
	if (u - a < 2.0*tol || b - u < 2.0*tol)
        {
	  d = sign_adjust(tol, xm - x);
        }
      }
    }
    else
    {
      d = golden * (e = (x >= xm ? a - x : b - x));
    }
    u = (fabs(d) >= tol ? x + d : x + sign_adjust(tol, d));
    fu = function(u);
    if (fu <= fx)
    {
      if (u >= x)
      {
	a = x;
      }
      else
      {
	b = x;
      }
      shift(v, w, x, u);
      shift(fv, fw, fx, fu);
    }
    else
    {
      if (u < x)
      {
	a = u;
      }
      else
      {
	b = u;
      }
      if (fu <= fw || w == x)
      {
	v = w;
	w = u;
	fv = fw;
	fw = fu;
      }
      else if (fu <= fv || v == x || v == w)
      {
	v = u;
	fv = fu;
      }
    }
    _iteration_count++;
  }
  status = MINIMIZE_ITERATION_LIMIT_EXCEEDED;

  end:
  return (int)status;
}

} // namespace math
