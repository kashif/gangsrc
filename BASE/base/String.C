/* GANG Software
 * BASE/base/String.C
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

#include <ctype.h>
#include <ctype.h>
#include "String.H"

namespace base {

void
String::
strip( std::string const &s )
{
  static char const *whitespace = " \t\r\n\v\f";
  std::string::size_type i = s.find_first_not_of( whitespace );
  if ( i == std::string::npos )
  {
    erase();
  }
  else
  {
    std::string::size_type j = s.find_last_not_of( whitespace );
    DIE_IF( j == std::string::npos );

    if ( i <= j) {
      *this = s.substr( i, j + 1 - i );
    }
    else {
      erase();
    }
  }
}

void
String::
uppercase( std::string const &s )
{
  uint i;
  for ( i = 0; i < s.length(); i++ )
  {
    (*this)[i] = toupper(s[i]);
  }
}

void
String::
lowercase( std::string const &s )
{
  uint i;
  for ( i = 0; i < s.length(); i++ )
  {
    (*this)[i] = tolower(s[i]);
  }
}

int
String::
compare_nocase( std::string const &a, std::string const &b)
{
  size_t i, n;
  int c = 0;

  n = std::min(a.length(), b.length());

  for (i = 0; i < n; i++)
  {
    c = int(toupper(a[i])) - int(toupper(b[i]));
    if (c != 0) { break; }
  }

  return (int)(i < n ? sign(c) :
               sign(int(a.length()) - int(b.length())));
}

int
String::
find_nocase(base::vector<String> const &s, std::string const &pattern)
{
  unsigned i;
  for (i = 0; i < s.size(); i++)
  {
    if (!compare_nocase(s[i], pattern))
       break;
  }
  return (i < s.size() ? (int)i : -1);
}

int
String::
split( base::vector<String> &w ) const
{
  size_t i = 0;
  size_t n = length();
  size_t m;

  w.erase(w.begin(), w.end());

  do
  {
    for (;;)
    {
      if (i >= n) { break; }
      if (!isspace( (*this)[i] )) { break; }
      i++;
    }

    if (i < n)
    {
      m = i;
      i++;

      for (;;)
      {
	if (i >= n) { break; }
	if (isspace( (*this)[i] )) { break; }
	i++;
      }

      w.push_back( substr(m, i - m) );
    }

  }
  while (i < n);

  return (int)w.size();
}

} // namespace base
