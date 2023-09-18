/* GANG Software
 * GEOM/geom/surface/SurfaceBase.H
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

#ifndef geom_surface_SurfaceBase_INCLUDED
#define geom_surface_SurfaceBase_INCLUDED

#include <list>
#include <iostream>
#include "io/Istream.H"
#include "io/Ostream.H"
#include "milieu/kernel/MilieuBase.H"
#include "geom/io/Common.H"
#include "geom/surface0/BoundingBox.H"
#include "MaterialSetBase.H"

namespace geom {

namespace surface0 { class Surface; }

namespace surface {

/*
  List of surfaces.
*/

class SurfaceBase
  :
    virtual public MaterialSetBase
{

public:

  // void constructor
  SurfaceBase();

  // copy constructor
  SurfaceBase( SurfaceBase const & );

  // destructor
  virtual ~SurfaceBase();

  // assignment operator
  SurfaceBase &operator=( SurfaceBase const & );

  virtual void changed() const;

  virtual void insert( surface0::GeomObject const &g );
  virtual void insert( std::list<surface0::GeomObject *> const &L );
  virtual void insert( SurfaceBase const &G );
  virtual void insert_no_copy( surface0::GeomObject *g );
  virtual void insert_no_copy( std::list<surface0::GeomObject *> const &L );

  uint size() const
    { return (uint)list().size(); }

  bool empty() const
    { return list().empty(); }

  surface0::GeomObject *first()
    { DIE_IF( list().empty() ); return list().front(); }
  surface0::GeomObject const *first() const
    { DIE_IF( list().empty() ); return list().front(); }

  base::String const &name() const { return _name; }
  void name( base::String const &name ) { _name = name; }

  void read(
    ::io::Istream &stream,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT )
    throw (::io::ReadException);

  void read(
    ::io::Istream &stream,
    ::milieu::kernel::MilieuBase &M,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT )
    throw (::io::ReadException);

  void write(
    ::io::Ostream &stream,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT ) const
    throw (::io::WriteException);

  void write(
    ::io::Ostream &stream,
    uint normals, uint colors,
    milieu::kernel::MilieuBase const &milieu,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT ) const
    throw (::io::WriteException);

  void dump( ::io::Ostream & ) const;

  void clear();
  void clear_no_delete()
    { list().clear(); }

  // set the materials of *this to M
  virtual void materials( MaterialSetBase const &M );

  virtual void materials( uint id, Material const & );

  virtual surface::Material const &materials(uint i) const;

  uint vertex_count() const;
  uint edge_count() const;
  uint face_count() const;

  geom::Box const &box() const;

  /*
     Smooth a mesh.
     relaxes a mesh by replacing each point by the average of its
     adjacent points
     boundary points are omitted
     the points are relaxed in random order to prevent lopsidedness
     iterations is approximately how many cycles through all the vertices
     typically < 10
  */
  void relax( uint iterations );

//  void color_fixed( base::Color4 const &p );

  /*
     Color the surface a modification of its original color.
     surface0::GeomObjectrguments 1/2,1/2,1/2,1/2 restore the surface to its original color.
     Other arguments color the surface by piecewise linear interpolation
     between 0, the original value, and 1 (except hue which shifts).
  */
  void color_original( base::Color4 const &p );

  /*
     Color the surface at each vertex by the normal direction of the
     surface at that vertex
  */
  void color_by_normal( base::Color4 const &p );

  /*
     Color the surface at each vertex by its direction of that vertex
     from the origin
     (r,g,b) = scale * (unit direction base::vector)
  */
  void color_by_direction( base::Color4 const &p );

  /*
     Color the surface at each vertex by its distance from the origin
     the distance, in the interval [0,inf) is rescaled
     to the interval [0,1) by an arctan function
  */
  void color_by_distance( base::Color4 const &p, float scale );

  /*
     Color the surface at each vertex by the area of an adjacent face
  */
  void color_by_area( base::Color4 const &p, float scale );

  /*
     Color the surface by discrete Gaussian curvature.
  */
  void color_by_gaussian_curvature( base::Color4 const &p, float scale );

  /*
     Color the surface by discrete mean curvature.
  */
  void color_by_mean_curvature( base::Color4 const &p, float scale );

  /*
     Color the faces of the surface with randomly chosen colors.
  */
  void color_randomly( base::Color4 const &p );

  void color_checked( base::Color4 const &p1, base::Color4 const &p2 );


  void alpha_fade( float x0, float x1 );

#if 0
  virtual void draw() const {}
  virtual void draw(
    geom::Transform const &transform,
    geom::ProjectionMode mode ) const {}
#endif

  // CASTS
  static surface0::Surface *surface( surface0::GeomObject *s );
  static surface0::Surface const *surface( surface0::GeomObject const *s );

  virtual std::list<surface0::GeomObject *> const &list() const
    { return _; }

  surface0::GeomObject *strip();
  void position( std::list<geom::Transform> &x ) const;
  void position( geom::Transform const &x );

protected:

  mutable surface0::BoundingBox _box;

private:

  virtual std::list<surface0::GeomObject *> &list()
    { return _; }

  base::String _name;

  friend class Construct;

  std::list<surface0::GeomObject *> _;

};

} // namespace surface
} // namespace geom

#endif // geom_surface_SurfaceBase_INCLUDED
