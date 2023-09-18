/* GANG Software
 * WIDGET/gtk/widget0/ColorSelectionCb.H
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

#ifndef gtk_widget0_ColorSelectionCb_INCLUDED
#define gtk_widget0_ColorSelectionCb_INCLUDED

#include "Callback.H"
#include "ColorSelection.H"

namespace gtk {
namespace widget0 {

template <class A>
class ColorSelectionCb :
    public ColorSelection,
    public ObjectCallback<A>
{
public:
  typedef void (A::*CallbackFnPtr)();

  ColorSelectionCb(
    float const value[3],
    A *obj,
    CallbackFnPtr fn ) :
      ColorSelection( value ),
    ObjectCallback<A>( 
        GTK_OBJECT( GTK_COLOR_SELECTION( this->w() ) ),
        obj, fn, "color_changed") {}

  void set_blocked( float const value[3] )
    { block(); set(value); unblock(); }
  virtual void set_bounds( uint n, float lower, float upper )
    { DIE(); }

private:
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_ColorSelectionCb_INCLUDED
