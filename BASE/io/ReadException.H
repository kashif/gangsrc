/* GANG Software
 * BASE/io/ReadException.H
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

#ifndef io_ReadException_INCLUDED
#define io_ReadException_INCLUDED

#include "base/Exception.H"
#include "base/String.H"

namespace io {

class ReadException : public base::Exception
{

public:
  enum ErrorCode
  {
    OK,             // no error
    ERROR,          // generic error
    UNKNOWN_TYPE,   // the file has an unknown type (from filename extension)
    WRONG_TYPE,     // the file is not an appropriate type (from header info)
    OPEN_ERROR,     // error when opening the stream
    READ_ERROR,     // error when reading from the stream
    PARSE_ERROR     // error when parsing the file
  };

  ReadException(
    ErrorCode code,
    base::String const &filename ) throw() :
      base::Exception( (char *)0 ) 
    { create_message( code, filename ); }

  ReadException(
    ErrorCode code,
    base::String const &filename,
    uint lineno,
    base::String const &message ) throw() :
      base::Exception( (char *)0 )
    { create_message( code, filename, lineno, message ); }

  virtual ~ReadException() throw() {}

  ReadException( ReadException const &e ) throw()
      :
      base::Exception(e),
      _message(e._message) {}

  virtual char const *message() const throw()
    { return _message.c_str(); }

private:

  void create_message(
    ErrorCode code,
    base::String const &filename,
    uint lineno = 0U,
    base::String const &message = base::String() ) throw();

  base::String _message;

  static char const *const _message0[];

  ReadException const &operator=(ReadException const &);
};

} // namespace io

#endif // io_ReadException_INCLUDED
