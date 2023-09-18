/* GANG Software
 * GEOM/geom/surfacegl/Surface.H
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

#ifndef geom_surfacegl_Surface_INCLUDED
#define geom_surfacegl_Surface_INCLUDED

#include "base/Color3.H"
#include "base/Color4.H"
#include "io/Ostream.H"
#include "geom/io/Common.H"
#include "geom/surface/Construct.H"
#include "geom/surface/MaterialSet.H"
#include "Material.H"
#include "MaterialSet.H"
#include "SurfDrawer.H"

namespace geom {
namespace surfacegl {

/*
  List of surfaces.
*/

class Surface
  :
    public surface::Construct,
    public surfacegl::MaterialSet
{

public:

  // void constructor
  Surface();

  // copy constructor
  Surface( Surface const & );

  // destructor
  virtual ~Surface();

  // assignment operator
  Surface &operator=( Surface const & );

#if 0
  virtual void changed() const
    { surface::SurfaceBase::changed(); }
#endif

  void write(
    ::io::Ostream &out,
    ::geom::FileMode filemode = ::geom::FILEMODE_UNSPECIFIED ) const
    throw (::io::WriteException)
    { 
      surface::SurfaceBase::write( out, filemode );
    }

  void write(
    ::io::Ostream &out,
    ::geom::FileMode filemode,
    uint normals, uint colors,
    milieu::kernel::MilieuBase const &milieu ) const
    throw (::io::WriteException)
    { 
      surface::SurfaceBase::write(
        out, normals, colors, milieu, filemode );
    }

  void dump( ::io::Ostream &o ) const;

  virtual void draw() const;
  virtual void draw(
    geom::Transform const &transform,
    geom::ProjectionMode mode ) const;


  // set the materials of *this to M
  virtual void materials( surface::MaterialSetBase const &M );

  virtual void materials( uint id, surface::Material const & );

  virtual Material const &materials(uint i) const
    { return static_cast<surfacegl::MaterialSet const *>(this)->operator[](i); }

  /*
     Set the distance to move edge faces off the surface in the normal
     direction.
  */
  void normal_nudge(float);
  float const &normal_nudge() const;

  virtual void enable_bounding_box( bool state ) const
    { MaterialSet::enable( MaterialSet::BBOX); }

#if 0
  virtual void box( geom::Box &b ) const
    { surface::SurfaceBase::box(b); }
#endif

  virtual uint vertex_count() const
    { return surface::SurfaceBase::vertex_count(); }
  virtual uint edge_count() const
    { return surface::SurfaceBase::edge_count(); }
  virtual uint face_count() const
    { return surface::SurfaceBase::face_count(); }

protected:

private:

  virtual geom::Box const &box() const
    { return _box; }

  SurfDrawer _surf_drawer;
};

} // namespace surfacegl
} // namespace geom

#endif // geom_surfacegl_Surface_INCLUDED
