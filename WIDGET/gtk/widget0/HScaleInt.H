/* GANG Software
 * WIDGET/gtk/widget0/HScaleInt.H
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

#ifndef gtk_widget0_HScaleInt_INCLUDED
#define gtk_widget0_HScaleInt_INCLUDED

#include "widget/ui/Int.H"
#include "HScale.H"

namespace gtk {
namespace widget0 {

class HScaleInt
  :
    public widget::ui::Int,
    public HScale
{
public:
  HScale( GtkAdjustment *adjustment ) :
      HScale( adjustment ) {}
  HScale(
    float min, float max, float speed0, float speed1,
    uint digits, float value ) :
      HScale( min, max, speed0, speed1, digits, value ) {}

  virtual void set( int a )
    { HScale::set(a); }
  virtual int get() const
    { return HScale::get_int(); }
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_HScaleInt_INCLUDED
