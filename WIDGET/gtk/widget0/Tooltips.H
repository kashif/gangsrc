/* GANG Software
 * WIDGET/gtk/widget0/Tooltips.H
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

#ifndef gtk_widget0_Tooltips_INCLUDED
#define gtk_widget0_Tooltips_INCLUDED

#include "Widget.H"
#include "Data.H"

namespace gtk {
namespace widget0 {

class Tooltips : public Data
{
public:
  Tooltips() :
      Data( GTK_DATA(gtk_tooltips_new()) ) {}

  void set_tip( Widget *x, char const *tip_text, char const *tip_private )
  { gtk_tooltips_set_tip(GTK_TOOLTIPS(_w), x->w(), tip_text, tip_private ); }

  void enable(bool a) { if (a) enable(); else disable(); }

  void enable()
    { gtk_tooltips_enable( GTK_TOOLTIPS(w())); }
  void disable()
    { gtk_tooltips_disable( GTK_TOOLTIPS(w())); }
  void set_delay( uint delay )
    { gtk_tooltips_set_delay( GTK_TOOLTIPS(w()), delay ); }
  void set_tip( GtkWidget *widget, char const *tip_text, char const *tip_private )
    { gtk_tooltips_set_tip( GTK_TOOLTIPS(w()), widget, tip_text, tip_private ); }
  void set_colors( GdkColor *background, GdkColor *foreground )
    { gtk_tooltips_set_colors( GTK_TOOLTIPS(w()), background, foreground ); }
  GtkTooltipsData* data_get()
    { return gtk_tooltips_data_get( GTK_WIDGET(w())); }
  void force_window()
    { gtk_tooltips_force_window( GTK_TOOLTIPS(w())); }

protected:
  Tooltips( GtkData *x ) : Data(x) {}
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_Tooltips_INCLUDED
