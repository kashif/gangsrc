/* GANG Software
 * WIDGET/gtk/widget1/MenuButtonCb.H
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

#ifndef gtk_widget1_MenuButtonCb_INCLUDED
#define gtk_widget1_MenuButtonCb_INCLUDED

#include "MenuButton.H"

namespace gtk {
namespace widget1 {

template <class A>
class MenuButtonCallback
{
public:
  typedef void (A::*CallbackFnPtr)() ;

  MenuButtonCallback(
    MenuButton *w,
    uint count,
    A *obj,
    CallbackFnPtr fn )
      :
      _w(w),
      _count(count),
      _obj(obj),
      _fn(fn)
    { _w->_connect( this,
                    static_cast<MenuButton::StaticCallbackFnPtr>(
                    static_callback_fn ) ); }

  void block() { _w->_block(this); }
  void unblock() { _w->_unblock(this); }

private:

  // static wrapper for the callback fn
  static void static_callback_fn( GtkWidget *, gpointer p )
    {
      MenuButtonCallback<A> *me =
        static_cast<MenuButtonCallback *>((void *)p);
      (me->_obj->*(me->_fn))();
    }

  MenuButton *_w;
  uint _count;
  A *_obj;
  CallbackFnPtr _fn;
};


/*
  class gtk:LMenuButton: a GtkOptionMenu which knows it's own value

  template <class A> class gtk::widget0::MenuButtonWidgetCallback:
    version which provides a static callback
*/


template <class A>
class MenuButtonCb :
  public MenuButton,
  public MenuButtonCallback<A>
{
public:
  typedef void (A::*CallbackFnPtr)() ;

  MenuButtonCb(
    uint value,
    char const *label[],
    uint count,
    A *obj, CallbackFnPtr fn ) :
      MenuButton( value, label, count ),
      MenuButtonCallback<A>(
        this, count, obj, fn ) {}

  // NOTE: set() does not call the callback
  virtual void set_blocked(uint value)
    { block(); set(value); unblock(); }
};


} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_MenuButtonCb_INCLUDED
