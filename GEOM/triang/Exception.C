/* GANG Software
 * GEOM/triang/Exception.C
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

namespace triang {

char const *const
Exception::
_message0[] =
{
  "",
  "No points in specification of triangulation domain",
  "Syntax error in domain specification",

  "Syntax error in triangulation domain: max_area",
  "Syntax error in triangulation domain: min_angle",
  "Syntax error in triangulation domain: smooth",
  "Syntax error in triangulation domain: refine",
  "Syntax error in triangulation domain: max_area2",
  "Syntax error in triangulation domain: curvature_exp",
  "Syntax error in triangulation domain: curvature_cut",

  "Syntax error in triangulation domain: circle",
  "Syntax error in triangulation domain: circle center",
  "Syntax error in triangulation domain: circle radius",
  "Syntax error in triangulation domain: circle angle0",
  "Syntax error in triangulation domain: circle angle1",
  "Syntax error in triangulation domain: circle count",
  "Syntax error in triangulation domain: line",
  "Syntax error in triangulation domain: line x",
  "Syntax error in triangulation domain: line x",
  "Syntax error in triangulation domain: line_count",
  "Syntax error in triangulation domain: point",
  "Syntax error in triangulation domain: unknown keyword",
  "Syntax error in triangulation domain: multiline",
  "Error in triangulation computation"
};

void
Exception::
create_message( uint code, uint lineno )
    throw()
{
  _message = _message0[code];
  if ( lineno > 0 )
  {
    TRACE;
    _message += " (line ";
    base::String t;
    t.to_string( lineno );
    _message += t;
    _message += ")";
  }
}

} // namespace triang
