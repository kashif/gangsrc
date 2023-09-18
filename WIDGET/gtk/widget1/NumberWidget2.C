/* GANG Software
 * WIDGET/gtk/widget1/NumberWidget2.C
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

#include <iostream>
#include "NumberWidget2.H"

namespace gtk {
namespace widget1 {

NumberWidget2::
  NumberWidget2(
    char const *frame_label,
    numberwidget_config const config[],
    uint count )
      :
      gtk::widget0::Frame( frame_label ),
      _vbox( new gtk::widget0::VBox( false, 0) ),
      _count(count)
{
  set_label_align( 0, 0 );
  set_shadow_type( GTK_SHADOW_ETCHED_IN );

  _vbox->show(true);
  add( _vbox );

  _numberwidget = new NumberWidget *[_count];

  uint i;
  for( i = 0; i < _count; i++ )
  {
    _numberwidget[i] = new NumberWidget(config + i);
    _numberwidget[i]->show(true);
    _vbox->add( _numberwidget[i], true, true, 0 );
  }
}

NumberWidget2::
~NumberWidget2()
{
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    delete _numberwidget[i];
  }
  delete [] _numberwidget;
  delete _vbox;
}

void
NumberWidget2::
_connect( gpointer obj, GtkSignalFunc fn )
{
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    gtk_signal_connect(
      GTK_OBJECT(_numberwidget[i]->adjustment()),
      "value_changed",
      fn, obj );
  }
}

void
NumberWidget2::
_block( gpointer obj )
{
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    gtk_signal_handler_block_by_data(
      GTK_OBJECT(_numberwidget[i]->adjustment()), obj );
  }
}

void
NumberWidget2::
_unblock( gpointer obj )
{
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    gtk_signal_handler_unblock_by_data(
      GTK_OBJECT(_numberwidget[i]->adjustment()), obj );
  }
}

void
NumberWidget2::
set( float const a[] )
{
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    _numberwidget[i]->set(a[i]);
  }
}

void
NumberWidget2::
set( int const a[] )
{
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    _numberwidget[i]->set(a[i]);
  }
}

void
NumberWidget2::
get( float a[] ) const
{
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    a[i] = _numberwidget[i]->get();
  }
}

void
NumberWidget2::
get( int a[] ) const
{
  uint i;
  for ( i = 0; i < _count; i++ )
  {
    a[i] = _numberwidget[i]->get_int();
  }
}

void
NumberWidget2::
set_sensitive( uint n, bool state )
{
  DIE_IF( n >= _count );
  gtk_widget_set_sensitive(
    GTK_WIDGET(_numberwidget[n]->w()),
    state );
}

} // namespace widget1
} // namespace gtk
