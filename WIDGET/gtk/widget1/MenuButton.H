/* GANG Software
 * WIDGET/gtk/widget1/MenuButton.H
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

#ifndef gtk_widget1_MenuButton_INCLUDED
#define gtk_widget1_MenuButton_INCLUDED

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1174
#endif
#include <gtk/gtkoptionmenu.h>
#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#endif

#include "widget/ui/Choice.H"
#include "gtk/widget0/Widget.H"

namespace gtk {
namespace widget1 {

/*
  class gtk:LMenuButton: a GtkOptionMenu which knows it's own value
*/

class MenuButton
  :
    public widget::ui::Choice,
    public gtk::widget0::Widget
{

public:

  // constructor
  MenuButton( uint value, char const *label[], uint count );

  // destructor
  virtual ~MenuButton();

  void set( uint value );
  uint get() const
    { return _value; }

  virtual bool showing( uint n ) const
    { return GTK_WIDGET_VISIBLE(_menu_item[n]); }
  virtual void show( bool state = true )
    { ::gtk::widget0::Widget::show(state); }
  virtual void show( uint n, bool state )
    {
      if (state)
      { gtk_widget_show( GTK_WIDGET(_menu_item[n]) ); }
      else
      { gtk_widget_hide( GTK_WIDGET(_menu_item[n]) ); }
    }
  virtual void set_sensitive( uint n, bool state )
    { gtk_widget_set_sensitive( GTK_WIDGET(_menu_item[n]), state ); }

  typedef void (*StaticCallbackFnPtr)(GtkWidget *, gpointer);

  void _block( void *obj );
  void _unblock( void *obj );
  void _connect( void *obj, StaticCallbackFnPtr fn );

protected:

private:

  GtkMenu *_menu;
  GtkMenuItem **_menu_item;
  uint _value;
  uint _count;

  struct Data
  {
    MenuButton *widget;
    uint value;
  };

  Data *_data;

  static void data_callback( GtkWidget *, void *p );

private:

  MenuButton( MenuButton const & );
  MenuButton &operator=( MenuButton const & );
};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_MenuButton_INCLUDED
