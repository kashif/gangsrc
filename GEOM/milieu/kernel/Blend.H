/* GANG Software
 * GEOM/milieu/kernel/Blend.H
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

#ifndef milieu_kernel_Blend_INCLUDED
#define milieu_kernel_Blend_INCLUDED

#include "io/Ostream.H"
#include "base/ArrayX.H"
#include "base/Color3.H"

namespace milieu {
namespace kernel {

class Blend
{

public:
  // constructor
  Blend();

  // copy constructor
  Blend( Blend const & );

  // destructor
  virtual ~Blend();

  // assignment operator
  Blend &operator=( Blend const & );

  void clear();

  // ACCESS FUNCTIONS
  virtual bool const &antialias_point() const
    { return _antialias_point; }
  virtual bool const &antialias_line() const
    { return _antialias_line; }
  virtual bool const &blend_enable() const
    { return _blend_enable; }
  virtual uint const &blend_src_function() const
    { return _blend_src_function; }
  virtual uint const &blend_dest_function() const
    { return _blend_dest_function; }
  virtual bool const &fog_enable() const
    { return _fog_enable; }
  virtual uint const &fog_mode() const
    { return _fog_mode; }
  virtual base::ArrayX<float,3U> const &fog_parameter() const
    { return _fog_parameter; }
  virtual base::Color3 const &fog_color() const
    { return _fog_color; }
  virtual bool const &depth_enable() const
    { return _depth_enable; }
  virtual uint const &depth_function() const
    { return _depth_function; }
  virtual bool const &depth_mask() const
    { return _depth_mask; }
#if 0
  virtual bool const &hint_point_smooth() const
    { return _hint_point_smooth; }
  virtual bool const &hint_line_smooth() const
    { return _hint_line_smooth; }
  virtual bool const &hint_polygon_smooth() const
    { return _hint_polygon_smooth; }
  virtual bool const &hint_fog() const
    { return _hint_fog; }
  virtual bool const &hint_perspective_correction() const
    { return _hint_perspective_correction; }
#endif

  virtual void antialias_point(bool a)
    { _antialias_point = a; }
  virtual void antialias_line(bool a)
    { _antialias_line = a; }
  virtual void blend_enable( bool a)
    { _blend_enable = a; }
  virtual void blend_src_function( uint a )
    { _blend_src_function = a; }
  virtual void blend_dest_function( uint a )
    { _blend_dest_function = a; }
  virtual void fog_enable( bool a)
    { _fog_enable = a; }
  virtual void fog_mode( uint a )
    { _fog_mode = a; }
  virtual void fog_parameter( base::ArrayX<float,3U> const &a )
    { _fog_parameter = a; }
  virtual void fog_color( base::Color3 const &a )
    { _fog_color = a; }
  virtual void depth_enable( bool a)
    { _depth_enable = a; }
  virtual void depth_function( uint a)
    { _depth_function = a; }
  virtual void depth_mask( bool a)
    { _depth_mask = a; }
#if 0
  virtual void hint_point_smooth( uint a)
    { _hint_point_smooth = a; }
  virtual void hint_line_smooth( uint a)
    { _hint_line_smooth = a; }
  virtual void hint_polygon_smooth( uint a)
    { _hint_polygon_smooth = a; }
  virtual void hint_fog( uint a)
    { _hint_fog = a; }
  virtual void hint_perspective_correction( uint a)
    { _hint_perspective_correction = a; }
#endif

  void dump( io::Ostream & ) const;

protected:

private:

  void copy( Blend const & );

  bool _blend_enable;
  uint _blend_src_function;
  uint _blend_dest_function;
  bool _antialias_point;
  bool _antialias_line;

  bool _depth_enable;
  uint _depth_function;
  bool _depth_mask;

  bool _fog_enable;
  uint _fog_mode;
  base::ArrayX<float,3U> _fog_parameter;
  base::Color3 _fog_color;

  bool _hint_point_smooth;
  bool _hint_line_smooth;
  bool _hint_polygon_smooth;
  bool _hint_fog;
  bool _hint_perspective_correction;

};

} // namespace kernel
} // namespace milieu

#endif // milieu_kernel_Blend_INCLUDED
