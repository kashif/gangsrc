/* GANG Software
 * WIDGET/gtk/widget1/ButtonBar.H
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

#ifndef gtk_widget1_ButtonBar_INCLUDED
#define gtk_widget1_ButtonBar_INCLUDED

#include "widget/ui/Choice.H"
#include "gtk/widget0/Widget.H"
#include "gtk/widget0/ObjectCallback.H"
#include "gtk/widgetc/gtk_button_bar.h"

namespace gtk {
namespace widget1 {

/*
   Gtk button bar.
*/
class ButtonBar
  :
    public widget::ui::Choice,
    public gtk::widget0::Widget
{
public:
  ButtonBar( uint value,
             char const *label[],
             uint rows,
             uint cols );
  void set( uint n )
    { gtk_button_bar_set( GTK_BUTTON_BAR(w()), n ); }
  uint get() const
    { return gtk_button_bar_get_value( GTK_BUTTON_BAR(w()) ); }

//  bool showing() const
//    { return ::gtk::widget0::Widget::showing(); }
  virtual bool showing( uint n ) const
    { WARN(); return true; }
//  void set_sensitive( bool state )
//    { ::gtk::widget0::Widget::set_sensitive(state); }
  virtual void set_sensitive( uint n, bool state )
    { gtk_button_bar_set_sensitive( GTK_BUTTON_BAR(w()), n, state ); }
  virtual void show( bool state = true )
    { gtk::widget0::Widget::show(state); }
  virtual void show( uint n, bool state )
    { gtk_button_bar_show( GTK_BUTTON_BAR(w()), n, state ); }

};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_ButtonBar_INCLUDED
