/* GANG Software
 * BASE/math/ReadUtil.H
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

#ifndef math_ReadUtil_INCLUDED
#define math_ReadUtil_INCLUDED

#include "base/ReadUtil.H"
#include "math/Matrix.H"

namespace math {

class ReadUtil
  :
    public base::ReadUtil
{

public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  ReadUtil();

  // destructor
  virtual ~ReadUtil();

  void read_transform( Transform &t,
                       base::String const &s );

protected:

private:

  // disabled copy constructor
  ReadUtil( ReadUtil const & );
  // disabled assignment operator
  ReadUtil &operator=( ReadUtil const & );

};

} // namespace math

#endif // math_ReadUtil_INCLUDED
