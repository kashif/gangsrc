/* GANG Software
 * GEOM/milieu/opengl/LightSet.H
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

#ifndef milieu_opengl_LightSet_INCLUDED
#define milieu_opengl_LightSet_INCLUDED

#include "base/Color3.H"
#include "milieu/kernel/LightSetBase.H"
#include "Light.H"

namespace milieu {
namespace opengl {

class LightSet
  :
    public milieu::kernel::LightSetBase
{

public:
  // constructor
  LightSet();

  // destructor
  virtual ~LightSet();

  void reset();
  void reset( uint n );

//  virtual void geomobject_move_enable(bool state) = 0;
//  virtual void clipplane_moving_off() = 0;

  bool moving( uint id ) const
    { return LightSetBase::moving(id); }
  void moving( uint id, bool state );

protected:

  void move( motion::TransformX const & );
  void draw() const;
  virtual void refresh() = 0;
  virtual void _milieu_moving_notify(bool) = 0;

private:

  virtual Light &elem(uint id) { return *_[id]; }
  virtual Light const &elem(uint id) const { return *_[id]; }

  Light &operator[](uint id)
    { return *static_cast<Light *>(_[id]); }
  Light const &operator[](uint id) const
    { return *static_cast<Light const *>(_[id]); }

  class Light1 : public Light
  {
  public:
    Light1( uint id, LightSet *parent )
        : Light(id), _parent(parent) {}
  protected:
    virtual void refresh()
      { _parent->refresh(); }
  private:
    LightSet *_parent;
  };

  void _reset( uint );

  base::ArrayX<Light1 *, LIGHT_COUNT> _;

  // disabled copy constructor
  LightSet( LightSet const & );
  // disabled assignment operator
  LightSet &operator=( LightSet const & );

};

} // namespace opengl
} // namespace milieu

#endif // milieu_opengl_LightSet_INCLUDED
