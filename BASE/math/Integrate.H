/* GANG Software
 * BASE/math/Integrate.H
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

#ifndef math_Integrate_INCLUDED
#define math_Integrate_INCLUDED

#include "base/System.H"

namespace math {

/*
  Line integral
  */

template <class BASE_TYPE, class RESULT_TYPE>
class Integrate
{

public:

  // void constructor
  Integrate() {};

  // destructor
  virtual ~Integrate() {};

  /* perform the integration along straight line from x1 to x2
      in count steps, starting with Y. output in Y. */
  void
  compute(
    RESULT_TYPE &R,
    BASE_TYPE const &x1, BASE_TYPE const &y1,
    BASE_TYPE const &x2, BASE_TYPE const &y2,
    uint count );
protected:

  // function to integrate (pure virtual)
  virtual void function(
    RESULT_TYPE &dRx,
    RESULT_TYPE &dRy,
    BASE_TYPE const &x,
    BASE_TYPE const &y ) = 0;

private:
  // disabled (private) copy constructor
  Integrate( Integrate const & ) {DIE();};

  // disabled (private) assignment operator
  Integrate &operator=( Integrate const & ) {DIE();};
};


template <class BASE_TYPE, class RESULT_TYPE>
void
Integrate<BASE_TYPE,RESULT_TYPE>::
compute(
    RESULT_TYPE &R,
    BASE_TYPE const &x1,
    BASE_TYPE const &x2,
    BASE_TYPE const &y1,
    BASE_TYPE const &y2,
    uint count )
{
  DIE_IF(count == 0);
  BASE_TYPE dx = (x2 - x1)/BASE_TYPE(count);
  BASE_TYPE dy = (y2 - y1)/BASE_TYPE(count);

  BASE_TYPE const c4 = BASE_TYPE(4.0);
  BASE_TYPE const c1_6 = BASE_TYPE(1.0)/BASE_TYPE(6.0);
  uint i;
  for ( i = 0; i < count; i++ )
  {
    BASE_TYPE x = x1 + BASE_TYPE(i) * dx;
    BASE_TYPE y = y1 + BASE_TYPE(i) * dy;

#if 0
    // order 1 integration
    RESULT_TYPE dRx, dRy;
    function( dRx, dRy, x, y);
    R += dRx * dx + dRy * dy;
#endif

#if 1
    // order 4 integration
    RESULT_TYPE dRx1, dRy1;
    function( dRx1, dRy1, x, y );

    RESULT_TYPE dRx2, dRy2;
    function(dRx2, dRy2, x + 0.5*dx, y + 0.5*dy);

    RESULT_TYPE dRx3, dRy3;
    function(dRx3, dRy3, x + dx, y + dy);

    R += c1_6 * ( dx * (dRx1 + c4*dRx2 + dRx3) + dy * (dRy1 + c4*dRy2 + dRy3) );
#endif
  }
}

} // namespace math

#endif // math_Integrate_INCLUDED
