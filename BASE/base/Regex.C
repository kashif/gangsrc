/* GANG Software
 * BASE/base/Regex.C
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

#include <sys/types.h>
#include <regex.h>
#include <algorithm>
#include "Exception.H"
#include "Regex.H"
#include "System.H"

namespace base {

bool
match(
  base::String const &pattern_string,
  base::String const &test_string )
{
  DIE_IF( pattern_string.c_str() == (char *)0 );
  DIE_IF( test_string.c_str() == (char *)0 );

  regex_t pattern;

  // compile the pattern
  int flag =
    regcomp( &pattern, pattern_string.c_str(), REG_EXTENDED | REG_NOSUB );

  if ( flag != 0 )
  {
    throw base::Exception( "error in regex pattern" );
  }

  // pattern compiled successfully: attempt match
  // size_t len = pattern.re_nsub + 1;

  // attempt match
  flag = regexec( &pattern, test_string.c_str(), (size_t)0,
                  (regmatch_t *)0, (int)0 );

  bool r = ( flag == 0 );

  // free memory
  regfree(&pattern);

  return r;
}


bool
match(
  base::String const &pattern_string,
  base::String const &test_string,
  base::vector<base::String> &subexpressions )
{
  DIE_IF( pattern_string.c_str() == (char *)0 );
  DIE_IF( test_string.c_str() == (char *)0 );

  regex_t pattern;

  subexpressions.clear();

  // compile the pattern
  int flag = regcomp( &pattern, pattern_string.c_str(), REG_EXTENDED );

  if ( flag != 0 )
  {
    throw base::Exception( "error in regex pattern" );
  }

  // pattern compiled successfully: attempt match
  size_t len = pattern.re_nsub + 1;

  // attempt match
  regmatch_t *match = new regmatch_t[len];

  // attempt match
  flag = regexec( &pattern, test_string.c_str(), len, match, (int)0 );
  bool r = ( flag == 0 );

  if ( r )
  {
    // match found

    // create base::vector of subexpressions
    uint i;
    for ( i = 0; i < len; i++ )
    {
      if ( match[i].rm_so != -1 && match[i].rm_eo != -1 )
      {
        subexpressions.push_back(
          base::String( test_string,
                        match[i].rm_so, match[i].rm_eo-match[i].rm_so) );
      }
      else
      {
        subexpressions.push_back( base::String() );
      }
    }
  }
  
  // free memory
  regfree(&pattern);
  delete [] match;

  return r;
}

void
split( base::vector<base::String> &w, base::String const &s_,
       base::String const &pattern )
{
  /*
    Note: with ":" as pattern,
    ":1:2" splits into [], [1], [2]
    "1:2:" splits into [1], [2]
    as in perl

    pattern must not contain parentheses (will cause error)
  */

  w.clear();
  base::String s = s_;

  base::String p = pattern + base::String("(.*)$");
  base::vector<base::String> v;

  while ( match( p, s, v ) )
  {
    // found match
    DIE_IF(v.size() != 2);

    // save first part of s
    DIE_IF( s.length() < v[0].length() );
    w.push_back( s.substr( 0, s.length() - v[0].length() ) );

    // set s to last part
    s = v[1];
  }

  // save remaining portion
  if (!s.empty())
  {
    w.push_back(s);
  }
}

void
split( base::vector<base::String> &w, base::String const &s )
{
  // split by whitespace
  split( w, s, base::String( "[ \f\r\t\v\n]+" ) );
}

void
split( base::vector<base::String> &w, base::String const &s, char c )
{
  base::String pattern = "[ \f\r\t\v\n]*";
  pattern += c;
  pattern += "[ \f\r\t\v\n]*";
  split( w, s, pattern );
}


#if 0
// OLD
void
split( base::vector<base::String> &w, base::String const &s_, char c )
{
  // set up pattern = "^\s*([^c]+)\s*c(.*$)"

  base::String pattern = "^[ \f\r\t\v\n]*([^";
  pattern += c;
  pattern += "]+)[ \f\r\t\v\n]*";
  pattern += c;
  pattern += "(.*)$";

  base::String s = s_;

  w.clear();

  base::vector<base::String> v;

  for (;;)
  {
    // match initial characters which are not c
    if ( ! match( pattern, s, v) )
    { break; }

    // found a match: push matched item into w
    w.push_back(v[1]);

    // set s to the remaining, unmatched portion
    s = v[2];
  }

  // push any remaining stuff into w
  if ( match( "^[ \f\r\t\v\n]*(.*[^ \f\r\t\v\n])[ \f\r\t\v\n]*$", s, v ) )
  {
    w.push_back(v[1]);
  }
}
#endif

} // namespace base
