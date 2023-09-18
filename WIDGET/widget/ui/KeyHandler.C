/* GANG Software
 * WIDGET/widget/ui/KeyHandler.C
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

#include <iostream>
#include <iomanip>
#include "gtk/widget0/Callback.H"
#include "KeyHandler.H"

namespace widget {
namespace ui {

KeyHandler::
KeyHandler()
{
}

KeyHandler::
~KeyHandler()
{
}

int
KeyHandler::
go( uint key, uint modifier ) const
{
  // only see shift, control and alt
  GdkModifierType mask =
    GdkModifierType(GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK);

  // if caps lock is on, interprets key as capital

  std::list<EntryBase *>::const_iterator i;
  for ( i = entry().begin(); i != entry().end(); i++ )
  {
#if 0
    std::cerr << ")" << (char)key << ", " << modifier << ")"
              << "(" << (char)(*i)->key << ", " << (*i)->modifier << ")\n";
#endif
    if ( (*i)->key == key &&
         ((*i)->modifier & mask) == GdkModifierType(modifier) )
    {
      (*i)->call();
      return 1;
    }
  }
  return 0;
}


} // namespace ui
} // namespace widget
