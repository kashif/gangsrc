/* GANG Software
 * LAB/lab/kernel/Circle.H
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

#ifndef lab_kernel_Circle_INCLUDED
#define lab_kernel_Circle_INCLUDED

#include "Curve.H"

namespace lab {
namespace kernel {

class Circle
  :
  public Curve
{

public:
  class Exception : public base::Exception
  {

  public:

    enum ErrorCode
    {
      ERR_OK,
      ERR_PARSE,
      ERR_CENTER,
      ERR_RADIUS,
      ERR_ANGLE0,
      ERR_ANGLE1,
      ERR_COUNT,
      ERR_COUNT_VAL,
      ERR_RADIUS_VAL
    };

    Exception( ErrorCode code ) throw() :
        base::Exception( _message0[code] ) {}

  private:

    static char const *const _message0[];
  };

  // void constructor
  Circle( base::String const &s );

  Circle( Complex const &center,
               Real radius, Real angle0, Real angle1,
               uint count );

  // copy constructor
  Circle( Circle const & );

  // destructor
  virtual ~Circle();

  // assignment operator
  Circle &operator=( Circle const & );

  //
  void set( Complex const &center,
            Real radius, Real angle0, Real angle1,
            uint count );
  void set( base::String const &s );
  //
  void get( Complex &center,
            Real &radius, Real &angle0, Real &angle1,
            uint &count ) const;

  //
  Complex z(uint) const;

  //
  uint count() const { return _count; }

protected:
  //
  Complex _center;
  //
  Real _radius, _angle0, _angle1;
  //
  uint _count;
  //
  Real _delta;

private:

};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_Circle_INCLUDED
