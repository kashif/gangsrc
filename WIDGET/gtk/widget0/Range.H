/* GANG Software
 * WIDGET/gtk/widget0/Range.H
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

#ifndef gtk_widget0_Range_INCLUDED
#define gtk_widget0_Range_INCLUDED

#include "Widget.H"

namespace gtk {
namespace widget0 {

class Range : public Widget
{
public:
  GtkAdjustment* get_adjustment()
    { return gtk_range_get_adjustment( GTK_RANGE(w())); }
  void set_update_policy( GtkUpdateType policy )
    { gtk_range_set_update_policy( GTK_RANGE(w()), policy ); }
  void set_adjustment( GtkAdjustment *adjustment )
    { gtk_range_set_adjustment( GTK_RANGE(w()), adjustment ); }
  void draw_background()
    { gtk_range_draw_background( GTK_RANGE(w())); }
  void clear_background()
    { gtk_range_clear_background( GTK_RANGE(w())); }
  void draw_trough()
    { gtk_range_draw_trough( GTK_RANGE(w())); }
  void draw_slider()
    { gtk_range_draw_slider( GTK_RANGE(w())); }
  void draw_step_forw()
    { gtk_range_draw_step_forw( GTK_RANGE(w())); }
  void draw_step_back()
    { gtk_range_draw_step_back( GTK_RANGE(w())); }
  void slider_update()
    { gtk_range_slider_update( GTK_RANGE(w())); }
  int trough_click( int x, int y, float *jump_perc )
    { return gtk_range_trough_click( GTK_RANGE(w()), x, y, jump_perc ); }
  void default_hslider_update()
    { gtk_range_default_hslider_update( GTK_RANGE(w())); }
  void default_vslider_update()
    { gtk_range_default_vslider_update( GTK_RANGE(w())); }
  int default_htrough_click( int x, int y, float *jump_perc )
    { return gtk_range_default_htrough_click( GTK_RANGE(w()), x, y, jump_perc ); }
  int default_vtrough_click( int x, int y, float *jump_perc )
    { return gtk_range_default_vtrough_click( GTK_RANGE(w()), x, y, jump_perc ); }
  void default_hmotion( int xdelta, int ydelta )
    { gtk_range_default_hmotion( GTK_RANGE(w()), xdelta, ydelta ); }
  void default_vmotion( int xdelta, int ydelta )
    { gtk_range_default_vmotion( GTK_RANGE(w()), xdelta, ydelta ); }

protected:
  Range( GtkWidget *x ) : Widget(x) {}
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_Range_INCLUDED
