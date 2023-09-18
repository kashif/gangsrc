/* GANG Software
 * BASE/math/Minimize2.C
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
#include <limits.h>
#include <math.h>
#include <iostream>
#include "base/System.H"
#include "Math.H"
#include "base/Stl.H"
#include "Minimize1.H"
#include "Minimize2.H"

namespace math {

double const minimize2::smallreal_double = 100 * DBL_MIN;

minimize2::
minimize2( uint dimension )
{
  _dimension = dimension;
  _precision_goal = 1.0e-6;
  _accuracy_goal = 1.0e-12;
  _iteration_limit = 100;
  _iteration_count = 0;
  _gradient_dt = 1.0e-8;
  _powell_dt = 1.0e-4;

  function_1dim_x.fill( 0.0, _dimension );
  function_1dim_dx.fill( 0.0, _dimension );
  function_1dim_tmp.fill( 0.0, _dimension );

  minimize_1dim._parent = this;
  minimize_1dim.set_precision_goal(_precision_goal);
  minimize_1dim.set_accuracy_goal(_accuracy_goal);
  minimize_1dim.set_iteration_limit(_iteration_limit);
}

minimize2::
~minimize2()
{
}

//--------------------------------------------
// minimize by gradient method

int
minimize2::
find_minimum_gradient(
  base::vector<double> &p,
  double &y )
{
  DIE_IF( _accuracy_goal < 0.0 );
  DIE_IF( _precision_goal < 0.0 );

  y = DBL_MAX;

  minimize1::Status status = minimize1::MINIMIZE_OK;
  uint j;
  double gg, gam, fp, dgg;

  base::vector<double> g, h, xi;
  g.fill(0.0, _dimension );
  h.fill(0.0, _dimension );
  xi.fill(0.0, _dimension );

  fp = function(p);

  // NOTE this calls the auto-gradient
  dfunction_auto(xi, p, fp);

  _iteration_count += _dimension + 1;

  for (j = 0; j < _dimension; j++)
  {
    g[j] = -xi[j];
    xi[j] = h[j] = g[j];
  }
  for (;;)
  {

    double y0 = y;
    status = (minimize1::Status)line_minimize( y, p, xi );

    if ( status != minimize1::MINIMIZE_OK )
    {
      // line_minimize return non-zero
      goto end;
    }

    report( y, p );

    if (
      fabs(y0 - y) <=
        std::max(_precision_goal * 0.5*(fabs(y0) + fabs(y)),
                      smallreal_double )
      ||
      fabs(y0 - y) <= _accuracy_goal )
    {
      // minimum found
      goto end;
    }

    fp = y;

    // NOTE this calls the auto-gradient
    dfunction_auto(xi, p, fp);

    _iteration_count += _dimension;

    dgg = gg = 0.0;
    for (j = 0; j < _dimension; j++)
    {
      gg += g[j] * g[j];

      // the following is Polak-Ribiere method (recommended)
      dgg += (xi[j] + g[j]) * xi[j];

      // alternately, the following is Fletcher-Reeves method
      // dgg += xi[j]*xi[j];
    }
    if (gg < smallreal_double )
    {
      // gradient is exactly 0: minimum found
      goto end;
    }
    gam = dgg / gg;
    for (j = 0; j < _dimension; j++)
    {
      g[j] = -xi[j];
      xi[j] = h[j] = g[j] + gam * h[j];
    }
  }
  end:
  return (int)status;
}


// minimize by the gradient method with an internally-provided gradient
int
minimize2::
find_minimum_gradient_auto(
  base::vector<double> &x,
  double &y )
{
  return find_minimum_gradient( x, y );
}



//--------------------------------------------
// minimize by Powell's method

int
minimize2::
find_minimum_powell(
  base::vector<double> &p,
  base::vector<base::vector<double> > &xi,
  double &y )
{
  // xi should be base::filled with direections such as
  //( 0.1, 0.0, 0.0, ...)
  //( 0.1, 0.1, 0.0, ...)
  //( 0.0, 0.1, 0.1, ...)
  // ...

  DIE_IF( _accuracy_goal < 0.0 );
  DIE_IF( _precision_goal < 0.0 );

  minimize1::Status status = minimize1::MINIMIZE_OK;

  uint i, ibig=0, j;
  double del, fp, fptt, t;

  base::vector<double> pt, ptt, xit;
  pt.fill( 0.0, _dimension );
  ptt.fill( 0.0, _dimension );
  xit.fill( 0.0, _dimension );

  y = function(p);
  _iteration_count++;

  for (j = 0; j < _dimension; j++)
  {
    pt[j] = p[j];
  }

  for (;;)
  {
    fp = y;
    del = 0.0;
    for (i = 0; i < _dimension; i++)
    {
      for (j = 0; j < _dimension; j++)
      {
        xit[j] = xi[i][j];
      }
      fptt = y;

      status = (minimize1::Status)line_minimize( y, p, xit );

      if ( status != minimize1::MINIMIZE_OK )
      {
        // line_minimize returned non-zero status
        goto end;
      }

      report( y, p );

      if (fptt - y > del)
      {
        del = fptt - y;
        ibig = i;
      }
    }
    if (
      fabs(fp - y) <=
      std::max(_precision_goal * 0.5*(fabs(fp) + fabs(y)),
                    smallreal_double )
      ||
      fabs(fp - y) <= _accuracy_goal )
    {
      // minimum found
      goto end;
    }


    for (j = 0; j < _dimension; j++)
    {
      ptt[j] = 2.0 * p[j] - pt[j];
      xit[j] = p[j] - pt[j];
      pt[j] = p[j];
    }

    fptt = function(ptt);
    _iteration_count++;

    if (fptt < fp)
    {
      t = 2.0 * (fp - 2.0 * (y) + fptt) * math::sqr(fp - (y) - del) -
        del * math::sqr(fp - fptt);
      if (t < 0.0)
      {
#if 0
        std::cerr << "### jackstep [" << ibig << "]\n";
#endif
        status = (minimize1::Status)line_minimize( y, p, xit );

        if ( status != minimize1::MINIMIZE_OK )
        {
          // line_minimize returned non-zero status
          goto end;
        }

        report( y, p );

        // xi[ibig] <- xi[n-1]
        // xi[n-1] <- xit
        for (j = 0; j < _dimension; j++)
        {
          xi[ibig][j] = xi[_dimension-1][j];
          xi[_dimension-1][j] = xit[j];
        }
      }
    }
  }
  end:
  return (int)status;
}


int
minimize2::
find_minimum_powell(
  base::vector<double> &x,
  double &y )
{
  base::vector<base::vector<double> > dx;
  base::fill( dx, double(0.0), _dimension, _dimension );

  uint i;
  for ( i = 0; i < _dimension; i++ )
  {
    dx[i][i] = _powell_dt;
  }
  return find_minimum_powell( x, dx, y );
}


double
minimize2::
minimize1_subclass::
function(double t)
{
  uint j;
  for (j = 0; j < _parent->_dimension; j++)
  {
    _parent->function_1dim_tmp[j] =
      _parent->function_1dim_x[j] +
      t * _parent->function_1dim_dx[j];
  }
  double y = _parent->function(_parent->function_1dim_tmp);
  return y;
}


void
minimize2::
dfunction_auto(
  base::vector<double> &gradient,
  base::vector<double> const &x,
  double y)
{
  base::vector<double> xt;
  xt.fill( 0.0, _dimension );

  uint i, j;
  for ( i = 0; i < _dimension; i++ )
  {
    for ( j = 0; j < _dimension; j++ )
    {
      xt[j] = x[j];
    }
    xt[i] += _gradient_dt;
    gradient[i] = (function(xt) - y) / _gradient_dt;
  }
}


//=========================================================================
// common routines
int
minimize2::
line_minimize(
  double &y,
  base::vector<double> &x,
  base::vector<double> &dx )
{
  // sets y to minimum value
  // sets x to the minimum domain
  // sets dx to the amount shifted

  minimize1::Status status = minimize1::MINIMIZE_OK;
  uint j;
  double xx, t, fx, fb, fa, bx, ax;

  for (j = 0; j < _dimension; j++)
  {
    function_1dim_x[j] = x[j];
    function_1dim_dx[j] = dx[j];
  }
  ax = 0.0;
  xx = 1.0;

  status = (minimize1::Status)bracket_minimum( ax, xx, bx, fa, fx, fb );

  if (status != minimize1::MINIMIZE_OK)
  {
    // bracket_minimum returned non-zero status
    goto end;
  }

  status = (minimize1::Status)minimize_1dim.find_minimum( t, y, ax, xx, bx );

  if ( status != minimize1::MINIMIZE_OK )
  {
    // minimize1 returned non-zero status
    goto end;
  }
  for (j = 0; j < _dimension; j++)
  {
    dx[j] *= t;
    x[j] += dx[j];
  }

  end:
  return (int)status;
}


// routine for initially bracketing a minimum
int
minimize2::
bracket_minimum(
  double &x1, double &x2, double &x3,
  double &y1, double &y2, double &y3 )
{
  minimize1::Status status = minimize1::MINIMIZE_OK;
  static double const GOLD = 0.5*(1.0+sqrt(5.0));
  static double const GLIMIT = 100.0;
  static double const TINY = 1.0e-20;

  double ulim, u, r, q, fu;

  y1 = minimize_1dim.function(x1);
  y2 = minimize_1dim.function(x2);
  _iteration_count += 2;

  if (y2 > y1)
  {
    math::swap( x1, x2 );
    math::swap( y1, y2 );
  }

  x3 = x2 + GOLD * (x2 - x1);
  y3 = minimize_1dim.function(x3);
  _iteration_count++;

  while (y2 >= y3)
  {
    r = (x2 - x1) * (y2 - y3);
    q = (x2 - x3) * (y2 - y1);

    double s = fabs(q-r);
    if ( s == 0 ) { s = TINY; }
    u = x2 - ((x2 - x3) * q - (x2 - x1) * r) / ( 2.0 * s );

    ulim = x2 + GLIMIT * (x3 - x2);

    if ( math::between( x2, u, x3 ) )
    {
      fu = minimize_1dim.function(u);
      _iteration_count++;
      if (fu < y3)
      {
        x1 = x2;
        x2 = u;
        y1 = y2;
        y2 = fu;
        // found bracket
        goto end;
      }
      else if (fu > y2)
      {
        x3 = u;
        y3 = fu;
        // found bracket
        goto end;
      }
      u = x3 + GOLD * (x3 - x2);
      fu = minimize_1dim.function(u);
      _iteration_count++;
    }
    else if ( math::between( x3, u, ulim ) )
    {
      fu = minimize_1dim.function(u);
      _iteration_count++;
      if (fu < y3)
      {
//        shift( x2, x3, u, x3 + GOLD * (x3 - x2) );
        shift( x2, x3, u, u + GOLD * (u - x3) );
        // u has now changed
        shift( y2, y3, fu, minimize_1dim.function(u) );
        _iteration_count++;
      }
    }
    else if ( math::between( u, ulim, x3 ) || u == ulim || x3 == ulim )
    {
      u = ulim;
      fu = minimize_1dim.function(u);
      _iteration_count++;
    }
    else
    {
      u = x3 + GOLD * (x3 - x2);
      fu = minimize_1dim.function(u);
      _iteration_count++;
    }
    shift(x1, x2, x3, u);
    shift(y1, y2, y3, fu);
  }

  end:
  if ( y2 >= y1 || y2 >= y3 ||
      !( (x1 < x2 && x2 < x3)||(x1 > x2 && x2 > x3) ) )
  {
    // function could not be bracketed
    status = minimize1::MINIMIZE_COULD_NOT_BRACKET;
  }
  return (int)status;
}


void minimize2::set_precision_goal( double x )
{ _precision_goal = x;
  minimize_1dim.set_precision_goal(x);
}


double minimize2::get_precision_goal()
{ return _precision_goal; }


void minimize2::set_accuracy_goal( double x )
{ _accuracy_goal = x;
  minimize_1dim.set_accuracy_goal(x);
}


double minimize2::get_accuracy_goal()
{ return _accuracy_goal; }


void minimize2::set_iteration_limit( uint x )
{ _iteration_limit = x;
  minimize_1dim.set_iteration_limit(x);
}


uint minimize2::get_iteration_limit()
{ return _iteration_limit; }


uint minimize2::get_iteration_count()
{ return _iteration_count; }


void minimize2::set_gradient_dt( double x )
{ _gradient_dt = x; }


double minimize2::get_gradient_dt()
{ return _gradient_dt; }


void minimize2::set_powell_dt( double x )
{ _powell_dt = x; }


double minimize2::get_powell_dt()
{ return _powell_dt; }

} // namespace math
