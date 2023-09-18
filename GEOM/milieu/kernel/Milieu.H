/* GANG Software
 * GEOM/milieu/kernel/Milieu.H
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

#ifndef milieu_kernel_Milieu_INCLUDED
#define milieu_kernel_Milieu_INCLUDED

#include "MilieuBase.H"

namespace milieu {
namespace kernel {

class Milieu
  :
    public MilieuBase
{

public:
  // constructor
  Milieu();

  // destructor
  virtual ~Milieu();

protected:

private:

  // disabled copy constructor
  Milieu( Milieu const & );
  // disabled assignment operator
  Milieu &operator=( Milieu const & );

};

} // namespace kernel
} // namespace milieu

#endif // milieu_kernel_Milieu_INCLUDED
