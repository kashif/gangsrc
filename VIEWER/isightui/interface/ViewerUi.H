/* GANG Software
 * VIEWER/isightui/interface/ViewerUi.H
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

#ifndef isightui_ViewerUi_INCLUDED
#define isightui_ViewerUi_INCLUDED

#include "base/ArrayX.H"
#include "base/String.H"
#include "math/Matrix.H"
#include "widget/ui/KeyBase.H"
#include "geom/interface/Surface.H"
#include "geom/interface/SurfaceGL.H"
#include "motion/Common.H"

namespace geomui { class GeomUi; }
namespace milieu { class MilieuUi; }
namespace isight { namespace kernel { class ViewerBase; } }

namespace isightui {

class GeomUi;
class MilieuUi;

class ViewerUi
{

public:
//  typedef double Real;
//  typedef math::Matrix<Real> Transform;

  virtual void _hide_all() = 0;
  virtual void _enable_tooltips(bool state) = 0;

  virtual bool _command( base::String const &command,
                        base::String const &argment,
                        base::String &response ) = 0;

  // read from a stream
  virtual void read(
    io::Istream &stream,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT )
    throw (io::ReadException) = 0;

  // read a file
  virtual void read(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED )
    throw (io::ReadException) = 0;

  // read a list of files
  virtual void read(
    base::vector<base::String> const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED )
    throw (io::ReadException) = 0;

  // write to a stream
  virtual void write(
    io::Ostream &stream,
    geom::FileMode filemode = geom::FILEMODE_DEFAULT) const
    throw (io::WriteException) = 0;

  // write a file
  virtual void write(
    base::String const &filename,
    geom::FileMode filemode = geom::FILEMODE_UNSPECIFIED) const
    throw (io::WriteException) = 0;

  // insert a surface
  virtual void insert_geomobject( geom::Surface const & ) = 0;

  // insert a surface
  virtual void insert_geomobject( geom::SurfaceGL const & ) = 0;

  // set a background image from an image file
  virtual void background_image( base::String const &filename ) = 0;

  // set mouse so that all geomobjects are moved by mouse
  virtual void move_all_geomobjects(bool state) = 0;

  // show/hide the geometry dialog box
  virtual void geometry_toggle_raise_show() = 0;
  // show/hide the mouse dialog box
  virtual void mouse_toggle_raise_show() = 0;
  // show/hide the read-file dialog box
  virtual void read_toggle_raise_show() = 0;
  // show/hide the object-selection dialog box
  virtual void geomobject_toggle_raise_show() = 0;
  // show/hide the window-selection dialog box
  virtual void window_toggle_raise_show() = 0;
  // show/hide the style dialog box
  virtual void style_toggle_raise_show() = 0;
  // show/hide the windowsize dialog box
  virtual void windowsize_toggle_raise_show() = 0;
  // show/hide the write-file dialog box
  virtual void write_toggle_raise_show() = 0;
  // show/hide the write-configuration dialog box
  virtual void writeconfig_toggle_raise_show() = 0;

  // windowsize
  virtual void windowsize_reset() = 0;
  virtual void windowsize_set( base::ArrayX<uint,2U> const &x ) = 0;
  virtual void windowsize_fullscreen( bool state ) = 0;
  virtual void windowsize_toggle_fullscreen() = 0;
  virtual void windowsize_synchronize_notify() = 0;

  // style
  virtual void style( uint n ) = 0;
  virtual void axes(bool a) = 0;
  virtual void toggle_axes() = 0;
  virtual void sphere(bool a) = 0;
  virtual void toggle_sphere() = 0;
  virtual void stars(bool a) = 0;
  virtual void toggle_stars() = 0;
  virtual void style_prev() = 0;
  virtual void style_next() = 0;


  virtual void geomobject_position(
    uint n, motion::Transform const &position ) = 0;

  // geometry
  virtual void set_geometry( motion::GeometryMode mode,
                             motion::GeometryGroup group,
                             uint dim ) = 0;
  virtual void get_geometry( motion::GeometryMode &mode,
                             motion::GeometryGroup &group,
                             uint &dim ) const = 0;
  virtual void reset_geometry() = 0;
  virtual void geometry_mousemode( motion::MouseMode ) = 0;

  // mouse
  virtual void mouse_reset() = 0;
  virtual void mouse_inertia_enable( bool x ) = 0;
  virtual void mouse_inertia_decay_enable( bool x ) = 0;
  virtual void mouse_inertia_decay_rate( float x ) = 0;
  virtual void mouse_speed( base::ArrayX<float,2U> const &x ) = 0;
  virtual void mouse_viewmode( uint x ) = 0;
  virtual void mouse_rotation() = 0;
  virtual void mouse_translation() = 0;
  virtual void mouse_inversion() = 0;
  virtual void mouse_scale() = 0;

  // geomobject select operations
  virtual void select_geomobject( uint n ) = 0;
  virtual void show_geomobject( uint n, bool state ) = 0;
  virtual void move_geomobject( uint n, bool state ) = 0;
  virtual void delete_geomobject( uint n ) = 0;
  virtual void delete_all_geomobjects() = 0;
  virtual bool replace_geomobject() const = 0;
  virtual void replace_geomobject(bool) = 0;
  virtual uint selected_geomobject() const = 0;
  virtual void geomobject_inherit_materials(bool) = 0;
  virtual bool geomobject_inherit_materials() const = 0;

  // position_by_box:
  // 0 = never, 1 = first surface, 2 = always
  virtual uint position_by_box() const = 0;
  virtual void position_by_box(uint) = 0;
  virtual void insert_geomobject_notify( base::String const &name ) = 0;
  virtual void delete_geomobject_notify( uint n ) = 0;

  // window select operations
  virtual void new_window() = 0;
  virtual void select_window( uint n ) = 0;
  virtual void show_window( uint n, bool state ) = 0;
  virtual void delete_window( uint n ) = 0;
  virtual uint selected_window() const = 0;
  virtual void reset_position() = 0;
  virtual void stop_motion() = 0;

  // write config
  virtual bool image_size_use_window() const = 0;
  virtual void image_size_use_window( bool state ) = 0;
  virtual void get_image_size( uint &width, uint &height ) const = 0;
  virtual void set_image_size( uint width, uint height ) = 0;
  virtual float image_compression() const = 0;
  virtual void image_compression( float a ) = 0;
  virtual uint write_normals() const = 0;
  virtual void write_normals( uint state ) = 0;
  virtual uint write_colors() const = 0;
  virtual void write_colors( uint state ) = 0;
  virtual bool transparent() const = 0;

  // synchronize the widgets with the current Surface
  virtual void synchronize() = 0;

protected:

  virtual ::geomui::GeomUi *geom_ui() = 0;
  virtual ::geomui::GeomUi const *geom_ui() const = 0;
  virtual ::milieu::MilieuUi *milieu_ui() = 0;
  virtual ::milieu::MilieuUi const *milieu_ui() const = 0;
  virtual isight::kernel::ViewerBase *viewer() = 0;
  virtual isight::kernel::ViewerBase const *viewer() const = 0;
  virtual geom::Surface const *surface() const = 0;
  virtual geom::Surface *surface() = 0;

};

} // namespace isightui

#endif // isightui_ViewerUi_INCLUDED
