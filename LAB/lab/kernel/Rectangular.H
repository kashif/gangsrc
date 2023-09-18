/* GANG Software
 * LAB/lab/kernel/Rectangular.H
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

#ifndef lab_kernel_Rectangular_INCLUDED
#define lab_kernel_Rectangular_INCLUDED

#include "PlanarDomain.H"

namespace lab {
namespace kernel {

class Rectangular
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
      ERR_BASE,
      ERR_A0,
      ERR_COUNT0,
      ERR_A1,
      ERR_COUNT1,
      ERR_COUNT0_VAL,
      ERR_COUNT1_VAL
    };

    Exception( ErrorCode code ) throw() :
        base::Exception( _message0[code] ) {}

  private:

    static char const *const _message0[];
  };

public:
  // constructor
  Rectangular( base::String const & );

  Rectangular(
    Complex const &base,
    Complex const &a0, uint count0,
    Complex const &a1, uint count1 );

  // copy constructor
  Rectangular( Rectangular const & );

  // destructor
  virtual ~Rectangular();

  // assignment operator
  Rectangular &operator=( Rectangular const & );

  void set(
    Complex const &base,
    Complex const &a0, uint count0,
    Complex const &a1, uint count1 );

  void set( base::String const & );

  void get(
    Complex &base,
    Complex &a0, uint &count0,
    Complex &a1, uint &count1 ) const;

  virtual Complex z( uint i, uint j ) const;

protected:

private:

  Complex _base;
  Complex _a0;
  Complex _a1;
  Complex _delta0;
  Complex _delta1;
};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_Rectangular_INCLUDED
