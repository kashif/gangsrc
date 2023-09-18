/* GANG Software
 * GEOM/milieu/opengl/GlobalLight.H
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

#ifndef milieu_opengl_GlobalLight_INCLUDED
#define milieu_opengl_GlobalLight_INCLUDED

#include "milieu/kernel/GlobalLight.H"

namespace milieu {
namespace opengl {

class GlobalLight
  :
    virtual public ::milieu::kernel::GlobalLight
{

public:
  // constructor
  GlobalLight();

  // copy constructor
  GlobalLight( GlobalLight const & );

  // destructor
  virtual ~GlobalLight();

  // assignment operator
  GlobalLight &operator=( GlobalLight const & );

  // access functions
  virtual bool const &enable() const
    { return ::milieu::kernel::GlobalLight::enable(); }
  virtual base::Color3 const &ambient() const
    { return ::milieu::kernel::GlobalLight::ambient(); }
  virtual bool const &viewpoint() const
    { return ::milieu::kernel::GlobalLight::viewpoint(); }
  virtual bool const &sidedness() const
    { return ::milieu::kernel::GlobalLight::sidedness(); }

  virtual void enable( bool );
  virtual void ambient( base::Color3 const &a );
  virtual void viewpoint( bool );
  virtual void sidedness( bool );

protected:

  void draw() const;
  virtual void refresh() = 0;

private:

};

} // namespace opengl
} // namespace milieu

#endif // milieu_opengl_GlobalLight_INCLUDED
