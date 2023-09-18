/* GANG Software
 * GEOM/opengl/Fade.C
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

#include "Fade.H"

namespace opengl {

GLubyte Fade::_stipple_pattern[Fade::COUNT][4*32];

Fade::
Fade()
    :
    _enable(true)
{
  uint i;
  for ( i = 0; i < COUNT; i++ )
  {
    uint j;
    for ( j = 0; j < 4*32; j++)
    {
      _stipple_pattern[i][j] = 0;
    }
  }

  for ( i = 1; i < COUNT; i++ )
  {
    uint j;
    for ( j = 0; j < 4*32; j++)
    {
      _stipple_pattern[i][j] = _stipple_pattern[i-1][j];
    }
    for ( j = 0; j < (8*4*32)/COUNT + 500*i/COUNT; j++)
    {
      // pick a bit
      uint k = (uint)(1024*drand48());
      if (k == 1024) { k = 1023;}
      _stipple_pattern[i][k/8] |= (1 << (k%8));
    }
  }
}

Fade::
~Fade()
{
}

void
Fade::
fade()
{
  if (!_enable) { return; }

  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glEnable(GL_POLYGON_STIPPLE);

  uint i;
  for ( i= 0; i < COUNT; i++)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonStipple( &_stipple_pattern[i][0] );
    draw();
    swap_buffers();
  }
  glDisable(GL_POLYGON_STIPPLE);

  glPopAttrib();
}

} // namespace opengl
