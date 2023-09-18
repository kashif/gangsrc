/* GANG Software
 * BASE/base/Getopt.C
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

#include <getopt.h>
#include <iostream>
#include "Exception.H"
#include "Getopt.H"

namespace base {

Getopt::
Getopt( Getopt::Options const *options, uint length )
    :
    _optstring(),
    _opthash()
#ifdef _GNU_SOURCE
    ,_longoptions()
#endif
{
  uint i;
  for ( i = 0; i < length; i++ )
  {
    _optstring += options[i].short_option;
    if (options[i].has_arg)
    {
      _optstring += ':';
    }
#ifdef _GNU_SOURCE
    ::option longoption;
    longoption.name = options[i].long_option;
    longoption.has_arg = options[i].has_arg;
    longoption.flag = (int *)0;
    longoption.val = options[i].short_option;
    _longoptions.push_back(longoption);
#endif
  }
#ifdef _GNU_SOURCE
  // make the last element 0
  ::option longoption;
  longoption.name = (char *)0;
  longoption.has_arg = 0;
  longoption.flag = (int *)0;
  longoption.val = 0;
  _longoptions.push_back(longoption);
#endif

  // set ::opterr to 0 to prevent getopt() from reporting errors
  ::opterr = 0;
}

int
Getopt::
getopt( int argc, char const * const argv[] )
{
  int r = 0;

  // put options into _opthash
  int c;
  for (;;)
  {
#ifdef _GNU_SOURCE
    c = ::getopt_long( argc, (char *const *)argv, _optstring.c_str(),
                  &*_longoptions.begin(), (int *)0 );
#else
    c = ::getopt( argc, (char *const *)argv, _optstring.c_str() );
#endif
    if ( c == -1 )
    {
      // done
      break;
    }
    else if ( c == '?' )
    {
#ifdef _GNU_SOURCE
      // look for option in list
      uint i;
      DIE_IF(_longoptions.size() == 0);
      for ( i = 0; i < _longoptions.size() - 1; i++ )
      {
        if (_longoptions[i].val == optopt())
        {
          // option with missing argument
          r = 2;
          break;
        }
      }
      // unknown option
      if (r==0) { r = 1; }
      break;
#else
      // unknown option
      r = 1;
#endif
      break;
    }
    else if ( c == ':' )
    {
      // option with missing argument
      r = 2;
      break;
    }
    else if (c == 0)
    {
      DIE();
    }
    else
    {
      // valid option
      _opthash[c] = ( optarg == (char *)0 ? "" : optarg );
    }
  }
  return r;
}

Getopt::
~Getopt()
{
}

int
Getopt::
optind()
{
  return ::optind;
}

char
Getopt::
optopt()
{
  return ::optopt;
}

bool
Getopt::
defined( char c )
{
  Opt::const_iterator i = _opthash.find(c);
  return i != _opthash.end();
}

base::String const &
Getopt::
option( char c )
{
  Opt::const_iterator i = _opthash.find(c);
  DIE_IF( i == _opthash.end(), "reference to unspecified option %c", c );
  return (*i).second;
}

} // namespace base
