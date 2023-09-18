/* GANG Software
 * BASE/parser/MathParser.C
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

#include "MathParser.H"

namespace parser {

MathParser::
MathParser()
{
}

MathParser::
~MathParser()
{
}

void
MathParser::
parse( std::istream &stream )
{
  // Simple parser of mathematica nested lists
  // NOTE: does not check for syntax error

  uint counter = 0;
  uint depth = 0;

  base::String s;

  char c;
  for (;;)
  {
    stream.read(&c, 1);

    int n = stream.gcount();

    // return if EOF
    if (n == 0) { return; }

    // skip white space
    if (c == '\n' || c == '\\') { continue; }
    else if (c == '{' )
    {
      depth++;
      continue;
    }
    else if (c == '}')
    {
      if (s.length() != 0)
      {
        handler(s, counter++, depth);
      }
      s.erase();
      depth--;
    }
    else if (c == ',')
    {
      if (s.length() != 0)
      {
        handler(s, counter++, depth);
      }
      s.erase();
    }
    else
    {
      s += c;
    }
  }
}

} // namespace parser
