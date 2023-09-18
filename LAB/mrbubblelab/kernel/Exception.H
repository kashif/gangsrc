/* GANG Software
 * LAB/mrbubblelab/kernel/Exception.H
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

#ifndef mrbubblelab_kernel_Exception_INCLUDED
#define mrbubblelab_kernel_Exception_INCLUDED

#include "base/Exception.H"

namespace mrbubblelab {
namespace kernel {

class Exception : public base::Exception
  {

  public:
    enum ErrorCode
    {
      ERR_OK,
      ERR_STOPPED,
      ERR_FILE_READ,
      ERR_FILE_INVALID,
      ERR_COEFFICIENT,
      ERR_EXPONENT,
      ERR_U0,
      ERR_UPRIME0,
      ERR_NORMALSHIFT,
      ERR_INITIAL_INTEGRATOR_COUNT,
      ERR_INTEGRATOR_COUNT
    };

    Exception( ErrorCode code ) throw() :
        base::Exception(_message0[code]) {}

  private:

    static char const *const _message0[];
};

} // namespace kernel
} // namespace mrbubblelab

#endif // mrbubblelab_kernel_Exception_INCLUDED
