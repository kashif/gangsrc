/* GANG Software
 * LAB/cmclab/ui/Ui.C
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

#include <iostream>
#include "base/String.H"
#include "base/System.H"
#include "base/String.H"
#include "base/Regex.H"
#include "base/Stl.H"
#include "widget/ui/KeyBase.H"
#include "Ui.H"

namespace cmclab {
namespace ui {

Ui::
Ui()
    :
    Controls()
{
}

Ui::
~Ui()
{
}

void
Ui::
show_all(bool state)
{
  lab::ui::Ui::show_all(state);
  controls_p()->show_d(state);
}

void
Ui::
enable_tooltips(bool state)
{
  lab::ui::Ui::show_all(state);
  controls_p()->enable_tooltips_d(state);
}

#if FIXME
void
Ui::
append_window_keys( ::widget::ui::KeyBase &p )
{
  p.insert(
    "Toggle normalshift", GDK_F4, MOD_NONE,
    static_cast< ::cmclab::ui::Controls *>(this),
    &::cmclab::ui::Controls::toggle_normalshift );

  p.insert(
    "associate", GDK_Right, MOD_SHIFT,
    static_cast< ::cmclab::ui::Controls *>(this),
    &::cmclab::ui::Controls::inc_lambda_R3_slow );

  p.insert(
    "associate", GDK_Right, MOD_NONE,
    static_cast< ::cmclab::ui::Controls *>(this),
    &::cmclab::ui::Controls::inc_lambda_R3_med );

  p.insert(
    "associate", GDK_Right, MOD_CTRL,
    static_cast< ::cmclab::ui::Controls *>(this),
    &::cmclab::ui::Controls::inc_lambda_R3_fast );

  p.insert(
    "associate", GDK_Left, MOD_SHIFT,
    static_cast< ::cmclab::ui::Controls *>(this),
    &::cmclab::ui::Controls::dec_lambda_R3_slow );

  p.insert(
    "associate", GDK_Left, MOD_NONE,
    static_cast< ::cmclab::ui::Controls *>(this),
    &::cmclab::ui::Controls::dec_lambda_R3_med );

  p.insert(
    "associate", GDK_Left, MOD_CTRL,
    static_cast< ::cmclab::ui::Controls *>(this),
    &::cmclab::ui::Controls::dec_lambda_R3_fast );
}
#endif

} // namespace ui
} // namespace cmclab
