/* GANG Software
 * BASE/base/System.C
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

// Recompile this file to update the version date string.

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <new>
#include <iostream>
#include <exception>
#include "Exception.H"
#include "System.H"
#include "memory.H"

/*
  NOTE:
  BUG: If a first DIE_IF() calls a second DIE_IF(),
  the second returns successfully and the first aborts,
  then the file/line info will be wrong (will match the second DIE_IF()
*/

namespace base {

static System system0;
System * const system = &system0;

System::
System()
{
  name("");
  file(__FILE__,__LINE__,_FUNCTION);
  set_new_handler(newhandler);
  std::set_terminate(terminate);

  getdate(_version);
}


int
System::
run( int (*main)(int argc, char *argv[]), int argc, char *argv[] )
{
#ifdef DEBUG
#if defined(__sgi)
  std::cerr << "---------------------------------------------------\n";
#endif
#endif

  try
  {
    int x = main(argc, argv);
#ifdef DEBUG
    ::check_memory();
#endif
    return x;
  }
  catch ( Exception const &e )
  {
    fprintf( stderr, "top level exception:\n");
//    DIE( e.message().c_str());
    DIE( e.message() );
    return 1;
  }
}

void
System::
print_version() const
{
  std::cout << _name << "-v" << _version << " " << _copyright << std::endl;
}

void
System::
help() const
{
  std::cout << _name << "-" << _version << " " << _copyright << "\n"
       << _usage << "\n" << _options << std::flush;
}

void
System::
usage(char option, int error_type) const
{
  if (option == 0 )
  {
    std::cerr << "usage: " << _usage << "\n" << _options << std::flush;
  }
  else
  {
    std::cerr << _name << ": ";
    if ( error_type == 1 )
    {
      std::cerr << "unknown option \'" << option << "\'\n";
    }
    else if ( error_type == 2 )
    {
      std::cerr << "missing argument to option \'" << option << "\'\n";
    }
  }
}

void
System::
newhandler()
{
  system->file(__FILE__,__LINE__,_FUNCTION);
  system->die( "out of memory" );
}

void
System::
terminate()
{
  system->file(__FILE__,__LINE__,_FUNCTION);
  system->die( "top-level exception" );
}

#if defined(DEBUG)
void
System::
warn( const char *fmt, ...) const
{
  fprintf( stderr, "%s: warning: ", _name );

  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);

  print();
}

void
System::
warn( bool flag ) const
{
  if (!flag) { return; }

  fprintf( stderr, "%s: warning", _name );
  print();
}

void
System::
warn( bool flag, const char *fmt, ...) const
{
  if (!flag) { return; }

  fprintf( stderr, "%s: warning: ", _name );

  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);

  print();
}

void
System::
die( bool flag ) const
{
  if (!flag) { return; }

  fprintf( stderr, "%s: error", _name );

  print();

  abort();
}

void
System::
die( const char *fmt, ...) const
{
  fprintf( stderr, "%s: error: ", _name );

  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);

  print();

  abort();
}

void
System::
die( bool flag, const char *fmt, ...) const
{
  if (!flag) { return; }

  fprintf( stderr, "%s: error: ", _name );

  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);

  print();

  abort();
}

void
System::
trace() const
{
  fprintf( stderr, "%s: trace", _name );
  print();
}
#endif

void
System::
print() const
{
  if (_function == (char *)0)
  {
    fprintf( stderr, " (%s:%d)\n", _file, _line );
  }
  else
  {
    fprintf( stderr, "\n  [%s]\n  (%s:%d)\n", _function, _file, _line );
  }
}

void
System::
getdate( char date[7] )
{
  static const char *months[] =
  {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
   "Jul", "Aug","Sep", "Oct", "Nov", "Dec"};

  // Recompile this file to update the version date string.
  char const *d = __DATE__;
  // date looks like "Mar 04 2001"

  // year
  date[0] = d[9];
  date[1] = d[10];

  // month
  int month = 0;
  uint i;
  for (i = 0; i < 12; i++)
  {
    if (!strncmp(d, months[i], 3))
    {
      month = i + 1; break;
    }
  }
  DIE_IF(month == 0);
  if (month < 10)
  { date[2] = '0'; date[3] = month + '0'; }
  else
  { date[2] = '1'; date[3] = month-10 + '0'; }

  // day
  date[4] = ( d[4] == ' ' ? '0' : d[4] );
  date[5] = d[5];
  date[6] = 0;
}

} // namespace base
