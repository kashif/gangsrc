/* GANG Software
 * LAB/surflab/kernel/Exception.C
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

#include "base/String.H"
#include "Exception.H"

namespace surflab {
namespace kernel {

char const *const
Exception::
_message0[] =
{
  "",
  "Syntax error in function",
  "Computational error in function",
  "Computation stopped.",
  "Error reading file",
  "Invalid file",
  "Error in model",
  "Error in geometry",
  "Error in dimension",
  "Error in variable name"
};

void
Exception::
create_message(ErrorCode code, uint n)
    throw()
{
  _message = _message0[code];
  _message += " x";

  base::String t;
  t.to_string( n + 1 );
  _message += t;
}

} // namespace kernel
} // namespace surflab
