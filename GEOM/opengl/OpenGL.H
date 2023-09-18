/* GANG Software
 * GEOM/opengl/OpenGL.H
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

#ifndef opengl_OpenGL_INCLUDED
#define opengl_OpenGL_INCLUDED

#include <GL/gl.h>
#include "base/Color3.H"
#include "base/Color4.H"
#include "math/Vector3Math.H"
#include "math/VectorX.H"
#include "math/Matrix.H"

namespace opengl {

typedef double Real;
typedef math::Vector3Math<Real> Vertex3;
typedef math::VectorX<Real,4U> Vertex4;
typedef math::Matrix<Real> Transform;
typedef math::Vector3Math<Real> Normal3;

uint opengl_version();
  // 1=not-Mesa, 2=Mesa

extern const GLenum gl_bool[2];

inline void
glenable( GLenum feature, bool state )
{
  if (state)
  { glEnable( feature ); }
  else
  { glDisable( feature ); }
}

#if 1
// for use with 'typedef double Real'
inline void glGet( GLenum pname, GLdouble *params )
{ glGetDoublev( pname, params ); }
inline void glLoadMatrix(Transform const &x )
{ glLoadMatrixd( x.data() ); }
inline void glVertex(Vertex3 const &x)
{ glVertex3dv( x.data() ); }
inline void glVertex(Vertex4 const &x)
{ glVertex4dv( x.data() ); }
inline void glNormal(Normal3 const &x)
{ glNormal3dv( x.data() ); }
#endif

#if 0
// for use with 'typedef float Real'
inline void glGet( GLenum pname, GLfloat *params )
{ glGetFloatfv( pname, params ); }
inline void glLoadMatrix(Transform const &x )
{ glLoadMatrixf( x.data() ); }
inline void glVertex(Vertex3 const &x)
{ glVertex3fv( x.data() ); }
inline void glVertex(Vertex4 const &x)
{ glVertex4fv( x.data() ); }
inline void glNormal(Normal3 const &x)
{ glNormal3fv( x.data() ); }
#endif

inline void glColor(::base::Color3 const &x)
{ glColor3fv( x.data() ); }
inline void glColor(::base::Color4 const &x)
{ glColor4fv( x.data() ); }


GLenum const gl_depth_function[8] =
{
  GL_NEVER, GL_ALWAYS, GL_LESS, GL_LEQUAL, GL_EQUAL,
  GL_GEQUAL, GL_GREATER, GL_NOTEQUAL
};

#if 0
GLenum const gl_hint[3] =
{
  GL_FASTEST, GL_NICEST, GL_DONT_CARE
};
#endif

GLenum const gl_fog_mode[3] =
{
  GL_LINEAR, GL_EXP, GL_EXP2
};

GLenum const gl_blend_factor_src[12] =
{
  GL_ZERO,
  GL_ONE,
  GL_SRC_COLOR,
  GL_ONE_MINUS_SRC_COLOR,
  GL_SRC_ALPHA,
  GL_ONE_MINUS_SRC_ALPHA,
  GL_DST_ALPHA,
  GL_ONE_MINUS_DST_ALPHA,
  GL_CONSTANT_COLOR_EXT,
  GL_ONE_MINUS_CONSTANT_COLOR_EXT,
  GL_CONSTANT_ALPHA_EXT,
  GL_ONE_MINUS_CONSTANT_ALPHA_EXT
};

GLenum const gl_blend_factor_dest[13] =
{
  GL_ZERO,
  GL_ONE,
  GL_DST_COLOR,
  GL_ONE_MINUS_DST_COLOR,
  GL_SRC_ALPHA_SATURATE,
  GL_SRC_ALPHA,
  GL_ONE_MINUS_SRC_ALPHA,
  GL_DST_ALPHA ,
  GL_ONE_MINUS_DST_ALPHA,
  GL_CONSTANT_COLOR_EXT,
  GL_ONE_MINUS_CONSTANT_COLOR_EXT,
  GL_CONSTANT_ALPHA_EXT,
  GL_ONE_MINUS_CONSTANT_ALPHA_EXT
};

} // namespace opengl

#endif // opengl_OpenGL_INCLUDED
