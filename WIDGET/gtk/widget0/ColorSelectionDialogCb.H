/* GANG Software
 * WIDGET/gtk/widget0/ColorSelectionDialogCb.H
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

#ifndef gtk_widget0_ColorSelectionDialogCb_INCLUDED
#define gtk_widget0_ColorSelectionDialogCb_INCLUDED

#include "Callback.H"
#include "ColorSelectionDialog.H"

namespace gtk {
namespace widget0 {

template <class A>
class ColorSelectionDialogCb :
  public ColorSelectionDialog
{
public:
  typedef void (A::*CallbackFnPtr)();

  ColorSelectionDialogCb(
    char const *title,
    float const value[3],
    A *obj,
    CallbackFnPtr fn ) :
      ColorSelectionDialog( title, value ),
    _callback( obj, fn )
    {
      gtk_signal_connect(
        GTK_OBJECT(
          GTK_COLOR_SELECTION_DIALOG(this->w())->colorsel ),
        "color_changed",
        GTK_SIGNAL_FUNC(_callback.static_callback_fn),
        (gpointer)&_callback );
    }

  void set_blocked( float value[3] )
    { block(); set(value); unblock(); }

private:
  Callback<A> _callback;
};

} // namespace widget0
} // namespace gtk

#endif // gtk_widget0_ColorSelectionDialogCb_INCLUDED
