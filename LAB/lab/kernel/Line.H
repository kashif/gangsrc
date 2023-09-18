/* GANG Software
 * LAB/lab/kernel/Line.H
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

#ifndef lab_kernel_Line_INCLUDED
#define lab_kernel_Line_INCLUDED

#include "Exception.H"
#include "Curve.H"

namespace lab {
namespace kernel {

class Line
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
      ERR_X0,
      ERR_X1,
      ERR_COUNT,
      ERR_COUNT_VAL
    };

    Exception( ErrorCode code ) throw() :
        base::Exception( _message0[code] ) {}

  private:

    static char const *const _message0[];
  };

  // void constructor
  Line( base::String const & );

  Line( Complex const &x0, Complex const &x1, uint count );

  // copy constructor
  Line( Line const & );

  // destructor
  virtual ~Line();

  // assignment operator
  Line &operator=( Line const & );

  //
  void set( Complex const &x0, Complex const &x1, uint count );
  void set( base::String const & );
  //
  void get( Complex &x0, Complex &x1, uint &count ) const;

  //
  Complex z(uint) const;

  //
  uint count() const { return _count; }

protected:
  //
  Complex _x0, _x1;
  //
  uint _count;
  //
  Complex _delta;

private:

};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_Line_INCLUDED
