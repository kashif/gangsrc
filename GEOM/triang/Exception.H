/* GANG Software
 * GEOM/triang/Exception.H
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

#ifndef triang_Exception_INCLUDED
#define triang_Exception_INCLUDED

#include "base/String.H"
#include "base/Exception.H"

namespace triang {

class Exception : public base::Exception
{

public:

  enum ErrorCode
  {
    ERR_OK,
    ERR_EMPTY,
    ERR_SYNTAX,

    ERR_MAX_AREA,
    ERR_MIN_ANGLE,
    ERR_SMOOTH,
    ERR_REFINE,
    ERR_MAX_AREA2,
    ERR_CURVATURE_EXP,
    ERR_CURVATURE_CUT,
    ERR_CIRCLE,
    ERR_CIRCLE_CENTER,
    ERR_CIRCLE_RADIUS,
    ERR_CIRCLE_ANGLE0,
    ERR_CIRCLE_ANGLE1,
    ERR_CIRCLE_COUNT,
    ERR_LINE,
    ERR_LINE_X,
    ERR_LINE_Y,
    ERR_LINE_COUNT,
    ERR_POINT,
    ERR_UNKNOWN_KEYWORD,
    ERR_MULTILINE,
    ERR_INTERNAL
  };

  Exception( ErrorCode code ) throw() :
      base::Exception( (char *)0 )
    { _message = _message0[code]; }

  Exception( char const *message ) throw() :
      base::Exception( (char *)0 )
    { _message = message; }

  Exception( ErrorCode code, uint lineno ) throw() :
      base::Exception( (char *)0 )
    { create_message( code, lineno ); }

  virtual ~Exception() {}

  virtual char const *message() const throw()
    { return _message.c_str(); }

private:

  void create_message( uint code, uint lineno ) throw();

  base::String _message;

  static char const *const _message0[];
};


} // namespace triang

#endif // triang_Exception_INCLUDED
