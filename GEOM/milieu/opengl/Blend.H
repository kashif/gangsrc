/* GANG Software
 * GEOM/milieu/opengl/Blend.H
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

#ifndef milieu_opengl_Blend_INCLUDED
#define milieu_opengl_Blend_INCLUDED

#include "milieu/kernel/Blend.H"

namespace milieu {
namespace opengl {

class Blend
  :
    virtual public ::milieu::kernel::Blend
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

  // access functions
  virtual bool const &antialias_point() const
    { return ::milieu::kernel::Blend::antialias_point(); }
  virtual bool const &antialias_line() const
    { return ::milieu::kernel::Blend::antialias_line(); }
  virtual bool const &blend_enable() const
    { return ::milieu::kernel::Blend::blend_enable(); }
  virtual uint const &blend_src_function() const
    { return ::milieu::kernel::Blend::blend_src_function(); }
  virtual uint const &blend_dest_function() const
    { return ::milieu::kernel::Blend::blend_dest_function(); }
  virtual bool const &fog_enable() const
    { return ::milieu::kernel::Blend::fog_enable(); }
  virtual uint const &fog_mode() const
    { return ::milieu::kernel::Blend::fog_mode(); }
  virtual base::ArrayX<float,3U> const &fog_parameter() const
    { return ::milieu::kernel::Blend::fog_parameter(); }
  virtual base::Color3 const &fog_color() const
    { return ::milieu::kernel::Blend::fog_color(); }
  virtual bool const &depth_enable() const
    { return ::milieu::kernel::Blend::depth_enable(); }
  virtual uint const &depth_function() const
    { return ::milieu::kernel::Blend::depth_function(); }
  virtual bool const &depth_mask() const
    { return ::milieu::kernel::Blend::depth_mask(); }
#if 0
  virtual bool const &hint_point_smooth() const
    { return ::milieu::kernel::Blend::hint_point_smooth(); }
  virtual bool const &hint_line_smooth() const
    { return ::milieu::kernel::Blend::hint_line_smooth(); }
  virtual bool const &hint_polygon_smooth() const
    { return ::milieu::kernel::Blend::hint_polygon_smooth(); }
  virtual bool const &hint_fog() const
    { return ::milieu::kernel::Blend::hint_fog(); }
  virtual bool const &hint_perspective_correction() const
    { return ::milieu::kernel::Blend::hint_perspective_correction(); }
#endif

  virtual void antialias_point( bool );
  virtual void antialias_line( bool );
  virtual void blend_enable( bool );
  virtual void blend_src_function( uint );
  virtual void blend_dest_function( uint );
  virtual void fog_enable( bool );
  virtual void fog_mode( uint a );
  virtual void fog_parameter( base::ArrayX<float,3U> const &a );
  virtual void fog_color( base::Color3 const &a );
  virtual void depth_enable( bool );
  virtual void depth_function( uint );
  virtual void depth_mask( bool );
#if 0
  virtual void hint_point_smooth( uint );
  virtual void hint_line_smooth( uint );
  virtual void hint_polygon_smooth( uint );
  virtual void hint_fog( uint );
  virtual void hint_perspective_correction( uint );
#endif
protected:

  void draw() const;
  virtual void refresh() = 0;

private:
  void fog();
};

} // namespace opengl
} // namespace milieu

#endif // milieu_opengl_Blend_INCLUDED
