/* GANG Software
 * WIDGET/gtk/widget1/NumberWidget2Float.H
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

#ifndef gtk_widget1_NumberWidget2Float_INCLUDED
#define gtk_widget1_NumberWidget2Float_INCLUDED

#include "widget/ui/FloatSet.H"
#include "NumberWidget2.H"

namespace gtk {
namespace widget1 {

class NumberWidget2Float
  :
    public widget::ui::FloatSet,
    public NumberWidget2
{
public:
  NumberWidget2Float(
    char const *frame_label,
    numberwidget_config const config[],
    uint count )
      : NumberWidget2( frame_label, config, count ) {}

  virtual void set( float const a[] )
    { NumberWidget2::set(a); }
  virtual void get( float a[] ) const
    { NumberWidget2::get(a); }
  virtual void set_sensitive( bool state = true )
    { ::gtk::widget0::Widget::set_sensitive(state); }
  virtual void set_sensitive( uint n, bool state )
    { NumberWidget2::set_sensitive(n, state); }

  virtual void set_bounds( uint n, float lower, float upper )
    {
      GtkAdjustment *adj = adjustment(n);
      adj->lower = lower;
      adj->upper = upper;
    }
};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_NumberWidget2Float_INCLUDED
