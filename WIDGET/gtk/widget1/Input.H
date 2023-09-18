/* GANG Software
 * WIDGET/gtk/widget1/Input.H
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

#ifndef gtk_widget1_Input_INCLUDED
#define gtk_widget1_Input_INCLUDED

#include <gdk/gdk.h>
#include "base/System.H"

namespace gtk {
namespace widget1 {

template <class A>
class InputCallback
{
public:
  typedef void (A::*CallbackFnPtr)( uint fd, uint type );

  // GtkWidget constructor
  InputCallback( A *obj, CallbackFnPtr fn ) :
      _obj(obj),
      _fn(fn) {}

  // static wrapper for the callback fn
  static void static_callback_fn( gpointer p, gint fd,
                                  GdkInputCondition type )
    {
      InputCallback<A> *me = static_cast<InputCallback *>((void *)p);
      (me->_obj->*(me->_fn))( fd, type );
    }

  A *_obj;
  CallbackFnPtr _fn;

private:
  InputCallback( InputCallback<A> const & );
  InputCallback &operator=( InputCallback<A> const & );
};


template <class A>
class Input
  :
    public InputCallback<A>
{

public:
  typedef InputCallback<A>::CallbackFnPtr CallbackFnPtr;

  // constructor
  Input( A *obj, CallbackFnPtr fn );

  // destructor
  virtual ~Input();

  void set( bool state );

protected:

private:

  bool _state;
  uint _tag;

  // disabled copy constructor
  Input( Input const & );
  // disabled assignment operator
  Input &operator=( Input const & );

};


template <class A>
Input<A>::
Input( A *obj, CallbackFnPtr fn )
    :
    InputCallback<A>(obj, fn),
    _state(false),
    _tag(0)
{
}

template <class A>
Input<A>::
~Input()
{
}

template <class A>
void
Input<A>::
set( bool state )
{
  if (state)
  {
    // add stdin to input
    if (_state) { return; }
    _tag =
      gdk_input_add(
        0, GDK_INPUT_READ, static_callback_fn,
        gpointer(static_cast<InputCallback<A> *>(this)) );
  }
  else {
    // remove stdin to input
    if (!_state) { return; }
    gdk_input_remove( _tag );
  }
}

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_Input_INCLUDED
