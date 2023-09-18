/* GANG Software
 * WIDGET/app/gtk/About.H
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

#ifndef app_gtk_About_INCLUDED
#define app_gtk_About_INCLUDED

#include "gtk/widget1/Pixmap.H"
#include "app/app/Dialog.H"
#include "app/ui/About.H"
#include "About_.H"

namespace app {
namespace gtk {

/*
   Gtk message box.
*/
class About
  :
    virtual public ui::About,
    public About_,
    public ::app::app::Dialog
{

public:

  // constructor
  About( char const *title,
         char const *app_name,
         char const *about_info,
         char const * const *xpm );

  // destructor
  virtual ~About();

  char const *label() const
    { return "About"; }

protected:

private:

  // connector functions
  virtual void raise_d( bool state = true )
    { ::app::app::Dialog::raise(state); }
  virtual void show_d( bool state = true )
    { ::app::app::Dialog::show(state); }
  virtual void toggle_raise_show_d()
    { ::app::app::Dialog::toggle_raise_show(); }
  virtual void enable_tooltips_d( bool state = true )
    { About_::enable_tooltips(state); }
  virtual int key_press_event( uint key, uint state )
    { return key_press_event_d( key, state ); }

  ::gtk::widget1::Pixmap *_pixmap;

  About( About const & );
  About &operator=( About const & );
};

} // namespace gtk
} // namespace app

#endif // app_gtk_About_INCLUDED
