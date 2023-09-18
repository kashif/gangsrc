/* GANG Software
 * GEOM/geom/surfacegl/MaterialSet.H
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

#ifndef geom_surfacegl_MaterialSet_INCLUDED
#define geom_surfacegl_MaterialSet_INCLUDED

#include "geom/surface/MaterialSetBase.H"
#include "Material.H"

namespace geom {
namespace surfacegl {

class MaterialSet
  :
    virtual public surface::MaterialSetBase
{

public:
  // constructor
  MaterialSet();

  // copy constructor
  MaterialSet( MaterialSet const & );

  // destructor
  virtual ~MaterialSet();

  // assignment operator
  MaterialSet &operator=( MaterialSet const & );

  virtual Material &operator[](uint id)
    { return _[id]; }
  virtual Material const &operator[](uint id) const
    { return _[id]; }

  bool draw( uint id ) const
    { return (*this)[id].draw(); }
  bool draw_color( uint id ) const
    { return (*this)[id].draw_color(); }
  bool draw_normal( uint id ) const
    { return (*this)[id].draw_normal(); }
  void begin( uint id ) const
    { (*this)[id].begin(); }
  void end( uint id ) const
    { (*this)[id].end(); }

protected:

private:

  base::ArrayX<Material, MATERIALS_COUNT> _;

};

} // namespace surfacegl
} // namespace geom

#endif // geom_surfacegl_MaterialSet_INCLUDED
