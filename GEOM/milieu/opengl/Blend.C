/* GANG Software
 * GEOM/milieu/opengl/Blend.C
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

#include "base/System.H"
#include "opengl/OpenGL.H"
#include "Blend.H"

namespace milieu {
namespace opengl {

Blend::
Blend()
{
}

Blend::
Blend( Blend const & )
{
}

Blend::
~Blend()
{
}

Blend &
Blend::
operator=( Blend const & )
{
  return *this;
}


void
Blend::
depth_enable( bool state )
{
  ::milieu::kernel::Blend::depth_enable( state );
  ::opengl::glenable( GL_DEPTH_TEST, state );
  refresh();
}

void
Blend::
blend_enable( bool state )
{
  ::milieu::kernel::Blend::blend_enable( state );
  ::opengl::glenable( GL_BLEND, state );
  refresh();
}

void
Blend::
blend_src_function( uint a )
{
  DIE_IF( a >= sizeof(::opengl::gl_blend_factor_src)/sizeof(GLenum) );
  ::milieu::kernel::Blend::blend_src_function( a );
  glBlendFunc( ::opengl::gl_blend_factor_src[blend_src_function()],
               ::opengl::gl_blend_factor_dest[blend_dest_function()] );
  refresh();
}

void
Blend::
blend_dest_function( uint a )
{
  DIE_IF( a >= sizeof(::opengl::gl_blend_factor_src)/sizeof(GLenum) );
  ::milieu::kernel::Blend::blend_dest_function( a );
  glBlendFunc( ::opengl::gl_blend_factor_src[blend_src_function()],
               ::opengl::gl_blend_factor_dest[blend_dest_function()] );
  refresh();
}

void
Blend::
depth_function( uint n )
{
  if ( n >= 8 ) { return; }
  ::milieu::kernel::Blend::depth_function(n);
  glDepthFunc( ::opengl::gl_depth_function[n] );
  refresh();
}

void
Blend::
depth_mask( bool n )
{
  // FALSE=0: read only
  // TRUE=1:  read/write
  ::milieu::kernel::Blend::depth_mask(n);
  glDepthMask( ::opengl::gl_bool[n] );
  refresh();
}

void
Blend::
antialias_point( bool state )
{
  ::opengl::glenable( GL_POINT_SMOOTH, state );
  refresh();
}

void
Blend::
antialias_line( bool state )
{
  ::opengl::glenable( GL_LINE_SMOOTH, state );
  refresh();
}

void
Blend::
fog_enable( bool state )
{
  ::milieu::kernel::Blend::fog_enable( state );
  ::opengl::glenable( GL_FOG, state );
  refresh();
}

void
Blend::
fog_mode( uint a )
{
  ::milieu::kernel::Blend::fog_mode(a);
  fog();
}

void
Blend::
fog_parameter( base::ArrayX<float,3U> const &a )
{
  ::milieu::kernel::Blend::fog_parameter(a);
  fog();
}

void
Blend::
fog()
{
  glFogi( GL_FOG_MODE, ::opengl::gl_fog_mode[fog_mode()] );

  if ( fog_mode() == 0 )
  {
    // linear
    glFogf( GL_FOG_START, fog_parameter()[1] );
    glFogf( GL_FOG_END, fog_parameter()[2] );
  }
  else
  {
    // exp or exp2
    glFogf( GL_FOG_DENSITY, fog_parameter()[0] );
  }
  refresh();
}

void
Blend::
fog_color( base::Color3 const &a )
{
  ::milieu::kernel::Blend::fog_color( a );
  glFogfv( GL_FOG_COLOR, a.data() );
  refresh();
}


#if 0
void
Blend::
hint_point_smooth( uint n )
{
  if ( n >= 3 ) { return; }
  ::milieu::kernel::Blend::hint_point_smooth(n);
  glHint( GL_POINT_SMOOTH_HINT, gl_hint[n] );
  refresh();
}

void
Blend::
hint_line_smooth( uint n )
{
  if ( n >= 3 ) { return; }
  ::milieu::kernel::Blend::hint_line_smooth(n);
  glHint( GL_LINE_SMOOTH_HINT, gl_hint[n] );
  refresh();
}

void
Blend::
hint_polygon_smooth( uint n )
{
  if ( n >= 3 ) { return; }
  ::milieu::kernel::Blend::hint_polygon_smooth(n);
  glHint( GL_POLYGON_SMOOTH_HINT, gl_hint[n] );
  refresh();
}

void
Blend::
hint_fog( uint n )
{
  if ( n >= 3 ) { return; }
  ::milieu::kernel::Blend::hint_fog(n);
  glHint( GL_FOG_HINT, gl_hint[n] );
  refresh();
}

void
Blend::
hint_perspective_correction( uint n )
{
  if ( n >= 3 ) { return; }
  ::milieu::kernel::Blend::hint_perspective_correction(n);
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, gl_hint[n] );
  refresh();
}
#endif

void
Blend::
draw() const
{
  // BLENDING
  ::opengl::glenable( GL_DEPTH_TEST, depth_enable() );
  glDepthFunc( ::opengl::gl_depth_function[depth_function()] );
  glDepthMask( ::opengl::gl_bool[depth_mask()] );

  ::opengl::glenable( GL_BLEND, blend_enable() );

  glBlendFunc(
    ::opengl::gl_blend_factor_src[blend_src_function()],
    ::opengl::gl_blend_factor_dest[blend_dest_function()] );

  ::opengl::glenable( GL_FOG, fog_enable() );

  glFogi( GL_FOG_MODE, ::opengl::gl_fog_mode[fog_mode()] );
  glFogf( GL_FOG_DENSITY, fog_parameter()[0] );
  glFogf( GL_FOG_START, fog_parameter()[1] );
  glFogf( GL_FOG_END, fog_parameter()[2] );
  glFogfv( GL_FOG_COLOR, fog_color().data() );

#if 0
  glHint( GL_POINT_SMOOTH_HINT, gl_hint[hint_point_smooth()] );
  glHint( GL_LINE_SMOOTH_HINT, gl_hint[hint_line_smooth()] );
  glHint( GL_POLYGON_SMOOTH_HINT, gl_hint[hint_polygon_smooth()] );
  glHint( GL_FOG_HINT, gl_hint[hint_fog()] );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT,
          gl_hint[hint_perspective_correction()] );
#endif
}

} // namespace opengl
} // namespace milieu
