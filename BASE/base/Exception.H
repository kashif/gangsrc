/* GANG Software
 * BASE/base/Exception.H
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

#ifndef base_Exception_INCLUDED
#define base_Exception_INCLUDED

#include <exception>
//#include <string>

namespace base {

class Exception
{
public:
  Exception( char const *message ) throw() : _message(message) {}
  virtual char const *message() const throw() { return _message; }
private:
  char const *_message;
};

#if 0
/*
  Simple virtual base class for exception handling.
  Provides a message string.
*/
class Exception
  :
    public ::std::exception
{

public:

  // constructor
  Exception(char const *m) throw()
    { _message = m; }

  Exception(std::string const &m) throw()
    { _message = m; }

  // destructor
  virtual ~Exception() throw() {}

  virtual std::string const &message() const throw()
    { return _message; }

  // copy constructor
  Exception( Exception const &e ) throw()
    { _message = e._message; }

  // assignment operator
  Exception &operator=( Exception const &e ) throw()
    { if (&e != this)
    {_message = e._message; }
    return *this; }

protected:

private:
  virtual char const *what() const
    { return _message.c_str(); }

  std::string _message;
};
#endif

} // namespace base

#endif // base_Exception_INCLUDED
