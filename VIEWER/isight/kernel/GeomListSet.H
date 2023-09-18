/* GANG Software
 * VIEWER/isight/kernel/GeomListSet.H
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

#ifndef isight_kernel_GeomListSet_INCLUDED
#define isight_kernel_GeomListSet_INCLUDED

#include "base/System.H"
#include "base/vector.H"
#include "motion/Common.H"
#include "milieu/kernel/MilieuBase.H"
#include "geom/interface/SurfaceGL.H"
#include "ViewerBase.H"

namespace isight {
namespace kernel {

class GeomListSet
  :
    public ViewerBase
{

public:
  // constructor
  GeomListSet();

  // destructor
  virtual ~GeomListSet();

  // current geomlist
  virtual geom::SurfaceGL *geomlist()
    { return _geomobject; }
  virtual geom::SurfaceGL const *geomlist() const
    { return _geomobject; }

protected:

  // nth geomlist
  virtual geom::SurfaceGL *geomlist( uint n )
    { return _[n]; }
  virtual geom::SurfaceGL const *geomlist( uint n ) const
    { return _[n]; }

  bool empty() const
    { return _.empty(); }

  uint find()
    { uint n = find( geomlist() ); DIE_IF(n == geomlist_count()); return n; }
  uint find( geom::SurfaceGL const *g );

  uint geomlist_count() const
    { return _.size(); }

  geom::SurfaceGL const *reference_geomobject() const
    { return _reference_geomobject; }
  geom::SurfaceGL const * const &previous_geomobject() const
    { return _previous_geomobject; }
  geom::SurfaceGL const *&previous_geomobject()
    { return _previous_geomobject; }

  // takes responsibilty for deallocating g
  void insert_geomobject0( geom::SurfaceGL *g );

  // make the id'th geomobject the current one
  void select_geomobject0( uint id );

  // delete a geomobject
  void delete_geomobject0( uint id );

  void write_geomobject(
    uint id, io::Ostream &stream,
    uint normals, uint colors,
    milieu::kernel::MilieuBase const &milieu,
    geom::FileMode filemode ) const
    throw(::io::WriteException);

private:
  
  // get the position of the i'th geomobject
  virtual geom::Transform const &geomobject_position( uint i ) const = 0;

  // enable the bounding box for all surfaces in list
  void enable_bounding_box( bool state );

  // set the changed flag on all surfaces in list
  void changed() const;

  // List of geometry objects.
  base::vector<geom::SurfaceGL * > _;

  // The current surface
  geom::SurfaceGL *_geomobject;

  // A reference surface with no polygons. This surface gets modified when
  // the user changes the material widgets, when no real surfaces are
  // loaded into the viewer.
  geom::SurfaceGL *_reference_geomobject;

  // latest geomobject inserted (to be replaced if replace button is on)
  geom::SurfaceGL const *_previous_geomobject;

  // disabled copy constructor
  GeomListSet( GeomListSet const & );
  // disabled assignment operator
  GeomListSet &operator=( GeomListSet const & );
};

} // namespace kernel
} // namespace isight

#endif // isight_kernel_GeomListSet_INCLUDED
