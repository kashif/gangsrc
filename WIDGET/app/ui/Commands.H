/* GANG Software
 * WIDGET/app/ui/Commands.H
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

#ifndef app_ui_Commands_INCLUDED
#define app_ui_Commands_INCLUDED

#include "base/String.H"
#include "widget/ui/Dialog.H"
#include "widget/ui/String.H"

namespace app {
namespace ui {

class Commands
  :
    public widget::ui::Dialog
{

public:

  // constructor
  Commands();

  // destructor
  virtual ~Commands();

  virtual void command_respond(
    base::String const &text, bool raw );

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:

  // callbacks
  virtual void execute_cb();

  char const *label() const
    { return "Commands"; }

private:

  // pure virtuals
  virtual void execute_command( base::String const &text ) = 0;

  // widgets
  virtual ::widget::ui::String *text_w() = 0;
  virtual ::widget::ui::String const *text_w() const = 0;

  Commands( Commands const & );
  Commands &operator=( Commands const & );

};

} // namespace ui
} // namespace app

#endif // app_ui_Commands_INCLUDED
