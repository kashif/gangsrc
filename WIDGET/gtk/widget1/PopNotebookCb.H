/* GANG Software
 * WIDGET/gtk/widget1/PopNotebookCb.H
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

#ifndef gtk_widget1_PopNotebookCb_INCLUDED
#define gtk_widget1_PopNotebookCb_INCLUDED

#include "PopNotebook.H"

namespace gtk {
namespace widget1 {

template <class A>
class PopNotebookCb :
  public PopNotebook
{
public:

  typedef void (A::*PopNotebookCallbackFnPtr)();

  PopNotebookCb( A *obj, PopNotebookCallbackFnPtr fn ) :
      PopNotebook(),
      _page(0),
      _obj(obj),
      _fn(fn)
    {
      gtk_signal_connect(
        GTK_OBJECT(w()),
        "switch_page",
        GTK_SIGNAL_FUNC(static_callback_fn),
        this );
    }

  void add_blocked( gtk::widget0::Widget *w )
    { block(); add(w); unblock(); }

  void set_blocked( uint page )
    { _page = page; block(); set_page(page); unblock(); }

  virtual uint get() const { return _page; }

  void block()
    { gtk_signal_handler_block_by_data(GTK_OBJECT(w()), this ); }
  void unblock()
    { gtk_signal_handler_unblock_by_data(GTK_OBJECT(w()), this ); }

private:
  uint _page; // set by callback

private:

  // static wrapper for the callback fn
  static void static_callback_fn(
    GtkPopNotebook *, GtkPopNotebookPage *, gint page, gpointer p )
    {
      PopNotebookCb *me = static_cast<PopNotebookCb *>((void *)p);
      me->_page = page;
      (me->_obj->*(me->_fn))();
    }

  A *_obj;
  PopNotebookCallbackFnPtr _fn;

};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_PopNotebookCb_INCLUDED
