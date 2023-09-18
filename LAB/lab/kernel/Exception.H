/* GANG Software
 * LAB/lab/kernel/Exception.H
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

#ifndef lab_kernel_Exception_INCLUDED
#define lab_kernel_Exception_INCLUDED

#include "base/Exception.H"

namespace lab {
namespace kernel {

class Exception
  :
    public base::Exception
{

public:

  enum ErrorCode
  {
    ERR_OK,
    ERR_UNCONFIGURED,
    ERR_UNKNOWN_DOMAIN,
    ERR_FILE_INPUT,
    ERR_START_INDEX,
    ERR_EDGE,
    ERR_NOT_TRIANGLE,
    ERR_REFINE,
    ERR_MAX_AREA2,
    ERR_CURVATURE_EXP,
    ERR_CURVATURE_CUT,
    ERR_SEQUENCER,
    STOP,
    STOP_SEQUENCE,
    ERR_INTERNAL
  };
  
  Exception( ErrorCode code ) throw() :
      base::Exception( _message0[code] ),
      _code(code) {}

  ErrorCode code() const
    { return _code; }

private:
  
  static char const *const _message0[];
  ErrorCode _code;
};

} // namespace kernel
} // namespace lab

#endif // lab_kernel_Exception_INCLUDED
