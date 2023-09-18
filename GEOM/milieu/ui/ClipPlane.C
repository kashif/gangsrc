/* GANG Software
 * GEOM/milieu/ui/ClipPlane.C
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

#include "milieu/opengl/ClipPlane.H"
#include "ClipPlane.H"

namespace milieu {
namespace ui {

ClipPlane::
ClipPlane()
{
}

ClipPlane::
~ClipPlane()
{
}

// interface

void
ClipPlane::
clipplane_reset()
{
  clipplaneset()->reset();
  clipplane_synchronize();
//  geomobject_move_enable(true);
}

void
ClipPlane::
clipplane_reset( uint id )
{
  clipplaneset()->reset( id );
  clipplane_synchronize();
//  geomobject_move_enable(true);
}

void
ClipPlane::
clipplane_enable( uint id, bool a )
{
  _enable(id, a);
  if ( id == id_w()->get() ) { enable_w()->set_blocked(a); }
}

void
ClipPlane::
clipplane_moving( uint id, bool a )
{
  clipplaneset()->moving(id, a);
  if ( id == id_w()->get() ) { moving_w()->set_blocked(a); }
}

void
ClipPlane::
clipplane_show( uint id, bool a )
{
  _show(id, a);
  if ( id == id_w()->get() ) { show_w()->set_blocked(a); }
}

void
ClipPlane::
clipplane_attached( uint id, bool a )
{
  _attached(id, a);
  if ( id == id_w()->get() ) { attached_w()->set_blocked(a); }
}

void
ClipPlane::
clipplane_position( bool id, Transform const &a )
{
  clipplaneset()->position(id, a);
}

// utility

void
ClipPlane::
set_ui_from_data( opengl::ClipPlaneSet *clipplaneset )
{
  uint id = id_w()->get();
  enable_w()->set_blocked( clipplaneset->enable(id) );
  moving_w()->set_blocked( clipplaneset->moving(id) );
  show_w()->set_blocked( clipplaneset->show(id) );
  attached_w()->set_blocked( clipplaneset->attached(id) );
}

#if 0
void
ClipPlane::
_moving( uint id, bool state )
{
  if (state)
  {
    // turn off clipplane motion
    light_moving_off();

    // turn off clipplane motion
    uint i;
    for ( i = 0; i < 6; i++ )
    {
      if ( i != id) { clipplaneset()->moving( i, false ); }
    }
  }

  // reset off geomobject motion
  geomobject_move_enable(!state);

  clipplaneset()->moving( id, state );
}
#endif

bool
ClipPlane::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "clipplaneReset" )
  {
    if ( argument.empty() )
    {
      clipplane_reset();
    }
    else
    {
      clipplane_reset( read_uint(argument) );
    }
    r = true;
  }
  if ( command == "clipplaneEnable" )
  {
    base::String id, x;
    split1( id, x, argument );
    clipplane_enable( read_uint(id), read_uint(x) );
    r = true;
  }
  if ( command == "clipplaneMoving" )
  {
    base::String id, x;
    split1( id, x, argument );
    clipplane_moving( read_uint(id), read_uint(x) );
    r = true;
  }
  if ( command == "clipplaneAttached" )
  {
    base::String id, x;
    split1( id, x, argument );
    clipplane_attached( read_uint(id), read_uint(x) );
    r = true;
  }
  if ( command == "clipplanePosition" )
  {
    base::String id, x;
    split1( id, x, argument );
    Transform t;
    read_transform( t, x );
    clipplane_position( read_bool(id), t );
    r = true;
  }

  return r;
}

} // namespace ui
} // namespace milieu
