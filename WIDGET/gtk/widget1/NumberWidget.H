/* GANG Software
 * WIDGET/gtk/widget1/NumberWidget.H
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

#ifndef gtk_widget1_NumberWidget_INCLUDED
#define gtk_widget1_NumberWidget_INCLUDED

#include <gtk/gtkframe.h>
#include <gtk/gtkvbox.h>
#include "math/Math.H"
#include "gtk/widgetc/gtk_numberwidget.h"
#include "gtk/widget0/Widget.H"

namespace gtk {
namespace widget1 {

/*
  class gtk::widget0::NumberWidget: a GtkWidget made up of a GtkNumberPatch and a GtkNumberInput.
  A GtkNumberWidget is used to input real or integer values like a GtkSpinButton,
  with mouse drags (three speeds for three buttons) to increase/decrease
  values. Is a wrapper for gtk_numberwidget

  class gtk::widget0::NumberWidget2: a stack of gtk::widget0::NumberWidgets in a frame

  template <class A> class gtk::widget0::NumberWidget2Callback: NumberWidget2 which provides a static callback
*/

class NumberWidget
  :
    public gtk::widget0::Widget
{
public:
  NumberWidget( numberwidget_config const *config) :
    gtk::widget0::Widget( gtk_numberwidget_new() )
    { gtk_numberwidget_configure( GTK_NUMBERWIDGET(_w), config ); }

  void set( float a )
    { gtk_numberwidget_set_value( GTK_NUMBERWIDGET(_w), a ); }
  float get() const
    { return gtk_numberwidget_get_value( GTK_NUMBERWIDGET(_w) ); }
  int get_int() const
    { return gtk_numberwidget_get_value_as_int( GTK_NUMBERWIDGET(_w) ); }
  GtkAdjustment *adjustment()
    { return gtk_numberwidget_get_adjustment( GTK_NUMBERWIDGET(_w) ); }
  void connect( gpointer obj, GtkSignalFunc fn );
};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_NumberWidget_INCLUDED
