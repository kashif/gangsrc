/* GANG Software
 * LAB/cmclab/kernel/Exception.H
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

#ifndef cmclab_kernel_Exception_INCLUDED
#define cmclab_kernel_Exception_INCLUDED

#include "base/Exception.H"

namespace cmclab {
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

      ERR_POTENTIAL_SYNTAX,
      ERR_POTENTIAL_NAN,
      ERR_IWASAWA,

      ERR_SPACEFORM,

      ERR_INIT_POTENTIAL_SYNTAX,
      ERR_INIT_POTENTIAL_NAN,
      ERR_INIT_IWASAWA,

      ERR_POTENTIAL_INDEX,
      ERR_XSTART_SYNTAX,
      ERR_XSTART_EVAL,

      ERR_POLYLEN,
      ERR_POLYLEN_PARITY,
      ERR_BASISLEN,
      ERR_BASISLEN_PARITY,
      ERR_POLYLEN_BASISLEN,

      ERR_FILE_READ,
      ERR_FILE_INVALID,

      ERR_DOMAIN_INDEXED,
      ERR_DOMAIN_GRID,
      ERR_ZSTART,
      ERR_MEAN_CURVATURE,
      ERR_LAMBDA,
      ERR_NORMAL_SHIFT,
      ERR_XSTART,
      ERR_POTENTIAL,
      ERR_INTEGRATOR_COUNT,
      ERR_INTEGRATOR_COUNT_VAL,
      ERR_INITIAL_INTEGRATOR_COUNT,
      ERR_INITIAL_INTEGRATOR_COUNT_VAL,
      ERR_POLYNOMIAL_LENGTH,
      ERR_POLYNOMIAL_LENGTH_VAL,
      ERR_BASIS_LENGTH,
      ERR_BASIS_LENGTH_VAL,
      ERR_BASIS_POLY_RATIO,
      ERR_IWASAWA_METHOD,
      ERR_BIRKHOFF,
      ERR_TWO_COLUMN
    };

    Exception( ErrorCode code ) throw() :
        base::Exception(_message0[code]) {}

  private:
    static char const *const _message0[];
};

} // namespace kernel
} // namespace cmclab

#endif // cmclab_kernel_Exception_INCLUDED
