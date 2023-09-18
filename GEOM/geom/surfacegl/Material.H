/* GANG Software
 * GEOM/geom/surfacegl/Material.H
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

#ifndef geom_surfacegl_Material_INCLUDED
#define geom_surfacegl_Material_INCLUDED

#include "opengl/OpenGL.H"
#include "geom/surface/Material.H"

namespace geom {
namespace surfacegl {

class Material
  :
    public geom::surface::Material
{

public:
  // constructor
  Material();

  // copy constructor
  Material( Material const & );

  // destructor
  virtual ~Material();

  // assignment operator
  Material &operator=( Material const & );

  bool draw() const;
  bool draw_color() const;
  bool draw_normal() const;

  void begin() const;
  void end() const;

protected:

private:

};

} // namespace surfacegl
} // namespace geom

#endif // geom_surfacegl_Material_INCLUDED
