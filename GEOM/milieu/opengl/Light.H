/* GANG Software
 * GEOM/milieu/opengl/Light.H
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

#ifndef milieu_opengl_Light_INCLUDED
#define milieu_opengl_Light_INCLUDED

#include "motion/Mobile.H"
#include "milieu/kernel/Light.H"

namespace milieu {
namespace opengl {

class Light
  :
    public ::milieu::kernel::Light,
    public ::motion::Mobile
{

public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  Light( uint id );

  // destructor
  virtual ~Light();

  uint id() const { return _id; }
  void draw() const;
  void reset();

  // access functions
  virtual bool const &enable() const
    { return ::milieu::kernel::Light::enable(); }
  virtual bool const &moving() const
    { return ::milieu::kernel::Light::moving(); }
  virtual bool const &show() const
    { return ::milieu::kernel::Light::show(); }
  virtual bool const &attached() const
    { return ::milieu::kernel::Light::attached(); }
  virtual base::Color3 const &ambient() const
    { return ::milieu::kernel::Light::ambient(); }
  virtual base::Color3 const &diffuse() const
    { return ::milieu::kernel::Light::diffuse(); }
  virtual base::Color3 const &specular() const
    { return ::milieu::kernel::Light::specular(); }
  virtual base::ArrayX<float,5U> const &spot() const
    { return ::milieu::kernel::Light::spot(); }
  virtual base::ArrayX<float,3U> const &attenuation() const
    { return ::milieu::kernel::Light::attenuation(); }
  virtual Transform const &position() const
    { return Mobile::position(); }

  virtual void enable( bool a );
  virtual void moving( bool a );
  virtual void show( bool a );
  virtual void attached( bool a );
  virtual void ambient( base::Color3 const &a );
  virtual void diffuse( base::Color3 const &a );
  virtual void specular( base::Color3 const &a );
  virtual void spot( base::ArrayX<float,5U> const &a );
  virtual void attenuation( base::ArrayX<float,3U> const &a );
  virtual void position( Transform const &x )
    { Mobile::position(x); }

protected:

  virtual void refresh() = 0;

private:

  void draw_position() const;

  // light at the origin
  static float const standard_light[4];

  uint _id;

  // copy constructor
  Light( Light const & );
  // assignment operator
  Light &operator=( Light const & );

};

} // namespace opengl
} // namespace milieu

#endif // milieu_opengl_Light_INCLUDED
