/* GANG Software
 * BASE/math/Minimize2.H
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

#ifndef math_Minimize2_INCLUDED
#define math_Minimize2_INCLUDED

#include "base/vector.H"
#include "base/Use.h"
#include "Minimize1.H"

namespace math {

/*
  Finds minimum of a function f:R^n-->R^1<br>

  minimize2_gradient()<br>
  Finds minimum of a function f:R^n-->R^1<br>

  Adapted from Numerical Recipes in C, 2nd ed. sec. 10.6.
  (Gradient Method)<br>

  function<br>
    function to minimize<br>

  dfunction<br>
    gradient of 'function'<br>
    computes the gradient of f at x<br>
    y is function(x)<br>

  report:<br>
  after each line minimization, called with value<br>
  report(y, x)<br>


  minimize2_powell()<br>
  Finds minimum of a function f:R^n-->R^1<br>

  Adapted from Numerical Recipes in C, 2nd ed. sec. 10.4.
  (Powell's Method)<br>

  p: starting point<br>

  xi<br>
    initial directions<br>
    an array of 'dimension' vectors of dimension 'dimension'<br>

  iteration_maximum:<br>
    maximum allowaAble iterations (e.g. 100)<br>

  return value:<br>
    0: minimum found<br>
    !=0: minimum not found<br>
  */

class minimize2
{

public:

  // constructor
  minimize2( uint dimension );

  // destructor
  virtual ~minimize2();

  //
  void set_precision_goal( double x );
  //
  double get_precision_goal();
  //
  void set_accuracy_goal( double x );
  //
  double get_accuracy_goal();
  //
  void set_iteration_limit( uint x );
  //
  uint get_iteration_limit();
  //
  uint get_iteration_count();
  //
  void set_gradient_dt( double x );
  //
  double get_gradient_dt();
  //
  void set_powell_dt( double x );
  //
  double get_powell_dt();

  // minimize by the gradient method with an internally-provided gradient
  int
  find_minimum_gradient_auto(
    base::vector<double> &x,
    double &y );

  // minimize by the gradient method with a user-provided gradient
  // (not implemented)
  int
  find_minimum_gradient(
    base::vector<double> &x,
    double &y );

  // minimize by powell's method
  int
  find_minimum_powell(
    base::vector<double> &x,
    double &y );

  // minimize by powell's method (with dx)
  int
  find_minimum_powell(
    base::vector<double> &x,
    base::vector<base::vector<double> > &dx,
    double &y );

protected:

  // function to minimize
  virtual double function( base::vector<double> const &x ) = 0;

#if 0
  // gradient of function to minimize
  virtual void dfunction(
    base::vector<double> &,
    base::vector<double> const &,
    double) {};
#endif

  //
  virtual void report( double y, base::vector<double> const &x )
    { USE(y); USE(x); };


private:

  //
  void dfunction_auto(
    base::vector<double> &gradient,
    base::vector<double> const &x,
    double y);

  //
  int
  line_minimize(
    double &y,
    base::vector<double> &x,
    base::vector<double> &dx );

  //
  int bracket_minimum(
    double &ax, double &bx, double &cx, double &fa, double &fb,
    double &fc );

  //
  static inline void shift(double &a, double &b, double &c, double d)
    { a = b; b = c; c = d; }


  //
  double _precision_goal;
  //
  double _accuracy_goal;
  //
  uint _iteration_limit;
  //
  uint _iteration_count;
  //
  double _gradient_dt;
  //
  double _powell_dt;

  //
  uint _dimension;

  //
  base::vector<double> function_1dim_x;
  //
  base::vector<double> function_1dim_dx;
  //
  base::vector<double> function_1dim_tmp;


  //
  class minimize1_subclass : public minimize1
  {
    //
    virtual double function(double);
    //
    minimize2 *_parent;
    //
    friend class minimize2;
  };

  //
  minimize1_subclass minimize_1dim;
  friend class minimize1_subclass;

  static double const smallreal_double;

  // Disabled copy constructor.
  minimize2( minimize2 const & );

  // Disabled assignment operator.
  minimize2 &operator=( minimize2 const & );
};

} // namespace math

#endif // math_Minimize2_INCLUDED
