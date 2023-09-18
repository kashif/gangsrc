/* GANG Software
 * WIDGET/app/ui/Message.H
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

#ifndef app_ui_Message_INCLUDED
#define app_ui_Message_INCLUDED

#include "base/String.H"
#include "widget/ui/String.H"
#include "widget/ui/Dialog.H"

namespace app {
namespace ui {

class Message
  :
    public widget::ui::Dialog
{

public:

  // constructor
  Message();

  // destructor
  virtual ~Message();

  virtual void message( base::String const &text ) const;

  bool command(
    base::String const &command,
    base::String const &argument,
    base::String &response );

protected:
  // widgets
  virtual widget::ui::String *messagebox_w() = 0;
  virtual widget::ui::String const *messagebox_w() const = 0;

  // callbacks
  void clear_cb();

  char const *label() const
    { return "Message"; }

private:

  Message( Message const & );
  Message &operator=( Message const & );
};

} // namespace ui
} // namespace app

#endif // app_ui_Message_INCLUDED
