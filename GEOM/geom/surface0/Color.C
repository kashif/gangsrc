/* GANG Software
 * GEOM/geom/surface0/Color.C
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

#include <algorithm>
#include "base/Stl.H"
#include "base/ColorBase.H"
#include "Color.H"

namespace geom {
namespace surface0 {

Color::
Color()
    :
    Geometry(),
    _colormode(),
    _has_original_color(false),
    _fixed_color0(),
    _fixed_color1(),
    _fixed_color(_fixed_color0),
    _face_color0(),
    _face_color1(),
    _face_color(&_face_color0),
    _vertex_color0(),
    _vertex_color1(),
    _vertex_color(&_vertex_color0)
{
}

Color::
Color( Color const &a )
    :
    Geometry(a),
    _colormode(a._colormode),
    _has_original_color( a._has_original_color ),
    _fixed_color0( a._fixed_color0 ),
    _fixed_color1( a._fixed_color1 ),
    _fixed_color( a._fixed_color ),
    _face_color0( a._face_color0 ),
    _face_color1( a._face_color1 ),
    _face_color( a._face_color ),
    _vertex_color0( a._vertex_color0 ),
    _vertex_color1( a._vertex_color1 ),
    _vertex_color( a._vertex_color )
{
}

Color::
~Color()
{
}

Color &
Color::
operator=( Color const &a )
{
  if ( this == &a ) { return *this; }
  Geometry::operator=(a);

  _colormode = a._colormode;
  _has_original_color = a._has_original_color;
  _fixed_color0 = a._fixed_color0;
  _fixed_color1 = a._fixed_color1;
  _fixed_color = a._fixed_color;
  _face_color0 = a._face_color0;
  _face_color1 = a._face_color1;
  _face_color = a._face_color;
  _vertex_color0 = a._vertex_color0;
  _vertex_color1 = a._vertex_color1;
  _vertex_color = a._vertex_color;

  return *this;
}

void
Color::
clear_color()
{
  _fixed_color0.clear();
  _fixed_color1.clear();
  _fixed_color = _fixed_color0;
  _face_color0.clear();
  _face_color1.clear();
  _face_color = &_face_color0;
  _vertex_color0.clear();
  _vertex_color1.clear();
  _vertex_color = &_vertex_color0;
  _colormode = ColorMode();
}

void
Color::
reset_color()
{
  _fixed_color1.clear();
  _fixed_color = _fixed_color0;
  _face_color1.clear();
  _face_color = &_face_color0;
  _vertex_color1.clear();
  _vertex_color = &_vertex_color0;
  _colormode = ColorMode();
}

void
Color::
set_fixed_color( base::Color4 const &c )
{
  clear_color();
  _fixed_color0 = c;
  _has_original_color = true;
}

void
Color::
import_face_color(
  base::vector<base::Color4> const &face_color )
{
  // import INDEXED face color
  DIE_IF( type() != INDEXED );
  DIE_IF( face_color.size() != face_count() );

  clear_color();
  _face_color0 = face_color;
  _compute_vertex_color();
  _has_original_color = true;
}

void
Color::
import_vertex_color(
  base::vector<base::vector<base::Color4> > const &vertex_color )
{
  // import GRID vertex color
  DIE_IF( type() != GRID );
  DIE_IF( vertex_color.size() != i_count() );
  DIE_IF( vertex_color[0].size() != j_count() );

  clear_color();

  base::vector<base::vector<base::Color4> >::const_iterator i;
  for ( i = vertex_color.begin(); i != vertex_color.end(); i++ )
  {
    _vertex_color0.insert(
      _vertex_color0.end(), (*i).begin(), (*i).end() );
  }

  _compute_face_color();
  _has_original_color = true;
}

void
Color::
import_face_color(
  base::vector<base::vector<base::Color4> > const &face_color )
{
  // import GRID face color
  DIE_IF( type() != GRID );
  DIE_IF( face_color.size() != vertex_count() );

  clear_color();

  // insert face_normal into _face_normal
  base::vector<base::vector<base::Color4> >::const_iterator i;
  for ( i = face_color.begin(); i != face_color.end(); i++ )
  {
    _face_color0.insert(
      _face_color0.end(), (*i).begin(), (*i).end() );
  }

  _compute_vertex_color();
  _has_original_color = true;
}

void
Color::
import_vertex_color(
  base::vector<base::Color4> const &vertex_color )
{
  // import INDEXED vertex color
  DIE_IF( type() != INDEXED );
  DIE_IF( vertex_color.size() != vertex_count() );

  clear_color();

  _vertex_color0 = vertex_color;
  _compute_face_color();
  _has_original_color = true;
}

void
Color::
_compute_color( base::Color4 const &p, ColorFunction0 f )
{
  reset_color();

  _face_color1.reserve(face_count());
  base::Color4 c;

  uint i;
  for ( i = 0; i != face_count(); i++ )
  {
    float hue = (this->*f)( i );
    _adjust_color( c, hue, p );
    _face_color1.push_back(c);
  }

  _face_color = &_face_color1;
  _vertex_color = &_vertex_color1;

  _compute_vertex_color();
  changed(true);
}

void
Color::
_compute_color( base::Color4 const &p, float scale, ColorFunction1 f )
{
  reset_color();

  _face_color1.reserve(face_count());
  base::Color4 c;

  uint i;
  for ( i = 0; i != face_count(); i++ )
  {
    float hue = (this->*f)( i, scale );
    _adjust_color( c, hue, p );
    _face_color1.push_back(c);
  }

  _face_color = &_face_color1;
  _vertex_color = &_vertex_color1;

  _compute_vertex_color();

  changed(true);
}

void
Color::
color_original( base::Color4 const &p )
{
  _colormode.mode = 0;
  _colormode.color0 = p;
  _colormode.color1.clear();
  _colormode.scale = 0.0f;

  if ( !_face_color0.empty() )
  {
    reset_color();

    _face_color1.reserve( face_count() );
    base::Color4 c;
    uint i;
    for ( i = 0; i < face_count(); i++ )
    {
      _adjust_color( c, _face_color0[i], p );
      _face_color1.push_back(c);
    }
    _face_color = &_face_color1;
    _vertex_color = &_vertex_color1;

    _compute_vertex_color();
  }
  else
  {
    reset_color();
    _fixed_color = _fixed_color1;
    _adjust_color( _fixed_color1, _fixed_color0, p );
  }
  changed(true);
}


void
Color::
color_by_normal( base::Color4 const &p )
{
  _colormode.mode = 1;
  _colormode.color0 = p;
  _colormode.color1.clear();
  _colormode.scale = 0.0f;

  compute_normal();
  _compute_color( p, &::geom::surface0::Color::_color_by_normal_fn );
}

void
Color::
color_by_gaussian_curvature(
  base::Color4 const &p,
  float scale )
{
  _colormode.mode = 2;
  _colormode.color0 = p;
  _colormode.color1.clear();
  _colormode.scale = scale;

  compute_gaussian_curvature();
  _compute_color( p, scale,
                  &::geom::surface0::Color::_color_by_gaussian_curvature_fn );
}

void
Color::
color_by_mean_curvature(
  base::Color4 const &p,
  float scale )
{
  _colormode.mode = 3;
  _colormode.color0 = p;
  _colormode.color1.clear();
  _colormode.scale = scale;

  compute_mean_curvature();
  _compute_color( p, scale,
                  &::geom::surface0::Color::_color_by_mean_curvature_fn );
}
void
Color::
color_by_area( base::Color4 const &p, float scale )
{
  _colormode.mode = 4;
  _colormode.color0 = p;
  _colormode.color1.clear();
  _colormode.scale = scale;

  compute_face_area();
  _compute_color(p, scale, &::geom::surface0::Color::_color_by_area_fn);
}

void
Color::
color_by_direction( base::Color4 const &p )
{
  _colormode.mode = 5;
  _colormode.color0 = p;
  _colormode.color1.clear();
  _colormode.scale = 0.0f;

  compute_face_center();
  _compute_color( p, &::geom::surface0::Color::_color_by_direction_fn );
}

void
Color::
color_by_distance( base::Color4 const &p, float scale )
{
  _colormode.mode = 6;
  _colormode.color0 = p;
  _colormode.color1.clear();
  _colormode.scale = scale;

  compute_face_center();
  _compute_color( p, scale, &::geom::surface0::Color::_color_by_distance_fn );
}

void
Color::
color_randomly(
  base::Color4 const &p )
{
  _colormode.mode = 7;
  _colormode.color0 = p;
  _colormode.color1.clear();
  _colormode.scale = 0.0f;

  math::random_seed(0xabcd1234);
  _compute_color( p, &::geom::surface0::Color::_color_randomly_fn );
}

void
Color::
color_checked(
  base::Color4 const &c0,
  base::Color4 const &c1 )
{
  _colormode.mode = 8;
  _colormode.color0 = c0;
  _colormode.color1 = c1;
  _colormode.scale = 0.0f;

  DIE_IF( type() != GRID );

  reset_color();

  base::Color4 d0, d1;

  base::hsv2rgb( d0, c0 );
  base::hsv2rgb( d1, c1 );

  uint i;
  for ( i = 0; i < i_count()-1; i++ )
  {
    uint j;
    for ( j = 0; j < j_count()-1; j++ )
    {
      _face_color1.push_back( (i+j) % 2 == 0 ? d0 : d1 );
    }
  }

  _face_color = &_face_color1;
  _vertex_color = &_vertex_color1;

  _compute_vertex_color();

  changed(true);
}

void
Color::
alpha_fade(
  float x0,
  float x1 )
{
  if ( _face_color1.empty() )
  {
    if ( _face_color0.empty() )
    {
      _face_color1.fill( _fixed_color0, face_count() );
    }
    else
    {
      _face_color1 = _face_color0;
    }
  }

  _face_color = &_face_color1;
  _vertex_color = &_vertex_color1;

  if ( x0 < 0.0 ) { x0 = 0.0; }
  if ( x1 < 0.0 ) { x1 = 0.0; }

  uint i;
  for ( i = 0; i != face_count(); i++ )
  {
    Vertex3 const &v = face_center(i);
    _face_color1[i].alpha() = _alpha_fade( v.abs(), x0, x1 );
  }
  _compute_vertex_color();
  changed(true);
}

float
Color::
_alpha_fade( float x, float x0, float x1 )
{
  float alpha = 1.0;
  if ( x0 <= x1 )
  {
    if ( x < x0 ) { alpha = 1.0f; }
    else if ( x > x1 ) { alpha = 0.0f; }
    else
    {
      alpha = 1.0f - _interpolate1( x, x0, x1 );
    }
  }
  else
  {
    if ( x < x1 ) { alpha = 0.0f; }
    else if ( x > x0 ) { alpha = 1.0f; }
    else
    {
      alpha = _interpolate1( x, x1, x0 );
    }
  }
  return alpha;
}

float
Color::
_color_by_normal_fn(uint i )
{
  return _point_to_hue( face_normal(i) );
}

float
Color::
_color_by_direction_fn(uint i )
{
  Vertex3 a = face_center(i);
  a.normalize();
  return _point_to_hue( a );
}

float
Color::
_color_by_distance_fn( uint i, float scale )
{
  Vertex3 const &a = face_center(i);
  float d = a.abs();
  // scale [0,inf) to [0,1)
  return _implode1( 2.0f * scale * d );
}

float
Color::
_color_by_area_fn( uint i, float scale )
{
  // scale [0,inf) to [0,1)
  return _implode1( 100.0f * scale * face_area(i) );
}

float
Color::
_color_by_gaussian_curvature_fn( uint i, float scale )
{
  float K = face_gaussian_curvature(i);
  if (K < 0.0f)
  {
    K = -1.0f/3.0f * log(1.0f-K);
  }
  
  K = 1.0f/(scale+0.1f)*( K >= 0.0f ?
                          powf(K,scale) :
                          -powf(-K,scale) );
  
  // rescale (-inf, +inf) to (0,1)
  return _implode2( K );
}

float
Color::
_color_by_mean_curvature_fn( uint i, float scale )
{
  return _implode2( scale * face_mean_curvature(i) );
}

float
Color::
_color_randomly_fn( uint )
{
  return math::random();
}

void
Color::
_adjust_color(
  base::Color4 &color_out,
  float hue,
  base::Color4 const &color_spec )
{
  /*
    Computes color_out by adjusts hue according to p

    hue is input
    p is a HSV specification telling how to change hue into color_out
    color_out is the result in RGB
   */
  color_out = color_spec;
  color_out.hue() += hue;
  base::hsv2rgb( color_out );
}


void
Color::
_adjust_color(
  base::Color4 &color_out,
  base::Color4 const &color_in,
  base::Color4 const &color_spec )
{
  /*
    Adjusts color_in by color_spec, putting the result into color_out

    color_in is RGB
    color_spec is a HSV specification
    color_out is RGB
  */

  // get the RGB color at the i'th vertex
  base::Color4 c = color_in;

  // convert color to HSV for processing
  base::rgb2hsv(c);

  // interpolate
  color_out = c;
  color_out.hue() += color_spec.hue();
  color_out.sat() = _interpolate0( color_spec.sat(), 0.5f, c.sat() );
  color_out.val() = _interpolate0( color_spec.val(), 0.5f, c.val() );
  color_out.alpha() = _interpolate0( color_spec.alpha(), 0.5f, c.alpha() );

  // convert colorback to RGB
  base::hsv2rgb(color_out);
}

float
Color::
_implode1( float x )
{
  // maps (0, inf) to (0,1)
  float y = (2.0f/math::pi) * atan( x );
  y = std::max( 0.0f, y );
  y = std::min( 1.0f, y );
  return y;
}


float
Color::
_implode2( float x )
{
  // maps (-inf, inf) to (0,1)
  float y =  (1.0f/math::pi) * atan( x ) + 0.5;
  y = std::max( 0.0f, y );
  y = std::min( 1.0f, y );
  return y;
}

float
Color::
_interpolate0( float x, float x0, float y0 )
{
  // piecewise linear function [0, 1]->R whose graph is two line segments
  // through the points (0,0), (x0,y0), (1,1)

  return
    x <= x0
    ?
    (y0/x0)*x
    :
    (y0-1.0f)/(x0-1.0f)*(x-1.0f)+1.0f;
}

float
Color::
_interpolate1( float x, float x0, float x1 )
{
  // the function f=interpolate is defined by the following properties:
  //  f(x0) = 0,  f(x1) = 1,
  //  f'(x0) = 0, f'(x1) = 0

  if ( math::effectively_zero(x1-x0) ) { return 0.0f; }
  float y = (x - x0)/(x1 - x0);
  return y * y * ( 3.0f - 2.0f * y );
}

float
Color::
_point_to_hue( Vertex3 const &a )
{
  // converts a point in R^3 to a hue

  Vertex3 v = a;
  v.normalize();
  Real w = math::abs(v.x, v.y);
  Real t = math::arctan( w, v.z );
  if (math::isnan(t)) { t = 0.0f; }

  return math::frac( t / (2.0f*math::pi) );
}

void
Color::
_compute_vertex_color()
{
  // computes _vertex_color from _face_color

  base::Color4 c; 
  _vertex_color->fill( c, vertex_count() );
  base::vector<uint> count;
  count.fill( 0U, vertex_count() );

  uint i;
  for ( i = 0; i < face_count(); i++ )
  {
    uint j;
    for (j = 0; j < face_count(i); j++ )
    {
      uint k = face_vertex(i, j);
      count[k]++;
      uint q;
      for (q = 0; q < 4; q++)
      {
        (*_vertex_color)[k][q] += (*_face_color)[i][q];
      }
    }
  }

  for ( i = 0; i < vertex_count(); i++ )
  {
    if ( count[i] != 0)
    {
      uint q;
      for (q = 0; q < 4; q++)
      {
        (*_vertex_color)[i][q] /= count[i];
      }
    }
    else
    {
#if 0
      WARN( "vertex %d has no faces", i );
#endif
    }
  }
}

void
Color::
_compute_face_color()
{
  // computes _face_color from _vertex_color
  // the color of a face is the average of the colors of the vertices

  uint i;
  for ( i = 0; i < face_count(); i++ )
  {
    base::Color4 d;
    d.set(0.0f);
    uint j;
    for ( j = 0; j < face_count(i); j++ )
    {
      uint k = face_vertex(i, j);
      base::Color4 const &c = (*_vertex_color)[k];
      d[0] += c[0];
      d[1] += c[1];
      d[2] += c[2];
      d[3] += c[3];
    }
    if ( face_count(i) != 0 )
    {
      d[0] /= face_count(i);
      d[1] /= face_count(i);
      d[2] /= face_count(i);
      d[3] /= face_count(i);
    }
    (*_face_color).push_back(d);
  }
}

void
Color::
dump( io::Ostream &o ) const
{
  char const *tab = "\t\t\t";
  o << tab << "<custom_color>\n";
  o << tab << "\t<mode>" << _colormode.mode << "</mode>\n";
  o << tab << "\t<color0>"
    << _colormode.color0[0] << " " << _colormode.color0[1] << " "
    << _colormode.color0[2] << " " << _colormode.color0[3] << "</color0>\n";
  o << tab << "\t<color1>"
    << _colormode.color1[0] << " " << _colormode.color1[1] << " "
    << _colormode.color1[2] << " " << _colormode.color1[3] << "</color1>\n";
  o << tab << "\t<scale>" << _colormode.scale << "</scale>\n";
  o << tab << "</custom_color>\n";
}

} // namespace surface0
} // namespace geom
