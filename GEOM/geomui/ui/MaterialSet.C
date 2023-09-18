/* GANG Software
 * GEOM/geomui/ui/MaterialSet.C
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
#include "MaterialSet.H"

namespace geomui {
namespace ui {

MaterialSet::ShininessVal const
MaterialSet::_shininess_val[MaterialSet::SHININESS_COUNT] =
{
  { 0.0f, 0.0f },
  { 0.05f, 0.05f },
  { 0.1f, 0.1f },
  { 0.2f, 0.2f },
  { 1.0f, 1.0f }
};

MaterialSet::
MaterialSet()
    :
    widget::ui::Dialog(),
    base::ReadUtil(),
    _shininess_(3)
{
#if FIX
  set_color_widgets();
  set_model_widgets();
#endif
}

MaterialSet::
~MaterialSet()
{
}

// interface

void
MaterialSet::
material_reset()
{
  uint id;
  for ( id = 0; id < geom::Surface::material_count(); id++ )
  {
    material_reset(id);
  }
}

void
MaterialSet::
material_reset(uint id)
{
  geomlist()->reset_material(id);
  set_ui_from_data( id, *geomlist() );
}

void
MaterialSet::
material_element_size( uint id, float a )
{
  _element_size(id, a);
  if ( id == id_w()->get()) { element_size_w()->set_blocked(a); }
}

void
MaterialSet::
material_color( uint id, base::Color4 const &a )
{
  _color(id, a);
  if ( id == id_w()->get()) { color_w()->set_blocked(a.data()); }
}

void
MaterialSet::
material_ambient( uint id, base::Color3 const &a )
{
  _ambient(id, a);
  if ( id == id_w()->get()) { ambient_w()->set_blocked(a.data()); }
}

void
MaterialSet::
material_diffuse( uint id, base::Color4 const &a )
{
  _diffuse(id, a);
  if ( id == id_w()->get()) { diffuse_w()->set_blocked(a.data()); }
}

void
MaterialSet::
material_specular( uint id, base::Color3 const &a )
{
  _specular(id, a);
  if ( id == id_w()->get()) { specular_w()->set_blocked(a.data()); }
}

void
MaterialSet::
material_emissive( uint id, base::Color3 const &a )
{
  _emissive(id, a);
  if ( id == id_w()->get()) { emissive_w()->set_blocked(a.data()); }
}

void
MaterialSet::
material_shininess( uint id, float a )
{
  _shininess(id, a);
  if ( id == id_w()->get()) { shininess_w()->set_blocked(a); }
}

void
MaterialSet::
material_nudge( uint id, base::ArrayX<float,2U> const &a )
{
  _nudge(id, a);
  if ( id == id_w()->get()) { nudge_w()->set(a.data()); }
}

void
MaterialSet::
material_side( uint id, base::ArrayX<uint,2U> const &a )
{
  _side( id, a );
  if ( id == id_w()->get())
  {
    side0_w()->set(a[0]);
    side1_w()->set(a[1]);
  }
}



void
MaterialSet::
material_enable( uint id, bool a )
{
  _enable(id, a);
  if ( id == id_w()->get() ) { enable_w()->set_blocked(a); }
}

void
MaterialSet::
material_transparent( uint id, bool state )
{
  _transparent(id, state);
  if (id == id_w()->get()) { transparent_w()->set_blocked(state); }
}

void
MaterialSet::
material_shademodel( uint id, bool a )
{
  _shademodel(id, a);
  if (id == id_w()->get()) { shademodel_w()->set_blocked(a); }
}


void
MaterialSet::
material_gap( uint id, base::ArrayX<float,2U> const &a )
{
  _gap(id, a);
  if (id == id_w()->get()) { gap_w()->set_blocked(a.data()); }
}


void
MaterialSet::
material_lit( uint id, bool state )
{
  _lit(id, state);
  if (id == id_w()->get()) { lit_w()->set_blocked(state); }
}

void
MaterialSet::
material_toggle_geomobject( uint id )
{
  bool state = ! geomlist()->enable(id);
  _enable( id, state );
  if ( id == id_w()->get() )
  {
    enable_w()->set_blocked( state );
  }
  refresh_all();
}

void
MaterialSet::
material_toggle_shademodel( uint n )
{
  bool state = ! geomlist()->shademodel(n);
  geomlist()->shademodel(n, state);
  if ( n == id_w()->get() )
  {
    shademodel_w()->set_blocked( state );
  }
  refresh_all();
}

void
MaterialSet::
material_toggle_transparent( uint n )
{
  bool state = ! geomlist()->transparent(n);
  transparent_w()->set(state);
  geomlist()->transparent(n, state);
  if ( n == id_w()->get() )
  {
    transparent_w()->set_blocked( state );
  }
  refresh_all();
}

void
MaterialSet::
material_toggle_mirror( uint n )
{
  // toggle side[1] between 0 and 3
  base::ArrayX<uint,2U> const &a = geomlist()->side(n);
  if (a[0] == 3U && a[1] == 3U)
  {
    uint const b[2] = { 3U, 0U };
    base::ArrayX<uint,2U> c(b);
    geomlist()->side(n,c);
    if ( n == id_w()->get() )
    {
      side0_w()->set_blocked( c[0] );
      side1_w()->set_blocked( c[1] );
    }
  }
  else if ( a[0] == 3U && a[1] == 0U )
  {
    uint const b[2] = { 0U, 3U };
    base::ArrayX<uint,2U> c(b);
    geomlist()->side(n,c);
    if ( n == id_w()->get() )
    {
      side0_w()->set_blocked( c[0] );
      side1_w()->set_blocked( c[1] );
    }
  }
  else
  {
    uint const b[2] = { 3U, 3U };
    base::ArrayX<uint,2U> c(b);
    geomlist()->side(n,c);
    if ( n == id_w()->get() )
    {
      side0_w()->set_blocked( c[0] );
      side1_w()->set_blocked( c[1] );
    }
  }
  refresh_all();
}


void
MaterialSet::
material_shininess(uint)
{
  float c = _shininess_val[_shininess_].specular;
  base::Color3 s( c, c, c );

  geomlist()->specular(0, s );
  geomlist()->shininess(0, _shininess_val[_shininess_].shininess );

  if ( id_w()->get() == 0 )
  {
    specular_w()->set_blocked( s.data() );
    shininess_w()->set_blocked( _shininess_val[_shininess_].shininess );
  }
  refresh_all();
}

void
MaterialSet::
material_shininess_next()
{
  _shininess_ = ( _shininess_ == SHININESS_COUNT-1 ? 0 : _shininess_ + 1 );
  material_shininess(_shininess_);
}

void
MaterialSet::
material_shininess_prev()
{
  _shininess_ = ( _shininess_ == 0 ? SHININESS_COUNT-1 : _shininess_ - 1 );
  material_shininess(_shininess_);
}

// implementation

void
MaterialSet::
_enable( uint id, bool state )
{
  geomlist()->enable(id, state);
#if 0
  // adjust nudge
  uint const a0 = geom::BOUNDARY;
  uint const a1 = geom::SILHOUETTE;
  uint const a2 = geom::BBOX;
  uint const a3 = geom::POINT;
  uint const a4 = geom::LINE;

  if (id == a0 || id == a1 || id == a2 || id == a3 || id == a4)
  {
    bool f =
      geomlist()->enable(a0) ||
      geomlist()->enable(a1) ||
      geomlist()->enable(a2) ||
      geomlist()->enable(a3) ||
      geomlist()->enable(a4);
    if (f)
    {
      base::ArrayX<float,2U> a;
      a[0] = 1.0;
      a[1] = 1.0;
      material_nudge( geom::FACE, a );
      a[0] = 2.0;
      a[1] = 2.0;
      material_nudge( geom::EDGE, a );
    }
    else
    {
      base::ArrayX<float,2U> a;
      a[0] = 0.0;
      a[1] = 0.0;
      material_nudge( geom::FACE, a );
      a[0] = 0.0;
      a[1] = -1.0;
      material_nudge( geom::EDGE, a );
    }
  }
#endif
  refresh_all();
}

void
MaterialSet::
_model( uint id, uint model )
{
  set_model_widgets();
  geomlist()->model(id, model);
  refresh_all();
}


void
MaterialSet::
_transparent( uint id, bool state )
{
  geomlist()->transparent(id, state);
  refresh_all();
}

void
MaterialSet::
_shademodel( uint id, bool state )
{
  geomlist()->shademodel(id, state);
  refresh_all();
}

void
MaterialSet::
_gap( uint id, base::ArrayX<float,2U> const &a )
{
  geomlist()->gap(id, a);
  refresh_all();
}

void
MaterialSet::
_side( uint id, base::ArrayX<uint,2U> const &a )
{
  geomlist()->side(id, a);
  refresh_all();
}

void
MaterialSet::
_lit( uint id, bool state )
{
  set_color_widgets();
  geomlist()->lit(id, state);
  refresh_all();
}


void
MaterialSet::
_nudge( uint id, base::ArrayX<float,2U> const &a )
{
  geomlist()->nudge(id, a);
  refresh_all();
}

void
MaterialSet::
_color( uint id, base::Color4 const &a )
{
  geomlist()->color(id, a);
  refresh_all();
}

void
MaterialSet::
_custom_color( uint id, bool state )
{
  set_color_widgets();
  set_model_widgets();
  geomlist()->custom_color(id, state);
  refresh_all();
}

void
MaterialSet::
_ambient( uint id, base::Color3 const &a )
{
  geomlist()->ambient(id, a);
  refresh_all();
}

void
MaterialSet::
_diffuse( uint id, base::Color4 const &a )
{
  geomlist()->diffuse(id, a);
  refresh_all();
}

void
MaterialSet::
_specular( uint id, base::Color3 const &a )
{
  geomlist()->specular(id, a);
  refresh_all();
}

void
MaterialSet::
_emissive( uint id, base::Color3 const &a )
{
  geomlist()->emissive(id, a);
  refresh_all();
}

void
MaterialSet::
_shininess( uint id, float state )
{
  geomlist()->shininess(id, state);
  refresh_all();
}

void
MaterialSet::
_element_size( uint id, float a )
{
  geomlist()->element_size(id, a);
  refresh_all();
}

// utility

void
MaterialSet::
set_data_from_ui(
  uint id, geom::Surface &m )
{
  // read widgets into m

  {
    // materials
  float a2[2];

  m.enable( enable_w()->get() );

  m.transparent( id, transparent_w()->get() );
  m.element_size( id, element_size_w()->get() );
  gap_w()->get(a2); m.gap( id, a2 );
  m.shademodel( id, shademodel_w()->get() );
  nudge_w()->get(a2); m.nudge( id, a2 );
  uint a[2];
  a[0] = side0_w()->get();
  a[1] = side1_w()->get();
  m.side( id, a );
  }

  {
    // colors
  base::Color3 c3;
  base::Color4 c4;

  m.custom_color( custom_color_w()->get() );
  m.lit( id, lit_w()->get() );
  m.model( id, model_w()->get() );

  color_w()->get(c4.data()); m.color( id, c4 );
  ambient_w()->get(c3.data()); m.ambient( id, c3 );
  diffuse_w()->get(c4.data()); m.diffuse( id, c4 );
  specular_w()->get(c3.data()); m.specular( id, c3 );
  emissive_w()->get(c3.data()); m.emissive( id, c3 );
  m.shininess( id, shininess_w()->get() );
  }
}

void
MaterialSet::
set_ui_from_data(
  uint id,
  geom::Surface const &m )
{
  // set widgets from m
  {
    // materials
  enable_w()->set_blocked( m.enable(id) );
  transparent_w()->set_blocked( m.transparent(id) );
  element_size_w()->set_blocked( m.element_size(id) );
  gap_w()->set_blocked( m.gap(id).data() );
  shademodel_w()->set_blocked( m.shademodel(id) );
  nudge_w()->set_blocked( m.nudge(id).data() );
  side0_w()->set_blocked( m.side(id)[0] );
  side1_w()->set_blocked( m.side(id)[1] );
  refresh_all();
  }
  {
    // colors
  custom_color_w()->set_blocked( m.custom_color(id) );
  lit_w()->set_blocked( m.lit(id) );
  model_w()->set_blocked( m.model(id) );

  color_w()->set_blocked( m.color(id).data() );
  ambient_w()->set_blocked( m.ambient(id).data() );
  diffuse_w()->set_blocked( m.diffuse(id).data() );
  specular_w()->set_blocked( m.specular(id).data() );
  emissive_w()->set_blocked( m.emissive(id).data() );
  shininess_w()->set_blocked( m.shininess(id) );
  }
  set_color_widgets();
  set_model_widgets();
}

void
MaterialSet::
material_custom_color( uint id, bool state )
{
  if (id_w()->get() == id)
  {
    custom_color_w()->set_blocked( state );
  }

  set_color_widgets();
  set_model_widgets();

  geomlist()->custom_color(id, state);
  refresh_all();
}


void
MaterialSet::
set_color_widgets()
{
  bool lit = lit_w()->get();

  if (lit)
  {
    // lit
    color_w()->show(false);
    hidebox_w()->show(true);
  }
  else
  {
    // unlit
    bool custom = custom_color_w()->get();
    color_w()->show(!custom);
    hidebox_w()->show(false);
  }
}

void
MaterialSet::
set_model_widgets()
{
  bool lit = lit_w()->get();
  if (!lit) { return; }

  bool custom = custom_color_w()->get();
  uint model = model_w()->get();

  if (custom)
  {
    static const int sensitive[][4] =
      {
        { 0, 1, 1, 1 }, // AMBIENT
        { 1, 0, 1, 1 }, // DIFFUSE
        { 0, 0, 1, 1 }, // AMBIENT_AND_DIFFUSE
        { 1, 1, 0, 1 }, // SPECULAR
        { 1, 1, 1, 0 }  // EMISSION
      };

    ambient_w()->set_sensitive(sensitive[model][0]);
    diffuse_w()->set_sensitive(sensitive[model][1]);
    specular_w()->set_sensitive(sensitive[model][2]);
    emissive_w()->set_sensitive(sensitive[model][3]);
  }
  else
  {
    // lit, not custom color
    ambient_w()->set_sensitive(true);
    diffuse_w()->set_sensitive(true);
    specular_w()->set_sensitive(true);
    emissive_w()->set_sensitive(true);
  }
}


// callbacks

void
MaterialSet::
reset_cb()
{
  material_reset( id_w()->get() );
}

void
MaterialSet::
element_size_cb()
{
  uint id = id_w()->get();
  float a = element_size_w()->get();
  if (id != 0) { a = ::rint(a); }
  _element_size( id, a );
}

void
MaterialSet::
gap_cb()
{
  base::ArrayX<float,2U> a;
  gap_w()->get( a.data() );
  _gap( id_w()->get(), a );
}


void
MaterialSet::
side_cb()
{
  base::ArrayX<uint,2U> a;
  a[0] = side0_w()->get();
  a[1] = side1_w()->get();
  _side( id_w()->get(), a );
}

void
MaterialSet::
nudge_cb()
{
  base::ArrayX<float,2U> a;
  nudge_w()->get( a.data() );
  _nudge( id_w()->get(), a );
}

void
MaterialSet::
reset_color_cb()
{
}


void
MaterialSet::
color_cb()
{
  base::Color4 a;
  color_w()->get( a.data() );
  _color( id_w()->get(), a );
}

void
MaterialSet::
ambient_cb()
{
  base::Color3 a;
  ambient_w()->get( a.data() );
  _ambient( id_w()->get(), a );
}

void
MaterialSet::
diffuse_cb()
{
  base::Color4 a;
  diffuse_w()->get( a.data() );
  _diffuse( id_w()->get(), a );
}

void
MaterialSet::
specular_cb()
{
  base::Color3 a;
  specular_w()->get( a.data() );
  _specular( id_w()->get(), a );
}

void
MaterialSet::
emissive_cb()
{
  base::Color3 a;
  emissive_w()->get( a.data() );
  _emissive( id_w()->get(), a );
}


bool
MaterialSet::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "materialResetAll" )
  {
    material_reset();
    r = true;
  }
  else if ( command == "materialReset" )
  {
    base::String id, x;
    split1( id, x, argument );
    material_reset( read_uint(id) );
    r = true;
  }
  else if ( command == "materialEnable" )
  {
    base::String id, x;
    split1( id, x, argument );
    material_enable( read_uint(id), read_bool(x) );
    r = true;
  }

  else if ( command == "materialShademodel" )
  {
    base::String id, x;
    split1( id, x, argument );
    material_shademodel( read_uint(id), read_bool(x) );
    r = true;
  }

  else if ( command == "materialModel" )
  {
    base::String id, x;
    split1( id, x, argument );
    material_model( read_uint(id), read_uint(x) );
    r = true;
  }

  else if ( command == "materialElementSize" )
  {
    base::String id, x;
    split1( id, x, argument );
    material_element_size( read_uint(id), read_real(x) );
    r = true;
  }

  else if ( command == "materialGap" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::vector<float> v;
    read_list( v, 2, x );
    base::ArrayX<float, 2U> y(&v[0]);
    material_gap( read_uint(id), y );
    r = true;
  }

  else if ( command == "materialColor" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::Color4 y;
    read_color( y, x );
    material_color( read_uint(id), y );
    r = true;
  }

  else if ( command == "materialAmbient" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::Color3 y;
    read_color( y, x );
    material_ambient( read_uint(id), y );
    r = true;
  }

  else if ( command == "materialDiffuse" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::Color4 y;
    read_color( y, x );
    material_diffuse( read_uint(id), y );
    r = true;
  }

  else if ( command == "materialSpecular" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::Color3 y;
    read_color( y, x );
    material_specular( read_uint(id), y );
    r = true;
  }

  else if ( command == "materialEmissive" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::Color3 y;
    read_color( y, x );
    material_emissive( read_uint(id), y );
    r = true;
  }

  else if ( command == "materialShininess" )
  {
    base::String id, x;
    split1( id, x, argument );
    material_shininess( read_uint(id), read_real(x) );
    r = true;
  }

  else if ( command == "materialSide" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::vector<uint> v;
    read_list( v, 2, x );
    base::ArrayX<uint, 2U> y(&v[0]);
    material_side( read_uint(id), y );
    r = true;
  }

  else if ( command == "materialNudge" )
  {
    base::String id, x;
    split1( id, x, argument );
    base::vector<float> v;
    read_list( v, 2, x );
    base::ArrayX<float, 2U> y(&v[0]);
    material_nudge( read_uint(id), y );
    r = true;
  }

  else if ( command == "materialLit" )
  {
    base::String id, x;
    split1( id, x, argument );
    material_lit( read_uint(id), read_bool(x) );
    r = true;
  }

  else if ( command == "materialTransparent" )
  {
    base::String id, x;
    split1( id, x, argument );
    material_transparent( read_uint(id), read_bool(x) );
    r = true;
  }

  else if ( command == "materialCustomColor" )
  {
    base::String id, x;
    split1( id, x, argument );
    material_custom_color( read_uint(id), read_bool(x) );
    r = true;
  }
  else if ( command == "materialShininess" )
  {
    material_shininess( read_uint(argument) );
    r = true;
  }
  else if ( command == "materialShininessNext" )
  {
    material_shininess_next();
    r = true;
  }

  else if ( command == "materialShininessPrev" )
  {
    material_shininess_prev();
    r = true;
  }


  else if ( command == "materialToggleGeomobject" )
  {
    material_toggle_geomobject( read_uint(argument) );
    r = true;
  }
  else if ( command == "materialToggleFaces" )
  {
//    material_toggle_faces();
    r = true;
  }
  else if ( command == "materialToggleEdges" )
  {
    material_toggle_edges();
    r = true;
  }
  else if ( command == "materialToggleVertices" )
  {
    material_toggle_vertices();
    r = true;
  }
  else if ( command == "materialToggleBoundary" )
  {
    material_toggle_boundary();
    r = true;
  }
  else if ( command == "materialToggleSilhouette" )
  {
    material_toggle_silhouette();
    r = true;
  }
  else if ( command == "materialToggleBbox" )
  {
    material_toggle_bbox();
    r = true;
  }
  else if ( command == "materialToggleShademodel" )
  {
    material_toggle_shademodel();
    r = true;
  }
  else if ( command == "materialToggleTransparent" )
  {
    material_toggle_transparent();
    r = true;
  }
  else if ( command == "materialToggleMirror" )
  {
    material_toggle_mirror();
    r = true;
  }

  return r;
}

} // namespace ui
} // namespace geomui
