/* GANG Software
 * WIDGET/app/ui/Message.C
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

#include "base/System.H"
#include "Message.H"

namespace app {
namespace ui {

Message::
Message()
    :
    widget::ui::Dialog()
{
}

Message::
~Message()
{
}


void
Message::
message( base::String const &text ) const
{
  Message *p = (Message *)this;  // NOTE: remove const

  if (text.empty()) {
    p->messagebox_w()->set_blocked("");
  }
  else
  {
    p->messagebox_w()->set_blocked(text.c_str());
    p->raise_d(true);
    p->show_d(true);
  }
}

void
Message::
clear_cb()
{
  messagebox_w()->set_blocked("");
}

bool
Message::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  return false;
}

} // namespace ui
} // namespace app
