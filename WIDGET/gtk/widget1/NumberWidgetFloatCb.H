/* GANG Software
 * WIDGET/gtk/widget1/NumberWidgetFloatCb.H
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

#ifndef gtk_widget1_NumberWidgetFloatCb_INCLUDED
#define gtk_widget1_NumberWidgetFloatCb_INCLUDED

#include "widget/ui/Float.H"
#include "NumberWidgetCb.H"

namespace gtk {
namespace widget1 {

template <class A>
class NumberWidgetFloatCb
  :
    public widget::ui::Float,
    public NumberWidgetCb<A>
{
public:
  typedef void (A::*WidgetCallbackFnPtr)() ;

  NumberWidgetFloatCb(
    numberwidget_config const *config,
    A *obj, WidgetCallbackFnPtr fn ) :
      widget::ui::Float(),
      NumberWidgetCb<A>(config, obj, fn) {}

  virtual void set( float a )
    { NumberWidgetCb<A>::set(a); }
  virtual void set_blocked( float a )
    { NumberWidgetCb<A>::set_blocked(a); }
  virtual float get() const
    { return NumberWidgetCb<A>::get(); }
};

} // namespace widget1
} // namespace gtk

#endif // gtk_widget1_NumberWidgetFloatCb_INCLUDED
