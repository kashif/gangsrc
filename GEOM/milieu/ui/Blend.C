/* GANG Software
 * GEOM/milieu/ui/Blend.C
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

#include "milieu/opengl/Blend.H"
#include "Blend.H"

namespace milieu {
namespace ui {

Blend::
Blend()
{
}

Blend::
~Blend()
{
}

void
Blend::
blend_reset()
{
  fog_reset_cb();
}

void
Blend::
blend_synchronize()
{
  depth_enable_w()->set_blocked( blend()->depth_enable() );
  depth_function_w()->set_blocked( blend()->depth_function() );
  depth_mask_w()->set_blocked( blend()->depth_mask() );
  blend_dest_function_w()->set_blocked( blend()->blend_dest_function() );
  blend_src_function_w()->set_blocked( blend()->blend_src_function() );
  blend_enable_w()->set_blocked( blend()->blend_enable() );
  antialias_point_w()->set_blocked( blend()->antialias_point() );
  antialias_line_w()->set_blocked( blend()->antialias_line() );
  fog_enable_w()->set_blocked( blend()->fog_enable() );
  fog_mode_w()->set_blocked( blend()->fog_mode() );
  fog_parameter_w()->set_blocked( blend()->fog_parameter().data() );
  fog_color_w()->set_blocked( blend()->fog_color().data() );
}

void
Blend::
depth_enable_cb()
{
  blend()->depth_enable( depth_enable_w()->get() );
}

void
Blend::
depth_reset_cb()
{
  // reset the widgets
  depth_enable_w()->set_blocked( true );
  depth_mask_w()->set_blocked( 1 );
  depth_function_w()->set_blocked( 2 );

  // set the parameters in the milieu
  blend()->depth_enable(true);
  blend()->depth_function(2);
  blend()->depth_mask(1);
}

void
Blend::
depth_mask_cb()
{
  int n = depth_mask_w()->get();
  blend()->depth_mask(n);
}

void
Blend::
depth_function_cb()
{
  int n = depth_function_w()->get();
  blend()->depth_function(n);
}

void
Blend::
blend_enable_cb()
{
  blend()->blend_enable( blend_enable_w()->get() );
}

void
Blend::
blend_reset_cb()
{
  // set the widgets
  blend_enable_w()->set_blocked(false);
  blend_src_function_w()->set_blocked(4);
  blend_dest_function_w()->set_blocked(6);
  antialias_point_w()->set_blocked(false);
  antialias_line_w()->set_blocked(false);

  // set the milieu
  blend()->blend_enable(false);
  blend()->blend_src_function( 4 );
  blend()->blend_dest_function( 6 );
  blend()->antialias_point( false );
  blend()->antialias_line( false );
}

void
Blend::
blend_src_function_cb()
{
  uint n = blend_src_function_w()->get();
  blend()->blend_src_function( n );
}

void
Blend::
blend_dest_function_cb()
{
  uint n = blend_dest_function_w()->get();
  blend()->blend_dest_function( n );
}

void
Blend::
antialias_point_cb()
{
  blend()->antialias_point(
    antialias_point_w()->get() );
}

void
Blend::
antialias_line_cb()
{
  blend()->antialias_line(
    antialias_line_w()->get() );
}

void
Blend::
fog_set_sensitive( int mode )
{
  // enable/disable the appropriate parameter widgets
  // NOTE: this should be a method in NumberWidget2
  const int sensitive[][3] = {{0, 1, 1}, {1, 0, 0}, {1, 0, 0}};
  uint i;
  for ( i = 0; i < 3; i++)
  {
    fog_parameter_w()->set_sensitive( i, (bool)sensitive[mode][i] );
  }
}

void
Blend::
fog_enable_cb()
{
  blend()->fog_enable( fog_enable_w()->get() );
}

void
Blend::
fog_reset_cb()
{
  // unset the fog enable button
  fog_enable_w()->set(false);

  // set the mode widget (menubutton with choices exp/exp2/linear)
  // chose fog mode "exp"
  fog_mode_w()->set( 0 );
  // widgets set sensitive
  fog_set_sensitive( 0 );

  // set the parameters widgets (3 real numbers density/start/end)
  base::ArrayX<float,3U> parameter;
  parameter[0] = 0.1f;
  parameter[1] = 6.0f;
  parameter[2] = 12.0f;
  fog_parameter_w()->set( parameter.data() );

  // reset the fog color
  base::Color3 color( 1.0f, 1.0f, 1.0f );
  fog_color_w()->set( color.data() );
}

void
Blend::
fog_mode_cb()
{
  // fog_mode is a menubutton with choices exp/exp2/linear

  // get the fog mode
  int mode = fog_mode_w()->get();
  blend()->fog_mode( mode );

  fog_set_sensitive(mode);
}

void
Blend::
fog_parameter_cb()
{
  // fog_parameter are 3 real numbers density/start/end

  // get the fog parameters
  base::ArrayX<float,3U> parameter;
  fog_parameter_w()->get( parameter.data() );
  blend()->fog_parameter( parameter );
}

void
Blend::
fog_color_cb()
{
  base::Color3 a;
  fog_color_w()->get(a.data());
  blend()->fog_color( a );
}

bool
Blend::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  // blend
  if ( command == "antialiasPoint" )
  {
    antialias_point( read_bool(argument) );
    r = true;
  }
  else if ( command == "antialiasLine" )
  {
    antialias_line( read_bool(argument) );
    r = true;
  }
  else if ( command == "blendEnable" )
  {
    blend_enable( read_bool(argument) );
    r = true;
  }
  else if ( command == "blendSourceFunction" )
  {
    blend_src_function( read_uint(argument) );
    r = true;
  }
  else if ( command == "blendDestinationFunction" )
  {
    blend_dest_function( read_uint(argument) );
    r = true;
  }
  else if ( command == "fogEnable" )
  {
    fog_enable( read_bool(argument) );
    r = true;
  }
  else if ( command == "fogMode" )
  {
    fog_mode( read_uint(argument) );
    r = true;
  }
  else if ( command == "fogParameter" )
  {
    base::vector<float> v;
    read_list( v, 3, argument );
    base::ArrayX<float,3U> x(&v[0]);
    fog_parameter(x);
    r = true;
  }
  else if ( command == "fogColor" )
  {
    base::Color3 x;
    read_color(x, argument );
    fog_color(x);
    r = true;
  }
  else if ( command == "depthEnable" )
  {
    depth_enable( read_bool(argument) );
    r = true;
  }
  else if ( command == "depthFunction" )
  {
    depth_function( read_uint(argument) );
    r = true;
  }
  else if ( command == "depthMask" )
  {
    depth_mask( read_bool(argument) );
    r = true;
  }
#if 0
  else if ( command == "hintPointSmooth" )
  {
    hint_point_smooth( read_bool(argument) );
    r = true;
  }
  else if ( command == "hintLineSmooth" )
  {
    hint_line_smooth( read_uint(argument) );
    r = true;
  }
  else if ( command == "hintPolygonSmooth" )
  {
    hint_polygon_smooth( read_uint(argument) );
    r = true;
  }
  else if ( command == "hintFog" )
  {
    hint_fog( read_uint(argument) );
    r = true;
  }
  else if ( command == "hintPerspectiveCorrection" )
  {
    hint_perspective_correction( read_uint(argument) );
    r = true;
  }
#endif

  return r;
}

} // namespace ui
} // namespace milieu
