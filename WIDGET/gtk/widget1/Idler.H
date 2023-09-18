/* GANG Software
 * WIDGET/gtk/widget1/Idler.H
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

#ifndef gtk_widget1_Idler_INCLUDED
#define gtk_widget1_Idler_INCLUDED

#include <gtk/gtkmain.h>
#include "widget/ui/Idler.H"

namespace gtk {
namespace widget1 {

template <class A>
class IdlerCallback
{
public:
  typedef int (A::*CallbackFnPtr)();

  IdlerCallback( A *obj, CallbackFnPtr fn )
      : _obj(obj), _fn(fn) {}

  static int static_callback_fn( void *p )
    {
      IdlerCallback<A> *me = static_cast<IdlerCallback *>(p);
      return (me->_obj->*(me->_fn))();
    }
protected:
  A *_obj;
  CallbackFnPtr _fn;
};

template <class A>
class Idler
  :
    public IdlerCallback<A>
{
public:
  typedef int (A::*CallbackFnPtr)();

  // constructor
  Idler( A *obj, CallbackFnPtr fn )
      : IdlerCallback<A>( obj, fn ), _enable(false) {}
  void enable( bool state )
    {
      if ( state && ! _enable ) { enable_(_enable = true); }
      else if ( !state && _enable ) { enable_(_enable = false); }
    }
protected:
  virtual void enable_( bool state ) = 0;
private:
  mutable bool _enable;
};

template <class A>
class GtkIdler
  :
    public ::widget::ui::Idler,
    public ::gtk::widget1::Idler<A>
{
public:
  typedef int (A::*CallbackFnPtr)();

  // constructor
  GtkIdler( A *obj, CallbackFnPtr fn )
      : ::gtk::widget1::Idler<A>( obj, fn ), _id(0) {}

  virtual void enable(bool state)
    { ::gtk::widget1::Idler<A>::enable(state); }
protected:
  virtual void enable_( bool state )
    {
      if (state) { _id = gtk_idle_add(
                     &static_callback_fn,
                     static_cast<IdlerCallback<A> *>(this) ); }
      else { gtk_idle_remove( _id ); }
    }
private:
  gint _id;
};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_Idler_INCLUDED
