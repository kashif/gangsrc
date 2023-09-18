/* GANG Software
 * BASE/math/Minimize1.H
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

#ifndef math_Minimize1_INCLUDED
#define math_Minimize1_INCLUDED

#include <math.h>

namespace math {

/*
  Finds minimum of a function f:R^1-->R^1.

  Adapted from Numerical Recipes in C, 2nd ed. sec. 10.2, p. 404.
  (Parabolic Interpolation and Brent's Method in One Dimension)<br><br>

  input:<br>
  f = function to minimize<br>
  ax, bx, cx = initial points<br>
    the initial points must "bracket" a minimum, that is
    bx must be between ax and cx, and
    f(bx) must be std::less than f(ax) and f(cx)<br>
  tol = x-tolerance (may be 0.0)<br>
  max_iter: maximum allowable iterations (e.g. 100)<br>

  output:<br>
  [x, y] = minimum and function value at minimum<br>
  status<br><br>

  return value:<br>
  0: converged<br>
  1: too many iterations<br><br>
  */

class minimize1
{

public:

  // void constructor
  minimize1();

  // destructor
  virtual ~minimize1();

  //
  enum Status {
    MINIMIZE_OK=0,
    MINIMIZE_ITERATION_LIMIT_EXCEEDED,
    MINIMIZE_INPUT_NOT_BRACKETED,
    MINIMIZE_INPUT_NOT_SORTED,
    MINIMIZE_COULD_NOT_BRACKET };

  //
  int
  find_minimum(
    double &x,
    double &y,
    double ax, double bx, double cx );

  //
  void set_precision_goal( double x ) { _precision_goal = x; }
  //
  double get_precision_goal() { return _precision_goal; }
  //
  void set_accuracy_goal( double x ) { _accuracy_goal = x; }
  //
  double get_accuracy_goal() { return _accuracy_goal; }
  //
  void set_iteration_limit( uint x ) { _iteration_limit = x; }
  //
  uint get_iteration_limit() { return _iteration_limit; }
  //
  uint get_iteration_count() { return _iteration_count; }

protected:
  //
  virtual double function(double) = 0;

private:
  //
  double _precision_goal;
  //
  double _accuracy_goal;
  //
  uint _iteration_limit;
  //
  uint _iteration_count;


  //
  inline void
  shift(double &a, double &b, double &c, double d)
    { a = b; b = c; c = d; }

  //
  inline
  double
  sign_adjust( double x, double s )
    {
      // return the number with absolute value x and sign of s
      return( s >= 0.0 ? fabs(x) : -fabs(x) );
    }


  static double const smallreal_double;

  // Disabled copy constructor.
  minimize1( minimize1 const & );

  // Disabled assignment operator.
  minimize1 &operator=( minimize1 const & );
};

} // namespace math

#endif // math_Minimize1_INCLUDED
