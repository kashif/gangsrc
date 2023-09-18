/* GANG Software
 * GEOM/geom/surfacegl/Drawer.H
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

#ifndef geom_surfacegl_Drawer_INCLUDED
#define geom_surfacegl_Drawer_INCLUDED

#include <iostream>
#include <GL/gl.h>
#include <GL/glx.h>
#include "geom/surface0/GeomObject.H"
#include "MaterialSet.H"

namespace geom {
namespace surfacegl {

class Drawer
{

public:
  // constructor
  Drawer();


  // destructor
  virtual ~Drawer();

  // OpenGL draw
  void draw( surface0::GeomObject const *g ) const;
  void draw( surface0::GeomObject const *g,
             geom::Transform const &transform,
             geom::ProjectionMode mode ) const;

  void set_materials( MaterialSet const *materials )
    { _materials = materials; }

  void enable_display_list( bool state ) const
    { _enable_display_list = state; }

protected:

  virtual void _draw() const = 0;

  MaterialSet const *_materials;

  mutable bool _use_transform;
  mutable geom::ProjectionMode _projection_mode;

  mutable surface0::GeomObject const *_geomobject;
  mutable geom::Transform _transform;

private:

  // move lines toward camera by this amount
  Real _camera_nudge[2];

  mutable bool _enable_display_list;

  mutable GLXContext _current_context;

  // disabled copy constructor
  Drawer( Drawer const & );
  // disabled assignment operator
  Drawer &operator=( Drawer const & );
};

} // namespace surfacegl
} // namespace geom

#endif // geom_surfacegl_Drawer_INCLUDED
