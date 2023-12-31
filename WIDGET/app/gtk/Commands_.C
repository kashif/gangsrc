/* GANG Software
 * WIDGET/app/gtk/Commands_.C
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
// Generated by glade++

#include "Commands_.H"

namespace app {
namespace gtk {


Commands_::
Commands_()
{
  _tooltips = new ::gtk::widget0::Tooltips;


  // vbox1
  _vbox1_w = new ::gtk::widget0::VBox( false, 0 );
  _vbox1_w->show();

  // scrolledwindow1
  _scrolledwindow1_w = new ::gtk::widget0::ScrolledWindow( (GtkAdjustment *)0, (GtkAdjustment *)0 );
  _scrolledwindow1_w->set_policy(GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  _scrolledwindow1_w->show();
  _vbox1_w->add( _scrolledwindow1_w, true, true, 0 );

  // text
  _text_w = new ::gtk::widget0::Text( (GtkAdjustment *)0, (GtkAdjustment *)0 );
  _text_w->set_editable( true );
  _text_w->show();
  _scrolledwindow1_w->add( _text_w );
  set_tooltip( _text_w,
    "Enter iSight commands" );

  // execute
  _execute_w = new ::gtk::widget0::ButtonCb<Commands_>(
    "execute", this, &Commands_::execute_cb );
  _execute_w->show();
  _vbox1_w->add( _execute_w, false, false, 0 );
  set_tooltip( _execute_w,
    "" );


}

Commands_::
~Commands_()
{
  delete _execute_w;
  delete _text_w;
  delete _scrolledwindow1_w;
  delete _vbox1_w;

  delete _tooltips;
}

} // namespace gtk
} // namespace app

