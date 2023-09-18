/* GANG Software
 * BASE/math/WriteUtil.H
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

#ifndef math_WriteUtil_INCLUDED
#define math_WriteUtil_INCLUDED

#include "io/Ostream.H"
#include "math/Matrix.H"

namespace math {

class WriteUtil
{

public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  WriteUtil();

  // destructor
  virtual ~WriteUtil();

  static void write_transform(
    ::io::Ostream &stream,
    Transform const &t,
    base::String const &tab );

protected:

private:

  // disabled copy constructor
  WriteUtil( WriteUtil const & );
  // disabled assignment operator
  WriteUtil &operator=( WriteUtil const & );

};

} // namespace math

#endif // math_WriteUtil_INCLUDED
