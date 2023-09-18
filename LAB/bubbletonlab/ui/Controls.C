/* GANG Software
 * LAB/bubbletonlab/ui/Controls.C
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

namespace bubbletonlab {
namespace ui {

Controls::
Controls()
   :
    ::widget::ui::Dialog()
{
}

Controls::
~Controls()
{
}

void
Controls::
normalshift_cb()
{
  normalshift( normalshift_w()->get() );
  load_surface();
}

void
Controls::
set( parser::KeyParser const &data )
{
  // center
  center_w()->set( data.get("center").c_str() );

  // size
  size_w()->set( data.get("size").c_str() );

#if 0
  // normal shift
  int r = evaluate( _normalshift, data.get("normalshift").c_str() );
  if (r != 0)
  { throw kernel::Ui::Exception(
    kernel::Ui::Exception::ERR_NORMAL_SHIFT); }
#endif
}


void
Controls::
get( parser::KeyParser &data ) const
{
  // center
  data.set("center", center_w()->get() );

  // size
  data.set("size", size_w()->get() );

  // normalshift
  base::String s;
  s.to_string( normalshift_w()->get() );
  data.set("normalshift", s);
}

} // namespace ui
} // namespace bubbletonlab
