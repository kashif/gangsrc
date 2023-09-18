/* GANG Software
 * WIDGET/gtk/widget1/Menu.C
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
#include <gdk/gdkkeysyms.h>
#include <gtk/gtktearoffmenuitem.h>
#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#endif

#include "base/System.H"
#include <iostream>

#include "Menu.H"

namespace gtk {
namespace widget1 {

Menu::
Menu( base::String const &label )
    :
    gtk::widget0::Widget( gtk_menu_bar_new() ),
    widget::ui::KeyBase(),
    _accelgroup()
{
  // menu_bar -> menu_item -> menu -> m

  // create a new menu_bar
  GtkMenuBar *menu_bar = GTK_MENU_BAR(_w);
  gtk_widget_show(GTK_WIDGET(menu_bar));

  // create a new menu_item
  GtkMenuItem *menu_item = GTK_MENU_ITEM(
    gtk_menu_item_new_with_label(label.c_str()) );
  gtk_widget_show( GTK_WIDGET(menu_item) );

  // put the menu_item into the menu_bar
  gtk_menu_bar_append(GTK_MENU_BAR(menu_bar), GTK_WIDGET(menu_item));

#if 0
  // accelerator that drops the menu
  gtk_widget_add_accelerator(
    GTK_WIDGET(menu_item),
    "activate_item",
    accelgroup,
    GDK_A + (toupper(label[0]) - 'A'), GDK_MOD1_MASK,
    GTK_ACCEL_LOCKED);
#endif

  // create a new menu
  _menu = GTK_MENU(gtk_menu_new());
  gtk_widget_show( GTK_WIDGET(_menu) );

  // put menu into menu_item
  gtk_menu_item_set_submenu(menu_item, GTK_WIDGET(_menu));

  // make menu tearoff
  GtkTearoffMenuItem *tearoff =
    GTK_TEAROFF_MENU_ITEM(gtk_tearoff_menu_item_new());
  gtk_widget_show(GTK_WIDGET(tearoff));

  gtk_menu_append( _menu, GTK_WIDGET(tearoff) );
}

Menu::
~Menu()
{
  std::list<_Item>::iterator i;
  for (i = _menuitem_list.begin(); i != _menuitem_list.end(); i++ )
  {
    gtk_widget_destroy( GTK_WIDGET( (*i).menuitem ) );
    if ( (*i).callback !=
         (gtk::widget0::Callback< ::widget::ui::EntryBase> *)0 )
    { delete (*i).callback; }
  }
}

void
Menu::
insert_v( widget::ui::EntryBase *e )
{

  GtkMenuItem *m = GTK_MENU_ITEM(gtk_menu_item_new_with_label(
                                   e->label.c_str() ));


  gtk::widget0::Callback< widget::ui::EntryBase> *p = new
    gtk::widget0::Callback<
    widget::ui::EntryBase>(e, &widget::ui::EntryBase::call);



  // save pointers for later delete
  _Item o;
  o.menuitem = m;
  o.callback = p;
  _menuitem_list.push_back(o);


  gtk_signal_connect(
    GTK_OBJECT(m), "activate",
    GTK_SIGNAL_FUNC( p->static_callback_fn ),
    (gpointer)p );

    
  if (e->key != 0)
  {
    gtk_widget_add_accelerator(
      GTK_WIDGET(m), "activate", _accelgroup.w(),
      e->key, e->modifier, GTK_ACCEL_VISIBLE );
  }
  gtk_menu_append( _menu, GTK_WIDGET(m));
  gtk_widget_show(GTK_WIDGET(m));
}

void
Menu::
insert_separator()
{
  GtkMenuItem *m = GTK_MENU_ITEM(gtk_menu_item_new());

  // save pointers for later delete
  _Item o;
  o.menuitem = m;
  o.callback = (gtk::widget0::Callback< widget::ui::EntryBase> *)(0);
  _menuitem_list.push_front(o);

  gtk_widget_set_sensitive( GTK_WIDGET(m), false );
  gtk_menu_append( _menu, GTK_WIDGET(m));
  gtk_widget_show(GTK_WIDGET(m));
}

} // namespace widget1
} // namespace gtk
