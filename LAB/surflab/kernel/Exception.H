/* GANG Software
 * LAB/surflab/kernel/Exception.H
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

#ifndef surflab_kernel_Exception_INCLUDED
#define surflab_kernel_Exception_INCLUDED

#include "base/Exception.H"

namespace surflab {
namespace kernel {

class Exception
  :
    public base::Exception
{
public:

  enum ErrorCode
  {
    ERR_OK,
    ERR_SYNTAX,
    ERR_MATH,
    ERR_STOPPED,
    ERR_FILE_READ,
    ERR_FILE_INVALID,
    ERR_MODEL,
    ERR_GEOMETRY,
    ERR_DIM,
    ERR_VARNAME
  };

  Exception( ErrorCode code ) throw() :
      base::Exception( (char *)0 )
    { _message = _message0[code]; }

  Exception( ErrorCode code, uint n ) throw() :
      base::Exception( (char *)0 )
    { create_message( code, n ); }

  virtual ~Exception() {}

  virtual char const *message() const throw()
    { return _message.c_str(); }

private:

  void create_message(ErrorCode code, uint n) throw();

  base::String _message;

  static char const *const _message0[];
};

} // namespace kernel
} // namespace surflab

#endif // surflab_kernel_Exception_INCLUDED
