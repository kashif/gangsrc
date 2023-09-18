/* GANG Software
 * GEOM/milieu/kernel/Light.H
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

#ifndef milieu_kernel_Light_INCLUDED
#define milieu_kernel_Light_INCLUDED

#include "base/Color3.H"
#include "math/WriteUtil.H"

namespace milieu {
namespace kernel {

class Light
  :
    public math::WriteUtil
{
  
public:
  typedef double Real;
  typedef math::Matrix<Real> Transform;

  // constructor
  Light();

  // copy constructor
  Light( Light const & );

  // destructor
  virtual ~Light();

  // assignment operator
  Light &operator=( Light const & );

  virtual void reset();
  void dump( io::Ostream & ) const;

  // access functions
  virtual bool const &enable() const
    { return _enable; }
  virtual bool const &moving() const
    { return _moving; }
  virtual bool const &show() const
    { return _show; }
  virtual bool const &attached() const
    { return _attached; }
  virtual base::Color3 const &ambient() const
    { return _ambient; }
  virtual base::Color3 const &diffuse() const
    { return _diffuse; }
  virtual base::Color3 const &specular() const
    { return _specular; }
  virtual base::ArrayX<float,5U> const &spot() const
    { return _spot; }
  virtual base::ArrayX<float,3U> const &attenuation() const
    { return _attenuation; }
  virtual Transform const &position() const
    { return _position; }

  virtual void enable( bool a )
    { _enable = a; }
  virtual void moving( bool a )
    { _moving = a; }
  virtual void show( bool a )
    { _show = a; }
  virtual void attached( bool a )
    { _attached = a; }
  virtual void ambient( base::Color3 const &a )
    { _ambient = a; }
  virtual void diffuse( base::Color3 const &a )
    { _diffuse = a; }
  virtual void specular( base::Color3 const &a )
    { _specular = a; }
  virtual void spot( base::ArrayX<float,5U> const &a )
    { _spot = a; }
  virtual void attenuation( base::ArrayX<float,3U> const &a )
    { _attenuation = a; }
  virtual void position( Transform const &a )
    { _position = a; }

protected:

private:
  void copy( Light const &a );

  bool _enable;
  bool _moving;
  bool _show;
  bool _attached;

  // colors in RGBA format
  base::Color3 _ambient;
  base::Color3 _diffuse;
  base::Color3 _specular;

  // GL_SPOT_DIRECTION: (spot[0], spot[1], spot[2])
  // GL_SPOT_EXPONENT: spot[3] in range [0, 1] (not [0,128])
  // GL_SPOT_CUTOFF:   spot[4] in range [0, 1] (not [0,180])
  base::ArrayX<float,5U> _spot;

  // GL_CONSTANT_ATTENUATION:   attenuation[0]
  // GL_LINEAR_ATTENUATION:     attenuation[1]
  // GL_QUADRATIC_ATTENUATION:  attenuation[2]
  base::ArrayX<float,3U> _attenuation;

  Transform _position;
};

} // namespace kernel
} // namespace milieu

#endif // milieu_kernel_Light_INCLUDED
