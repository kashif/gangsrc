/* GANG Software
 * WIDGET/app/app/AppMenu.H
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

#ifndef app_app_AppMenu_INCLUDED
#define app_app_AppMenu_INCLUDED

#include "gtk/widget0/VBox.H"
#include "gtk/widget0/Dialog.H"
#include "gtk/widget1/Menu.H"

namespace app {
namespace app {

class AppMenu
  :
    public ::gtk::widget0::Dialog
{

public:

  // constructor
  AppMenu( char const *app_name );

  virtual ~AppMenu();

  virtual void raise_show();

protected:

  void insert_menu( ::gtk::widget1::Menu &menu );

private:

  ::gtk::widget0::VBox *_vbox_w;

  // disabled copy constructor
  AppMenu( AppMenu const & );

  // disabled assignment operator
  AppMenu &operator=( AppMenu const & );
};

} // namespace app
} // namespace app

#endif // app_app_AppMenu_INCLUDED
