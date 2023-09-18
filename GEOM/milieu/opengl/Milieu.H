/* GANG Software
 * GEOM/milieu/opengl/Milieu.H
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

#ifndef milieu_opengl_Milieu_INCLUDED
#define milieu_opengl_Milieu_INCLUDED

#include "milieu/kernel/MilieuBase.H"
#include "Background.H"
#include "Blend.H"
#include "ClipPlaneSet.H"
#include "Camera.H"
#include "GlobalLight.H"
#include "LightSet.H"

namespace milieu {
namespace opengl {

class Milieu
  :
    virtual public kernel::MilieuBase,
    virtual public Background,
    virtual public Blend,
    virtual public ClipPlaneSet,
    virtual public Camera,
    virtual public GlobalLight,
    virtual public LightSet
{

public:
  // constructor
  Milieu();

  // destructor
  virtual ~Milieu();

  void move( motion::TransformX const & );
  void draw() const;

protected:

private:

  virtual void milieu_moving_notify(bool state) = 0;
  void _milieu_moving_notify(bool state);

  // copy constructor
  Milieu( Milieu const & );
  // assignment operator
  Milieu &operator=( Milieu const & );
};

} // namespace opengl
} // namespace milieu

#endif // milieu_opengl_Milieu_INCLUDED
