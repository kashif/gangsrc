/* GANG Software
 * VIEWER/isight/kernel/GeomListSet.C
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

#include "GeomListSet.H"

namespace isight {
namespace kernel {

GeomListSet::
GeomListSet()
    :
    _(),
    _geomobject( (geom::SurfaceGL *)0 ),
    _reference_geomobject( new geom::SurfaceGL ),
    _previous_geomobject( (geom::SurfaceGL *)0 )
{
  _geomobject = _reference_geomobject;
}

GeomListSet::
~GeomListSet()
{
  // delete all geomobjects
  base::vector< geom::SurfaceGL * >::iterator j;
  for ( j = _.begin(); j != _.end(); j++ )
  {
    delete (*j);
  }
  _.clear();
  delete _reference_geomobject;
}

void
GeomListSet::
write_geomobject(
  uint id,
  io::Ostream &stream,
  uint normals, uint colors,
  milieu::kernel::MilieuBase const &milieu,
  geom::FileMode filemode ) const
  throw (::io::WriteException)
{
  // set positions
#if 0
  std::list<geom::kernel::GeomObject *>::const_iterator i;
  uint c;
  for ( i = _[id]->list().begin(), c=0; i != _[id]->list().end(); i++, c++ )
  {
    (*i)->position( geomobject_position( c ) );
  }
#endif
  _[id]->position(geomobject_position(id));

  _[id]->write( stream, normals, colors, milieu, filemode );
}

void
GeomListSet::
enable_bounding_box( bool state )
{
  uint i;
  for ( i = 0; i < geomlist_count(); i++ )
  {
#if 0
    WARN();
    _[i]->enable_bounding_box( state );
#endif
  }
}

uint
GeomListSet::
find( geom::SurfaceGL const *g )
{
  // find g in geomobject_vect
  // returns index of g, or geomlist_count() if not found
  uint i;
  for (i = 0; i < geomlist_count(); i++)
  {
    if (_[i] == g) { break; }
  }

  return i;
}


void
GeomListSet::
insert_geomobject0( geom::SurfaceGL *g )
{
  _.push_back( g );
  _geomobject = g;
}

void
GeomListSet::
select_geomobject0( uint id )
{
  _geomobject = _[id];
}

void
GeomListSet::
delete_geomobject0( uint n )
{
  delete _[n];
  _.erase( _.begin() + n );
  _geomobject = _reference_geomobject;
}

void
GeomListSet::
changed() const
{
  uint i;
  for ( i = 0; i < geomlist_count(); i++ )
  {
    _[i]->changed();
  }
}

} // namespace kernel
} // namespace isight
