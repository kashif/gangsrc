/* GANG Software
 * WIDGET/app/app/App.H
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

#ifndef app_app_App_INCLUDED
#define app_app_App_INCLUDED

#include "widget/ui/KeyBase.H"
#include "app/gtk/Ui.H"
#include "app/ui/Ui.H"
#include "AppMenu.H"
#include "AppWindow.H"
#include "Help.H"

namespace app {
namespace app {

class App
  :
    protected ::app::ui::Ui,
    protected ::app::gtk::Ui,
    protected Help,
    protected AppMenu,
    protected AppWindow
{

public:
  // constructor
  App(
    char const *app_name,
    char const *window_title,
    char const *about_info,
    char const * const *xpm,
    char const *help_url_env );

  // destructor
  virtual ~App();

protected:

  virtual void exit() = 0;
  static void sync();

  void controls_file( ::widget::ui::KeyBase &p );
  void controls( ::widget::ui::KeyBase &p );

private:

  virtual void hide_all() = 0;
  virtual void enable_tooltips(bool state) = 0;

  void hide_all_cb();
  void toggle_tooltips_cb();

  bool _tooltip_state;

  // disabled copy constructor
  App( App const & );
  // disabled assignment operator
  App &operator=( App const & );

};

} // namespace app
} // namespace app

#endif // app_app_App_INCLUDED
