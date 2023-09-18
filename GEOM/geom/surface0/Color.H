/* GANG Software
 * GEOM/geom/surface0/Color.H
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

#ifndef geom_surface0_Color_INCLUDED
#define geom_surface0_Color_INCLUDED

#include "io/Ostream.H"
#include "base/ColorBase.H"
#include "base/Color3.H"
#include "base/Color4.H"
#include "Common.H"
#include "Geometry.H"

namespace geom {

namespace surface0 {

class Color
  :
    public Geometry
{

public:

  // constructor
  Color();

  // copy constructor
  Color( Color const & );

  // destructor
  virtual ~Color();

  // assignment operator
  Color &operator=( Color const & );

//  virtual void color_fixed( base::Color4 const &p );

  /*
    Color the surface a modification of its original color.
    Arguments 1/2,1/2,1/2,1/2 restore the surface to its original color.
    Other arguments color the surface by piecewise linear interpolation
    between 0, the original value, and 1 (except hue which shifts).
  */

  virtual void color_original( base::Color4 const &p );
  /*
     Color the surface at each vertex by the normal direction of the
     surface at that vertex
  */
  virtual void color_by_normal( base::Color4 const &p );

  /*
     Color the surface at each vertex by its direction of that vertex
     from the origin
     (r,g,b) = scale * (unit direction vector)
  */
  virtual void color_by_direction( base::Color4 const &p );

  /*
     Color the surface at each vertex by its distance from the origin
     the distance, in the interval [0,inf) is rescaled
     to the interval [0,1) by an arctan function
  */
  virtual void color_by_distance( base::Color4 const &p, float scale );

  /*
     Color the surface at each vertex by the area of an adjacent face
  */
  virtual void color_by_area( base::Color4 const &p, float scale );

  /*
     Color the surface by discrete Gaussian curvature.
  */
  virtual void color_by_gaussian_curvature(
    base::Color4 const &p, float scale );

  /*
     Color the surface by discrete mean curvature.
  */
  virtual void color_by_mean_curvature(
    base::Color4 const &p, float scale );

  /*
     Color the faces of the surface with randomly chosen colors.
  */
  virtual void color_randomly( base::Color4 const &p );

  void color_checked( base::Color4 const &c0, base::Color4 const &c1 );

  /*
    sets alpha as follows:
      alpha is 1 in the interval [0,x0]
      alpha ranges from 1->0 linerarly in the interval [x0,x1]
      alpha is 1 in the interval [x1,inf]
  */
  void alpha_fade( float alpha, float scale );

  bool has_original_color() const
    { return _has_original_color; }
  bool has_array_color() const
    { return ! _face_color->empty(); }
  base::Color4 const &fixed_color() const
    { return _fixed_color; }

  base::Color4 const &vertex_color(uint i) const
    { return (*_vertex_color)[vertex_index(i)]; }
  base::Color4 const &face_color(uint i) const
    { return (*_face_color)[face_index(i)]; }

  void import_face_color(
    base::vector<base::Color4> const &color );
  void import_vertex_color(
    base::vector<base::Color4> const &color );
  void import_face_color(
    base::vector<base::vector<base::Color4> > const &color );
  void import_vertex_color(
    base::vector<base::vector<base::Color4> > const &color );
  void set_fixed_color( base::Color4 const & );

  void clear_color();
  void reset_color();

  void dump( ::io::Ostream & ) const;

  void colorData(
    uint &mode,
    base::Color4 &color0,
    base::Color4 &color1,
    float &scale )
    {
      mode = _colormode.mode;
      color0 = _colormode.color0;
      color1 = _colormode.color1;
      scale = _colormode.scale;
    }

protected:

private:
  void _compute_vertex_color();
  void _compute_face_color();

  float _color_by_normal_fn(uint i );
  float _color_by_direction_fn(uint i );
  float _color_by_distance_fn( uint i, float scale );
  float _color_by_area_fn( uint i, float scale );
  float _color_by_gaussian_curvature_fn( uint i, float scale );
  float _color_by_mean_curvature_fn( uint i, float scale );
  float _color_randomly_fn( uint );

  typedef float (Color::*ColorFunction0)(uint i);
  typedef float (Color::*ColorFunction1)(uint i, float scale);

  void _compute_color( base::Color4 const &p, ColorFunction0 f );
  void _compute_color( base::Color4 const &p, float scale, ColorFunction1 f );

  virtual base::Color4 &face_color(uint n)
    { return (*_face_color)[face_index(n)]; }
  virtual base::Color4 &vertex_color(uint n)
    { return (*_vertex_color)[vertex_index(n)]; }

  static void _adjust_color(
    base::Color4 &color_out,
    float hue,
    base::Color4 const &color_spec );
  static void _adjust_color(
    base::Color4 &color_out,
    base::Color4 const &color_in,
    base::Color4 const &color_spec );
  static float _alpha_fade( float x, float x0, float x1 );

  static float _point_to_hue( Vertex3 const & );

  static float _implode1( float );
  static float _implode2( float );

  static float _interpolate0( float x, float x0, float y0 );
  static float _interpolate1( float x, float x0, float x1 );

  struct ColorMode
  {
    /*
      0 = original
      1 = normal
      2 = gaussian curvature
      3 = mean curvature
      4 = area
      5 = direction
      6 = distance
      7 = random
      8 = checked
      (9 = fade)
    */
    uint mode;
    base::Color4 color0;
    base::Color4 color1;
    float scale;
    ColorMode() : mode(0), color0(0.0f, 0.5f, 0.5f, 0.5f),
      color1(), scale(0.0f) {}
  };
  mutable ColorMode _colormode;

  mutable bool _has_original_color;

  base::Color4 _fixed_color0;
  mutable base::Color4 _fixed_color1;
  mutable base::Color4 &_fixed_color;

  base::vector<base::Color4> _face_color0;
  mutable base::vector<base::Color4> _face_color1;
  mutable base::vector<base::Color4> *_face_color;

  base::vector<base::Color4> _vertex_color0;
  mutable base::vector<base::Color4> _vertex_color1;
  mutable base::vector<base::Color4> *_vertex_color;
};

} // namespace surface0
} // namespace geom

#endif // geom_surface0_Color_INCLUDED
