/* GANG Software
 * LAB/klab/kernel/Exception.H
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

#ifndef klab_kernel_Exception_INCLUDED
#define klab_kernel_Exception_INCLUDED

#include "base/Exception.H"

namespace klab {
namespace kernel {

class Exception : public base::Exception
  {
  public:

    enum ErrorCode
    {
      OK,
      ERR_STOPPED,
      ERR_INPUT,
      ERR_DOMAIN_INIT,
      ERR_DOMAIN,

      ERR_POTENTIAL_X_SYNTAX,
      ERR_POTENTIAL_Y_SYNTAX,
      ERR_POTENTIAL_X_NAN,
      ERR_POTENTIAL_Y_NAN,
      ERR_FACTORIZATION,

      ERR_INIT_POTENTIAL_X_SYNTAX,
      ERR_INIT_POTENTIAL_Y_SYNTAX,
      ERR_INIT_POTENTIAL_X_NAN,
      ERR_INIT_POTENTIAL_Y_NAN,
      ERR_INIT_FACTORIZATION,

      ERR_POTENTIAL_X_INDEX,
      ERR_POTENTIAL_Y_INDEX,
      ERR_XSTART_SYNTAX,
      ERR_XSTART_EVAL,
      ERR_YSTART_SYNTAX,
      ERR_YSTART_EVAL,

      ERR_POLYLEN,
      ERR_POLYLEN_PARITY,

      ERR_FILE_READ,
      ERR_FILE_INVALID,
      ERR_DOMAIN_INDEXED,
      ERR_DOMAIN_GRID,
      ERR_ZSTART,
      ERR_LAMBDA,
      ERR_INITIAL_X,
      ERR_INITIAL_Y,
      ERR_POTENTIAL_X,
      ERR_POTENTIAL_Y,
      ERR_INTEGRATOR_COUNT,
      ERR_INTEGRATOR_COUNT_VAL,
      ERR_INITIAL_INTEGRATOR_COUNT,
      ERR_INITIAL_INTEGRATOR_COUNT_VAL,
      ERR_POLYNOMIAL_LENGTH,
      ERR_POLYNOMIAL_LENGTH_VAL,

      ERR_SYM
    };

    Exception( ErrorCode code ) throw() :
        base::Exception(_message0[code]) {}

  private:
    static char const *const _message0[];
};

} // namespace kernel
} // namespace klab

#endif // klab_kernel_Exception_INCLUDED
