/* GANG Software
 * BASE/base/System.H
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
// Recompile System.C to update the version date string.

#ifndef base_System_INCLUDED
#define base_System_INCLUDED

#include "Use.h"

typedef int unsigned uint;

namespace base {

#if defined(__GNUC__)
#define _FUNCTION __PRETTY_FUNCTION__
#else
#define _FUNCTION (char *)0
#endif

class System
{
public:

  static int run( int (*main)(int argc , char* argv[]),
                  int argc, char *argv[] );

  // Constructor.
  System();

  char const *version() const
    { return _version; }

  // Print an app version message to std::cout.
  void print_version() const;

  // Print a help message to std::cout.
  void help() const;

  // Print a usage message to std::cout.
  // option == 0: Print a simple usage message.
  // option != 0 and error_type == 1: Print an "unknown option" message.
  // option != 0 and error_type == 2: Print an "missing argument to option"
  // message.
  void usage( char option = 0, int error_type = 0 ) const;

#if 0
  // Set the app version number to s.
  void version(char const *s) { _version = s; }
#endif

  // Set the copyright message to s.
  void copyright(char const *s) { _copyright = s; }

  // Set the usage message to s.
  void usage(char const *s) { _usage = s; }

  // Set the options informational message to s.
  void options(char const *s) { _options = s; }

  // Returns the app's name
  char const *name() const
    { return _name; }

  // Set the app's name
  void name( char const *name ) { _name = name; }

  // Set the file and line number information. Used by the WARN and DIE
  // macros.
  void file( char const *file, int line, char const *function )
    { _file = file; _line = line; _function = function; }

#if defined(DEBUG)
  void warn( bool flag=true ) const;
  void warn( char const *format, ... ) const;
  void warn( bool flag, char const *format, ... ) const;
  void die( bool flag=true ) const;
  void die( char const *format, ... ) const;
  void die( bool flag, char const *format, ... ) const;
  void trace() const;
#else
  void warn( bool flag=true ) const {}
  void warn( char const *format, ... ) const {}
  void warn( bool flag, char const *format, ... ) const {}
  void die( bool flag=true ) const {}
  void die( char const *format, ... ) const {}
  void die( bool flag, char const *format, ... ) const {}
  void trace() const {}
#endif

private:
  void print() const;

  void getdate( char date[7] );

  // App name.
  char const *_name;

  // App version number.
  char _version[7];

  // Copyright message.
  char const *_copyright;

  // App usage message.
  char const *_usage;

  // Options info message.
  char const *_options;

  // Filename.
  char const *_file;

  // File line number.
  int _line;

  // Function name.
  char const *_function;

  // Catch out-of-memory errors.
  static void newhandler();

  // Catch top-level exceptions.
  static void terminate();
};

extern System * const system;

// macros are used here to automatically insert file/line info
// WARN and DIE use macros in a non-standard way to allow
// variable numbers of arguments
#undef WARN
#undef WARN_IF
#undef DIE
#undef DIE_IF
#undef TRACE

#if defined(DEBUG)

#define WARN \
 base::system->file(__FILE__,__LINE__,_FUNCTION); base::system->warn
#define WARN_IF WARN
#define DIE \
 base::system->file(__FILE__,__LINE__,_FUNCTION); base::system->die
#define DIE_IF DIE
#define TRACE \
 base::system->file(__FILE__,__LINE__,_FUNCTION); base::system->trace();

#else

#define WARN \
 base::system->warn
#define WARN_IF WARN
#define DIE \
 base::system->die
#define DIE_IF DIE
#define TRACE \
 base::system->trace();

#endif // DEBUG

} // namespace base

#endif // base_System_INCLUDED
