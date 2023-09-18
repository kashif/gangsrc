/* GANG Software
 * LAB/minlab/gtk/Controls.C
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

#include "Controls.H"

namespace minlab {
namespace gtk {

Controls::
Controls(char const *title)
    :
    ui::Controls(),
    Controls_(),
    ::app::app::Dialog( title, label(), main_widget() )
{
  _zstart_spinor_w->set_usize(60, 0);
  _spinor1_w->set_usize(60, 0);
  _spinor2_w->set_usize(60, 0);
  _spinor0_init_w->set_usize(60, 0);
  _spinor1_init_w->set_usize(60, 0);
  _spinor2_init_w->set_usize(60, 0);
  _zstart_weierstrass_w->set_usize(60, 0);
  _weierstrass1_w->set_usize(60, 0);
  _weierstrass2_w->set_usize(60, 0);
  _weierstrass0_init_w->set_usize(60, 0);
  _weierstrass1_init_w->set_usize(60, 0);
  _weierstrass2_init_w->set_usize(60, 0);
}

Controls::
~Controls()
{
}

} // namespace gtk
} // namespace minlab
