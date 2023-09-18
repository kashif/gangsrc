/* GANG Software
 * BASE/math/RungeKutta.H
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

#ifndef math_RungeKutta_INCLUDED
#define math_RungeKutta_INCLUDED

#include "base/System.H"

namespace math {

/*
  Runge-Kutta integrator template.

  Computes by fourth-order Runge-Kutta methods a solution to a
  first-order system of ordinary differential equations of the form

    dY/dx = F(x, Y)

  x is of type A (base type)
  Y is of type B (typically an A, a vector of A's, or a matrix of A's)
    type B must support vector-space operations

  Example:<br>

<blockquote><font face="courier>
  #include <iostream><br>
  #include <complex><br>
  #include "math.H"<br>
  #include "RungeKutta.H"<br>
<br>
  class RungeKuttaSubclass<br>
    : public math::RungeKutta<std::complex<double>, std::complex<double> ><br>
  {<br>
    void function( std::complex<double> &w,<br>
                   std::complex<double> const &z,<br>
                   std::complex<double> const & )<br>
      { w = z*z; }<br>
  };<br>
<br>
  main()<br>
  {<br>
    RungeKuttaSubclass integrator;<br>
<br>
    std::complex<double> x0 = 1;<br>
    std::complex<double> x1 = 2;<br>
    uint steps = 100;<br>
    std::complex<double> y = 0.0;  // compute() adds to y<br>
<br>
    integrator.compute( y, x0, x1, steps );<br>
    std::cout << y << std::endl;<br>
  }<br>
</font></blockquote>
  */

template <class A, class B>
class RungeKutta
{

public:

  // void constructor
  RungeKutta() {};

  // destructor
  virtual ~RungeKutta() {};

  /* perform the integration along straight line from x1 to x2
      in count steps, starting with Y. output in Y. */
  void
  compute( B &Y, A const &x1, A const &x2,
           uint count );
protected:

  // function to integrate (pure virtual)
  virtual void function( B &, A const &, B const & ) = 0;

private:
  // disabled (private) copy constructor
  RungeKutta( RungeKutta const & ) {DIE();};

  // disabled (private) assignment operator
  RungeKutta &operator=( RungeKutta const & ) {DIE();};
};


template <class A, class B>
void
RungeKutta<A,B>::
compute(
    B &Y,
    A const &x1, A const &x2, uint count )
{
  /*
    PHI( dY0, Y, x )
    PHI( dY1, Y+0.5*dY0, x+0.5*dx )
    PHI( dY2, Y+0.5*dY1, x+0.5*dx )
    PHI( dY3, Y+dY2, x+dx )
    Y = (1.0/6.0) * dx * (dY0+2.0*dY1+2.0*dY2+dY3);
  */

  DIE_IF(count == 0);
  A dx = (x2 - x1)/A(count);
  B dY;

  uint i;
  for ( i = 0; i < count; i++ )
  {
    A x = x1 + A(i) * dx;
    function( dY, x, Y );

    A dx2 = dx * 0.5;
    A xh = x + dx2;
    B Y1, dY1, dY2;

    Y1 = Y + dY * dx2;
    function(dY1, xh, Y1);
    Y1 = Y + dY1 * dx2;
    function(dY2, xh, Y1);
    Y1 = Y + dY2 * dx;
    dY2 += dY1;
    function(dY1, x + dx, Y1);
    Y += (dY + dY1 + dY2 * A(2.0)) * (dx/A(6.0));
  }
}

} // namespace math

#endif // math_RungeKutta_INCLUDED
