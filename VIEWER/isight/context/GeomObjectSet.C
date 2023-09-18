/* GANG Software
 * VIEWER/isight/context/GeomObjectSet.C
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

#include "GeomObject.H"
#include "GeomObjectSet.H"

namespace isight {
namespace context {

GeomObjectSet::
GeomObjectSet( ContextSetBase *base )
    :
    ContextBase1(base),
    _initial_place(),
    _center(),
    _null_object(3, motion::CENTRAL),
    _move_count(0),
    _()
{
  uint m = 4U;
  _initial_place.rotation.identity(m);
  _initial_place.translation.identity(m);
  _initial_place.position.identity(m);
  _center.set(0.0);
}

GeomObjectSet::
~GeomObjectSet()
{
  uint i;
  for ( i = 0; i < _.size(); i++ )
  {
    delete _[i];
  }
}

void
GeomObjectSet::
insert_geomobject( geom::SurfaceGL const *g )
{
  // create a new geomobject
  GeomObject *h;

  if (standard_geometry())
  {
    h = new GeomObject( g, initial_place(), center(),
                        geom_motion()->projectionMode() );
    h->set_movemode(standard_geometry());
  }
  else
  {
    motion::Place t;
    t.rotation.identity(geom_motion()->matrix_dim());
    t.translation.identity(geom_motion()->matrix_dim());
    t.position.identity(geom_motion()->matrix_dim());
    motion::Center c;
    c.set(0.0);

    h = new GeomObject( g, t, c, geom_motion()->projectionMode() );
  }

  h->showing(true);
  h->moving(true);

  // add h to list
  _.push_back( h );

  compute_box();

  // position_by_box:
  // 0 = never, 1 = first surface, 2 = always
  uint f = base()->viewer_ui()->position_by_box();
  if (  (f==1 && _.size()==1) || f==2)
  {
    geomobject_reset_position();
  }

  // set the window's geometric position to that of g
  std::list<geom::Transform> x;
  g->position(x);

  std::list<geom::Transform>::const_iterator i;
  uint c;
  for ( i = x.begin(), c=0; i != x.end(); i++, c++ )
  {
    if ( (*i).dim() != 0 )
    {
      geomobject_position( c, *i );
    }
  }
  refresh();
}

void
GeomObjectSet::
delete_geomobject( uint n )
{
  delete _[n];
  _.erase( _.begin() + n );
  refresh();
}

void
GeomObjectSet::
delete_all_geomobjects()
{
  uint i;
  for ( i = 0; i < _.size(); i++ )
  {
    delete _[i];
  }
  _.clear();
  refresh();
}

void
GeomObjectSet::
geomobject_moving( uint id, bool state )
{
  stop_motion();
  _[id]->moving(state);

#if 0
  // this is supposed to fix the problem of two objects
  // rotating differently
  if (_.size() > 1)
  {
  motion::Center x;
  _compute_center(x);

  uint i;
  for ( i = 0; i < _.size(); i++ )
  {
    if ( _[i]->moving() )
    {
      motion::Transform const &t = _[i]->translation();
      motion::Center y;
      y[0] = x[0] - t[3U][0];
      y[1] = x[1] - t[3U][1];
      y[2] = x[2] - t[3U][2];
      _[i]->set_center( y );
    }
  }
  }
#endif

  refresh();
}

void
GeomObjectSet::
geomobject_reset_position()
{
  stop_motion();

  if ( standard_geometry() )
  {

    // set the position of the place-holder object
    _null_object.set(initial_place(), center(), geom_motion()->projectionMode());

    // set the position of each surface in list
    uint i;
    for ( i = 0; i < _.size(); i++ )
    {
      _[i]->set(initial_place(), center(), geom_motion()->projectionMode());
      _[i]->set_movemode(standard_geometry());
    }
  }
  else
  {
    motion::Place t;
    t.rotation.identity(geom_motion()->matrix_dim());
    t.translation.identity(geom_motion()->matrix_dim());
    t.position.identity(geom_motion()->matrix_dim());
    motion::Center c;
    c.set(0.0);

    // set the position of the place-holder object
    _null_object.set( t, c, geom_motion()->projectionMode());

    // set the position of each surface in list
    uint i;
    for ( i = 0; i < _.size(); i++ )
    {
      _[i]->set( t, c, geom_motion()->projectionMode());
      _[i]->set_movemode(standard_geometry());
    }
  }

  refresh();
}

void
GeomObjectSet::
compute_box()
{
  // compute initial place as center of box bounding all geomobjects
  if ( ! standard_geometry() ) { return; }
  if ( _.empty() ) { return; }

  initialize(_box);

  uint i;
  for ( i = 0; i < _.size(); i++ )
  {
    merge(_box, _[i]->geomobject()->box());
  }
}

#if 0
void
GeomObjectSet::
_compute_initial_place( geom::Box const &box )
{
  // DIAMETER_SCALE scales the radius of the object into a z-shift
  // NOTE: this is tied to the camera field of view. When fov is changed,
  // this is wrong
  motion::Real const DIAMETER_SCALE = 1.1;

  uint n = geom_motion()->matrix_dim() - 1U;

  // center of object
  motion::Real diameter = 0.0;

  float const BOUND = 1e5;
  if ( math::abs(box.xmin) > BOUND || math::abs(box.xmax) > BOUND ||
       math::abs(box.ymin) > BOUND || math::abs(box.ymax) > BOUND ||
       math::abs(box.zmin) > BOUND || math::abs(box.zmax) > BOUND )
  {
    WARN("object is too big to center");
    center().set(0.0);
    diameter = 0.0;
  }
  else
  {
    motion::Center corner_min( box.xmin, box.ymin, box.zmin );
    motion::Center corner_max( box.xmax, box.ymax, box.zmax );
    center() = corner_min+corner_max;
    center() *= 0.5;
    // diameter of object
    diameter = (corner_max-corner_min).abs();
  }
  
  initial_place().translation[n][0] = -center().x;
  initial_place().translation[n][1] = -center().y;
  initial_place().translation[n][2] = -center().z - DIAMETER_SCALE*diameter;
  initial_place().position = initial_place().translation;
}
#endif

#if 0
void
GeomObjectSet::
_compute_center( motion::Center &x )
{
  x.set(0.0);

  // compute the center of the set of objects which are moving
  if ( ! standard_geometry() ) { return; }

  uint const n = 3U;
  uint c = 0;
  uint i;
  for ( i = 0; i < _.size(); i++ )
  {
    if ( _[i]->moving() )
    {
      motion::Transform const &t = _[i]->translation();
      x[0] += t[n][0];
      x[1] += t[n][1];
      x[2] += t[n][2];
      c++;
    }
  }
  if ( c == 0 ) { return; }

  x /= float(c);
}
#endif

#if 0
void
GeomObjectSet::
_reset()
{
  initial_place().rotation.identity(geom_motion()->matrix_dim());
  initial_place().translation.identity(geom_motion()->matrix_dim());
  initial_place().position.identity(geom_motion()->matrix_dim());
}
#endif

void
GeomObjectSet::
geomobject_reset_position(uint n)
{
  stop_motion();
  _[n]->set( initial_place(), center(), geom_motion()->projectionMode() );
  _[n]->draw();
  refresh();
}

void
GeomObjectSet::
draw() const
{
  uint i;
  for ( i = 0; i < _.size(); i++ )
  {
    if (_[i]->showing() )
    {
#if 0
// NOTE
      _[i]->geomobject()->changed();
#endif
      _[i]->draw();
    }
  }
}

void
GeomObjectSet::
move( motion::TransformX const &inertia ) const
{
  // move the place-holder object
  _null_object.move(inertia);

  // move each geomobject
  uint i;
  for ( i = 0; i < _.size(); i++ )
  {
    if ( _[i]->moving() )
    {
      _[i]->move(inertia);
    }
  }
}

void
GeomObjectSet::
geomobject_view_mode( int model )
{
  uint i;
  for ( i = 0; i < _.size(); i++ )
  {
    _[i]->view_mode(model);
  }
}

void
GeomObjectSet::
geomobject_moving( bool state )
{
  uint i;
  for ( i = 0; i < _.size(); i++ )
  {
    geomobject_moving( i, state );
  }
}

void
GeomObjectSet::
set_center(
  math::Vector3<double> const &center_,
  math::Vector3<double> const &position )
{
  if ( ! standard_geometry() ) { return; }

  center() = center_;
  initial_place().translation.identity();
  initial_place().translation[3][0] = position.x;
  initial_place().translation[3][1] = position.y;
  initial_place().translation[3][2] = position.z;
  initial_place().position = initial_place().translation;

  geomobject_reset_position();
}

void
GeomObjectSet::
initialize(
  geom::Box &a )
{
  geom::Real M;
  if (sizeof(geom::Real)==sizeof(double))
  {
    M = DBL_MAX;
  }
  else if (sizeof(geom::Real)==sizeof(float))
  {
    M = FLT_MAX;
  }
  else
  {
    DIE();
  }

  a.xmin = M;
  a.xmax = -M;
  a.ymin = M;
  a.ymax = -M;
  a.zmin = M;
  a.zmax = -M;
}

void
GeomObjectSet::
merge(
  geom::Box &a, geom::Box const &b )
{
  if ( b.xmin < a.xmin ) { a.xmin = b.xmin; }
  if ( b.xmax > a.xmax ) { a.xmax = b.xmax; }
  if ( b.ymin < a.ymin ) { a.ymin = b.ymin; }
  if ( b.ymax > a.ymax ) { a.ymax = b.ymax; }
  if ( b.zmin < a.zmin ) { a.zmin = b.zmin; }
  if ( b.zmax > a.zmax ) { a.zmax = b.zmax; }
}

} // namespace context
} // namespace isight
