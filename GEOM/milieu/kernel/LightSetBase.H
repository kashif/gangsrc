/* GANG Software
 * GEOM/milieu/kernel/LightSetBase.H
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

#ifndef milieu_kernel_LightSetBase_INCLUDED
#define milieu_kernel_LightSetBase_INCLUDED

#include <iostream>
#include "Light.H"

namespace milieu {
namespace kernel {

class LightSetBase
{

public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  LightSetBase();

  // destructor
  virtual ~LightSetBase();

  void dump( io::Ostream &o ) const;

  static uint count()
    { return LIGHT_COUNT; }

  static uint const LIGHT_COUNT = 8U;

  // interface
  virtual void reset() { WARN(); }
  virtual void reset( uint id ) { WARN(); }

  virtual bool enable( uint id ) const
    { return elem(id).enable(); }
  virtual bool moving( uint id ) const
    { return elem(id).moving(); }
  virtual bool show( uint id ) const
    { return elem(id).show(); }
  virtual bool attached( uint id ) const
    { return elem(id).attached(); }
  virtual base::Color3 const &ambient( uint id ) const
    { return elem(id).ambient(); }
  virtual base::Color3 const &diffuse( uint id ) const
    { return elem(id).diffuse(); }
  virtual base::Color3 const &specular( uint id ) const
    { return elem(id).specular(); }
  virtual base::ArrayX<float,5U> const &spot( uint id ) const
    { return elem(id).spot(); }
  virtual base::ArrayX<float,3U> const &attenuation( uint id ) const
    { return elem(id).attenuation(); }
  virtual Transform const &position( uint id ) const
   { return elem(id).position(); }

  // access functions
  virtual void enable( uint id, bool a )
    { elem(id).enable(a); }
  virtual void moving( uint id, bool a )
    { elem(id).moving(a); }
  virtual void show( uint id, bool a )
   { elem(id).show(a); }
  virtual void attached( uint id, bool a )
    { elem(id).attached(a); }
  virtual void ambient( uint id, base::Color3 const &a )
    { elem(id).ambient(a); }
  virtual void diffuse( uint id, base::Color3 const &a )
    { elem(id).diffuse(a); }
  virtual void specular( uint id, base::Color3 const &a )
    { elem(id).specular(a); }
  virtual void spot( uint id, base::ArrayX<float,5U> const &a )
    { elem(id).spot(a); }
  virtual void attenuation( uint id, base::ArrayX<float,3U> const &a )
    { elem(id).attenuation(a); }
  virtual void position( uint id, Transform const &a )
    { elem(id).position(a); }

protected:

private:

  virtual Light &elem(uint) = 0;
  virtual Light const &elem(uint) const = 0;

  // disabled copy constructor
  LightSetBase( LightSetBase const & );
  // disabled assignment operator
  LightSetBase &operator=( LightSetBase const & );
};

} // namespace kernel
} // namespace milieu

#endif // milieu_kernel_LightSetBase_INCLUDED
