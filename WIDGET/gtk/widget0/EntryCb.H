/* GANG Software
 * WIDGET/gtk/widget0/EntryCb.H
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

#ifndef gtk_widget0_EntryCb_INCLUDED
#define gtk_widget0_EntryCb_INCLUDED

#include "Entry.H"
#include "ObjectCallback.H"

namespace gtk {
namespace widget0 {

template <class A>
class EntryCb :
  public Entry,
  public ObjectCallback<A>
{
public:
  typedef void (A::*CallbackFnPtr)();

  EntryCb(
    A *obj, CallbackFnPtr fn ) :
      Entry(),
      ObjectCallback<A>( this, obj, fn, "activate" ) {}

  EntryCb(
    uint max,
    A *obj, CallbackFnPtr fn ) :
      Entry( max ),
      ObjectCallback<A>( this, obj, fn, "activate" ) {}

};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_EntryCb_INCLUDED
