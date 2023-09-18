/* GANG Software
 * BASE/base/Getopt.H
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

#ifndef base_Getopt_INCLUDED
#define base_Getopt_INCLUDED

#ifdef _GNU_SOURCE
#include <vector>
#endif
#include <map>
#ifdef _GNU_SOURCE
#include <getopt.h>
#else
#include <unistd.h>
#endif
#include "System.H"
#include "String.H"

namespace base {

/*
  Parse commandline options.
  Places command line options into a hash.
 */

class Getopt
{

public:

  struct Options
  {
    char short_option;
    char const *long_option;
    bool has_arg;
  };

  // void constructor
  Getopt( Options const *options, uint length );

  // destructor
  virtual ~Getopt();

  // Flags is something like "c:h:op" (see getopt(3)).
  // Flags should not start with a ":".
  // Returns:
  //   0: no errors
  //   1: illegal option ( optopt() returns the option )
  //   2: missing argument ( optopt() returns the option ).
  int getopt( int argc, char const * const argv[] );

  // Returns true if the option c was used on the command line
  // (c may be an option with or without argument).
  bool defined( char c );

  // Returns the argument associated with the c option
  // if the c option was not used on the command line or is a boolean
  // option, returns the empty string.
  base::String const &option( char c );

  // Returns the index into argv after the command line options and
  // their arguments (same as the optind set by getopt(3)).
  int optind();

  // Returns the character that caused an error.
  char optopt();

protected:

private:

  base::String _optstring;
  typedef std::map<char, base::String, std::less<char> > Opt;
  Opt _opthash;

#ifdef _GNU_SOURCE
  std::vector< ::option> _longoptions;
#endif

  // disabled copy constructor
  Getopt( Getopt const & );
  // disabled assignment operator
  Getopt &operator=( Getopt const & );
};

} // namespace base

#endif // base_Getopt_INCLUDED
