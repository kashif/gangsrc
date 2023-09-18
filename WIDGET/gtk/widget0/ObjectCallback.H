/* GANG Software
 * WIDGET/gtk/widget0/ObjectCallback.H
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

#ifndef gtk_widget0_ObjectCallback_INCLUDED
#define gtk_widget0_ObjectCallback_INCLUDED

#include "Callback.H"

namespace gtk {
namespace widget0 {

template <class A>
class ObjectCallback
  :
    public Callback<A>
{
public:
  typedef void (A::*CallbackFnPtr)();

  ObjectCallback(
    Object *x,
    A *obj,
    CallbackFnPtr fn,
    char const *signal_name )
      :
      Callback<A>( obj, fn ),
    _w(x->w())
    {
      // set the widget's callback fn
      gtk_signal_connect(
        _w,
        signal_name,
        GTK_SIGNAL_FUNC(static_callback_fn),
        this );
    }

  // GtkWidget constructor
  ObjectCallback(
    GtkObject *x,
    A *obj,
    CallbackFnPtr fn,
    char const *signal_name )
      :
      Callback<A>( obj, fn ),
    _w(x)
    {
      // set the widget's callback fn
      gtk_signal_connect(
        _w,
        signal_name,
        GTK_SIGNAL_FUNC(static_callback_fn),
        this );
    }

  void block()
    { gtk_signal_handler_block_by_data(_w, this); }
  void unblock()
    { gtk_signal_handler_unblock_by_data(_w, this); }

private:
  GtkObject *_w;

  ObjectCallback( ObjectCallback<A> const & );
  ObjectCallback &operator=( ObjectCallback<A> const & );
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_ObjectCallback_INCLUDED
