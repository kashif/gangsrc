/* GANG Software
 * WIDGET/gtk/widget1/NumberWidget2Cb.H
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

#ifndef gtk_widget1_NumberWidget2Cb_INCLUDED
#define gtk_widget1_NumberWidget2Cb_INCLUDED

#include "NumberWidget2.H"

namespace gtk {
namespace widget1 {


template <class A>
class NumberWidget2Callback
{
public:
  typedef void (A::*WidgetCallbackFnPtr)() ;

  NumberWidget2Callback(
    NumberWidget2 *w,
    uint count,
    A *obj,
    WidgetCallbackFnPtr fn )
      :
      _w(w),
      _count(count),
      _obj(obj),
      _fn(fn)
    { _w->_connect( this, GTK_SIGNAL_FUNC(static_callback_fn) ); }

  void block() { _w->_block(this); }
  void unblock() { _w->_unblock(this); }

private:

  // static wrapper for the callback fn
  static void static_callback_fn( GtkWidget *, gpointer p )
    {
      NumberWidget2Callback<A> *me =
        static_cast<NumberWidget2Callback *>((void *)p);
      (me->_obj->*(me->_fn))();
    }

  NumberWidget2 *_w;
  uint _count;
  A *_obj;
  WidgetCallbackFnPtr _fn;
};


template <class A>
class NumberWidget2Cb :
  public NumberWidget2,
  public NumberWidget2Callback<A>
{
public:
  typedef void (A::*ObjectCallbackFnPtr)() ;

  NumberWidget2Cb(
    char const *frame_label,
    numberwidget_config const config[],
    uint count, A *obj, ObjectCallbackFnPtr fn ) :
      NumberWidget2( frame_label, config, count ),
      NumberWidget2Callback<A>(
        this, count, obj, fn ) {}

  void set_blocked(float const value[])
    { block(); set(value); unblock(); }
  void set_blocked(int const value[])
    { block(); set(value); unblock(); }
};


} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_NumberWidget2Cb_INCLUDED
