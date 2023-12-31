/* GANG Software
 * WIDGET/gtk/widget0/Scale.H
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
// generated by gtk2c++

#ifndef gtk_widget0_Scale_INCLUDED
#define gtk_widget0_Scale_INCLUDED

#include <math.h>
#include "Range.H"

namespace gtk {
namespace widget0 {

class Scale
  :
    public Range
{
public:
  float get() const
    { return adjustment()->value; }
  int get_int() const
    { return (int)rint(gtk_range_get_adjustment( GTK_RANGE(w()) )->value); }
  void set( float a )
    { gtk_adjustment_set_value(
      gtk_range_get_adjustment( GTK_RANGE(w()) ), a ); }
  void set( int a )
    { gtk_adjustment_set_value(
      gtk_range_get_adjustment( GTK_RANGE(w()) ), float(a) ); }
  GtkAdjustment *adjustment()
    { return gtk_range_get_adjustment( GTK_RANGE(w()) ); }
  GtkAdjustment const *adjustment() const
    { return gtk_range_get_adjustment( GTK_RANGE(w()) ); }

  void set_digits( int digits )
    { gtk_scale_set_digits( GTK_SCALE(w()), digits ); }
  void set_draw_value( bool draw_value )
    { gtk_scale_set_draw_value( GTK_SCALE(w()), draw_value ); }
  void set_value_pos( GtkPositionType pos )
    { gtk_scale_set_value_pos( GTK_SCALE(w()), pos ); }
  int get_value_width()
    { return gtk_scale_get_value_width( GTK_SCALE(w())); }
  void draw_value()
    { gtk_scale_draw_value( GTK_SCALE(w())); }

protected:
  Scale( GtkWidget *x ) : Range(x) {}
  Scale( GtkWidget *x,
    float min, float max, float speed0, float speed1,
    uint digits, float value )
      : Range(x)
    {
      gtk_scale_set_draw_value( GTK_SCALE(_w), false );
      GtkAdjustment *a = gtk_range_get_adjustment( GTK_RANGE(_w) );
      a->lower = min;
      a->upper = max;
      a->step_increment = speed0;
      a->page_increment = speed1;
      gtk_adjustment_set_value( a, value );
      gtk_scale_set_digits( GTK_SCALE(_w), (gint)digits );
    }
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_Scale_INCLUDED
