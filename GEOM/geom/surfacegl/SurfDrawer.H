/* GANG Software
 * GEOM/geom/surfacegl/SurfDrawer.H
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

#ifndef geom_surfacegl_SurfDrawer_INCLUDED
#define geom_surfacegl_SurfDrawer_INCLUDED

#include "geom/surface0/Surface.H"
#include "Drawer.H"

namespace geom {
namespace surfacegl {

class SurfDrawer
  :
    public Drawer
{

public:
  // constructor
  SurfDrawer();


  // destructor
  virtual ~SurfDrawer();

protected:

private:

  surface0::Surface const *surface() const
    { DIE_IF(_geomobject->dimension() != 2U);
    return static_cast<surface0::Surface const *>(_geomobject); }

  virtual void _draw() const;

  void draw_element( uint ) const;
  void _draw_element( uint ) const;
  void draw_points() const;
  void draw_lines() const;
  void draw_boundary() const;
  void draw_silhouette() const;
  void draw_bbox() const;

  void draw_vertex( uint k ) const;
  void draw_vertex( geom::Vertex3 const & ) const;

  void draw_face_color(uint) const;
  void draw_vertex_color(uint) const;
  void draw_face_normal(uint) const;
  void draw_vertex_normal(uint) const;

  inline void draw_normal_nudge( uint i ) const;

  mutable bool _draw_normal;
  mutable bool _draw_color;

  // move lines off from surface along normal by this amount
  Real _normal_nudge;

  mutable geom::Transform _transform_inv;

  // copy constructor
  SurfDrawer( SurfDrawer const & );
  // assignment operator
  SurfDrawer &operator=( SurfDrawer const & );

};

} // namespace surfacegl
} // namespace geom

#endif // geom_surfacegl_SurfDrawer_INCLUDED
