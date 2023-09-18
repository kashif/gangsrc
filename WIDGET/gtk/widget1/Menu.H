/* GANG Software
 * WIDGET/gtk/widget1/Menu.H
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

#ifndef gtk_widget1_Menu_INCLUDED
#define gtk_widget1_Menu_INCLUDED

#include <list>
#include "base/vector.H"
#include "gtk/widget0/Widget.H"
#include "gtk/widget0/Callback.H"
#include "widget/ui/KeyBase.H"

namespace gtk {
namespace widget1 {

/*
   Gtk menu
*/
class Menu
  :
    public gtk::widget0::Widget,
    public widget::ui::KeyBase
{

public:

  // constructor
  Menu( base::String const &label );

  // destructor
  virtual ~Menu();

  void title( base::String const &t );

  virtual void insert_separator();

  gtk::widget0::AccelGroup *accelerator()
    { return &_accelgroup; }
  gtk::widget0::AccelGroup const *accelerator() const
    { return &_accelgroup; }

private:

  virtual void insert_v( widget::ui::EntryBase *e );

  struct _Item {
    GtkMenuItem *menuitem;
    gtk::widget0::Callback< ::widget::ui::EntryBase> *callback;
  };

  std::list<_Item> _menuitem_list;

  gtk::widget0::AccelGroup _accelgroup;

  GtkMenu *_menu;
};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_Menu_INCLUDED
