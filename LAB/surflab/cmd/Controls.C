/* GANG Software
 * LAB/surflab/cmd/Controls.C
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

namespace surflab {
namespace cmd {

Controls::
Controls()
    :
    ui::Controls()
{
#if 0
  uint i;
  for ( i = 0; i < COUNT; i++ )
  {
    _function_w[i] = new widget0::String;
    _functionbox_w[i] = new widget::Widget;
  }
#endif
#if 0
  _function_w[0] = _function0_w;
  _function_w[1] = _function1_w;
  _function_w[2] = _function2_w;
  _function_w[3] = _function3_w;
  _function_w[4] = _function4_w;

  _function_box_w[0] = _function_box0_w;
  _function_box_w[1] = _function_box1_w;
  _function_box_w[2] = _function_box2_w;
  _function_box_w[3] = _function_box3_w;
  _function_box_w[4] = _function_box4_w;
#endif
#if 0
  _function_box_w[3]->show(false);
  _function_box_w[4]->show(false);
#endif
}

Controls::
~Controls()
{
}

} // namespace cmd
} // namespace surflab
