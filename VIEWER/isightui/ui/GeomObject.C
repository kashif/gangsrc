/* GANG Software
 * VIEWER/isightui/ui/GeomObject.C
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

#if defined(__sgi) && !defined(__GNUG__)
#pragma set woff 1174
#endif
#include <gtk/gtkclist.h>
#if defined(__sgi) && !defined(__GNUG__)
#pragma reset woff 1174
#endif

#include "base/System.H"
#include "isight/kernel/ViewerBase.H"
#include "GeomObject.H"

namespace isightui {
namespace ui {

GeomObject::
GeomObject()
    :
    _inherit_materials(false),
    _position_by_box(1)
{
}

GeomObject::
~GeomObject()
{
}

void
GeomObject::
insert_geomobject_notify( base::String const &label )
{
  select_geomobject_w()->append_blocked(label.c_str());

  // select the last object
  DIE_IF( item_count() == 0 );
  uint id = item_count() - 1;
  select_geomobject_w()->set_blocked(id);

  synchronize();
  set_sensitive();
}

void
GeomObject::
delete_all_geomobjects()
{
  while( item_count() != 0 )
  {
    select_geomobject_w()->set( item_count() - 1 );
    delete_geomobject_cb();
  }
}

void
GeomObject::
delete_geomobject_notify( uint id )
{
  DIE_IF( id >= item_count() );

  select_geomobject_w()->remove(id);

  // select object id (or id-1)
  if( item_count() == 0 ) { return; }

  if (id >= item_count() ) { id--; }
  select_geomobject(id);
}

void
GeomObject::
synchronize()
{
  uint id = select_geomobject_w()->get();
  if ( id == NONE ) { return; }

  show_geomobject_w()->set( viewer()->geomobject_showing_(id) );
  move_geomobject_w()->set( viewer()->geomobject_moving_(id) );
}

void
GeomObject::
set_sensitive()
{
  bool flag = item_count() != 0 &&
    select_geomobject_w()->selected();
  show_geomobject_w()->set_sensitive( flag );
  move_geomobject_w()->set_sensitive( flag );
  delete_geomobject_w()->set_sensitive( flag );
}

void
GeomObject::
select_geomobject_cb()
{
  uint id = select_geomobject_w()->get();
  if ( id == NONE ) { return; }
  viewer()->select_geomobject_( id );

  DIE_IF( id >= item_count() );
  select_geomobject_w()->set_blocked(id);

  synchronize();
  set_sensitive();
}

void
GeomObject::
show_geomobject_cb()
{
  uint id = select_geomobject_w()->get();
  if ( id == NONE ) { return; }
  bool state = show_geomobject_w()->get();
  viewer()->show_geomobject_( id, state );

  synchronize();
  set_sensitive();
}

void
GeomObject::
move_geomobject_cb()
{
  uint id = select_geomobject_w()->get();
  if ( id == NONE ) { return; }
  DIE_IF( id >= item_count() );

  bool state = move_geomobject_w()->get();
  viewer()->move_geomobject_( id, state );

  if ( id == select_geomobject_w()->get() )
  {
    move_geomobject_w()->set(state);
  }

  synchronize();
  set_sensitive();
}

void
GeomObject::
delete_geomobject_cb()
{
  uint id = select_geomobject_w()->get();
  if ( id == NONE ) { return; }
  DIE_IF( id >= item_count() );

  viewer()->delete_geomobject_( id );

  select_geomobject_w()->remove(id);

  // select object id (or id-1)
  if( item_count() == 0 ) { return; }

  if (id >= item_count() ) { id--; }
  select_geomobject(id);
}

void
GeomObject::
move_all_geomobjects( bool state )
{
  if ( item_count() == 0 ) { return; }

  uint id;
  for ( id = 0; id < item_count(); id++ )
  {
    viewer()->move_geomobject_( id, state );
  }
  move_geomobject_w()->set(state);
  
  synchronize();
  set_sensitive();
}

bool
GeomObject::
command(
  base::String const &command, 
  base::String const &argument,
  base::String &response )
{
  bool r = false;
  if ( command == "selectedObject" )
  {
    response.to_string( selected_geomobject() );
    r = true;
  }
  if ( command == "selectObject" )
  {
    select_geomobject( read_uint(argument) );
    r = true;
  }
  if ( command == "showObject" )
  {
    base::String id, x;
    split1( id, x, argument );
    show_geomobject( read_uint(id), read_bool(x) );
    r = true;
  }
  if ( command == "moveObject" )
  {
    base::String id, x;
    split1( id, x, argument );
    move_geomobject( read_uint(id), read_bool(x) );
  }
  if ( command == "deleteObject" )
  {
    delete_geomobject( read_uint(argument) );
    r = true;
  }
  if ( command == "geomobjectPosition" )
  {
    geom::Transform t;
    read_transform( t, argument );
    viewer()->context()->geomobject_position(0, t);
    return true;
  }
  return r;
}

} // namespace ui
} // namespace isightui
