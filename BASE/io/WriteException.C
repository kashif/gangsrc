/* GANG Software
 * BASE/io/WriteException.C
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

#include "WriteException.H"

namespace io {

// BUG: when accessed as a base::Exception, message() returns (char *)0

char const * const
WriteException::_message0[] =
{
  "",
  "Error",
  "Unknown file format",
  "Error opening stream",
  "Error writing to stream"
};

void
WriteException::
create_message(
  WriteException::ErrorCode code,
  base::String const &filename,
  uint lineno,
  base::String const &message )
  throw()
{
  _message = _message0[code];
  if (! message.empty() )
  {
    _message += ": ";
    _message += message;
  }
  if ( !filename.empty() || lineno != 0)
  {
    _message += " (";
  }
  if (! filename.empty())
  {
    _message += filename;
    if (lineno != 0)
    {
      _message += " ";
    }
  }
  if (lineno != 0)
  {
    _message += "line ";
    base::String x;
    x.to_string(lineno);
    _message += x;
  }
  if ( !filename.empty() || lineno != 0)
  {
    _message += ")";
  }
}

} // namespace io
