/* GANG Software
 * GEOM/opengl/Fade.H
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

#ifndef opengl_Fade_INCLUDED
#define opengl_Fade_INCLUDED

#include <GL/gl.h>
#include "base/System.H"
#include "base/vector.H"

namespace opengl {

class Fade
{

public:
  // constructor
  Fade();

  // destructor
  virtual ~Fade();

  void fade();

  bool fade_enable() const
    { return _enable; }
  void fade_enable(bool state)
    { _enable = state; }

protected:

  virtual void draw() = 0;
  virtual void swap_buffers() = 0;

private:

  bool _enable;

  static uint const COUNT = 12;

  static GLubyte _stipple_pattern[COUNT][4*32];

  // disabled copy constructor
  Fade( Fade const & );
  // disabled assignment operator
  Fade &operator=( Fade const & );

};

} // namespace opengl

#endif // opengl_Fade_INCLUDED
