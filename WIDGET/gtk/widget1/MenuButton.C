/* GANG Software
 * WIDGET/gtk/widget1/MenuButton.C
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

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1174
#endif
#include <gtk/gtksignal.h>
#include <gtk/gtkmenu.h>
#include <gtk/gtkmenuitem.h>
#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#endif

#include "base/System.H"
#include "gtk/widget0/Widget.H"
#include "MenuButton.H"

namespace gtk {
namespace widget1 {

  /*
    four entities:
    (1) widget overarching GtkMenuButton
    (2) its parent, the GtkOptionMenu
    (3) the menu (inside the GtkOptionMenu)
    (4) the menu_items (inside the GtkOptionMenu)
  */

MenuButton::
MenuButton(
  uint value,
  char const *label[],
  uint count )
    :
    gtk::widget0::Widget(gtk_option_menu_new()),
    _value(0),
    _count(count)
{
  _data = new Data[count];
  _menu_item = new GtkMenuItem *[_count];

  //  create a new menu, put it into the option_menu, and show it
  _menu = GTK_MENU(gtk_menu_new());
  gtk_option_menu_set_menu( GTK_OPTION_MENU(_w), GTK_WIDGET(_menu) );
  gtk_widget_show( GTK_WIDGET(_menu) );

  uint i;
  for ( i = 0; i < _count ; i++ )
  {
    // create a new menu_item and insert it
    _menu_item[i] =
      GTK_MENU_ITEM(gtk_menu_item_new_with_label(label[i]));
    gtk_widget_show( GTK_WIDGET(_menu_item[i]) );
    gtk_menu_append( _menu, GTK_WIDGET(_menu_item[i]) );
    _data[i].widget = this;
    _data[i].value = i;

    //  connect a signal, passing integer index to the signal
    gtk_signal_connect(
      GTK_OBJECT(_menu_item[i]),
      "activate",
      GTK_SIGNAL_FUNC( data_callback ), _data + i );
  }
  set(value);
}

MenuButton::
~MenuButton()
{
  gtk_widget_destroy( GTK_WIDGET(_menu) );
  delete [] _menu_item;
  delete [] _data;
}

void
MenuButton::
set( uint value )
{
  DIE_IF( value >= _count );
  _value = value;
  gtk_option_menu_set_history( GTK_OPTION_MENU(_w), _value );
}

void
MenuButton::
_connect( void *obj, StaticCallbackFnPtr fn )
{
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    gtk_signal_connect(
      GTK_OBJECT(_menu_item[i]),
      "activate",
      GTK_SIGNAL_FUNC(fn), obj );
  }
}

void
MenuButton::
_block( gpointer obj )
{
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    gtk_signal_handler_block_by_data( GTK_OBJECT(_menu_item[i]), obj );
  }
}

void
MenuButton::
_unblock( gpointer obj )
{
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    gtk_signal_handler_unblock_by_data( GTK_OBJECT(_menu_item[i]), obj );
  }
}

void
MenuButton::
data_callback( GtkWidget *, void *p )
{
  ((Data *)p)->widget->_value = ((Data *)p)->value;
}

} // namespace widget1
} // namespace gtk
