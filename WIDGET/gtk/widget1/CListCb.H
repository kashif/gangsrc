/* GANG Software
 * WIDGET/gtk/widget1/CListCb.H
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

#ifndef gtk_widget1_CListCb_INCLUDED
#define gtk_widget1_CListCb_INCLUDED

#include <iostream>
#include "CList.H"

namespace gtk {
namespace widget1 {

/*
  CListCallbackBase
*/
template <class A>
class CListCallbackBase
{
public:
  typedef void (A::*CallbackFnPtr)();

  // GtkWidget constructor
  CListCallbackBase( A *obj, CallbackFnPtr fn ) :
      _obj(obj),
      _fn(fn) {}

  // static wrapper for the callback fn
  static void static_callback_fn(
    GtkWidget *, gint row, gint column, GdkEventButton *event, gpointer p )
    {
      CListCallbackBase<A> *me = static_cast<CListCallbackBase *>((void *)p);
      (me->_obj->*(me->_fn))();
    }

  A *_obj;
  CallbackFnPtr _fn;

private:
  CListCallbackBase( CListCallbackBase<A> const & );
  CListCallbackBase &operator=( CListCallbackBase<A> const & );
};


/*
  CListCallback
*/
template <class A>
class CListCallback
  :
    public CListCallbackBase<A>
{
public:
  typedef void (A::*CallbackFnPtr)();

  CListCallback(
    gtk::widget0::Object *x,
    A *obj,
    CallbackFnPtr fn )
      :
      CListCallbackBase<A>( obj, fn ),
    _w(x->w())
    {
      // set the widget's callback fn
      gtk_signal_connect(
        _w,
        "select_row",
        GTK_SIGNAL_FUNC(static_callback_fn),
        this );
    }

  void block()
    { gtk_signal_handler_block_by_data(_w, this); }
  void unblock()
    { gtk_signal_handler_unblock_by_data(_w, this); }

private:
  GtkObject *_w;

  CListCallback( CListCallback<A> const & );
  CListCallback &operator=( CListCallback<A> const & );
};


/*
  CListCb
*/
template <class A>
class CListCb
  :
    public gtk::widget0::CList,
    public CListCallback<A>
{

public:
  typedef void (A::*CallbackFnPtr)();

  // constructor
  CListCb( int columns, A *obj, CallbackFnPtr fn )
      : gtk::widget0::CList(columns),
        CListCallback<A>( this, obj, fn) {}

  // constructor
  CListCb( int columns, char *titles[] )
      : gtk::widget0::CList(columns, titles),
        CListCallback<A>( this, obj, fn) {}

  // destructor
  virtual ~CListCb() {}

//  typedef void (*StaticCallbackFnPtr)(GtkWidget *, gpointer);

  void select_row_blocked( int row, int column )
    { block(); select_row(row, column); unblock(); }
  int append_blocked( char const *text[] )
    { block(); int r = append(text); unblock(); return r; }

  virtual void set_blocked( uint n )
    { select_row_blocked(n, 0); }
  virtual void append_blocked(char const *label)
    { append_blocked(&label); }

protected:

private:

  // disabled copy constructor
  CListCb( CListCb const & );

  // disabled assignment operator
  CListCb &operator=( CListCb const & );

};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_CListCb_INCLUDED
