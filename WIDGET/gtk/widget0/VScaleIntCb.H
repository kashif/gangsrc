/* GANG Software
 * WIDGET/gtk/widget0/VScaleIntCb.H
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

#ifndef gtk_widget0_VScaleIntCb_INCLUDED
#define gtk_widget0_VScaleIntCb_INCLUDED

#include "widget/ui/Int.H"
#include "HScaleCb.H"

namespace gtk {
namespace widget0 {

template <class A>
class HScaleIntCb
  :
    public widget::ui::Int,
    public HScaleCb<A>
{
public:
  HScaleIntCb(
    float min, float max, float speed0, float speed1,
    uint digits, float value,
    A *obj, CallbackFnPtr fn ) :
      HScaleCb<A>( min, max, speed0, speed1, digits, value, obj, fn ) {}

  virtual void set( int a )
    { VScaleCb<A>::set(a); }
  virtual void set_blocked( int value )
    { VScaleCb<A>::set_blocked(value); }
  virtual int get() const
    { return HScaleCb<A>::get_int(); }
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_VScaleIntCb_INCLUDED
