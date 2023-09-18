/* GANG Software
 * GEOM/geomui/ui/CustomColor.C
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

#include "base/ArrayX.H"
#include "CustomColor.H"

namespace geomui {
namespace ui {

base::Color4 const CustomColor::color_surface_default_orig(
  0.5f, 0.25f, 0.25f, 0.5f ); // RGB
base::Color4 const CustomColor::color_surface_default(
  0.5f, 0.25f, 0.25f, 0.5f ); // RGB
float const CustomColor::scale_default = 0.5;

CustomColor::
CustomColor()
    :
    widget::ui::Dialog(),
    base::ReadUtil()
{
}

CustomColor::
~CustomColor()
{
}

void
CustomColor::
customcolor_synchronize()
{
  if (geomlist()->empty()) { return; }

  uint mode;
  base::Color4 color0;
  base::Color4 color1;
  float scale;
  geomlist()->colorData(mode, color0, color1, scale);
  base::hsv2rgb( color0 );
  base::hsv2rgb( color1 );

  color_choice_w()->set_blocked(mode);

  if ( mode == 0U )
  {
    color0_w()->set( color0.data() );
  }
  else if ( mode == 1U )
  {
    color1_w()->set( color0.data() );
  }
  else if ( mode == 2U )
  {
    color2_w()->set( color0.data() );
    scale2_w()->set( scale );
  }
  else if ( mode == 3U )
  {
    color3_w()->set( color0.data() );
    scale3_w()->set( scale );
  }
  else if ( mode == 4U )
  {
    color4_w()->set( color0.data() );
    scale4_w()->set( scale );
  }
  else if ( mode == 5U )
  {
    color5_w()->set( color0.data() );
  }
  else if ( mode == 6U )
  {
    color6_w()->set( color0.data() );
    scale6_w()->set( scale );
  }
  else if ( mode == 7U )
  {
    color7_w()->set( color0.data() );
  }
  else if ( mode == 8U )
  {
    color8a_w()->set( color0.data() );
    color8b_w()->set( color1.data() );
  }
  else if ( mode == 9U )
  {
    // NOTE
  }
}

void
CustomColor::
customcolor_reset()
{
  if (geomlist()->empty()) { return; }

  // if the new surface has color data, set the viewer
  // to show it (ambient+diffuse)
  if ( geomlist()->has_original_color() )
  {
    // make "original color" widget sensitive
    color_choice_w()->show(0, true);

    // original color
    color_choice_w()->set_blocked(0);
    customcolor_select(0);
  }
  else
  {
    // make "original color" widget insensitive
    color_choice_w()->show(0, false);

    // color by normal
    color_choice_w()->set_blocked(1);
    customcolor_select(1);
  }

  if ( geomlist()->type() == geomlist()->INDEXED )
  {
    // disable widgets inappropriate for Indexed surfaces
    color_choice_w()->show(8, false);
  }
  else if ( geomlist()->type() == geomlist()->GRID )
  {
    // enable widgets appropriate for Grid surfaces
    color_choice_w()->show(8, true);
  }
  else
  {
    DIE();
  }
}

void
CustomColor::
customcolor_select( uint id )
{
  if ( id == 0 ) { customcolor_set_color0(); }
  else if ( id == 1 ) { customcolor_set_color1(); }
  else if ( id == 2 ) { customcolor_set_color2(); }
  else if ( id == 3 ) { customcolor_set_color3(); }
  else if ( id == 4 ) { customcolor_set_color4(); }
  else if ( id == 5 ) { customcolor_set_color5(); }
  else if ( id == 6 ) { customcolor_set_color6(); }
  else if ( id == 7 ) { customcolor_set_color7(); }
  else if ( id == 8 ) { customcolor_set_color8(); }
  else if ( id == 9 ) { customcolor_set_color9(); }
  else { DIE(); }
}

void
CustomColor::
customcolor_set_color0()
{
  base::Color4 a;
  color0_w()->get( a.data() );
  base::rgb2hsv( a );
  geomlist()->color_original( a );
}

void
CustomColor::
customcolor_set_color1()
{
  base::Color4 a;
  color1_w()->get( a.data() );
  base::rgb2hsv( a );
  geomlist()->color_by_normal( a );
}

void
CustomColor::
customcolor_set_color2()
{
  base::Color4 a;
  color2_w()->get( a.data() );
  float scale = scale2_w()->get();
  base::rgb2hsv( a );
  geomlist()->color_by_gaussian_curvature( a, scale );
}

void
CustomColor::
customcolor_set_color3()
{
  base::Color4 a;
  color3_w()->get( a.data() );
  float scale = scale3_w()->get();
  base::rgb2hsv( a );
  geomlist()->color_by_mean_curvature( a, scale );
}

void
CustomColor::
customcolor_set_color4()
{
  base::Color4 a;
  color4_w()->get( a.data() );
  float scale = scale4_w()->get();
  base::rgb2hsv( a );
  geomlist()->color_by_area( a, scale );
}

void
CustomColor::
customcolor_set_color5()
{
  base::Color4 a;
  color5_w()->get( a.data() );
  base::rgb2hsv( a );
  geomlist()->color_by_direction( a );
}

void
CustomColor::
customcolor_set_color6()
{
  base::Color4 a;
  color6_w()->get( a.data() );
  float scale = scale6_w()->get();
  base::rgb2hsv( a );
  geomlist()->color_by_distance( a, scale );
}

void
CustomColor::
customcolor_set_color7()
{
  base::Color4 a;
  color7_w()->get( a.data() );
  base::rgb2hsv( a );
  geomlist()->color_randomly( a );
}

void
CustomColor::
customcolor_set_color8()
{
  base::Color4 a, b;

  color8a_w()->get( a.data() );
  color8b_w()->get( b.data() );

  base::rgb2hsv( a );
  base::rgb2hsv( b );

  geomlist()->color_checked(a, b);
}

void
CustomColor::
customcolor_set_color9()
{
  float a[2U];
  color9_w()->get( a );
  geomlist()->alpha_fade( a[0], a[1] );
}

void
CustomColor::
customcolor_next()
{
  bool _color0 = color_choice_w()->showing(0);
  bool _color8 = color_choice_w()->showing(8);
  uint n = color_choice_w()->get();
  n++;
  if (n > (_color8 ? 8 : 7)) { n = (_color0 ? 0 : 1); }
  color_choice_w()->set(n);
}

void
CustomColor::
customcolor_prev()
{
  bool _color0 = color_choice_w()->showing(0);
  bool _color8 = color_choice_w()->showing(8);

  int n = color_choice_w()->get();
  n--;
  if (n < (_color0 ? 0 : 1)) { n = (_color8 ? 8 : 7); }
  color_choice_w()->set(n);
}


void
CustomColor::
color_reset0_cb()
{
  color0_w()->set( color_surface_default_orig.data() );
}

void
CustomColor::
color_reset1_cb()
{
  color1_w()->set( color_surface_default.data() );
}

void
CustomColor::
color_reset2_cb()
{
  scale2_w()->set( scale_default );
  color2_w()->set( color_surface_default.data() );
}

void
CustomColor::
color_reset3_cb()
{
  scale3_w()->set( scale_default );
  color3_w()->set( color_surface_default.data() );
}

void
CustomColor::
color_reset4_cb()
{
  scale4_w()->set( scale_default );
  color4_w()->set( color_surface_default.data() );
}

void
CustomColor::
color_reset5_cb()
{
  color5_w()->set( color_surface_default.data() );
}

void
CustomColor::
color_reset6_cb()
{
  scale6_w()->set( scale_default );
  color6_w()->set( color_surface_default.data() );
}

void
CustomColor::
color_reset7_cb()
{
  color7_w()->set( color_surface_default.data() );
}

void
CustomColor::
color_reset8_cb()
{
  color8a_w()->set( color_surface_default.data() );
  color8b_w()->set( color_surface_default.data() );
}

void
CustomColor::
color_reset9_cb()
{
  float a[] = {1.0f, 2.0f };
  color9_w()->set( a );
}

void
CustomColor::
color_choice_cb()
{
  // set the materials custom color widget
  material_custom_color(0, true);

  customcolor_select( color_choice_w()->get() );
  refresh_all();
}

void
CustomColor::
customcolor_original(
  base::Color4 const &c )
{
  color0_w()->set_blocked(c.data());
  customcolor_select(0);
}

void
CustomColor::
customcolor_by_normal( base::Color4 const &c )
{
  color1_w()->set_blocked(c.data());
  customcolor_select(1);
}

void
CustomColor::
customcolor_by_gaussian_curvature(
  base::Color4 const &c, float scale )
{
  color2_w()->set_blocked(c.data());
  scale2_w()->set_blocked(scale);
  customcolor_select(2);
}

void
CustomColor::
customcolor_by_mean_curvature(
  base::Color4 const &c, float scale )
{
  color2_w()->set_blocked(c.data());
  scale2_w()->set_blocked(scale);
  customcolor_select(3);
}

void
CustomColor::
customcolor_by_area(
  base::Color4 const &c, float scale )
{
  color2_w()->set_blocked(c.data());
  scale2_w()->set_blocked(scale);
  customcolor_select(4);
}

void
CustomColor::
customcolor_by_direction(
  base::Color4 const &c )
{
  color2_w()->set_blocked(c.data());
  customcolor_select(5);
}

void
CustomColor::
customcolor_by_distance(
  base::Color4 const &c, float scale )
{
  color2_w()->set_blocked(c.data());
  scale2_w()->set_blocked(scale);
  customcolor_select(6);
}

void
CustomColor::
customcolor_randomly( base::Color4 const &c )
{
  color2_w()->set_blocked(c.data());
  customcolor_select(7);
}

void
CustomColor::
customcolor_checked(
  base::Color4 const &c1, base::Color4 const &c2 )
{
  color8a_w()->set_blocked(c1.data());
  color8b_w()->set_blocked(c2.data());
  customcolor_select(8);
}

void
CustomColor::
customcolor_fade( base::ArrayX<float,2U> const &a )
{
  color9_w()->set_blocked(a.data());
  customcolor_select(9);
}

bool
CustomColor::
command(
  base::String const &command,
  base::String const &argument,
  base::String &response )
{
  bool r = false;

  if ( command == "customcolorReset" )
  {
    customcolor_reset();
    r = true;
  }
  else if ( command == "customcolorSelect" )
  {
    customcolor_select( read_uint(argument) );
    r = true;
  }
  else if ( command == "customcolorOriginal" )
  {
    base::Color4 c;
    read_color(c, argument);
    customcolor_original(c);
    r = true;
  }
  else if ( command == "customcolorByNormal" )
  {
    base::Color4 c;
    read_color(c, argument);
    customcolor_by_normal(c);
    r = true;
  }
  else if ( command == "customcolorByGaussianCurvature" )
  {
    base::vector<float> v;
    read_list(v, 5, argument);
    base::Color4 c(&v[0]);
    customcolor_by_gaussian_curvature(c, v[4]);
    r = true;
  }
  else if ( command == "customcolorByMeanCurvature" )
  {
    base::vector<float> v;
    read_list(v, 5, argument);
    base::Color4 c(&v[0]);
    customcolor_by_mean_curvature(c, v[4]);
    r = true;
  }
  else if ( command == "customcolorByArea" )
  {
    base::vector<float> v;
    read_list(v, 5, argument);
    base::Color4 c(&v[0]);
    customcolor_by_area(c, v[4]);
    r = true;
  }
  else if ( command == "customcolorByDirection" )
  {
    base::Color4 c;
    read_color(c, argument);
    customcolor_by_direction(c);
    r = true;
  }
  else if ( command == "customcolorByDistance" )
  {
    base::vector<float> v;
    read_list(v, 5, argument);
    base::Color4 c(&v[0]);
    customcolor_by_distance( c, v[4] );
    r = true;
  }
  else if ( command == "customcolorRandomly" )
  {
    base::Color4 c;
    read_color(c, argument);
    customcolor_randomly(c);
    r = true;
  }
  else if ( command == "customcolorChecked" )
  {
    base::vector<float> v;
    read_list(v, 5, argument);
    base::Color4 c1(&v[0]);
    base::Color4 c2(&v[4]);
    customcolor_checked(c1, c2);
    r = true;
  }
  else if ( command == "customcolorFade" )
  {
    base::vector<float> x;
    read_list(x, 2, argument);
    base::ArrayX<float,2U> y(&x[0]);
    customcolor_fade(y);
    r = true;
  }
  else if ( command == "customcolorPrev" )
  {
    customcolor_prev();
    r = true;
  }
  else if ( command == "customcolorNext" )
  {
    customcolor_next();
    r = true;
  }

  return r;
}

} // namespace ui
} // namespace geomui
