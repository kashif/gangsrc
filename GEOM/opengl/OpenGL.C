/* GANG Software
 * GEOM/opengl/OpenGL.C
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

#include "base/Regex.H"
#include "OpenGL.H"

namespace opengl {

uint LIGHT_COUNT = 8U;
uint CLIPPLANE_COUNT = 6U;

GLenum const
gl_bool[2] =
{
  GL_FALSE, GL_TRUE
};

uint
opengl_version()
{
  static uint version = 0;
  if (version != 0) { return version; }

  version = 1;

  // opengl_version
  // this can't be called until a window is open
  char const *s = (char *)glGetString(GL_VERSION);
  DIE_IF(s == (char *)0);

  if ( base::match("Mesa", s) )
  { version = 2; }

  return version;
}

} // namespace opengl
