/* GANG Software
 * LAB/minlab/kernel/Exception.H
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

#ifndef minlab_kernel_Exception_INCLUDED
#define minlab_kernel_Exception_INCLUDED

#include "base/Exception.H"

namespace minlab {
namespace kernel {

class Exception : public base::Exception
  {

  public:
    /*
       Error codes arising from bad input. In the case of a GUI, these
       correspond roughly to the widgets.
    */
    enum ErrorCode
    {
      ERR_OK,
      ERR_STOPPED,
      ERR_FILE_READ,
      ERR_FILE_INVALID,
      ERR_VARNAME,
      ERR_MODE,
      ERR_ZSTART,
      ERR_SPINOR1,
      ERR_SPINOR2,
      ERR_WEIERSTRASS_G,
      ERR_WEIERSTRASS_F,
      ERR_INTEGRATOR_COUNT,
      ERR_INITIAL_INTEGRATOR_COUNT,
      ERR_XSTART1,
      ERR_XSTART2,
      ERR_XSTART3,
      ERR_INTEGRAND,
      ERR_ASSOCIATE
    };

    Exception( ErrorCode code ) throw() :
      base::Exception(_message0[code]) {}

  private:

    static char const *const _message0[];
};

} // namespace kernel
} // namespace minlab

#endif // minlab_kernel_Exception_INCLUDED
