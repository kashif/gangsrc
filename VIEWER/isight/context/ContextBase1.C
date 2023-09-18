/* GANG Software
 * VIEWER/isight/context/ContextBase1.C
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

#include "ContextBase1.H"

namespace isight {
namespace context {

ContextBase1::
ContextBase1( ContextSetBase *base )
    :
    ContextBase(),
    milieu::opengl::Milieu(),
    _motion_mode(GEOMOBJECT),
    _geom_motion(this),
    _milieu_motion(this),
    _current_motion(&_geom_motion),
    _base(base)
{
}

ContextBase1::
~ContextBase1()
{
}

void
ContextBase1::
milieu_moving_notify( bool state )
{
  if (state)
  {
    motion_mode(MILIEU);
    _current_motion = &_milieu_motion;
  }
  else
  {
    motion_mode(GEOMOBJECT);
    _current_motion = &_geom_motion;
  }
}

} // namespace context
} // namespace isight
