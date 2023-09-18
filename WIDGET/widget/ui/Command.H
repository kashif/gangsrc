/* GANG Software
 * WIDGET/widget/ui/Command.H
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

#ifndef widget_ui_Command_INCLUDED
#define widget_ui_Command_INCLUDED

#include <iostream>
#include <strstream>
#include "base/ReadUtil.H"

namespace widget {
namespace ui {

class Command
  :
    public base::ReadUtil
{

public:
  // constructor
  Command();

  // destructor
  virtual ~Command();

  void execute_command( uint fd, uint type );
  void execute_command( base::String const &text, bool raw = false );

protected:

  virtual void command_respond(
    base::String const &response, bool raw ) = 0;

private:

  // pure virtual
  virtual bool
  command(
    base::String const &command,
    base::String const &argument,
    base::String &response ) = 0;

  // pure virtual
  virtual void message( base::String const & ) const = 0;

  bool getline( base::String &s );
  base::String _buffer;

  // disabled copy constructor
  Command( Command const & );
  // disabled assignment operator
  Command &operator=( Command const & );

};


} // namespace ui
} // namespace widget

#endif // widget_ui_Command_INCLUDED
