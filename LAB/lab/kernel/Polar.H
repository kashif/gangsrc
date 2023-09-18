/* GANG Software
 * LAB/lab/kernel/Polar.H
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

#ifndef lab_kernel_Polar_INCLUDED
#define lab_kernel_Polar_INCLUDED

#include "PlanarDomain.H"

namespace lab {
namespace kernel {

class Polar
  :
    public PlanarDomain
{

  class Exception : public base::Exception
  {

  public:

    enum ErrorCode
    {
      ERR_OK,
      ERR_PARSE,
      ERR_CENTER,
      ERR_RADIUS0,
      ERR_RADIUS1,
      ERR_COUNT0,
      ERR_ANGLE0,
      ERR_ANGLE1,
      ERR_COUNT1,
      ERR_COUNT0_VAL,
      ERR_COUNT1_VAL,
      ERR_RADIUS0_VAL,
      ERR_RADIUS1_VAL
    };

    Exception( ErrorCode code ) throw() :
        base::Exception( _message0[code] ) {}

  private:

    static char const *const _message0[];
  };

public:
  // constructor
  Polar( base::String const & );

  Polar(
    Complex const &center,
    Real radius0, Real radius1, uint n_radius,
    Real angle0, Real angle1, uint n_angle, bool exp );

  // copy constructor
  Polar( Polar const & );

  // destructor
  virtual ~Polar();

  // assignment operator
  Polar &operator=( Polar const & );

  virtual Complex z( uint i, uint j ) const;

protected:

private:

  void set(
    Complex const &center,
    Real radius0, Real radius1, uint n_radius,
    Real angle0, Real angle1, uint n_angle, bool exp );

  void set( base::String const & );

  void get(
    Complex &center,
    Real &radius0, Real &radius1, uint &n_radius,
    Real &angle0, Real &angle1, uint &n_angle, bool &exp ) const;

  Complex _center;
  Real _radius0, _radius1, _d_radius;
  Real _angle0, _angle1, _d_angle;
  bool _exp;
};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_Polar_INCLUDED
