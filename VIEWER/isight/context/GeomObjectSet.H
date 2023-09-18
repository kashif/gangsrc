/* GANG Software
 * VIEWER/isight/context/GeomObjectSet.H
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

#ifndef isight_context_GeomObjectSet_INCLUDED
#define isight_context_GeomObjectSet_INCLUDED

#include "base/vector.H"
#include "GeomObject.H"
#include "geom/interface/SurfaceGL.H"
#include "isight/context/ContextBase1.H"

namespace isight {
namespace context {

class GeomObjectSet
  :
    public ContextBase1
{

public:

  // void constructor
  GeomObjectSet( ContextSetBase *base );

  // destructor
  virtual ~GeomObjectSet();

  geom::Box const &box() const
    { return _box; }

  void set_center(
    math::Vector3<double> const &center,
    math::Vector3<double> const &position );

protected:

  virtual void refresh() = 0;

  // insert a geomobject
  void insert_geomobject( geom::SurfaceGL const * );

  // get the position of the id'th surface
  motion::Transform const &geomobject_position( uint id ) const
    { return _[id]->position(); }

  // set the position of all surfaces
  void geomobject_position( uint id, motion::Transform const &t )
    { _[id]->position(t); refresh(); }

  // reset the position of all surfaces
  void geomobject_reset_position();

  // move all surfaces
  void move( motion::TransformX const &x ) const;

  // draw all surfaces
  void draw() const;

private:
  void compute_box();

  void _initialize(
    motion::Transform const &p,
    motion::Transform const &t );

  // remove surface 'id' from the context
  void delete_geomobject( uint id );

  // remove all surfaces form the context
  void delete_all_geomobjects();

  bool geomobject_showing( uint id ) const
    { return _[id]->showing(); }
  void geomobject_showing( uint id, bool state )
    { _[id]->showing(state); }

  bool geomobject_moving( uint id ) const
    { return _[id]->moving(); }
  void geomobject_moving( bool state );
  void geomobject_moving( uint id, bool state );

  void geomobject_reset_position( uint id );

  virtual uint geomobject_count() const
    { return _.size(); }

  motion::Place const &initial_place() const
    { return _initial_place; }
  motion::Place &initial_place()
    { return _initial_place; }
  motion::Center const &center() const
    { return _center; }
  motion::Center &center()
    { return _center; }

//  void compute_initial_place();

  void geomobject_view_mode( int );

  virtual GeomObject const *geomobject() const
    { DIE_IF(_.size() == 0U); return _[0]; }

//  void _compute_initial_place( geom::Box const &box );
//  void _compute_center( motion::Center &x );
//  void _reset();

  static void initialize( geom::Box &a );
  static void merge( geom::Box &a, geom::Box const &b );

//  motion::Place _initial_place0;
  motion::Place _initial_place;
  motion::Center _center;

  mutable motion::Mobile _null_object;

  uint _move_count;

  geom::Box _box;

  base::vector< GeomObject *> _;

  // disabled copy constructor
  GeomObjectSet( GeomObjectSet const & );
  // disabled assignment operator
  GeomObjectSet &operator=( GeomObjectSet const & );

};

} // namespace context
} // namespace isight

#endif // isight_context_GeomObjectSet_INCLUDED
