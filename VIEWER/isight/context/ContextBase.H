/* GANG Software
 * VIEWER/isight/context/ContextBase.H
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

#ifndef isight_context_ContextBase_INCLUDED
#define isight_context_ContextBase_INCLUDED

#include "io/Ostream.H"
#include "widget/ui/GLWindow.H"
#include "motion/Common.H"
#include "milieu/opengl/Milieu.H"
#include "geom/interface/SurfaceGL.H"

namespace isight {
namespace context {

class ContextBase
  :
    public widget::ui::GLWindow
{

public:
  virtual ~ContextBase() {}

  virtual milieu::opengl::Milieu *milieu() = 0;
  virtual milieu::opengl::Milieu const *milieu() const = 0;

  virtual void insert_geomobject( geom::SurfaceGL const * ) = 0;
  virtual void delete_geomobject( uint ) = 0;
  virtual void delete_all_geomobjects() = 0;

  virtual void write_image( base::String const &filename ) const = 0;
  virtual void write_postscript(
    io::Ostream &o, bool EPS ) const = 0;
  virtual void background_image( base::String const &filename ) = 0;
  virtual void background_clear_image() = 0;

  // geomobject
  virtual bool geomobject_showing( uint id ) const = 0;
  virtual void geomobject_showing( uint id, bool state ) = 0;
  virtual bool geomobject_moving( uint id ) const = 0;
  virtual void geomobject_moving( bool state ) = 0;
  virtual void geomobject_moving( uint id, bool state ) = 0;
#if 0
  virtual bool geomobject_attached( uint id ) const = 0;
  virtual void geomobject_attached( uint id, bool state ) = 0;
#endif
  virtual void geomobject_position(
    uint id, motion::Transform const &t ) = 0;
  virtual motion::Transform const &geomobject_position( uint id ) const = 0;
  virtual void geomobject_reset_position() = 0;
  virtual void geomobject_reset_position( uint id ) = 0;

  // geometry
  virtual void geometry( motion::GeometryMode mode,
                         motion::GeometryGroup group,
                         uint dim ) = 0;
  virtual motion::GeometryMode geometry_mode() const = 0;
  virtual motion::GeometryGroup geometry_group() const = 0;
  virtual uint geometry_dim() const = 0;
  virtual motion::MouseMode mouse_mode() const = 0;
  virtual void mouse_mode( motion::MouseMode ) = 0;
  virtual bool standard_geometry() const = 0;

  // mouse
  virtual bool inertia_enable() const = 0;
  virtual void inertia_enable( bool a ) = 0;
  virtual bool inertia_decay() const = 0;
  virtual float inertia_decay_rate() const = 0;
  virtual void inertia_decay( bool a ) = 0;
  virtual void inertia_decay_rate( float a ) = 0;
  virtual float speed() const = 0;
  virtual float acceleration() const = 0;
  virtual int view_mode() const = 0;
  virtual void speed( float, float ) = 0;
  virtual void view_mode( int model ) = 0;

  // windowsize
  virtual void save_window_size_and_position() = 0;
  virtual void restore_window_size_and_position() = 0;

  // style
  virtual void enable_draw(bool state) = 0;
  virtual void refresh() = 0;

  virtual bool axes() const = 0;
  virtual void axes(bool) = 0;
  virtual bool sphere() const = 0;
  virtual void sphere(bool) = 0;
  virtual bool stars() const = 0;
  virtual void stars(bool) = 0;

  virtual void stop_motion() = 0;

  virtual void mouse_rotation() = 0;
  virtual void mouse_translation() = 0;
  virtual void mouse_inversion() = 0;
  virtual void mouse_scale() = 0;


  virtual geom::Box const &box() const = 0;

  virtual void set_center(
    math::Vector3<double> const &center,
    math::Vector3<double> const &position ) = 0;

  virtual void fade() = 0;
  virtual void fade_enable(bool state) = 0;

  virtual void milieu_moving_notify( bool state ) = 0;
};

} // namespace context
} // namespace isight

#endif // isight_context_ContextBase_INCLUDED
