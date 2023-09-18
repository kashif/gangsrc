/* GANG Software
 * WIDGET/widget/ui/Command.C
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

#include <unistd.h>
#include <gdk/gdk.h>
#include "base/Regex.H"
#include "Command.H"

namespace widget {
namespace ui {

Command::
Command()
    :
    base::ReadUtil(),
    _buffer()
{
}

Command::
~Command()
{
}

void
Command::
execute_command( uint fd, uint type )
{
  DIE_IF(fd != 0);

  base::String s;
  while (getline(s))
  {
//    std::cerr << "command=[" << s << "]\n";
    execute_command( base::String(s), true );
  }
}

void
Command::
execute_command( base::String const &text_, bool raw )
{
  base::String text = text_;
  text.strip();
  if (text.empty()) { return; }

  base::String response;

  try
  {
    base::String command0, argument;
    split1( command0, argument, text );
    bool r = command( command0, argument, response );
    if ( ! r )
    { throw base::Exception("unknown command"); }
  }
  catch ( base::Exception const &e )
  {
    response = base::String("error: ") + e.message();
  }
  command_respond( response, raw );
}

bool
Command::
getline( base::String &s )
{
  static char tmpbuffer[1024];

  for (;;)
  {
    // look for '\n'
    uint v = _buffer.find( '\n');

    if ( v != base::String::npos )
    {
      // found '\n'
      // set s to first part of tmpbuffer
      s = _buffer.substr( 0, v );
      // set buffer to remaining part of tmpbuffer
      _buffer = _buffer.substr( v + 1 );
      return true;
    }

    // read more input into buffer
    int n = ::read( 0, tmpbuffer, 1024 );
    if ( n == -1 )
    {
      // no data
      s.erase();
      return false;
    }
    if ( n == 0 )
    {
      WARN( "no data" );
      ::exit(1);
    }
    _buffer += base::String(tmpbuffer, n);
  }
}


} // namespace ui
} // namespace widget
