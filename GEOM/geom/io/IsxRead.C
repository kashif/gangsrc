/* GANG Software
 * GEOM/geom/io/IsxRead.C
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

#include "io/OstreamStream.H"
#include "IsxRead.H"

namespace geom {
namespace io {

IsxRead::
IsxRead()
    :
    JvxRead(),
    _mode(NOTHING_MODE),
    _milieumode(NOTHING_MILIEUMODE),
    _material_id(0U),
    _clipplane_id(0U),
    _light_id(0U),
    _materials(),
    _position(),
    _custom_color()
{
  _position.allocate(4U);
  _position.identity();
  _custom_color.enable = false;
}

IsxRead::
~IsxRead()
{
}

void
IsxRead::
initialize()
{
  // baseclass version
  JvxRead::initialize();
}

void
IsxRead::
finalize()
{
  // baseclass version
  JvxRead::finalize();
}

void
IsxRead::
_finalize()
{
  // set custom color
  if (_custom_color.enable)
  {
    custom_color();
  }  
}

void
IsxRead::start_tag_cb(
  char const *tag,
  AttributeList const &attributes )
{
  if (_error) { return; }

  if ( _mode == NOTHING_MODE )
  {
    if ( equal( tag, "milieu" ) )
    {
      _mode = MILIEU;
    }
    else if ( equal(tag, "materialset" ))
    {
      _mode = MATERIALSET;
      _material_id = 0;
    }
    else if ( equal(tag, "custom_color" ))
    {
      _mode = CUSTOMCOLOR;
      _custom_color.mode = 0U;
      _custom_color.color0.clear();
      _custom_color.color1.clear();
      _custom_color.scale = 0.0f;
    }
    else
    {
      // baseclass version
      JvxRead::start_tag_cb( tag, attributes );
    }
  }
  else if (_mode == MILIEU)
  {
    if ( equal( tag, "background" ) )
    { _milieumode = BACKGROUND; }
    else if ( equal( tag, "depth" ) )
    { _milieumode = DEPTH; }
    else if ( equal( tag, "blend" ) )
    { _milieumode = BLEND; }
    else if ( equal( tag, "fog" ) )
    { _milieumode = FOG; }
#if 0
    else if ( equal( tag, "hint" ) )
    { _milieumode = HINTS; }
#endif
    else if ( equal( tag, "clipplanes" ) )
    { _milieumode = CLIPPLANESET; _clipplane_id = 0; }
    else if ( equal( tag, "camera" ) )
    { _milieumode = CAMERA; }
    else if ( equal( tag, "globallight" ) )
    { _milieumode = GLOBALLIGHT; }
    else if ( equal( tag, "lights" ) )
    { _milieumode = LIGHTSET; _light_id = 0; }
  }
}

void
IsxRead::
end_tag_cb( char const *tag )
{
  if (_error) { return; }

  if ( _mode == MILIEU )
  {
    if ( equal( tag, "milieu" ) )
    {
      _mode = NOTHING_MODE;
    }
    else if ( _milieumode == BACKGROUND )
    {
      if ( equal(tag, "background" ))
      {
        _milieumode = NOTHING_MILIEUMODE;
      }
      else if ( equal( tag, "color" ) )
      {
        base::Color3 c;
        read_color( c, text(), RGB, false );
        _milieu->color(c);
      }
      else
      {
        error( "unknown entry in <background>" );
        return;
      }
    }
    else if ( _milieumode == DEPTH )
    {
      if ( equal(tag, "depth" ))
      {
        _milieumode = NOTHING_MILIEUMODE;
      }
      else if ( equal( tag, "enable" ) )
      {
        _milieu->depth_enable( read_bool(text()) );
      }
      else if ( equal( tag, "function" ) )
      {
        _milieu->depth_function( read_uint(text()) );
      }
      else if ( equal( tag, "mask" ) )
      {
        _milieu->depth_mask( read_uint(text()) );
      }
      else
      {
        error( "unknown entry in <depth>" );
        return;
      }
    }
    else if ( _milieumode == BLEND )
    {
      if ( equal(tag, "blend" ))
      {
        _milieumode = NOTHING_MILIEUMODE;
      }
      else if ( equal( tag, "enable" ) )
      {
        _milieu->blend_enable( read_bool(text()) );
      }
      else if ( equal( tag, "source_function" ) )
      {
        _milieu->blend_src_function( read_uint(text()) );
      }
      else if ( equal( tag, "destination_function" ) )
      {
        _milieu->blend_dest_function( read_uint(text()) );
      }
      else
      {
        error( "unknown entry in <blend>" );
        return;
      }
    }
    else if ( _milieumode == FOG )
    {
      if ( equal(tag, "fog" ))
      {
        _milieumode = NOTHING_MILIEUMODE;
      }
      else if ( equal( tag, "enable" ) )
      {
        _milieu->fog_enable( read_bool(text()) );
      }
      else if ( equal( tag, "mode" ) )
      {
        _milieu->fog_mode( read_uint(text()) );
      }
      else if ( equal( tag, "parameters" ) )
      {
        base::vector<Real> v;
        read_list(v, 3U, text());
        base::ArrayX<float, 3U> w;
        w[0] = v[0];
        w[1] = v[1];
        w[2] = v[2];
        _milieu->fog_parameter( w );
      }
      else if ( equal( tag, "color" ) )
      {
        base::Color3 c;
        read_color( c, text(), RGB, false );
        _milieu->fog_color(c);
      }
      else
      {
        error( "unknown entry in <fog>" );
        return;
      }
    }
#if 0
    else if ( _milieumode == HINTS )
    {
      if ( equal(tag, "hint" ))
      {
        _milieumode = NOTHING_MILIEUMODE;
      }
      else if ( equal( tag, "point_smooth" ) )
      {
        _milieu->hint_point_smooth( read_bool() );
      }
      else if ( equal( tag, "line_smooth" ) )
      {
        _milieu->hint_line_smooth( read_bool() );
      }
      else if ( equal( tag, "polygon_smooth" ) )
      {
        _milieu->hint_polygon_smooth( read_bool() );
      }
      else if ( equal( tag, "fog" ) )
      {
        _milieu->hint_fog( read_bool() );
      }
      else if ( equal( tag, "perspective_correction" ) )
      {
        _milieu->hint_perspective_correction( read_bool() );
      }
      else
      {
        error( "unknown entry in <hints>" );
        return;
      }
    }
#endif
    else if ( _milieumode == CLIPPLANESET )
    {
      if ( equal(tag, "clipplanes" ))
      {
        _milieumode = NOTHING_MILIEUMODE;
      }
      else if ( equal(tag, "clipplane" ) )
      {
        _clipplane_id++;
      }
      else if ( equal( tag, "enable" ) )
      {
        _milieu->milieu::kernel::ClipPlaneSet::enable(
          _clipplane_id, read_bool(text()) );
      }
      else if ( equal( tag, "position" ) )
      {
      }
      else
      {
        error( "unknown entry in <clipplane>" );
        return;
      }
    }
    else if ( _milieumode == CAMERA )
    {
      if ( equal(tag, "camera" ))
      {
        _milieumode = NOTHING_MILIEUMODE;
      }
      else if ( equal( tag, "perspective" ) )
      {
        base::vector<Real> v;
        read_list( v, 3U, text() );
        milieu::Camera cam;
        cam.fov = v[0];
        cam.znear = v[1];
        cam.zfar = v[2];
        _milieu->set_camera(cam);
      }
      else if ( equal( tag, "orthographic" ) )
      {
        base::vector<Real> v;
        read_list( v, 3U, text() );
        milieu::Camera cam;
        cam.zoom = v[0];
        cam.znear = v[1];
        cam.zfar = v[2];
        _milieu->set_camera(cam);
      }
      else if ( equal( tag, "window_size" ) )
      {
        base::vector<uint> v;
        read_list( v, 2U, text() );
        _milieu->set_window_size( v[0], v[1] );
      }
      else
      {
        error( "unknown entry in <camera>" );
        return;
      }
    }
    else if ( _milieumode == GLOBALLIGHT )
    {
      if ( equal(tag, "globallight" ))
      {
        _milieumode = NOTHING_MILIEUMODE;
      }
      else if ( equal( tag, "enable" ) )
      {
        static_cast< ::milieu::kernel::GlobalLight *>(_milieu)->
          enable( read_bool(text()) );
      }
      else if ( equal( tag, "ambient" ) )
      {
        base::Color3 c;
        read_color( c, text(), RGB, false );
        static_cast< ::milieu::kernel::GlobalLight *>(_milieu)->
          ambient(c);
      }
      else if ( equal( tag, "viewpoint" ) )
      {
        _milieu->viewpoint( read_bool(text()) );
      }
      else if ( equal( tag, "sidedness" ) )
      {
        _milieu->sidedness( read_bool(text()) );
      }
      else
      {
        error( "unknown entry in <globallight>" );
        return;
      }
    }
    else if ( _milieumode == LIGHTSET )
    {
      if ( equal(tag, "lights" ))
      {
        _milieumode = NOTHING_MILIEUMODE;
      }
      else if ( equal(tag, "light" ) )
      {
        _light_id++;
      }
      else if ( equal( tag, "enable" ) )
      {
        static_cast< ::milieu::kernel::LightSet *>(_milieu)->
          enable(_light_id, read_bool(text()));        
      }
      else if ( equal( tag, "ambient" ) )
      {
        base::Color3 c;
        read_color( c, text(), RGB, false );
        static_cast< ::milieu::kernel::LightSet *>(_milieu)->
          ambient(_light_id, c);
      }
      else if ( equal( tag, "diffuse" ) )
      {
        base::Color3 c;
        read_color( c, text(), RGB, false );
        _milieu->diffuse(_light_id, c);
      }
      else if ( equal( tag, "specular" ) )
      {
        base::Color3 c;
        read_color( c, text(), RGB, false );
        _milieu->specular(_light_id, c);
      }
      else if ( equal( tag, "spot" ) )
      {
        base::vector<Real> v;
        read_list( v, 5U, text() );
        base::ArrayX<float, 5U> w;
        w[0] = v[0];
        w[1] = v[1];
        w[2] = v[2];
        w[3] = v[3];
        w[4] = v[4];
        _milieu->spot(_light_id, w);
      }
      else if ( equal( tag, "attenuation" ) )
      {
        base::vector<Real> v;
        read_list( v, 3U, text() );
        base::ArrayX<float, 3U> w;
        w[0] = v[0];
        w[1] = v[1];
        w[2] = v[2];
        _milieu->attenuation(_light_id, w);
      }
      else if ( equal( tag, "position" ) )
      {
        Transform t;
        read_transform(t, text());
        DIE_IF( t.dim() != 4U );
        _milieu->LightSet::position( _light_id, t );
      }
      else
      {
        error( "unknown entry in <light>" );
        return;
      }
    }
  }

  else if (_mode == MATERIALSET )
  {
    if ( equal( tag, "materialset" ) )
    {
      // insert materials
      _geomlist->materials( _materials );

      _mode = NOTHING_MODE;
    }
    else if ( equal(tag, "material" ) )
    {
      _material_id++;
    }
    else if ( equal(tag, "enable" ) )
    {
      _materials.enable(_material_id, read_bool(text()) );
    }
    else if ( equal(tag, "color" ) )
    {
      base::Color4 c;
      read_color( c, text(), RGBA, false );
      _materials.color(_material_id, c);
    }
    else if ( equal(tag, "ambient" ) )
    {
      base::Color3 c;
      read_color( c, text(), RGB, false );
      _materials.ambient(_material_id, c);
    }
    else if ( equal(tag, "diffuse" ) )
    {
      base::Color4 c;
      read_color( c, text(), RGBA, false );
      _materials.diffuse( _material_id, c );
    }
    else if ( equal(tag, "specular" ) )
    {
      base::Color3 c;
      read_color( c, text(), RGB, false );
      _materials.specular( _material_id, c );
    }
    else if ( equal(tag, "emissive" ) )
    {
      base::Color3 c;
      read_color( c, text(), RGB, false );
      _materials.emissive( _material_id, c );
    }
    else if ( equal(tag, "shininess" ) )
    {
      _materials.shininess( _material_id, read_real(text()) );
    }
    else if ( equal(tag, "element_size" ) )
    {
      _materials.element_size( _material_id, read_real(text()) );
    }
    else if ( equal(tag, "gap" ) )
    {
      base::vector<Real> v;
      read_list(v, 2U, text());
      base::ArrayX<float, 2U> w;
      w[0] = v[0];
      w[1] = v[1];
      _materials.gap( _material_id, w );
    }
    else if ( equal(tag, "model" ) )
    {
      _materials.model( _material_id, read_uint(text()) );
    }
    else if ( equal(tag, "shademodel" ) )
    {
      _materials.shademodel( _material_id, read_bool(text()) );
    }
    else if ( equal(tag, "nudge" ) )
    {
      base::vector<Real> v;
      read_list(v, 2U, text());
      base::ArrayX<float, 2U> w;
      w[0] = v[0];
      w[1] = v[1];
      _materials.nudge( _material_id, w );
    }
    else if ( equal(tag, "side" ) )
    {
      base::vector<uint> v;
      read_list(v, 2U, text());
      base::ArrayX<uint, 2U> w;
      w[0] = v[0];
      w[1] = v[1];
      _materials.side( _material_id, w );
    }
    else if ( equal(tag, "lit" ) )
    {
      _materials.lit( _material_id, read_bool(text()) );
    }
    else if ( equal(tag, "transparent" ) )
    {
      _materials.transparent( _material_id, read_bool(text()) );
    }
    else if ( equal(tag, "custom_color" ) )
    {
      _materials.custom_color( _material_id, read_bool(text()) );
      _custom_color.enable = true;
    }
    else
    {
      error( "unknown entry in <material>" );
      return;
    }
  }

  else if ( _mode == CUSTOMCOLOR )
  {
    if ( equal( tag, "custom_color" ) )
    {
      _mode = NOTHING_MODE;
    }
    else if ( equal( tag, "mode" ) )
    {
      uint x = read_uint(text());
      if (x > 8U)
      {
        error( "custom_color mode out of range" );
        return;
      }
      _custom_color.mode = x;
    }
    else if ( equal( tag, "color0" ) )
    {
      base::Color4 c;
      read_color( c, text(), RGBA, false );
      _custom_color.color0 = c;
    }
    else if ( equal( tag, "color1" ) )
    {
      base::Color4 c;
      read_color( c, text(), RGBA, false );
      _custom_color.color1 = c;
    }
    else if ( equal( tag, "scale" ) )
    {
      Real x = read_real(text());
      if (x < 0.0f || x > 1.0f)
      {
        error( "custom_color scale out of range" );
        return;
      }
      _custom_color.scale = x;
    }
    else
    {
      error( "unknown entry in <custom_color>" );
      return;
    }
  }

  else
  {
    if ( equal( tag, "position" ) )
    {
      Transform p;
      read_transform(p, text());
      if (p.dim() == 4U ) { _position = p; }
    }
    else
    {
      // baseclass version
      JvxRead::end_tag_cb( tag );
    }
  }
}

void
IsxRead::
custom_color()
{
  if (_custom_color.mode == 0U)
  {
  }
  else if (_custom_color.mode == 1U)
  {
    _geomlist->color_by_normal(
      _custom_color.color0 );
  }
  else if (_custom_color.mode == 2U)
  {
    _geomlist->color_by_gaussian_curvature(
      _custom_color.color0, _custom_color.scale);
  }
  else if (_custom_color.mode == 3U)
  {
    _geomlist->color_by_mean_curvature(
      _custom_color.color0, _custom_color.scale);
  }
  else if (_custom_color.mode == 4U)
  {
    _geomlist->color_by_area(
      _custom_color.color0, _custom_color.scale);
  }
  else if (_custom_color.mode == 5U)
  {
    _geomlist->color_by_direction(
      _custom_color.color0 );
  }
  else if (_custom_color.mode == 6U)
  {
    _geomlist->color_by_distance(
      _custom_color.color0, _custom_color.scale);
  }
  else if (_custom_color.mode == 7U)
  {
    _geomlist->color_randomly( _custom_color.color0 );
  }
  else if (_custom_color.mode == 8U)
  {
    _geomlist->color_checked( _custom_color.color0, _custom_color.color1 );
  }
}

void
IsxRead::
end_geometry( surface0::Surface &s )
{
  s.position(_position);
}

} // namespace io
} // namespace geom
