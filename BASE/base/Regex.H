/* GANG Software
 * BASE/base/Regex.H
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

#ifndef base_Regex_INCLUDED
#define base_Regex_INCLUDED

#include "vector.H"
#include "String.H"

namespace base {

/*
   Attempts to match teststring to pattern.

   match( pattern, teststring )

    Returns true iff the teststring matches the pattern
    Throws base::Exception if there is a syntax error in the pattern

  Wrapper for POSIX regular expression matching (man regcomp)
*/
bool match(
  base::String const &pattern,
  base::String const &teststring );

/*
   Attempts to match teststring to pattern.

   match( pattern, teststring, substrings )

    Returns true iff the teststring matches the pattern
    if true, sets substrings to:
               substring[0]: what matched the whole pattern
               substring[1]..substring[n-1]: what matched the parentheses
    Throws exception if there is a syntax error in the pattern

  Wrapper for POSIX regular expression matching (man regcomp)
*/
bool match(
  base::String const &pattern,
  base::String const &teststring,
  base::vector<base::String> &substrings );

/*
  split s into a vector of strings, separated by pattern
*/
void
split( base::vector<base::String> &w, base::String const &s_,
       base::String const &pattern );


/*
  split s into a vector of strings, separated by whitespace
  removes whitespace around beginning and end of each part
*/
void
split( base::vector<base::String> &w, base::String const &s_ );

/*
  split s into a vector of strings, separated by c
  removes whitespace around beginning and end of each part
*/
void
split( base::vector<base::String> &w, base::String const &s_, char c );


} // namespace base

#endif // base_Regex_INCLUDED
